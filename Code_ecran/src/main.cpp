/*
Code pour l'arduino lorsque l'ecran est la charge

Structure:
- fonctions pour le pcb de controle
- fonctions pour le pcb de sortie

- setup
-loop
*/


#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR   0x27
#define LCD_COLS   16
#define LCD_ROWS   2
#define POT_PIN    A0
#define VREF       5.0
#define ADC_MAX    1023.0
#define PWM_PIN    8
#define LOOP_MS    200


#define MOTOR_V_SUPPLY  24.0
#define MOTOR_MIN_DUTY  10.0             // %,   minimum duty to start turning
#define MOTOR_RESPONSE_TIME 0.3         // s,   mechanical time constant

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

/// fonctions pour le pcb de controle ///

float rpm_estimate = 0.0;

float target_rpm(float duty_percent) {
  if (duty_percent < MOTOR_MIN_DUTY || duty_percent <= 0.0)
    return 0.0;

  float v_motor = duty_percent / 100.0 * MOTOR_V_SUPPLY;
  float motor_voltage_mv = v_motor * 1000.0;
  float rpm = (motor_voltage_mv + 308.63) / 11.337;
  return rpm > 0.0 ? rpm : 0.0;
}

/// fonctions pour le pcb de sortie ///





/// setup et loop ///

void setup() {
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {
  // pcb controle //
  
  int raw = analogRead(POT_PIN);
  float voltage = raw * VREF / ADC_MAX;

  // 0..1023 -> 0..255
  int duty = raw >> 2;
  float duty_percent = duty * 100.0 / 255.0;
  if (duty_percent < MOTOR_MIN_DUTY)
    duty = 0;
  analogWrite(PWM_PIN, duty);
  duty_percent = duty * 100.0 / 255.0;

  // lag the target speed
  float target = target_rpm(duty_percent);
  float dt = LOOP_MS / 1000.0;
  float alpha = (MOTOR_RESPONSE_TIME > 0.0) ? dt / (MOTOR_RESPONSE_TIME + dt) : 1.0;
  rpm_estimate += alpha * (target - rpm_estimate);

  // pcb loop //


  // lcd print //
  lcd.setCursor(0, 0);
  lcd.print(voltage, 2);
  lcd.print(" V   ");
  lcd.setCursor(10, 0);
  lcd.print((int)(duty_percent + 0.5));
  lcd.print(" %  ");
  lcd.setCursor(0, 1);
  lcd.print("RPM: ");
  int displayed_rpm = (int)(rpm_estimate + 0.5);
  if (displayed_rpm == 0)
    lcd.print("-");
  else
    lcd.print(displayed_rpm);
  lcd.print("       ");


  // debug
  Serial.print("raw=");
  Serial.print(raw);
  Serial.print("  V=");
  Serial.print(voltage, 3);
  Serial.print("  duty=");
  Serial.print(duty_percent, 1);
  Serial.print("%  rpm=");
  Serial.println(rpm_estimate, 0);

  delay(LOOP_MS);
}

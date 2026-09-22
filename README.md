# Projet de sessions S3

## Prérequis

- [Git](https://git-scm.com/downloads) installé (utilise **Git Bash**, inclus avec l'installation)
- [Altium Designer](https://www.altium.com/) installé

## Git bash

C'est un terminal avec syntaxe linux, il y a quelques différences:
- shift + c = ctrl c
- shift + insert = ctrl v


## Cloner le projet

GitHub permet de stocker des fichiers en ligne et de conserver les anciennes versions si jamais un problème survient.

Crée un dossier vide Projet_S3_2026 à l'endroit où tu veux l'avoir sur ton ordinateur.

Ouvre **Git Bash**, place-toi dans le dossier (avec cd et ls comme à l'APP2 S1), puis colle ces commandes :

```bash
git clone https://github.com/nolinFelix/Projet_S3_2026.git
```

```bash
cd Projet_S3_2026
```

Confirme que le dossier est lié avec git
```bash
git status
```

Pour voir toutes les branches disponibles (locales et distantes) :
```bash
git branch -a
```

Pour te déplacer sur une branche en particulier :
```bash
git checkout nom-branche
```

Pour créer une branche qui part d'une copie d'une branche source
```bash
git checkout -b nom-nouvelle-branche nom-branche-source
```

> **Ferme Altium Designer avant de changer de branche.** Si le projet est ouvert dans Altium pendant un `git checkout`, les fichiers changent sur le disque sans qu'Altium le sache, ce qui peut corrompre l'état du projet ou causer des conflits inattendus. Change de branche d'abord, ouvre Altium ensuite.

> **Chaque fois que tu reprends le projet avant d'ouvrir Altium** fais un `pull` pour récupérer les dernières modifications des autres avant de commencer à travailler :
```bash
git pull origin nom-de-branche 
```

Ça évite de travailler sur une vielle version et de créer des conflits inutiles plus tard.

## Le projet dans Altium

Ouvre le projet dans Altium, le dossier `.git` devrait être reconnu automatiquement. Les fichiers modifiés sont en rouge et les fichiers identique qui sont à jour avec la version en ligne sont en vert. 

## Envoyer tes modifications (push)

Une fois tes changements faits dans Altium (pas besoin de fermer altium) :

Ajoute les changements à une liste
```bash
git add -A
```
Véririfie que les fichiers que tu as modifié ont été ajouté à la liste
```bash
git status
```
Crée un commit avec les changements effectués
```bash
git commit -m "message-du-commit"
```
Pousse les modifications sur le dossier en ligne
```bash
git push origin nom-de-branche
```
Vérifie que le dossier en ligne est à jour avec le dossier local
```bash
git status
```

## Notes importantes

- Ne clone pas le projet par-dessus un dossier existant qui contient déjà des fichiers Altium — utilise toujours un dossier vide pour éviter les conflits.
- Vérifie toujours sur quelle branche tu es avant de modifier quoi que ce soit :
  ```bash
  git status
  ```
- La branche main devrait toujours être fonctionnelle, il est mieu de se créer une branche de travail et lorsque c'est fini, merge dans main.

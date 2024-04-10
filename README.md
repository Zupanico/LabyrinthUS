# LabyrinthUS

Jeu d'horreur en C++ avec la manette Arduino

## Installation

```bash
git clone https://github.com/Zupanico/LabyrinthUS.git
```

## Usage

Exemples d'utilisation.

```bash
make
./labyrinthUS.exe
```

## Contribuer

```bash
git clone https://github.com/Zupanico/LabyrinthUS.git
git checkout -b feature/<nom_de_la_feature>
```
```bash
git add .
git commit -am "<prefix>:<description>"
git push
```

## Push
Si vous avez ce message d'erreur :

```
There is no tracking information for the current branch.
Please specify which branch you want to merge with.
See git-pull(1) for details

    git pull <remote> <branch>

If you wish to set tracking information for this branch you can do so with:

    git branch --set-upstream-to=origin/<branch> mybranch
```

Utiliser cette commande git pour configurer le push automatique sur la branche distante :

```bash
git config --global --add --bool push.autoSetupRemote true
```
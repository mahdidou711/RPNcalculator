# Calculatrice RPN (Reverse Polish Notation)

## Description du projet

Ce projet met en œuvre une calculatrice capable d’évaluer des expressions mathématiques écrites en notation postfixée (aussi appelée Reverse Polish Notation). Il se compose de plusieurs modules C qui gèrent :

- La lecture et la découpe de l’expression saisie par l’utilisateur (le parseur).
- La gestion d’une pile pour les opérations intermédiaires.
- L’évaluation de l’expression RPN grâce à la pile et aux fonctions mathématiques de base.
- La gestion optionnelle d’une variable (souvent nommée x) afin de tracer ou de tabuler la fonction.

La notation postfixée présente l’avantage de ne pas nécessiter de parenthèses ni de gestion complexe de priorité. Une simple pile suffit pour évaluer l’expression dans l’ordre correct.

## Fonctionnalités principales

### Évaluation d’expressions RPN

- Opérateurs binaires : +, -, *, /, ^
- Fonctions mathématiques usuelles : sin, cos, exp, sqrt, ln, .
- Gestion de la variable x (on peut lui attribuer une valeur lors de l’exécution).

### Saisie de l’expression

- L’utilisateur saisit directement une expression en notation postfixée (ex. 3 4 + 2 *).
- Le cutteur identifie les nombres, les opérateurs, les variables, ou les fonctions.

### Affichage du résultat

- Une fois l’expression évaluée, la calculatrice affiche le résultat final.

### Option de traçage (extension)

- En parcourant différentes valeurs de x (par exemple de -10 à +10), on génère une suite de points (x, f(x)) dans un fichier texte.
- Ces points peuvent ensuite être importés dans un logiciel de dessin de courbes (Gnuplot, Python, etc.).

## Comment utiliser cette calculatrice

### Configuration dans VS Code

1. Ouvre ton dossier de projet dans VS Code (menu File > Open Folder ou Ouvrir un dossier).
2. Installe l’extension CMake Tools (et l’extension C/C++ si ce n’est pas déjà fait) :
    - Dans VS Code, onglet Extensions (Ctrl + Shift + X), cherche “CMake Tools”.
    - Installe également “C/C++” (Microsoft) si besoin pour la coloration syntaxique et l’autocomplétion.
3. Dans la barre de statut (en bas), tu verras l’icône CMake et/ou un bouton “No Kit Selected” ou “Select a Kit”.
    - Sélectionne un compilateur (par ex. GCC, Clang, ou MSVC selon ta plateforme).
    - Clique ensuite sur “CMake: Configure” pour que CMake génère les fichiers de build dans un dossier (par défaut, build/).

### Compilation via CMake Tools dans VS Code

Une fois configuré :

- Dans la barre de statut, clique sur Build (ou tape Ctrl + Shift + P puis choisis “CMake: Build”).
- VS Code va exécuter la commande `cmake --build build --config Debug` (ou un équivalent) en arrière-plan.
- Cela génère un exécutable (souvent nommé `calculatrice_RPN` sur Linux/macOS, ou `calculatrice_RPN.exe` sous Windows) dans le dossier de build (build/Debug ou build/Release, selon la configuration).


### Exécution dans VS Code

Certains kits/versions de l’extension CMake Tools proposent un bouton Run ou Debug dans la barre de statut, qui lance l’exécutable après le build.

### 3. Saisie d’une expression RPN

Le programme te demande de taper une expression en notation postfixée. Par exemple :

```plaintext
Entrez une expression postfixee (ex: 3 4 + 2 *):
> 3 4 + 2 *
```

Tu peux également saisir une variable x si ton expression en contient (ex. `x 2 ^ 3 +`).

### 4. Entrer la valeur de x (optionnel)

Si l’expression contient la variable x, le programme te demandera la valeur de x :

```plaintext
Entrez la valeur de x :
> 2
```

### 5. Résultat

Le programme calcule et affiche le résultat final de l’expression. Par exemple :

```plaintext
Résultat = 14
```

### 6. Option de tracé (extension)

Si la fonctionnalité de traceur est activée dans le code, il peut te proposer de générer un fichier de données pour tracer la courbe f(x) en fonction de x :

- Il suffit d’indiquer un intervalle, un pas, etc.
- Le programme produit un fichier texte (par exemple `result.txt`) contenant une liste de valeurs :

```plaintext
x     f(x)
-----------
-10   ...
-9.9  ...
 ...
 10   ...
```

Tu peux ensuite utiliser un outil externe (Gnuplot, Python/Matplotlib, etc.) pour visualiser la courbe.

## Exemple d’utilisation

Expression : `3 4 + 2 *`

- `3` → push(3)
- `4` → push(4)
- `+` → pop(4), pop(3), calcule 3+4=7, push(7)
- `2` → push(2)
- `*` → pop(2), pop(7), calcule 7*2=14, push(14)

Résultat final = 14.

## Architecture du code

- `stack.h` / `stack.c` : Gestion de la pile (push, pop, etc.).
- `token.h` / `token.c` : Définition du type Token (nombre, opérateur, fonction, variable).
- `parser.h` / `parser.c` : Découpage (lexing) de la chaîne en tokens (ex. 3 4 + → [3, 4, +]).
- `eval.h` / `eval.c` : Évaluation RPN : parcours des tokens, utilisation de la pile, exécution des opérateurs/fonctions.
- `main.c` : Interface console : saisie de l’expression, appel du parseur, appel de l’évaluateur, affichage du résultat.
- (Optionnel) `plot.h` / `plot.c` : Génération d’un fichier texte pour tracer la fonction si la variable x est incluse.

## Dépendances

- Langage C standard.
- (Optionnel) Librairie mathématique (`-lm` sous Linux) pour les fonctions sin, cos, exp, etc.
- (Optionnel) CMake pour la compilation. Sinon, un simple `gcc *.c -o calculatrice_RPN -lm` peut suffire, selon l’organisation des fichiers.

## Limitations et pistes d’évolution


### Notation infixée

- Possibilité d’ajouter un module de conversion infix → postfix si on souhaite que l’utilisateur saisisse des expressions “normales” (ex. 3+4*2).

### Plusieurs variables

- Actuellement, seule la variable x est prévue. On pourrait gérer x, y, etc.

## Contributeurs et licence

Auteur : (mahdidou711)

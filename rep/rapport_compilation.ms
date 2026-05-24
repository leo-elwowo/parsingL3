.TL
Projet de Compilation 2025-2026 \[em] L3 Informatique
.AU
Léo Pierrat
.AB no
.AE
.NH 1
Manuel d'utilisation
.PP
Le compilateur se construit avec :
.DS
    make
.DE
L'exécutable produit est
.B bin/tpcc .
Il s'utilise de la façon suivante :
.DS
    ./bin/tpcc [options] < monfichier.tpc
.DE
.PP
Options disponibles :
.IP "\-t, \-\-tree" 18
Affiche l'arbre abstrait sur la sortie standard.
.IP "\-s, \-\-symtabs" 18
Affiche toutes les tables des symboles.
.IP "\-h, \-\-help" 18
Affiche l'aide et termine.
.PP
Codes de retour :
.IP "0" 6
Programme source valide (même si des avertissements ont été émis).
.IP "1" 6
Erreur lexicale ou syntaxique.
.IP "2" 6
Erreur sémantique.
.LP
.NH 1
Description du compilateur
.NH 2
Analyse lexicale et syntaxique
.PP
L'analyse lexicale est réalisée avec Flex.
Le lexeur gère les commentaires multi-lignes
.I "/* ... */"
via un état exclusif
.B COMM ,
ce qui permet de continuer à compter les numéros de ligne à l'intérieur des commentaires.
Les commentaires mono-ligne
.I "// ..."
sont ignorés par une règle simple.
Les types
.B int
et
.B char
sont renvoyés comme token
.B TYPE
avec leur valeur, ce qui permet au parseur de les traiter uniformément.
.PP
L'analyse syntaxique est réalisée avec Bison.
La grammaire implémente le langage TPC complet, y compris les types structure
.I "struct X { ... }" .
À chaque règle de grammaire correspond une action qui construit un nœud de l'arbre abstrait via le module
.B tree .
Chaque nœud contient un label (type du nœud), et selon le cas un entier, un caractère, une chaîne (identifiant ou opérateur).
.NH 2
Analyse sémantique
.PP
L'analyse sémantique est réalisée dans le module
.B sem.c ,
par un parcours en profondeur de l'arbre abstrait.
.PP
Quatre tables de hachage sont utilisées (module
.B symb.c ,
avec chaînage et optimisation move-to-front) :
.IP \(bu 3
.B global_table
: variables globales,
.IP \(bu 3
.B local_table
: variables locales à la fonction en cours (réinitialisée à chaque nouvelle fonction),
.IP \(bu 3
.B function_table
: noms des fonctions déclarées,
.IP \(bu 3
.B struct_table
: noms des types struct déclarés.
.PP
.B Pré-passe.
Avant le parcours principal, une pré-passe sur le nœud racine collecte tous les noms de fonctions et de structs globales. Cela permet de gérer les appels à des fonctions déclarées plus loin dans le fichier source sans générer de fausse erreur.
Les quatre fonctions built-in
.I "putchar, getchar, putint, getint"
sont également insérées dans
.B function_table
au démarrage.
.PP
.B Erreurs détectées :
.IP \(bu 3
Variable utilisée sans être déclarée.
.IP \(bu 3
Fonction appelée sans être déclarée.
.IP \(bu 3
Type
.I "struct X"
utilisé alors que
.I X
n'a pas été déclaré (en variable locale, globale ou en paramètre).
.PP
.B Avertissements :
.IP \(bu 3
Affectation d'une expression de type
.B int
à une variable de type
.B char .
.NH 2
Génération de code
.PP
Le code cible est de l'assembleur NASM x86-64 avec les conventions d'appel AMD64.
Le fichier de sortie est
.B _anonymous.asm
par défaut (entrée standard).
.PP
.B Structure du programme généré.
Le fichier assembleur contient :
un point d'entrée
.B _start
qui appelle
.B main
puis effectue le syscall
.I exit
avec le code de retour ;
les quatre fonctions built-in d'E/S ;
les fonctions du programme source ;
une section
.B .bss
pour les variables globales.
.PP
.B Expressions.
Les expressions sont évaluées par une approche à pile :
chaque sous-expression empile son résultat,
les opérateurs dépilent leurs opérandes dans
.B rax
et
.B r10
et empilent le résultat.
La division utilise
.B idiv
après
.I "xor rdx, rdx" .
La multiplication utilise la forme à deux opérandes
.I "imul rax, r10" .
.PP
.B Booléens.
Les expressions booléennes
.I "(&&, ||, !, ==, !=, <, >, <=, >=)"
utilisent l'évaluation paresseuse (court-circuit) avec des labels.
Chaque nœud booléen reçoit un
.I label_true
et un
.I label_false
et y saute directement sans passer par la pile.
.PP
.B Fonctions.
Chaque fonction génère un prologue
.I "(push rbp ; mov rbp, rsp ; sub rsp, N)"
et un épilogue
.I "(mov rsp, rbp ; pop rbp ; ret)" .
Les arguments sont passés dans les registres
.I "rdi, rsi, rdx, rcx, r8, r9"
et copiés sur la pile locale dans le prologue.
Les variables locales sont allouées avec des déplacements négatifs par rapport à
.B rbp .
.PP
.B Fonctions I/O built-in.
Les quatre fonctions sont écrites directement en NASM en utilisant uniquement les syscalls Linux.
Aucune instruction non vue en cours n'est utilisée.
.PP
.B Limitation.
L'accès aux champs de structures
.I "(a.x)"
n'est pas implémenté en génération de code.
Les types struct sont déclarés et vérifiés sémantiquement,
mais le layout mémoire et la lecture/écriture de champs ne sont pas gérés.
.NH 1
Difficultés rencontrées
.IP \(bu 3
.B "Convention AMD64 \[em] registres callee-save."
Le registre
.B rbx
est callee-save et ne peut pas être utilisé comme registre scratch sans être sauvegardé au préalable.
Tous les registres temporaires ont été remplacés par
.B r10
(caller-save).
.IP \(bu 3
.B "Instruction idiv."
L'instruction requiert que
.B rdx
soit mis à zéro avant la division, sous peine de comportement indéfini.
.IP \(bu 3
.B "Évaluation paresseuse."
La gestion des labels pour
.B &&
et
.B ||
est délicate : chaque nœud doit propager ses labels
.I true
et
.I false
récursivement sans les mélanger avec les labels des nœuds voisins.
.IP \(bu 3
.B "Pré-passe pour les fonctions."
Sans pré-passe, appeler une fonction déclarée après son point d'utilisation dans le fichier source provoquait une fausse erreur sémantique.
La pré-passe résout ce problème en collectant tous les noms avant le parcours principal.
.IP \(bu 3
.B "Prologue et allocation de la pile."
La taille de la zone locale n'est connue qu'après avoir parcouru toutes les déclarations locales.
L'instruction
.I "sub rsp, N"
est donc générée après le parcours du corps de la fonction, en utilisant la valeur finale de
.I current_offset .

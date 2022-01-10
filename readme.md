ABDELAZIZ Adame
MAGALHAES MONTEIRO William

Ce projet simule l'exécution  d'une machine de Turing à partir d'un fichier contenant le code d'une machine de Turing et d'une entrée de l'utilisateur.
Pour le code de la MT: 

- les états doivent être des chaînes de caractères commençant par une lettre majuscule (prise de liberté vis à vis de l'énoncé)
- l'alphabet d'entrée est {0,1}
- l'alphabet de travail est {0,1,#,_}

La syntaxe est la même que sur le site https://turingmachinesimulator.com/ 
Nous avons implémenté une gestion d'erreur concernant la syntaxe d'une MT dans un fichier, par exemple manque de virgule, alphabet non reconnu etc...

Exécution du code :

Dans le terminal tapez les commandes suivantes :

make : mode interactif vous permet de choisir le nom de fichier, quel type de MT vous faites tourner (alphabet {a,b,c,d}, bi infini ou simple)

make test : exécute 3 fichers prédéfinis contenant 3 MT simple (ruban semi-infini, alphabet {0,1}) à la suite avec une entrée aussi prédéfini
            premier fichier (palindrome) : MT acceptant les palindrome executé avec l'entrée 10001
            deuxième fichier (zero_pair) : MT acceptant une entrée avec un nombre pair de 0 executé avec l'entrée 000110
            troisième fichier (plus_un)  : MT qui ajoute 1 en binaire, executé avec l'entrée 11011
            

make test1 : Convertit dans un autre fichier une MT utilisant une ruban bi infini en une MT équivalente mais avec un ruban infini à droite seulement puis l'exécute
             puis converti une MT ayant un alphabet {a,b,c,d} dans un autre fichier en une MT équivalente mais fonctionnant sur l'alphabet {0,1} et l'exécute
             premier fichier (test_bi_infini) : ajoute 111 à gauche et à droite de l'entrée si on a que des 0 en entrée
             second fichier (test_abcd) : 'a' devient 'b', 'b' devient 'c', 'c' devient 'd', 'd' devient 'a', puis place un 'a' à droite de l'entrée 0011011011 (adbcd)

make test2 : Enregistre dans une structure le code de la MT du fichier opti_test puis l'optimise.
             fichier : opti_test

make debug : exécute le mode interactif avec l'outil valgrind.

Dans le fichier optimisation.c nous avons une fonction nous permettant d'optimiser une MT avant son execution.



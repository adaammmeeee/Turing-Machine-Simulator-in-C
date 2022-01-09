ABDELAZIZ Adame
MAGHALES MONTERO William

Ce projet simule l'execution  d'une machine de Turing à partir d'un fichier contenant le code d'une machine de Turing et d'une entrée de l'utilisateur.
Pour le code de la MT: 

- les états doivent être des chaînes de caractères commençant par une lettre majuscule (prise de liberté vis à vis de l'énoncé)
- l'alphabet d'entrée est {0,1}
- l'alphabet de travail est {0,1,#,_}

La syntaxe est la même que sur le site https://turingmachinesimulator.com/
Nous avons implémenté une gestion d'erreur concernant la syntaxe d'une MT dans un fichier, par exemple manque de virgule, alphabet non reconnu etc...

Execution du code :

Dans le terminal tapez les commandes suivantes :

make : mode interactif vous permet de choisir le nom de fichier, quel type de MT vous faites tourner (alphabet {a,b,c,d}, bi infini ou simple)

make test : execute 3 fichers prédéfinis contenant 3 MT simple (ruban semi-infini, alphabet {0,1}) à la suite avec une entrée aussi prédéfini
            premier fichier (palindrome) : MT acceptant les palindrome executé avec l'entrée 10001
            deuxième fichier todo
            troisième fichier todo

make test1 : execute un fichier avec une MT qui a un ruban bi-infini, converti dans une autre fichier cette MT équivalente mais fonctionnant sur un seul ruban 
             puis execute un fichier avec une MT ayant un alphabet {a,b,c,d} converti dans une autre fichier cette MT équivalente mais fonctionnant sur l'alphabet {0,1}
             premier fichier (test_bi_infini) : ajoute un 1 à gauche de l'entrée 10101
             second fichier (test_abcd) : échange les 'a' avec les 'b' ainsi que les 'c' et les 'd' puis place un 'a' à droite de l'entrée 0011011011 (adbcd)

make debug : execute le mode interactif avec l'outil valgrind.

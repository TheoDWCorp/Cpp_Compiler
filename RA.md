# Rapport d'activité :

*Date* : 26/10/23  
*Auteur* : Théo WALTER  
*Durée* : 1h  
*Détails des modifications* :
- ajout des templates pour le rapport d'activité et les comptes rendu de réunion
- ajout du compte rendu de réunion du 25/10
___

*Date* : 26/10/23  
*Auteur* : Léo GERMAIN  
*Durée* : 1h30  
*Détails des modifications* :
- création de la classe TreeNode pour l'AST et de son constructeur
- développement des premières fonctions utilisant cette classe : 
    - addNode, qui ajoute à l'arbre un noeud passé en argument
    - printTree, qui affiche les string portés par chacun des noeuds de l'arbre suivant un parcours "DFS Preorder Traversal"
- création d'un fichier DOC.md qui documente les méthodes de la classe TreeNode
___

*Date* : 31/10/23  
*Auteur* : Léo GERMAIN  
*Durée* : 1h 
*Détails des modifications* :
- modification des noms des fichiers : arbre.cpp devient TreeNode.cpp pour que le fichier porte le nom de la classe
- création d'un fichier de test "TreeNode_test.cpp"
- mise à jour du makefile
- ajout d'une fonction "ajoutkNode", qui ajoute k noeuds passés en argument dans un vecteur
- mise à jour de la documentation
___

*Date* : 03/11/23  
*Auteur* : Théo WALTER  
*Durée* : 3h  
*Détails des modifications* :
- ajout de `/prog_test`, contenant des fichiers pour tester notre compilateur sur les différent pattern  
- ajout de quelque programme ada pour tester le compilateur, et du makefile (all compile tous les prog de test, clean supprime les .ali, .o et les executables)
- ajout de `conception.md`, contenant les détails des éléments du compilateurs pour le pcl1  
___

*Date* : 09/11/23    
*Auteur* : Théo W.  
*Durée* :  10min  
*Détails des modifications* :
- ajout du CR de la réunion du 8/11
___

*Date* : 09/11/23  
*Auteur* : Théo W.  
*Durée* : 1 h  
*Détails des modifications* :
- ajout de `Lexique.md` qui contient les détails des patterns reconnu et des tokens associé.

  
*difficultés* :
- constante et variable string ?
- true et false : keyword ou constante
- type : keyword ou idf. 
___

*Date* : 10/11/23  
*Auteur* : Théo W.  
*Durée* : 1 h  
*Détails des modifications* :
- ajout des identifiant dans le `Lexique.md` et résolution de probleme pour true false etc  
- ajout des regex pour les identifieurs, les cst etc.  
___

*Date* : 10/11/23  
*Auteur* : Augustin DESBOIS  
*Durée* : 1h30  
*Détails des modifications* :
- mise en place du scanner avec le code contenu dans scanner.cpp
- mise en place d'un fichier tet qui contient différents cas pour lesquels le scanner doit agir
- mise en place d'un guide (scanner.md) pour comprendre les fonctions utilisées dans scanner.cpp
___

*Date* : 11/11/23  
*Auteur* : Théo D.  
*Durée* : 4 h  
*Détails des modifications* :
- ajout des tests pour le scanner
___
*Date* : 11/11/23  
*Auteur* : Théo W.  
*Durée* : 5 h  
*Détails des modifications* :
- ajout du lexeur dans `src/lex/`  
- ne renvoit pas de token mais un vecteur de string
- ne gère pas encore les constantes int ou float négative  

*difficultés* :
- chaine de charactère  
- symbole := /= <= >= qui contiènnent des séparateurs  
___

*Date* : 11/11/23  
*Auteur* : Augustin DESBOIS  
*Durée* : 20min  
*Détails des modifications* :
- ajout d'une fonction permettant de choisir le fichier à traiter directement dans la ligne de commande

___

*Date* : 11/11/23  
*Auteur* : Augustin DESBOIS  
*Durée* : 30min
*Détails des modifications* :
- ajout d'une fonctionnalité permettant de rajouter un troisième argument dans la ligne de commande pour choisir le chemin de fichier scanné
___

*Date* : 11/11/23  
*Auteur* : Léo GERMAIN  
*Durée* : 2h  
*Détails des modifications* :
- création de la classe abstraite Token, contenant les attributs name, index et line
- création des classes Operateur, Constante et Keyword, qui héritent de la classe Token
- création de la méthode "printToken()" pour chacune de ces classes, affichant le token sous la forme <name,index>
___

*Date* : 12/11/23  
*Auteur* : Théo D.  
*Durée* : 4 h  
*Détails des modifications* :
- ajout des tests automatiques pour le scanner
___
*Date* : 12/11/23  
*Auteur* : Léo GERMAIN  
*Durée* : 2h 
*Détails des modifications* :
- création d'une classe Identifier, contenant l'identifiant et le numéro de ligne
- création de fonctions s'appliquant à un vecteur d'Identifiant*, qui modélise une table des symboles

___

*Date* : 13/11/23  
*Auteur* : théo WALTER  
*Durée* : 2h 
*Détails des modifications* :
- retour des tokens par lexeur, option 1 1 1 pour afficher les lexemes et les tokens et la tds
- test du lexeur dans test_lexeur 

___

*Date* : 13/11/23  
*Auteur* : Léo GERMAIN  
*Durée* : 1h30 
*Détails des modifications* :
- modification de la classe Constante en classe abstraite, ajout de sous-classes portant la valeur de la constante, différant par le type de la constante
- ajout d'une classe Identifiant, héritant de Token
- passage de fonctionnel à orienté objet la gestion de la table des symboles, avec la création d'une classe TableDesSymboles et la transformation des fonctions en méthodes 
___

*Date* : 16/11/23  
*Auteur* : Augustin DESBOIS 
*Durée* : 1h40 
*Détails des modifications* :
- Début de propagation de la modification de la Classe constante aux autres fichiers
___

*Date* : 17/12/23  
*Auteur* : Augustin DESBOIS 
*Durée* : 2h00 
*Détails des modifications* :
- Fin de la propagation
___

*Date* : 19/11/23  
*Auteur* : Léo GERMAIN  
*Durée* : 4h 
*Détails des modifications* :
- écriture de l'automate LR(0) et de la table d'analyse LR(0) de la grammaire donnée dans l'énoncé
*Difficultés rencontrées* : 
- beaucoup trop long, je ne suis mếme pas rendu à mi-chemin après une après-midi de travail dessus, il faut penser à le faire automatiquement ou à changer de stratégie
___

*Date* : 21/11/23  
*Auteur* : Théo D.  
*Durée* : 4 h  
*Détails des modifications* :
- ajout des tests automatiques ada
___

*Date* : 22/11/23  
*Auteur* : Théo D.  
*Durée* : 4 h  
*Détails des modifications* :
- ajout de nouveaux test ada
___

*Date* : 23/11/23  
*Auteur* : Théo D.  
*Durée* : 8 h  
*Détails des modifications* :
- début de l'automatisation pour avoir un automate LR(1)
___

*Date* : 24/11/23  
*Auteur* : Théo D.  
*Durée* : 6 h  
*Détails des modifications* :
- fin de l'automatisation pour avoir un automate LR(1), il fonctionne sur des exemples
___

*Date* : 25/11/23
*Auteur* : Théo D.  
*Durée* : 3 h  
*Détails des modifications* :
- création automatique d'un diagramme uml représentant l'automate et réarrangement du code
___

*Date* : 26/11/23
*Auteur* : Théo D.  
*Durée* : 1 h  
*Détails des modifications* :
- ajout de la grammaire dans l'uml
___

*Date* : 27/11/23
*Auteur* : Théo D.  
*Durée* : 3 h  
*Détails des modifications* :
- modification de l'algorithme pour la création de l'automate et ajout de la grammaire du sujet
___

*Date* : 29/11/23
*Auteur* : Théo D.  
*Durée* : 3 h  
*Détails des modifications* :
- création automatique de la table d'analyse à partir de l'automate
___

*Date* : 2/12/23 - 4/12/23
*Auteur* : Théo D.  
*Durée* : 4 h  
*Détails des modifications* :
- modification automatique de la grammaire avec le lexeur et réarrangement du code
___

*Date* : 12/12/23  
*Auteur* : Léo GERMAIN  
*Durée* : 15min 
*Détails des modifications* :
- ajout d'une fonction "creePere", créant un TreeNode père à un vecteur de noeuds donnés en argument
- update de la doc
___

*Date* : 13/12/23  
*Auteur* : Augustin DESBOIS 
*Durée* : 2h00 
*Détails des modifications* :
- ajout d'un fichier "Visualisation.cpp" qui crée un fichier puml
- Pour l'instant, le fichier puml est généré manuellement sur un exemple (Visualisation ne parcours pas l'arbre)
___

*Date* : 14/12/23  
*Auteur* : Augustin DESBOIS 
*Durée* : 2h00 
*Détails des modifications* :
- Ajout d'une fonction pour que le fichier Visualisation.cpp puisse parcourir un arbre donné en argument en largeur et produire le code en puml dans un fichier à part prêt à être visualisé.
___

*Date* : 05/01/24
*Auteur* : Théo D.  
*Durée* : 3 h  
*Détails des modifications* :
- réarrangement du code avec des headers et ajouts de makefiles
___

*Date* : 13/01/24
*Auteur* : theo WALTER 
*Durée* : 2h00 
*Détails des modifications* :
- fin du parser et corection de la grammaire
- implémentation du parse tree

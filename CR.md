# Comptes Rendus de réunion PCL1 :

*Date* : 25/10/23  
*Durée* : 1h30  
*Objectifs* :
- choisir le langage
- se répartir le travail pour la semaine de vacances

*Résultats* :
- langage choisi : C++
- répartition des tâches :
  - Théo D. : table des symboles
  - Augustin : scanner
  - Léo : structure de l'AST et affichage
  - Théo W. : répartition du travail pour la suite
___

*Date* : 08/11/23  
*Durée* : 2h 
*Objectifs* :
- mise en commun du travail de chacun
- choix des prochains objectifs

*Résultats* :
- répartition des tâches :
  - Théo D. : Tests en ada
    - programmes en ada pour chaque pattern, avec doc
    - programmes test pour vérifier le scanner(commentaire, espaces multiples)
  - Augustin : scanner (commentaire, espaces multiples)
  - Léo : 
    - table des symboles (structure)
    - classes token
  - Théo W. :
    - CR 
    - lexique
- Prochaine réunion : Vendredi 17/11, 16h
___

*Date* : 17/11/23  
*Durée* : 40min 
*Objectifs* :
- mise en commun du travail de chacun
- choix des prochains objectifs
- choix du type d'analyseur syntaxique 

*Résultats* :
- nous avons choisi une analyse syntaxique ascendante à l'unanimité
- répartition des tâches :
  - Théo D. : Tests en ada
    - finir les programmes en ada pour chaque pattern, avec doc
  - Augustin : propagation des modifications sur les classes Token et TableDesSymboles sur le lexeur : 
    - Une classe TableDesSymboles a été crée et toutes les fonctions la concernant sont devenues des méthodes de cette classe
    - La classe Constante est devenue abstraite, et 5 sous-classes en héritant ont été crées. Elles correspondent à des constantes dont le type est fixé et est un des 5 types primitifs (int, float, char, string, bool)
    - Une nouvelle classe Identifiant hérite de Token, et permet de séparer de manière plus claires les keywords des identifiants.
  - Léo : 
    - gérer les conflits, notamment ceux liés aux opérations, afin de préparer l'analyse syntaxique ascendante
    - CR
  - Théo W. : corriger le lexeur
- Prochaine réunion : Mercredi 22/11, 14h
___

*Date* : 22/11/23  
*Durée* : 30min 
*Objectifs* :
- mise en commun du travail de chacun
- choix des prochains objectifs

*Résultats* :
- difficultés rencontrées : régler les conflits de la grammaire à la main est trop long et porte le risque d'erreurs potentielles, on choisit donc de coder un programme permettant de corriger automatiquement la grammaire
- répartition des tâches :
  - Théo D. : 
    - finir les derniers tests en ada pour chaque pattern, avec doc
    - gérer la grammaire automatiquement
  - Augustin : propagation des modifications sur les classes Token et TableDesSymboles sur le lexeur : 
    - Une classe TableDesSymboles a été crée et toutes les fonctions la concernant sont devenues des méthodes de cette classe
    - La classe Constante est devenue abstraite, et 5 sous-classes en héritant ont été crées. Elles correspondent à des constantes dont le type est fixé et est un des 5 types primitifs (int, float, char, string, bool)
    - Une nouvelle classe Identifiant hérite de Token, et permet de séparer de manière plus claires les keywords des identifiants.
  - Léo : 
    - répartition du travail en jalon pour la partie analyse syntaxique ascendante
    - CR
  - Théo W. : corriger le lexeur
- Prochaine réunion : Mercredi 29/11, 14h
___________________________________________________________

# Comptes Rendus de réunion PCL2 :

*Date* : 18/01/24  
*Durée* : 1h  
*Objectifs* :
- bilan du PCL1
- se répartir le travail

*Résultats* :
- Bilan du PCL1 : satisfaction de l'équipe sur le travail accompli et présenté à la soutenance ; volonté commune de découper encore davantage le travail, afin d'assurer que chacun puisse rejoindre n'importe quelle tâche en cours pour pouvoir s'épauler ; souhait  d'assurer un meilleur parallélisme en créant des tests intermédiaires permettant de tester chaque fonctionnalité, pour décorréler le travail sur toutes les fonctionnalités et permettre à tous d'avancer conjointement, sans avoir besoin de "s'attendre" les uns les autres ; besoin de revoir certains éléments du parser et du lexeur afin de s'assurer de partir sur les meilleures bases possibles pour le PCL2.
- Répartition du travail : 
  - Augustin : Ajout d'une Factory pour la classe TreeNode, permettant de la modifier plus facilement (ajout de commentaires, de l'indice de région, de l'indice d'imbrication) et changer tous les appels au constructeur de TreeNode en des appels à sa factory.
  - Théo D. : Débuggage du parser
  - Léo : Assurer l'exécution de toutes les étapes du PCL1 en une ligne de code
  - Théo W. : Réorganisation du code du lexeur, de manière à le rendre plus clair et plus facilement modifiable
- Prochaine réunion : Vendredi 26/01, 14h
___



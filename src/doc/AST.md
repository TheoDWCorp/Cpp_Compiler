# Documentation AST

### Détail des fonctions :

- **Constructeur de TreeNode** : Au maximum deux attributs peuvent être renseignés dans le constructeur : le string contenu par le noeud, et un pointeur vers noeud père. Il est également possible de ne pas renseigner l'un de ces paramètres, voire les deux, en instanciant cette classe. On attribue alors par défaut le mot vide au string et la valeur "nullptr" au pointeur du noeud père. 
- **printTree** : Prend en argument un TreeNode*, ne return rien. Affiche dans la sortie standard (via cout) les string contenus par chaque noeud de l'arbre suivant un parcours "DFS Preorder Traversal" (voir l'image ci-dessous).
![](traversal.png "Différents types de parcours d'arbre") 
- **ajoutNode** : Prend en argument un TreeNode* et l'insère dans un arbre en fonction du noeud père qui lui est associé via son attribut "pere". Cette fonction ne fonctionne pas si son pere vaut "nullptr". Cette fonction ne détecte pas les duplicatas : si on l'applique plusieurs fois au même noeud, plusieurs noeuds identiques seront ajoutés à l'arbre.
- **ajoutKNode** : Prend en argument un pointeur vers un vecteur de k TreeNode*. Réutilise la fonction "ajoutNode". Fonctionne donc avec un vecteur contenant des TreeNode* qui doivent s'insérer sur des branches différentes, et même sur des arbres différents, car ne dépend que de l'attribut "père" de chacun des TreeNode* du vecteur.
- **creePere** : Crée et renvoie un TreeNode*, le noeud père pour un ensemble de noeud fils. Cette fonction prend donc en argument un vecteur de TreeNode* (les noeuds fils) et un string, correspondant au nom porté par le noeud. Cette fonction devrait servir pour crée l'arbre de dérivation.

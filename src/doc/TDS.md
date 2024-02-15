# Documentation TDS

### La classe Identifier

La table des symboles contient un ensemble d'informations sur les identifiants rencontrés dans le texte source. 
Ici, on choisit de conserver les informations suivantes : 
- le nom de l'identifiant
- la ligne à laquelle il apparaît
- le code lexical attribué à l'identifiant

Pour cela, on construit une classe Identifier contenant le nom (string idf) et le numéro de ligne (int line) d'un identifiant.
Ainsi, on peut modéliser la table des symboles par un vector d'Identifier*.
Le code lexical de l'identifiant correspond alors à son indice dans le vector.

### Les fonctions

Attention, les fonctions prennent en argument des Identifier*. Il faut donc manipuler des adresses et non pas des objets de la classe Identifier.

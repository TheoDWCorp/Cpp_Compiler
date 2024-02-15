## Comprendre le code de scanner.cpp

### Ouverture du fichier

    Pour ouvrir un fichier en C++, il faut d'abord importer la bibliothèque "fstream"

```
    #include <fstream>
```

    Ensuite on utilise la classe "ifstream" pour ouvrir le fichier source

```
    ifstream sourceFile("test.cpp");
```

    On oublie pas de rajouter le cas d'erreur où le fichier n'existe pas ou n'est pas dans le bon dossier

```
    if (!sourceFile) {
        cerr << "Impossible d'ouvrir le fichier source." << endl;
        return 1;
    }
```

    Et un peu de bonne pratique, on oublie pas de fermer le fichier qu'on a ouvert

```
    sourceFile.close();
```

### Comment ça marche ?

    On commence par créer une variable String qui va devenir la version traitée du fichier source
    On crée les regex qui nous intéressent en utilisant la classe "regex" sans oublier d'importer la bibliothèque "regex"
    On crée ègalement une variable string qui va contenir au fur et à mesure les différentes lignes du fichier source

    On utilise ensuite la fonction getline(fichier_source, où stocker chaque ligne). Il est possible de rajouter un troisième argument qui correspond au marqueur de délimitation de ligne mais par défault il s'agit de '\n'

    On remplace les regex voulu par ce qu'on veut via la fonction regex_replace et on ajoute la ligne traitée à la variable de sortie

    Ici, la fonction regex_search est utilisée pour confirmer ou non la présence d'un regex dans une ligne

### Stockage dans un fichier txt

    Le code scanné est stocké dans un fichier scanned.txt
    Il a été crée grâce à la classe ofstream et à la fonction outFile

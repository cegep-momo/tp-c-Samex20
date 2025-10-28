# Construire le projet
Vous pouvez utiliser un dev container de base C++ de VScode.
Le projet utilise cmake, pensez à l'inclure dans votre dev container.

Voici les lignes de commandes pour compiler le projet:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Répertoire data

Il contient 2 fichiers `books.txt`et `users.txt` que vous pouvez utilisez pour tester votre code.
Pour ca il suffit de les copiers dans le repertoire `build` avec l'application `bibliotheque`



## Question 1 : Filestream (`std::ofstream`)

Lorsque vous effectuez une programmation C++, vous écrivez des informations dans un fichier à partir de votre programme à l'aide de l'opérateur d'insertion de flux (<<) tout comme vous utilisez cet opérateur pour afficher des informations à l'écran. La seule différence est que vous utilisez un flux sortant ou fstream objet au lieu du cout objet.

## Question 2 : Ajout d'une fonctionnalité

On pourrait ajouter une option dans la liste du menu où l’utilisateur peut simplement décrire le genre de livre qu’il cherche.
Le système lui renverrait alors une liste de livres recommandés, classés par pertinence, avec une courte explication pour chaque suggestion.
Au départ, on pourrait se baser sur une recherche par mots-clés ou un algorithme TF-IDF simple, puis améliorer le tout plus tard avec de l’intelligence artificielle pour offrir des recommandations beaucoup plus précises à grande échelle.
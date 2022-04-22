# codage-huffman
Projet étudiant de compression de données par codage de Huffman.

## Compilation

Le projet est compilé à l'aide de CMake.
Pour générer les fichiers cmake il est préférable de créer un nouveau dossier pour accueillir les fichiers générés par
CMake.

```
mkdir build-huffman
cd build-huffman
cmake ../CMakeLists.txt
```

On peut ensuite compiler le projet.
```
cmake --build .
```

Deux exécutables sont ensuite généré, `codage_huffman` et `test_codage_huffman`.

## Exécution du programme

Pour lancer le programme il faut appeler `codage_huffman` avec en argument le chemin vers le texte qui sera compressé.

Exemple :

```
./codage_huffman ../textes/textesimple.txt
```

## Convention de nommage des branches

Ajout de fonctionnalité :

feature-XXXXXXX

Refactorisation du code :

rework-XXXXXXX


Résolution de bugs ou de problèmes :

fix-XXXXXXX

Annulation de modifications :

rollback-XXXXXXX

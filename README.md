# Gestionnaire d'images en C

Logiciel en ligne de commande de traitement d'images au format PGM (P2).
L'image est encodée dans un **quadtree**, ce qui permet de la compresser.
Projet réalisé seul dans le cadre de ma formation à l'hepia (Genève, 2025-2026).

## Fonctionnalités
- Lecture et écriture de fichiers PGM (format P2, commentaires ignorés)
- Remplissage de l'image jusqu'à la puissance de 2 supérieure
- Encodage de l'image dans un quadtree
- Symétries horizontale et verticale, rotation de 90°
- Compression **avec perte** par quadtree, à seuil réglable (0-255)
- Réinitialisation de l'image, sauvegarde du résultat
- Affichage dans une fenêtre SDL2
- Menu interactif et script Bash de lancement (`run.sh`)

## Compilation
```bash
sudo apt install libsdl2-dev
make
```

## Utilisation
```bash
./run.sh                    # demande le chemin et vérifie que c'est un .pgm
./projet_image feep.pgm     # ou directement
```
Dans la fenêtre d'affichage, `q` ferme la fenêtre.

## Organisation du code
| Fichier | Rôle |
|---|---|
| `pgm.c / pgm.h` | Structure d'image, chargement, sauvegarde, remplissage |
| `quadtree.c / quadtree.h` | Construction, destruction, reconstruction et compression du quadtree |
| `transform.c / transform.h` | Symétries et rotation sur les pixels |
| `display.c / display.h` | Affichage SDL2 |
| `main.c` | Menu interactif |

## Compression
Les feuilles voisines sont fusionnées en une seule, de valeur égale à la moyenne,
lorsque l'écart entre leurs valeurs ne dépasse pas le seuil. Plus le seuil est
grand, plus la compression est forte et plus l'image perd en qualité.

## Limites connues
- Seul le format PGM texte (P2) est géré, avec des valeurs de pixel de 0 à 255.
- Les transformations agissent sur les pixels ; `quadtree_flip_h/v` et
  `quadtree_rotate_90` existent dans `transform.c` mais ne sont pas utilisées par le menu.
- Le quadtree compressé n'est pas sauvegardé sous une forme compacte : l'image
  est reconstruite puis enregistrée en PGM.

## Bibliothèque graphique
`gfx.c` et `gfx.h` (rendu SDL2) sont fournis par l'école (auteurs : Florent Gluck,
Michaël El Kharroubi) et ne font pas partie de ce dépôt.

## Auteur
Noé Lacazette-Leprêtre, hepia, 2025-2026

#ifndef PGM_H
#define PGM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Structure représentant une image PGM en niveaux de gris.
Les pixels sont stockés dans un tableau 2D : pixels[ligne][colonne].
Chaque valeur est un entier entre 0 (noir) et max (blanc).
*/
typedef struct pgm_image {
    uint32_t width;
    uint32_t height;
    uint32_t max;
    uint8_t **pixels;
} pgm_image_t;

/*
Alloue une image PGM vide de dimensions données.
Tous les pixels sont initialisés à 0 (noir).
@param width  largeur en pixels
@param height hauteur en pixels
@param max    valeur maximale d'un pixel
@return un pointeur vers l'image allouée, ou NULL si échec
*/
pgm_image_t *pgm_create(uint32_t width, uint32_t height, uint32_t max);

/*
Libère la mémoire d'une image PGM.
@param img pointeur vers l'image à libérer
*/
void pgm_destroy(pgm_image_t *img);

/*
Lit un fichier PGM (format P2) et retourne l'image en mémoire.
Ignore les lignes de commentaires commençant par '#'.
@param filename chemin vers le fichier PGM
@return un pointeur vers l'image lue, ou NULL si échec
*/
pgm_image_t *pgm_load(const char *filename);

/*
Sauvegarde une image PGM dans un fichier (format P2).
@param img      l'image à sauvegarder
@param filename chemin du fichier de destination
@return true si succès, false sinon
*/
bool pgm_save(const pgm_image_t *img, const char *filename);

/*
Agrandit l'image à la puissance de 2 supérieure.
Nécessaire pour construire un quadtree valide.
Les pixels ajoutés sont noirs (valeur 0).
@param img l'image source
@return une nouvelle image padded, ou NULL si échec
*/
pgm_image_t *pgm_pad(pgm_image_t *img);

#endif
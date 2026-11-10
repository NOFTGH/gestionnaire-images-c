#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "quadtree.h"

/**
Effectue une symétrie horizontale (miroir gauche/droite) sur le quadtree.
@param node la racine du quadtree
*/
void quadtree_flip_h(quadtree_node_t *node);

/**
Effectue une symétrie verticale (miroir haut/bas) sur le quadtree.
@param node la racine du quadtree
 */
void quadtree_flip_v(quadtree_node_t *node);

/**
Effectue une rotation de 90 degrés dans le sens horaire sur le quadtree.
@param node la racine du quadtree
 */
 void quadtree_rotate_90(quadtree_node_t *node);

 /**
 * Effectue une symétrie horizontale sur les pixels.
@param img l'image source
@return une nouvelle image transformée, ou NULL si échec
 */
pgm_image_t *pgm_flip_h(pgm_image_t *img);

/*
Effectue une symétrie verticale sur les pixels.
@param img l'image source
@return une nouvelle image transformée, ou NULL si échec
*/
pgm_image_t *pgm_flip_v(pgm_image_t *img);

/*
Effectue une rotation de 90 degrés dans le sens horaire sur les pixels.
@param img l'image source
@return une nouvelle image transformée, ou NULL si échec
*/
pgm_image_t *pgm_rotate_90(pgm_image_t *img);


 #endif
#ifndef QUADTREE_H
#define QUADTREE_H

#include "pgm.h"

/**noeud d un quadtree représentant une zone de l'image.
si is_leaf est vrai, value contient la valeur uniforme de la zone.
sinon, les 4 fils représentent les sous-zones.
 */

 typedef struct quadtree_node {
    bool is_leaf;
    uint8_t value;
    uint32_t x, y;
    uint32_t size;
    struct quadtree_node *nw;
    struct quadtree_node *ne;
    struct quadtree_node *sw;
    struct quadtree_node *se;
 }quadtree_node_t;

 /**construit un quadtree à partir d'une image PGM.
@param img l'image source
@param x position horizontale du coin superieur gauche
@param y position verticale du coin superieur gauche
@param size taille de la zone
@return la racine du quadtree, ou NULL si échec
*/

quadtree_node_t *quadtree_build(pgm_image_t *img, uint32_t x,uint32_t y,uint32_t size);

/**
Libere la mémoire d'un quadtree
@param node la racine du quadtree
*/

void quadtree_destroy(quadtree_node_t *node);

/**
reconstruit une image PGM depuis un quadtree.
@param node la racine du quadtree
@param img l'image de destination
*/

void quadtree_to_image(quadtree_node_t *node, pgm_image_t*img);

/**
compresse el quadtree en fusionnant les feuilles proches
plus le seuil est grand, plus la compression est forte
@param node la racine du quadtree
@param seuil difference max entre feuilles pour les fusionner
 */

void quadtree_compress(quadtree_node_t *node, uint8_t seuil);


#endif
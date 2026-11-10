#include "quadtree.h"

static bool is_uniform(pgm_image_t *img, uint32_t x, uint32_t y, uint32_t size) {
    uint8_t val = img->pixels[y][x];
    for (uint32_t row =y; row < y + size; row++) {
        for(uint32_t col =x; col < x + size; col++) {
            if (img->pixels[row][col] !=val){
                return false;
            }
        }
    }
    return true;
}

quadtree_node_t *quadtree_build(pgm_image_t *img, uint32_t x, uint32_t y, uint32_t size) {
    quadtree_node_t *node = malloc(sizeof(quadtree_node_t));
    if(!node){
        return NULL;
    }
    node->x = x;
    node->y = y; 
    node->size = size; 
    node->nw = node->ne = node->sw = node->se = NULL;

    if(is_uniform(img, x, y, size)) {
        node->is_leaf = true;
        node->value = img->pixels[y][x];
        return node;
    }

    node->is_leaf = false;
    node->value = 0;
    uint32_t half = size / 2;

    node->nw = quadtree_build(img, x, y, half);
    node->ne = quadtree_build(img, x + half, y, half);
    node->sw = quadtree_build(img, x, y+half, half);
    node->se = quadtree_build(img, x + half, y+ half, half);

    return node;

}

void quadtree_destroy(quadtree_node_t *node) {
    if(!node){
        return;
    }
    quadtree_destroy(node->nw);
    quadtree_destroy(node->ne);
    quadtree_destroy(node->sw);
    quadtree_destroy(node->se);

    free(node);

}

void quadtree_to_image(quadtree_node_t *node, pgm_image_t *img) {
    if(!node){
        return;
    }

    if(node->is_leaf) {
        for (uint32_t y = node->y; y < node->y + node->size; y++){
            for (uint32_t x = node->x; x < node->x + node->size; x++){
                img->pixels[y][x] = node->value;
            }
        }
        return;
    }

    quadtree_to_image(node->nw, img);
    quadtree_to_image(node->ne, img);
    quadtree_to_image(node->sw, img);
    quadtree_to_image(node->se, img);

}


void quadtree_compress(quadtree_node_t*node, uint8_t seuil) {
    if(!node || node->is_leaf) return;

    //on compresse d'abord les enfants récursivement

    quadtree_compress(node->nw, seuil);
    quadtree_compress(node->ne, seuil);
    quadtree_compress(node->sw, seuil);
    quadtree_compress(node->se, seuil);

    if(!node->nw->is_leaf || !node->ne->is_leaf || !node->sw->is_leaf || !node->se->is_leaf) {
        return;
    }

    // on calcule la valeur min et max des 4 feuilles
    uint8_t v[4] = { node->nw->value, node->ne->value,
                     node->sw->value, node->se->value };
    uint8_t min = v[0];
    uint8_t max = v[0];
    for (int i = 1; i < 4; i++) {
        if (v[i] < min) min = v[i];
        if (v[i] > max) max = v[i];
    }

    // si les 4 valeurs sont assez proches, on fusionne en une feuille (moyenne)
    if (max - min <= seuil) {
        uint8_t moyenne = (v[0] + v[1] + v[2] + v[3]) / 4;

        free(node->nw); node->nw =NULL;
        free(node->ne); node->ne =NULL;
        free(node->sw); node->sw =NULL;
        free(node->se); node->se =NULL;

        node->is_leaf = true;
        node->value = moyenne;

    }

}

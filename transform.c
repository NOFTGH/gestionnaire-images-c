#include "transform.h"

pgm_image_t *pgm_flip_h(pgm_image_t *img) {
    if (!img) return NULL;

    pgm_image_t *new = pgm_create(img->width, img->height, img->max);
    if (!new) return NULL;

    for (uint32_t y = 0; y < img->height; y++) {
        for (uint32_t x = 0; x < img->width; x++) {
            new->pixels[y][x] = img->pixels[y][img->width - 1 - x];
        }
    }
    return new;
}

pgm_image_t *pgm_flip_v(pgm_image_t *img) {
    if (!img) return NULL;

    pgm_image_t *new = pgm_create(img->width, img->height, img->max);
    if (!new) return NULL;

    for (uint32_t y = 0; y < img->height; y++) {
        for (uint32_t x = 0; x < img->width; x++) {
            new->pixels[y][x] = img->pixels[img->height - 1 - y][x];
        }
    }
    return new;
}


pgm_image_t *pgm_rotate_90(pgm_image_t *img) {
    if (!img) return NULL;

    pgm_image_t *new = pgm_create(img->height, img->width, img->max);
    if (!new) return NULL;

    for (uint32_t y = 0; y < img->height; y++) {
        for (uint32_t x = 0; x < img->width; x++) {
            new->pixels[x][img->height - 1 - y] = img->pixels[y][x];
        }
    }
    return new;
}


void quadtree_flip_h(quadtree_node_t *node) {
    if (!node || node->is_leaf){
        return;
    }

    quadtree_node_t *tmp = node->nw;
    node->nw = node->ne;
    node->ne = tmp;

    tmp = node->sw;
    node->sw = node->se;
    node->se = tmp;

    quadtree_flip_h(node->nw);
    quadtree_flip_h(node->ne);
    quadtree_flip_h(node->sw);
    quadtree_flip_h(node->se);

}

void quadtree_flip_v(quadtree_node_t *node) {
    if (!node || node->is_leaf) return;

    quadtree_node_t *tmp = node->nw;
    node->nw = node->sw;
    node->sw = tmp;

    tmp = node->ne;
    node->ne = node->se;
    node->se = tmp;

    quadtree_flip_v(node->nw);
    quadtree_flip_v(node->ne);
    quadtree_flip_v(node->sw);
    quadtree_flip_v(node->se);
}

void quadtree_rotate_90(quadtree_node_t *node) {
    if (!node || node->is_leaf) return;

    quadtree_node_t *tmp = node->nw;
    node->nw = node->sw;
    node->sw = node->se;
    node->se = node->ne;
    node->ne = tmp;

    quadtree_rotate_90(node->nw);
    quadtree_rotate_90(node->ne);
    quadtree_rotate_90(node->sw);
    quadtree_rotate_90(node->se);
}


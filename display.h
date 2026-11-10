#ifndef DISPLAY_H
#define DISPLAY_H

#include "gfx.h"
#include "pgm.h"

/**
-Affiche une image PGM dans une fenetre SDL2
-@param img l'image à afficher
*/

void display_image(pgm_image_t *img);

#endif

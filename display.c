#include "display.h"

void display_image(pgm_image_t *img) {

	struct gfx_context_t *ctxt = gfx_create ("Projet Image", img->width, img->height);

	if (!ctxt) { 
		fprintf(stderr, "Erreur : impossible d ecréer la fenetre\n");
		return;
	}

	gfx_clear(ctxt, COLOR_BLACK);

	for (uint32_t y = 0; y < img->height; y++) {
		for(uint32_t x = 0; x < img->width; x++){
			uint8_t val = img->pixels[y][x];
			uint8_t gray = (uint8_t)((val * 255) / img->max);
			uint32_t color = MAKE_COLOR(gray, gray ,gray);
			gfx_putpixel(ctxt, x, y, color);
		}
	}

	gfx_present(ctxt);

	while(!quit_signal()) {
		SDL_Keycode key = gfx_keypressed();
		if (key == SDLK_q) break;
	}

	gfx_destroy(ctxt);
}



#include <stdio.h>
#include "pgm.h"
#include "display.h"
#include "quadtree.h"
#include "transform.h"

void afficher_menu() {
	printf("\n╔════════════════Menu════════════════╗\n");
	printf("║                                    ║\n");
	printf("║   1- Afficher l'image              ║\n");
	printf("║   2- Symétrie horizontale          ║\n");
	printf("║   3- Symétrie verticale            ║\n");
	printf("║   4- Rotation a 90 degres          ║\n");
	printf("║   5- Compresser (entre 0 et 255)   ║\n");
	printf("║   6- Sauvegarder l'image           ║\n");
	printf("║   7- Quitter                       ║\n");
	printf("║   8- Reinitialiser l'image         ║\n");
	printf("║                                    ║\n");
	printf("╚════════════════════════════════════╝\n");
	printf("Votre choix: ");
}

/*
Lit un entier au clavier.
Vide la ligne en cas de saisie invalide pour éviter une boucle infinie.
@param out adresse où stocker l'entier lu
@return 1 si succès, 0 si saisie invalide, -1 si fin de fichier (EOF)
*/
static int lire_entier(int *out) {
	int r = scanf("%d", out);
	if (r == EOF) {
		return -1;
	}
	if (r != 1) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		return 0;
	}
	return 1;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage : %s <image.pgm>\n", argv[0]);
		return EXIT_FAILURE;
	}

	pgm_image_t *img = NULL;
	pgm_image_t *padded = NULL;
	pgm_image_t *current = NULL;
	quadtree_node_t *tree = NULL;
	int code = EXIT_FAILURE;

	// Charger l'image
	img = pgm_load(argv[1]);
	if (!img) goto cleanup;

	// Agrandir l'image à la puissance de 2 supérieure
	padded = pgm_pad(img);
	if (!padded) goto cleanup;

	// Construire le quadtree
	tree = quadtree_build(padded, 0, 0, padded->width);
	if (!tree) goto cleanup;

	// Image courante, reconstruite depuis le quadtree
	current = pgm_create(padded->width, padded->height, padded->max);
	if (!current) goto cleanup;
	quadtree_to_image(tree, current);

	int choix = 0;
	while (choix != 7) {
		afficher_menu();

		int r = lire_entier(&choix);
		if (r == -1) break;          // fin de fichier : on quitte
		if (r == 0) choix = 0;       // saisie invalide : message d'erreur

		pgm_image_t *tmp = NULL;

		switch (choix) {
			case 1:
				display_image(current);
				break;

			case 2:
				tmp = pgm_flip_h(current);
				if (tmp) {
					pgm_destroy(current);
					current = tmp;
				}
				printf("\n==============================\n");
				printf("Symetrie horizontale appliquée");
				printf("\n==============================\n");
				break;

			case 3:
				tmp = pgm_flip_v(current);
				if (tmp) {
					pgm_destroy(current);
					current = tmp;
				}
				printf("\n============================\n");
				printf("Symetrie verticale appliquée");
				printf("\n============================\n");
				break;

			case 4:
				tmp = pgm_rotate_90(current);
				if (tmp) {
					pgm_destroy(current);
					current = tmp;
				}
				printf("\n============================\n");
				printf("Rotation 90 degres appliquee !");
				printf("\n============================\n");
				break;

			case 5: {
				int seuil = 0;
				printf("\n==========================================\n");
				printf("Entrez le seuil de compression (0-255) : ");
				if (lire_entier(&seuil) != 1 || seuil < 0 || seuil > 255) {
					printf("Seuil invalide (entier entre 0 et 255).\n");
					break;
				}
				quadtree_destroy(tree);
				tree = quadtree_build(current, 0, 0, current->width);
				if (!tree) goto cleanup;
				quadtree_compress(tree, (uint8_t)seuil);
				quadtree_to_image(tree, current);
				printf("Compression appliquee avec seuil %d ", seuil);
				printf("\n============================================\n");
				break;
			}

			case 6: {
				char filename[256];
				printf("\n============================\n");
				printf("Entrez le chemin de sauvegarde : ");
				if (scanf("%255s", filename) != 1) break;
				if (pgm_save(current, filename)) {
					printf("\nImage sauvegardée avec succes !");
				}
				printf("\n============================\n");
				break;
			}

			case 7:
				printf("\n=====================\n");
				printf("\n");
				printf("- - -A bientot !- - -\n");
				printf("\n=====================\n");
				break;

			case 8: {
				pgm_image_t *fresh = pgm_create(padded->width, padded->height, padded->max);
				if (!fresh) goto cleanup;
				pgm_destroy(current);
				current = fresh;
				quadtree_destroy(tree);
				tree = quadtree_build(padded, 0, 0, padded->width);
				if (!tree) goto cleanup;
				quadtree_to_image(tree, current);
				printf("\n============================\n");
				printf("Image reinitalisee !");
				printf("\n============================\n");
				break;
			}

			default:
				printf("\n  ┌───────┐  \n");
				printf("  |       |\n");
				printf("  |   !   |    CHOIX INVALIDE \n");
				printf("  |       |\n");
				printf("  └───────┘   \n");
				break;
		}
	}

	code = EXIT_SUCCESS;

cleanup:
	quadtree_destroy(tree);
	pgm_destroy(img);
	pgm_destroy(padded);
	pgm_destroy(current);
	return code;
}

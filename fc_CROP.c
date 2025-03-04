// Leca Maria Catalina 315CA
#include "functions.h"

void crop(img *image, coordinates *coord)
{
	if (image->type == 0) {
		printf("No image loaded\n");
		return;
	}

	img aux;// imagine auxiliara
// se preiau informatiile de la imaginea incarcata
	aux.type = image->type;
	aux.max = image->max;
	aux.width = coord->c_stop - coord->c_start;
	aux.height = coord->r_stop - coord->r_start;

// se creaza matrice in funtie de tip
	if (aux.type == 2 || aux.type == 5) {
		aux.gray = gray_mat(aux.height, aux.width);
		if (!aux.gray) {
			printf("Failed to crop\n");
			return;
		}
	} else {
		aux.color = color_mat(aux.height, aux.width);
		if (!aux.color) {
			printf("Failed to crop\n");
			return;
		}
	}

// se copiaza in matricea auxiliara doar bucata din selectie
	int ir = 0, ic;
	for (int i = coord->r_start; i < coord->r_stop; i++) {
		ic = 0;
		for (int j = coord->c_start; j < coord->c_stop; j++) {
			if (image->type == 2 || image->type == 5) {
				aux.gray[ir][ic] = image->gray[i][j];
			} else {
				aux.color[ir][ic].red = image->color[i][j].red;
				aux.color[ir][ic].green = image->color[i][j].green;
				aux.color[ir][ic].blue = image->color[i][j].blue;
			}
			ic++;
		}
		ir++;
	}

	free_image(*image); // stergere imagine veche
	*image = aux; //noua imagine
	init_coord(*image, coord); // actualizare coordonate selectie
	printf("Image cropped\n");
}

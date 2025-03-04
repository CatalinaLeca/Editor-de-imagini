// Leca Maria Catalina 315CA
#include "functions.h"

// calculeza noul pixel de la pozitia i j
rgb new_pixel(img image, kernel ker, int i, int j)
{
	rgb new; // noul pixel
	double s = 0;
	int m, n;

// inmulteste valorile din blocul 3x3 cu cele din nucleu si le insumeaza
// pentru fiecare tip de culoare
	for (m = 0; m < 3; m++)
		for (n = 0; n < 3; n++)
			s += ker.mat[m][n] * image.color[i + m - 1][j + n - 1].red;
	s  = s / ker.x;
	new.red = clamp(my_round(s), image.max); // formula

	s = 0;
	for (m = 0; m < 3; m++)
		for (n = 0; n < 3; n++)
			s += ker.mat[m][n] * image.color[i + m - 1][j + n - 1].green;
	s = s / ker.x;
	new.green = clamp(my_round(s), image.max);

	s = 0;
	for (m = 0; m < 3; m++)
		for (n = 0; n < 3; n++)
			s += ker.mat[m][n] * image.color[i + m - 1][j + n - 1].blue;
	s = s / ker.x;
	new.blue = clamp(my_round(s), image.max);

	return new;
}

void apply(img *image, coordinates coord, char *arg)
{
	if (image->type == 0) {
		printf("No image loaded\n");
		return;
	}

	if (image->type == 2 || image->type == 5) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

// valorile pentru nucleu in functie de parametru
	kernel ker;
	if (strcmp(arg, "EDGE") == 0) {
		ker = (kernel){ { { -1, -1, -1 }, { -1, 8, -1 }, {-1, -1, -1 } }, 1};
	} else if (strcmp(arg, "SHARPEN") == 0) {
		ker = (kernel){ { { 0, -1, 0 }, { -1, 5, -1 }, { 0, -1, 0 } }, 1};
	} else if (strcmp(arg, "BLUR") == 0) {
		ker = (kernel){ { { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } }, 9};
	} else if (strcmp(arg, "GAUSSIAN_BLUR") == 0) {
		ker = (kernel){ { { 1, 2, 1 }, { 2, 4, 2 }, { 1, 2, 1 } }, 16};
	} else {
		printf("APPLY parameter invalid\n");
		return;
	}

// matrice auxiliara
	rgb **aux_mat;
	int height = coord.r_stop - coord.r_start;
	int width = coord.c_stop - coord.c_start;
	aux_mat = color_mat(height, width);
	if (!aux_mat) {
		printf("Failed to apply\n");
		return;
	}

// completare matricea auxiliara
	int i, j, ir = 0, ic;
	for (i = coord.r_start; i < coord.r_stop; i++) {
		ic = 0;
		for (j = coord.c_start; j < coord.c_stop; j++) {
			if (i == 0 || j == 0 || i == image->height - 1 ||
			    j == image->width - 1) // cand nu are in jur bloc 3x3
				aux_mat[ir][ic] = image->color[i][j];
			else
				aux_mat[ir][ic] = new_pixel(*image, ker, i, j);
			ic++;
		}
		ir++;
	}
// copiere in matricea originala noile valori
	ir = 0;
	for (i = coord.r_start; i < coord.r_stop; i++) {
		ic = 0;
		for (j = coord.c_start; j < coord.c_stop; j++) {
			image->color[i][j] = aux_mat[ir][ic];
			ic++;
		}
		ir++;
	}

	for (i = 0; i < height; i++)
		free(aux_mat[i]);
	free(aux_mat);

	printf("APPLY %s done\n", arg);
}

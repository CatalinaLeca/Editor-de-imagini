// Leca Maria Catalina 315CA
#include "functions.h"

int clamp(int x, int max)
{
	if (x > max)
		return max;
	if (x < 0)
		return 0;
	return x;
}

// calcul f(a) pentru pixel a
int eq_pixel(img image, int a, double *fr)
{
	double h = 0;
	for (int i = 0; i <= a; i++)
		h += fr[i]; // H(a)

	double area = image.height * image.width;
	double aux = (h * 255) / area; // formula din enunt
	//int result = my_round(aux);

	return clamp(my_round(aux), image.max);
}

void eq(img *image)
{
	if (image->type == 0) {
		printf("No image loaded\n");
		return;
	}

	if (image->type == 3 || image->type == 6) {
		printf("Black and white image needed\n");
		return;
	}

	double *f = freq(*image, 256); // vector frecventa
	if (!f) {
		printf("Failed to equalize\n");
		return;
	}

// modifica matricea
	for (int i = 0; i < image->height; i++)
		for (int j = 0; j < image->width; j++)
			image->gray[i][j] = eq_pixel(*image, image->gray[i][j], f);

	free(f);
	printf("Equalize done\n");
}

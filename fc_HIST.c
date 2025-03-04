// Leca Maria Catalina 315CA
#include "functions.h"

// creaza dinamic un vector ce va retine valorile de frecventa
double *freq(img image, int y)
{
	int i, j, k, l;
	double *v = (double *)malloc(y * sizeof(double));
	if (!v)
		return NULL;

	l = 256 / y;

	for (i = 0; i < y; i++) // initializeaza cu 0
		v[i] = 0;

	for (i = 0; i < image.height; i++)
		for (j = 0; j < image.width; j++)
			for (k = 0; k < y; k++)
				if (l * k <= image.gray[i][j] && image.gray[i][j] < l * (k + 1))
					v[k]++;
	return v;
}

void hist(img image, char arg[])
{
	if (image.type == 0) {
		printf("No image loaded\n");
		return;
	}
	if (image.type == 3 || image.type == 6) {
		printf("Black and white image needed\n");
		return;
	}

	int c[2], n = 0; // pentru parametrii
	char *p = strtok(arg, " ");
	while (p) {
		if (n == 2) { // mai multi parametrii
			printf("Invalid command\n");
			return;
		}

		for (size_t i = 0; i < strlen(p); i++) {
			if (p[i] < '0' || p[i] > '9') { // daca nu sunt numere
				printf("Invalid command\n");
				return;
			}
		}
		c[n++] = to_number(p);
		p = strtok(NULL, " ");
	}

	if (n < 2) {
		printf("Invalid command\n");
		return;
	}

	int x = c[0], y = c[1];
	if (x < 1 || y < 1 || y > 256) {
		printf("Invalid command\n");
		return;
	}

	double *v1 = freq(image, y); //  vectorul frecventa

	double max = v1[0]; // cauta valoarea maxima in vector
	for (int i = 1; i < y; i++)
		if (v1[i] > max)
			max = v1[i];

// un vector pentru valorile midificate din primul vector
	int *v2 = (int *)malloc(y * sizeof(int));
	if (!v2)
		return;

	double aux;
	for (int i = 0; i < y; i++) {
		aux = v1[i] / max;
		aux *= x; // se aplica formula
		v2[i] = (int)aux;
	}

	for (int i = 0; i < y; i++) {
		printf("%d\t|\t", v2[i]);
		for (int j = 0; j < v2[i]; j++) // afisare
			printf("*");
		printf("\n");
	}

// stergere vectori
	free(v1);
	free(v2);
}


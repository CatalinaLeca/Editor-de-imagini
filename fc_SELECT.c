// Leca Maria Catalina 315CA
#include "functions.h"

// pentru comanda SELECT ALL
void select_all(img image, coordinates *coord)
{
	if (image.type == 0) { // mesaj cand nu e incarcata o imagine
		printf("No image loaded\n"); // si terminarea functiei
		return;
	}
// coordonatele sunt pentru intreaga imagine
// deci de la 0 pana la latime/inaltime
	coord->r_start = 0;
	coord->c_start = 0;
	coord->r_stop = image.height;
	coord->c_stop = image.width;

	printf("Selected ALL\n");
}

void select_coord(img image, coordinates *coord, char *arg)
{
	if (image.type == 0) {
		printf("No image loaded\n");
		return;
	}
// desparte sirul de caractere in cuvinte
	int c[4]; // vector pentru coordonate
	int n = 0; // pentru numar de cuvinte
	char *p = strtok(arg, " ");
	while (p) {
		if (n == 4) {
			printf("Invalid command\n"); // daca sunt mai multe cuvinte
			return; // se opreste
		}
		for (size_t i = 0; i < strlen(p); i++) {
			if (p[0] == '-') { // daca este vreun numar negativ
				printf("Invalid set of coordinates\n");
				return; // se opreste
			}
			if (p[i] < '0' || p[i] > '9') { // daca nu sunt strict numere
				printf("Invalid command\n");
				return; // se opreste
			}
		}
		c[n++] = to_number(p);
		p = strtok(NULL, " ");
	}
	if (n < 4) { // mai putini parametrii
		printf("Invalid command\n");
		return;
	}

	if (c[0] == c[2] || c[1] == c[3]) { // nu exista interval de selectie
		printf("Invalid set of coordinates\n");
		return;
	}

	if (c[0] > c[2]) {// interschimba coordonatele deca e cazul
		int aux = c[0];
		c[0] = c[2];
		c[2] = aux;
	}

	if (c[1] > c[3]) {
		int aux = c[1];
		c[1] = c[3];
		c[3] = aux;
	}

// depaseste zona de selectie
	if (c[0] > image.width || c[2] > image.width) {
		printf("Invalid set of coordinates\n");
		return;
	}

	if (c[1] > image.height || c[3] > image.height) {
		printf("Invalid set of coordinates\n");
		return;
	}
// modificare zona de selectie
	coord->c_start = c[0];
	coord->r_start = c[1];
	coord->c_stop = c[2];
	coord->r_stop = c[3];

	printf("Selected %d %d %d %d\n", c[0], c[1], c[2], c[3]);
}

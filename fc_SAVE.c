// Leca Maria Catalina 315CA
#include "functions.h"

void save(img image, char *arg)
{
	if (image.type == 0) {
		printf("No image loaded\n");
		return;
	}

	char filename[50];
	char *p = strtok(arg, " ");
	strcpy(filename, p); // extragere nume fisier

	p = strtok(NULL, " ");
	int txt = 0;
	if (p) {
		if (strcmp(p, "ascii") == 0) {
			txt = 1; // verificare daca e text
		} else {
			printf("Invalid command\n");
			return;
		}

		p = strtok(NULL, " "); // daca mai exista parametrii
		if (p) {
			printf("Invalid command\n");
			return;
		}
	}

	if (txt)
		save_text(filename, image);
	else
		save_binary(filename, image);

	printf("Saved %s\n", filename);
}

void save_text(char *filename, img image)
{
	FILE *picture = fopen(filename, "wt");
	if (!picture) {
		printf("Failed to save\n");
		return;
	}

	if (image.type == 2 || image.type == 5) //daca e gri
		fprintf(picture, "P2\n");
	else
		fprintf(picture, "P3\n");

	fprintf(picture, "%d %d\n", image.width, image.height);
	fprintf(picture, "%d\n", image.max);

	for (int i = 0; i < image.height; i++) {
		for (int j = 0; j < image.width; j++) {
			if (image.type == 2 || image.type == 5) { // daca e gri
				fprintf(picture, "%d ", image.gray[i][j]);
			} else {
				fprintf(picture, "%d ", image.color[i][j].red);
				fprintf(picture, "%d ", image.color[i][j].green);
				fprintf(picture, "%d ", image.color[i][j].blue);
			}
		}
		fprintf(picture, "\n");
	}
	fclose(picture);
}

void save_binary(char *filename, img image)
{
	FILE *picture = fopen(filename, "wb");
	if (!picture) {
		printf("Failed to save\n");
		return;
	}

	if (image.type == 2 || image.type == 5)
		fwrite("P5\n", 3, 1, picture);
	else
		fwrite("P6\n", 3, 1, picture);

// transforma numerele in sir de caractere pentru a le folosi in fwrite()
	char ascii[20];
	to_string(image.width, ascii);
	fwrite(ascii, strlen(ascii), 1, picture);
	fwrite(" ", 1, 1, picture);
	to_string(image.height, ascii);
	fwrite(ascii, strlen(ascii), 1, picture);
	fwrite("\n", 1, 1, picture);
	to_string(image.max, ascii);
	fwrite(ascii, strlen(ascii), 1, picture);
	fwrite("\n", 1, 1, picture);

	for (int i = 0; i < image.height; i++) {
		for (int j = 0; j < image.width; j++) {
			if (image.type == 2 || image.type == 5) {
				fwrite(&image.gray[i][j], 1, 1, picture);
			} else {
				fwrite(&image.color[i][j].red, 1, 1, picture);
				fwrite(&image.color[i][j].green, 1, 1, picture);
				fwrite(&image.color[i][j].blue, 1, 1, picture);
			}
		}
	}
	fclose(picture);
}

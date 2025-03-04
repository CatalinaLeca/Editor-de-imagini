// Leca Maria Catalina 315CA
#include "functions.h"

// creaza dinamic o matrice de inturi folosita pentru stocarea
// imaginilor de tip grayscale
int **gray_mat(int height, int width)
{
	int **mat = (int **)calloc(height, sizeof(int *));
	if (!mat)
		return NULL;

	for (int i = 0; i < height; i++) {
		mat[i] = (int *)calloc(width, sizeof(int));
		if (!mat[i]) {
			for (int j = 0; j < i; j++)
				free(mat[j]);
			free(mat);
			return NULL;
		}
	}

	return mat;
}

// creaza dinamic o matrice de structuri rgb folosita pentru stocarea
// imaginilor de tip color
rgb **color_mat(int height, int width)
{
	rgb **mat = (rgb **)calloc(height, sizeof(rgb *));
	if (!mat)
		return NULL;

	for (int i = 0; i < height; i++) {
		mat[i] = (rgb *)calloc(width, sizeof(rgb));
		if (!mat[i]) {
			for (int j = 0; j < i; j++)
				free(mat[j]);
			free(mat);
			return NULL;
		}
	}
	return mat;
}

// eliberarea memoriei daca este cazul
void free_image(img image)
{
	if (image.type == 0)
		return;

	for (int i = 0; i < image.height; i++)
		if (image.type == 2 || image.type == 5)
			free(image.gray[i]);
		else
			free(image.color[i]);

	if (image.type == 2 || image.type == 5)
		free(image.gray);
	else
		free(image.color);

	image.type = 0;
}

// citeste primele 2 caractere din fisier pentru a determina
// tipul imaginii si returneaza un numar asemanator
int magic_number(char *filename)
{
	char s[3];

	FILE *image = fopen(filename, "rb");
	if (!image)
		return 0;

	fread(s, sizeof(char), 2, image);
	s[2] = '\0';
	fclose(image);

	if (strcmp(s, "P2") == 0)
		return 2;
	if (strcmp(s, "P3") == 0)
		return 3;
	if (strcmp(s, "P5") == 0)
		return 5;
	if (strcmp(s, "P6") == 0)
		return 6;

	return 0;
}

// incarcarea imaginilor de tip text
img load_ascii(char *filename)
{
	img image;
	image.type = magic_number(filename);

	FILE *picture = fopen(filename, "r");
	if (!picture) {
		printf("Failed to load %s\n", filename);
		image.type = 0;
		return image;
	}

	fseek(picture, 3, SEEK_CUR); // sare peste prima linie
	comments(picture); // sare peste comentarii
	fscanf(picture, "%d%d", &image.width, &image.height); // dimensiunile
	fseek(picture, 1, SEEK_CUR); // sare peste \n
	comments(picture);
	fscanf(picture, "%d", &image.max); // citeste valoarea maxima
	fseek(picture, 1, SEEK_CUR);
	comments(picture);

	if (image.type == 2) { // creaza matricea pentru imaginea gri
		image.gray = gray_mat(image.height, image.width);
		if (!image.gray) {
			image.type = 0;
			printf("Failed to load %s\n", filename);
			fclose(picture);
			return image;
		}

	} else { // creaza matricea pentru imaginea color
		image.color = color_mat(image.height, image.width);
		if (!image.color) {
			image.type = 0;
			printf("Failed to load %s\n", filename);
			fclose(picture);
			return image;
		}
	}
// citeste din fisier valorile si le pune in matricea
// conform tipului de imagine
	for (int i = 0; i < image.height; i++) {
		for (int j = 0; j < image.width; j++) {
			if (image.type == 2) {
				fscanf(picture, "%d", &image.gray[i][j]);
			} else {
				fscanf(picture, "%d", &image.color[i][j].red);
				fscanf(picture, "%d", &image.color[i][j].green);
				fscanf(picture, "%d", &image.color[i][j].blue);
			}
		}
	}

	printf("Loaded %s\n", filename);
	fclose(picture);
	return image;
}

// citeste din fisier ca sir de caractere un numar
// si il returneaza ca int
int get_number(FILE *filename)
{
	char aux[15], c;
	int i = 0;
	do {
		fread(&c, sizeof(char), 1, filename);
		aux[i] = c;
		i++;
	} while (c != ' ' && c != '\n');
	aux[i - 1] = '\0';
	return to_number(aux);
}

// incarcarea imaginilor de tip binar
// asemanator cu cel de tip text
img load_bin(char *filename)
{
	img image;
	image.type = magic_number(filename);

	FILE *picture = fopen(filename, "rb");
	if (!picture) {
		printf("Failed to load %s\n", filename);
		image.type = 0;
		return image;
	}

	fseek(picture, 3, SEEK_CUR);
	comments(picture);
	image.width = get_number(picture);
	image.height = get_number(picture);
	comments(picture);
	image.max = get_number(picture);
	comments(picture);

	if (image.type == 5) {
		image.gray = gray_mat(image.height, image.width);
		if (!image.gray) {
			image.type = 0;
			printf("Failed to load %s\n", filename);
			fclose(picture);
			return image;
		}

	} else {
		image.color = color_mat(image.height, image.width);
		if (!image.color) {
			image.type = 0;
			printf("Failed to load %s\n", filename);
			fclose(picture);
			return image;
		}
	}
	for (int i = 0; i < image.height; i++) {
		for (int j = 0; j < image.width; j++) {
			if (image.type == 5) {
				fread(&image.gray[i][j], 1, 1, picture);
			} else {
				fread(&image.color[i][j].red, 1, 1, picture);
				fread(&image.color[i][j].green, 1, 1, picture);
				fread(&image.color[i][j].blue, 1, 1, picture);
			}
		}
	}

	printf("Loaded %s\n", filename);
	fseek(picture, 0, SEEK_SET);
	fclose(picture);
	return image;
}

// incarcare imagine in fucntie de tip
void load(img *image, char *arg)
{
	int magic_no = magic_number(arg);
	if (magic_no == 2 || magic_no == 3)
		*image = load_ascii(arg);
	else
		*image = load_bin(arg);
}

// sare peste comentarii
void comments(FILE *file)
{
	char c, aux;
	fread(&c, 1, 1, file);
	while (c == '#') { // daca primul caracter e '#'
		fread(&aux, 1, 1, file); // citeste in "gol"
		while (aux != '\n') // pana ajune la finalul liniei
			fread(&aux, 1, 1, file);
		fread(&c, 1, 1, file); // citeste primul caracter de pe linia urmatoare
	}
	fseek(file, -1, SEEK_CUR);
	// ma intorc o pozitie pentru a citi mai usor linia respectiva
	// fara sa fie nevoie sa citesc separat primul caracter de restul liniei
}

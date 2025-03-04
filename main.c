// Leca Maria Catalina 315CA
#include "functions.h"

int main(void)
{
	// input e primul cuvant citit, arg e restul de sir de caractere
	char input[20], arg[100];
	img image;
	coordinates coord; // pentru selectia curenta
	init_img(&image); // initializeaza valorile
	init_coord(image, &coord); // initializeaza valorile
	int read = 1; // cat timp citeste
	while (read) {
		scanf("%s", input);
		if (strcmp(input, "LOAD") == 0) {
			if (getchar() == '\n') { // daca nu are parametru
				printf("Invalid command\n");
			} else {
				read_arg(arg); // citeste ce ramane din sirul dat
				free_image(image); // sterge imaginea curenta daca exista
				load(&image, arg); // incarca imaginea
				init_coord(image, &coord);
			}
		} else if (strcmp(input, "SELECT") == 0) {
			if (getchar() == '\n') {
				printf("Invalid command\n");
			} else {
				read_arg(arg);
				if (strcmp(arg, "ALL") == 0) // daca parametrul este ALL
					select_all(image, &coord);
				else
					select_coord(image, &coord, arg);
			}
		} else if (strcmp(input, "CROP") == 0) {
			if (getchar() != '\n') // daca are parametru
				printf("Invalid command\n");
			else
				crop(&image, &coord);
		} else if (strcmp(input, "HISTOGRAM") == 0) {
			char c = getchar();
			if (c == '\n' && image.type != 0) { //exisa imagine incarcata
				printf("Invalid command\n"); // dar nu are comanda parametru
			} else if (c == '\n' && image.type == 0) { // nu are parametru
				printf("No image loaded\n"); //dar nu exisa imagine incarcata
			} else {
				read_arg(arg);
				hist(image, arg);
			}
		} else if (strcmp(input, "EQUALIZE") == 0) {
			if (getchar() != '\n')
				printf("Invalid command\n");
			else
				eq(&image);
		} else if (strcmp(input, "APPLY") == 0) {
			char c = getchar();
			if (c == '\n' && image.type != 0) {
				printf("Invalid command\n");  // situatie ca mai sus
			} else if (c == '\n' && image.type == 0) {
				printf("No image loaded\n");
			} else {
				read_arg(arg);
				apply(&image, coord, arg);
			}
		} else if (strcmp(input, "SAVE") == 0) {
			if (getchar() == '\n') {
				printf("Invalid command\n");
			} else {
				read_arg(arg);
				save(image, arg);
			}
		} else if (strcmp(input, "EXIT") == 0) {
			if (image.type == 0) // nu exista imagine incarcata
				printf("No image loaded\n");
			free_image(image);
			read = 0; // citirea de comenzi se va incheia
		} else {
			printf("Invalid command\n"); // nu a fost tastata o comanda
			// citeste restul de carcatere ce nu ne intereseaza
			fgets(arg, sizeof(arg), stdin);
		}
	}

	return 0;
}

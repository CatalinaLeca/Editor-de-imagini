// Leca Maria Catalina 315CA
#include "functions.h"

//citeste un sir de caractere si elimina spatiile de la final
//deoarece acestea nu sunt luate in considerare in comanda
void read_arg(char *arg)
{
	fgets(arg, 100, stdin);
	arg[strlen(arg) - 1] = '\0';
	remove_spaces(arg);
}

// verifica daca un sir de caractere este un numar pozitiv
int is_number(char s[])
{
	size_t len = strlen(s), i;
	for (i = 0; i < len; i++) {
		if (i == 0 && s[i] == '-')
			continue;
		if (s[i] < '0' && s[i] > '9')
			return 0;
	}

	return 1;
}

// transforma un sir de caractere ce reprezinta un numar
// in numar de tip int si il returneaza
int to_number(char *s)
{
	size_t len = strlen(s), i;
	int n = 0, neg = 0;
	for (i = 0; i < len; i++) {
		if (i == 0 && s[i] == '-') {
			neg = 1;
			continue;
		}
		n = n * 10 + (s[i] - '0');
	}
	if (neg)
		n = 0 - n;
	return n;
}

// initializeaza datele pentru o imagine la "0"
void init_img(img *image)
{
	image->type = 0;
	image->height = 0;
	image->width = 0;
	image->max = 0;
	image->gray = NULL;
	image->color = NULL;
}

// initializeaza coordonatele pentru o selectie
// la "0" daca nu este imagine incarcata
// cu datele preluate din informatiile imaginii altfel
void init_coord(img image, coordinates *coord)
{
	coord->r_start = 0;
	coord->c_start = 0;
	if (image.type == 0) {
		coord->r_stop = 0;
		coord->c_stop = 0;
		return;
	}
	coord->r_stop = image.height;
	coord->c_stop = image.width;
}

//transforma un numar sub forma de sir de caractere
void to_string(int n, char *s)
{
	int i = 0;
	while (n) {
		s[i] = n % 10 + '0';
		n /= 10;
		i++;
	}
// cifrele din numar au fost asezate in sir in ordine inversa
// de aceea in for se pun in ordinea corecta
	for (int j = 0; j < i / 2; j++) {
		s[i] = s[j];
		s[j] = s[i - j - 1];
		s[i - j - 1] = s[i];
	}

	s[i] = '\0';
}

// elimina spatiile de la sfarsitul unui sir de caractere
void remove_spaces(char *str)
{
	size_t n = strlen(str);
	int i = n - 1;
	while (i >= 0 && str[i] == ' ') {
		str[i] = '\0';
		i--;
	}
}

int my_round(double x)
{
	return (int)(x + 0.5);
}

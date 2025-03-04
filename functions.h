// Leca Maria Catalina 315CA
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 100

typedef struct {
	int red;
	int green;
	int blue;
} rgb;

typedef struct {
	int type;
	int height;
	int width;
	int max;
	int **gray;
	rgb **color;
} img;

typedef struct {
	int r_start;
	int r_stop;
	int c_start;
	int c_stop;
} coordinates;

typedef struct {
	double mat[9][9];
	int x;
} kernel;

int is_number(char s[]);
int to_number(char *s);
img load_ascii(char *filename);
int **gray_mat(int height, int width);
rgb **color_mat(int height, int width);
void free_image(img image);
void init_img(img *image);
void init_coord(img image, coordinates *coord);
img load_bin(char *filename);
int get_number(FILE *filename);
int magic_number(char *filename);
void select_all(img image, coordinates *coord);
void select_coord(img image, coordinates *coord, char *arg);
void crop(img *image, coordinates *coord);
void hist(img image, char arg[]);
double *freq(img image, int y);
int clamp(int x, int max);
int eq_pixel(img image, int a, double *fr);
void eq(img *image);
rgb new_pixel(img image, kernel ker, int i, int j);
void apply(img *image, coordinates coord, char *arg);
void to_string(int n, char *s);
void save(img image, char *arg);
void save_text(char *filename, img image);
void save_binary(char *filename, img image);
void comments(FILE *filename);
void remove_spaces(char *str);
void read_arg(char *arg);
void load(img *image, char *arg);
int my_round(double x);

#endif

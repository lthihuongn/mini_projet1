#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>

#define LARGEUR 10
#define HAUTEUR 10

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef struct {
    char signature [3];
    char largeur [5];
    char hauteur [5];
    char intensite [5];
    Pixel *pixel;
} Pixmap;  // lit le RGB de ton pixel

void creer_pixmap(Pixmap *p, int largeur, int hauteur);
void supprimer_pixmap(Pixmap *p);
void saisir_pixmap(Pixmap *p);
void afficher_pixmap(Pixmap *p);

void creer_pixel(Pixel *px, unsigned char r, unsigned char g, unsigned char b);
void afficher_pixel(Pixel *px);
void saisir_pixel(Pixel *px);
void suppimer_pixel(Pixel *px);

#endif
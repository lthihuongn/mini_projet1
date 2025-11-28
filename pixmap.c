#include "image.h"



void creer_pixmap(Pixmap *p, int largeur, int hauteur){
    p->largeur = largeur;
    p->hauteur = hauteur;
    p->pixel = (Pixel*)malloc(largeur * hauteur * sizeof(Pixel));
    for(int i = 0; i < largeur * hauteur; i++){
        creer_pixel(&p->pixel[i], 0, 0, 0);
    }
}

void supprimer_pixmap(Pixmap *p){
    free(p->pixel);
}
void saisir_pixmap(Pixmap *p){
    
}
void afficher_pixmap(Pixmap *p){
    for(int i = 0; i < p->largeur * p->hauteur; i++){
        afficher_pixel(&p->pixel[i]);
    }
}
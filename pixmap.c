#include "image.h"



void creer_pixmap(Pixmap *p, int largeur, int hauteur){
    p->largeur[largeur] = largeur;
    p->hauteur[hauteur] = hauteur;
    p->pixel = (Pixel*)malloc(largeur * hauteur * sizeof(Pixel));


}

void supprimer_pixmap(Pixmap *p){
    free(p->pixel);
}
void saisir_pixmap(Pixmap *p){
    
}
void afficher_pixmap(Pixmap *p){
    for(int i = 0; i < p->largeur[5] * p->hauteur[5]; i++){
        afficher_pixel(&p->pixel[i]);
    }
}
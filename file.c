#include "file.h"
void ecrire_fichier(const char* nom_fichier, Pixmap* p) {

    FILE *f = fopen(nom_fichier, "wb");
        if (!f) {
            perror("Erreur ouverture fichier");
            return;
        }

        // Écrire l'en-tête PPM
        fprintf(f, "P6\n%d %d\n255\n", p->largeur, p->hauteur);

        // Écrire les pixels en binaire
        fwrite(p->pixel, sizeof(Pixel), p->largeur * p->hauteur, f);

        fclose(f);
}

void supprimer_fichier(const char* nom_fichier){

}
void lire_fichier(const char* nom_fichier, Pixmap* p){

}

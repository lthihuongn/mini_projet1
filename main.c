#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "file.h"

int main(int argc, char const *argv[]){
    Pixmap p;
    creer_pixmap_disque(&p, 600, 400, 200);
    ecrire_fichier("image.ppm", &p);
    supprimer_pixmap(&p);
    
    return 0;
}
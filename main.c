#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "file.h"

int main(int argc, char const *argv[]){
    Pixmap p;
    creer_pixmap(&p, 10, 10);
    ecrire_fichier("image.ppm", &p);
    
    return 0;
}
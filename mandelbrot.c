#include "mandelbrot.h"
#include "file.h"
#include <math.h>

int convergence(double x, double y){
    double u_reel = x;
    double u_imag = y;
    
    for(int n = 0; n < MAX_ITER; n++){
        double module_carre = u_reel * u_reel + u_imag * u_imag; //module carre de U(n)
        
        //si module >= 2, suite diverge
        if(module_carre >= 4.0){  // 2**2 = 4
            return n;
        }
        
        //Calculer U(n+1) = U(n)**2 + Z
        //(a+ib)**2 = a**2 - b**2 + 2iab
        double nouveau_reel = u_reel * u_reel - u_imag * u_imag + x;
        double nouveau_imag = 2 * u_reel * u_imag + y;
        
        u_reel = nouveau_reel;
        u_imag = nouveau_imag;
    }
    
    //ici, suite converge
    return 0;
}

//pixel (0-900, 0-600) en coordonnees math (-2 a 1, 1 a -1)
double pixel_vers_x(int px, double x1, double x2, int largeur){
    double proportion = (double)px / (largeur - 1);
    double largeur_zone = x2 - x1;
    return x1 + proportion * largeur_zone;
}

double pixel_vers_y(int py, double y1, double y2, int hauteur){
    double proportion = (double)py / (hauteur - 1);
    double hauteur_zone = y2 - y1;
    return y1 + proportion * hauteur_zone;
}

//index dans le tableau de pixels
int calculer_index(int px, int py, int largeur){
    return py * largeur + px;
}

//couleur selon la convergence
void creer_couleur_mandelbrot(Pixel *pixel, int c){
    unsigned char r = 0;
    unsigned char g = (3 * c > 255) ? 255 : 3 * c;
    unsigned char b = 255;
    creer_pixel(pixel, r, g, b);
}

void creer_pixmap_mandelbrot(Pixmap *p){
    p->largeur = MANDELBROT_LARGEUR;
    p->hauteur = MANDELBROT_HAUTEUR;
    
    int nb_pixels = MANDELBROT_LARGEUR * MANDELBROT_HAUTEUR;
    p->pixel = (Pixel*)malloc(nb_pixels * sizeof(Pixel));
    
    for(int py = 0; py < MANDELBROT_HAUTEUR; py++){
        for(int px = 0; px < MANDELBROT_LARGEUR; px++){
            //position pixel en coordonnées mathématiques
            double x = pixel_vers_x(px, MANDELBROT_X1, MANDELBROT_X2, MANDELBROT_LARGEUR);
            double y = pixel_vers_y(py, MANDELBROT_Y1, MANDELBROT_Y2, MANDELBROT_HAUTEUR);
            
            //si ce point converge
            int c = convergence(x, y);
            
            //placer me pixel dans le tableau
            int index = calculer_index(px, py, MANDELBROT_LARGEUR);
            
            //couleur du pixel
            creer_couleur_mandelbrot(&p->pixel[index], c);
        }
    }
}

//5)
//coordonnees personalisees : peut zoomer sur une zone specifique
void creer_pixmap_mandelbrot_zoom(Pixmap *p, double x1, double y1, double x2, double y2){
    p->largeur = MANDELBROT_LARGEUR;
    p->hauteur = MANDELBROT_HAUTEUR;
    
    int nb_pixels = MANDELBROT_LARGEUR * MANDELBROT_HAUTEUR;
    p->pixel = (Pixel*)malloc(nb_pixels * sizeof(Pixel));
    
    for(int py = 0; py < MANDELBROT_HAUTEUR; py++){
        for(int px = 0; px < MANDELBROT_LARGEUR; px++){
            double x = pixel_vers_x(px, x1, x2, MANDELBROT_LARGEUR);
            double y = pixel_vers_y(py, y1, y2, MANDELBROT_HAUTEUR);
            
            int c = convergence(x, y);
            
            int index = calculer_index(px, py, MANDELBROT_LARGEUR);
            
            creer_couleur_mandelbrot(&p->pixel[index], c);
        }
    }
}

// Créer une série d'images avec effet de zoom sur un point
void creer_serie_zoom_mandelbrot(int nb_images, double x_target, double y_target){
    Pixmap p;
    
    double x1_init = MANDELBROT_X1;
    double y1_init = MANDELBROT_Y1;
    double x2_init = MANDELBROT_X2;
    double y2_init = MANDELBROT_Y2;
    
    
    for(int i = 0; i < nb_images; i++){
        // Calculer le facteur de zoom (progression linéaire)
        double t = (double)i / (nb_images - 1);  // de 0 à 1
        
        // Calculer la taille de la fenêtre (diminue avec le zoom)
        double largeur_init = x2_init - x1_init;
        double hauteur_init = y1_init - y2_init;
        
        // Réduire la fenêtre progressivement (facteur de 100)
        double facteur_zoom = 1.0 - t * 0.99;  // de 1.0 à 0.01
        double largeur = largeur_init * facteur_zoom;
        double hauteur = hauteur_init * facteur_zoom;
        
        // Centrer la fenêtre sur le point cible
        double x1 = x_target - largeur / 2;
        double x2 = x_target + largeur / 2;
        double y1 = y_target + hauteur / 2;
        double y2 = y_target - hauteur / 2;
        
        // Créer l'image
        creer_pixmap_mandelbrot_zoom(&p, x1, y1, x2, y2);
        
        char nom_fichier[20];
        sprintf(nom_fichier, "im%d.ppm", i);
        
        ecrire_fichier(nom_fichier, &p);
        supprimer_pixmap(&p);
    }
}

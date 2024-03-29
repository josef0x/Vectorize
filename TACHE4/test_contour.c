#include "contour.h"
#include "image.h"
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "[USAGE] : ./test_contour exemple.pbm exemple.contours\n");
		return -1;
	}

	Liste_Point C;

	Image I;
	Robot R;

    I = lire_fichier_image(argv[1]);

    Point P0;
    P0 = trouver_pixel_depart(I);

    P0.x--;
    P0.y--;
    
    init_robot(P0,&R);
    
    Point P_current; // Point courant

    do {

    	P_current.x = R.x;
    	P_current.y = R.y;

        memoriser_position(R, &C, P_current);
        avancer(&R);
        nouvelle_orientation(&R, I);
        
    } while(!( (R.x == P0.x) && (R.y == P0.y) && (R.O == EST) ));
    memoriser_position(R, &C, P0);
    printf("\n");

    printf("== CONTOUR : == \n\n");
    //printf("Le nombre de segments est : %d\n",C.taille);
    ecrire_contour(C);

    /* Ci-dessous la partie ecriture dans le fichier *.contours (de sortie) */

    //sauvegarder_contour(argv[2],C);
    
    /* Sortie format EPS selon le mode choisi */

    int mode;
    printf("Mode de sortie du fichier EPS : ");
    scanf("%d", &mode);

    /*char fichier_sortie[33];
    strcat(fichier_sortie, argv[1]);
    strcat(fichier_sortie);
    strcat(fichier_sortie, ".eps");*/


    convert_to_EPS(C, argv[2], mode, I);

    
    printf("Fichier PostScript enregistré sous le nom %s\n", argv[2]);

}

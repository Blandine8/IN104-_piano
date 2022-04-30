#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <complex.h>
#include <stdlib.h>

int main(){

	//le fichier doit contenir en première ligne le nombre de données qui suivent
	/*-------------- selection du fichier audio(.txt)-------------------------------*/
	printf ("entrer le nom du fichier audio a extraire en data :\n");
	char fichieraudio[100];
    scanf("%s", fichieraudio);
    printf ("nom du fichier : %s\n", fichieraudio);
    //sprintf (fichierdat,"%s.dat", fichieraudio); //%s.dat 

    /*--------------fin de selection du fichier audio-------------------------------*/

   	FILE *sgnl=fopen(fichieraudio, "rb");
   	if ( sgnl == NULL )
    {
        printf("\nne peut pas ouvrir le fichier demande, verifier le nom\n");
        printf("ne pas oublier l'extention .txt\n");
        return(1);
    }
    
    int N;
    fscanf(sgnl, "%d", &N);


   double* tab;
   tab = malloc(sizeof(double)*N);

   	int i=0;
   	double d;
   	while (!feof(sgnl)){
   		fscanf(sgnl,"%lf", &d);
   		tab[i]= d;
   		i=i+1;
   		//printf("%f %d\n", d, i);
		}   	

	int a = gsl_fft_real_radix2_transform(tab,1,N);
}








#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

typedef double complex cplx;

cplx* audiofileSelec(){


//le fichier doit contenir en première ligne le nombre de données qui suivent
  /*-------------- selection du fichier audio(.txt)-------------------------------*/
  printf ("entrer le nom du fichier audio a extraire en data :\n");
  char fichieraudio[100];
  scanf("%s", fichieraudio);
  printf ("nom du fichier : %s\n", fichieraudio);
  //sprintf (fichierdat,"%s.dat", fichieraudio); //%s.dat 

   /*--------------fin de selection du fichier audio-------------------------------*/

  FILE *sgnl=fopen(fichieraudio, "rb");
    //printf("ok");
    if ( sgnl == NULL )
    {
        printf("\nne peut pas ouvrir le fichier demande, verifier le nom\n");
        printf("ne pas oublier l'extention .txt\n");
        exit(1);
    }
    
    int N;
    fscanf(sgnl, "%d", &N);
    printf("N1=%d\n", N);

    N=500;

    cplx* tab;
    printf("taille de tab = %ld", sizeof(tab));
    tab = malloc(sizeof(double)*N);

    if (tab==NULL){
      printf("error.malloc");
      exit(1);
    }

    int i=0;
    double d;

    //printf("ok");
    while (i<N){
      //printf("%d\n",i);
      fscanf(sgnl,"%lf", &d);

      cplx z= CMPLX (d,0);
      //printf("d= %lf\n",d);
      tab[i]= z;
      i=i+1;
      printf("tab(%d)=%.1f + %1.fi\n", i, creal(tab[i]), cimag(tab[i]));
    }

    return (tab);
}

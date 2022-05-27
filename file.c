#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])
//typedef double complex cplx;

double* audiofileSelec(){


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

    //N=500;

    //cplx* tab;
    double* data;
    //printf("taille de tab = %ld", sizeof(tab));
    //tab = malloc(sizeof(double)*N);
    data = malloc(sizeof(double)*2*N);

    /*if (tab==NULL){
      printf("error.malloc");
      exit(1);
    }*/

    if (data==NULL){
      printf("error.malloc");
      exit(1);
    }

    int i=0;
    double d;

    //printf("ok");
    while (i<N){
      //printf("%d\n",i);
      fscanf(sgnl,"%lf", &d);

      //cplx z= CMPLX (d,0);
      //printf("d= %lf\n",d);
      //tab[i]= z;
      REAL(data,i)=d;
      IMAG(data,i)=0;
      i=i+1;
      //printf("tab(%d)=%.1f + %1.fi\n", i, creal(tab[i]), cimag(tab[i]));
    }

    return data;
}

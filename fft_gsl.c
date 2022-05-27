#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>
#include <gsl/gsl_sf_trig.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])


int main(int argc, char* argv[]){
  char *nom=argv[1];
    int n=atoi(argv[2]);
    FILE* file=fopen(nom,"r");
    if (file == NULL)
    {
        printf("Error: could not open file");
        return 1;
    }
    double raw_data[n];
    int i=1;
    fscanf(file,"%le",&raw_data[0]);
    while (i<n){
        fscanf(file,"%le",&raw_data[i]);
      ++i;
    }
    // close the file
    fclose(file);


    // fenêtre de Hamming
    double hamming [n] ;
    for (i=0; i<n ; ++i) {
      // hamming[i] = (0.5 - 0.5*gsl_sf_cos(2*M_PI*(i/n)))*raw_data[i] ;
    }

    //printf("%f\n",raw_data[n]);


    double data[2*n];

    gsl_fft_complex_wavetable * wavetable;
    gsl_fft_complex_workspace * workspace;
    for (i = 0; i < n; i++){
        REAL(data,i) = raw_data[i];
        //REAL(data,i) = hamming[i];
        IMAG(data,i) = 0.0;
    }

    for (i = 0; i < n; i++)
    {
      //printf ("%d: %e %e\n", i, REAL(data,i),IMAG(data,i));
    }
    printf ("\n");

    wavetable = gsl_fft_complex_wavetable_alloc (n);
    workspace = gsl_fft_complex_workspace_alloc (n);

    for (i = 0; i < (int) wavetable->nf; i++){
       //printf ("# factor %d: %zu\n", i, wavetable->factor[i]);
    }

    gsl_fft_complex_forward (data, 1, n, wavetable, workspace);

    double module[n];
    double max =1 ;
    int ind ;
    int f=5000;

    for (i = 0; i < n; i++ ){
        printf ("%d: %e %e\n", i, REAL(data,i),IMAG(data,i));
        
        module[i]= sqrt(REAL(data,i)*REAL(data,i) + IMAG(data,i)*IMAG(data,i));
    }


    for (i = 0; i < 5; i++){
        for (j=i, j< 10, j++){
        max=max*module[j]
    }
        if (module[i]> max){
            max = (module[i]);
            ind = i;
        }
    }

    

    printf ("%f\n %i\n",max,ind);

    gsl_fft_complex_wavetable_free (wavetable);
    gsl_fft_complex_workspace_free (workspace);

    return 0;
}
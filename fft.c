//TRANSFORMEE DE FOURIER 

#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>
 
double PI;
typedef double complex cplx;
 
void _fft(cplx buf[], cplx out[], int n, int step)
{
	if (step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);
 
		for (int i = 0; i < n; i += 2 * step) {
			cplx t = cexp(-I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}
 
void fft(cplx buf[], int n)
{
	cplx out[n];
	for (int i = 0; i < n; i++) out[i] = buf[i];
 
	_fft(buf, out, n, 1);
}
 
 
void show(const char * s, cplx buf[]) {
	printf("%s", s);
	for (int i = 0; i < 8; i++)
		if (!cimag(buf[i]))
			printf("%g ", creal(buf[i]));
		else
			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
}
 
int main()
{
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

   	cplx* tab;
   	tab = malloc(sizeof(double)*N);

   	int i=0;
   	double d;
   	while (!feof(sgnl)){
   		fscanf(sgnl,"%lf", &d);
   		tab[i]= d;
   		i=i+1;
   		//printf("%f %d\n", d, i);
   	}


	/*PI = atan2(1, 1) * 4;
	cplx buf[] = {1, 1, 1, 1, 0, 0, 0, 0};
 
	show("Data: ", buf);
	fft(buf, 8);
	show("\nFFT : ", buf);*/

	PI = atan2(1, 1) * 4;
	//cplx buf[];
 
	show("Data: ", tab);
	fft(tab, 8);
	show("\nFFT : ", tab);
 
	return 0;
}

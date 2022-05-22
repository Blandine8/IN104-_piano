#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>




struct wavfile //définit la structure de l entete d un wave
{
    char        id[4];          // doit contenir "RIFF"
    int         totallength;        // taille totale du fichier moins 8 bytes
    char        wavefmt[8];     // doit etre "WAVEfmt "
    int         format;             // 16 pour le format PCM
    short       pcm;              // 1 for PCM format
    short       channels;         // nombre de channels
    int         frequency;          // frequence d echantillonage
    int         bytes_per_second;   // nombre de bytes par secondes
    short       bytes_by_capture;
    short       bits_per_sample;  // nombre de bytes par echantillon
    char        data[4];        // doit contenir "data"
    int         bytes_in_data;      // nombre de bytes de la partie data
};



int main(int argc, char *argv[])
{


    int i=0;
    unsigned int nbech=0; //nombre d echantillons extraits du fichier audio
    char fichieraudio[100];
    char fichierdat[100];
    float filtre_freq, filtre_large;


    /*---------------------selection du fichier audio-------------------------------*/
    printf ("entrer le nom du fichier audio a extraire en data :\n");
    scanf("%s", fichieraudio);
    printf ("nom du fichier : %s\n", fichieraudio);
    sprintf (fichierdat,"%s.dat", fichieraudio);
    /*--------------fin de selection du fichier audio-------------------------------*/



    /*---------------------ouverture du wave----------------------------------------*/
    FILE *wav = fopen(fichieraudio,"rb"); //ouverture du fichier wave
    struct wavfile header; //creation du header

    if ( wav == NULL )
    {
        printf("\nne peut pas ouvrir le fichier demande, verifier le nom\n");
        printf("ne pas oublier l'extention .wav\n");
        exit(1);
    }
    /*---------------------fin de ouverture du wave---------------------------------*/



    /*---------------------lecture de l entete et enregistrement dans header--------*/
    //initialise le header par l'entete du fichier wave
    //verifie que le fichier posséde un entete compatible
    if ( fread(&header,sizeof(header),1,wav) < 1 )
    {
        printf("\nne peut pas lire le header\n");
        exit(1);
    }
    if (    header.id[0] != 'R'|| header.id[1] != 'I'|| header.id[2] != 'F'|| header.id[3] != 'F' )
    {
        printf("\nerreur le fichier n'est pas un format wave valide\n");
        exit(1);
    }
    if (header.channels!=1)
    {
        printf("\nerreur : le fichier n'est pas mono\n");
        exit(1);
    }
    /*----------------fin de lecture de l entete et enregistrement dans header-------*/

    /*---donne les caractéristiques de l'entête dans le terminal----*/
    printf("l'id est %s. \n",header.id);
    printf("La taille totale du fichier est %d +8 octets\n", header.totallength);
    printf("WAVEfmt = %s. \n", header.wavefmt);
    printf("format = %d\n", header.format);
    printf("pcm= %d\n", header.pcm);
    printf("nb_channel= %d\n", header.channels);
    printf("f_e= %d\n", header.frequency);
    printf("nb_octet par sec = %d\n", header.bytes_per_second);
    printf("octets by capture= %d\n", header.bytes_by_capture);
    printf("bits par echantillon= %d\n", header.bits_per_sample);
    printf("data= %s\n", header.data);
    printf("octects de la partie data= %d\n", header.bytes_in_data);
    /*-------------fin--------------------------------------------------------------*/




    /*-------------------------determiner la taille des tableaux---------------------*/
    //nbech=(header.bytes_in_data/header.bytes_by_capture);
    nbech=(header.totallength/header.bytes_per_second*header.frequency);
    printf("nb_ech=%d\n", nbech);
    /*------------------fin de determiner la taille des tableaux---------------------*/



    /*---------------------creation des tableaux dynamiques--------------------------*/
    float *donnee=NULL; //tableau de l'onde temporelle
    donnee=malloc( (nbech) * sizeof(float));
    if (donnee == NULL)
    {
        exit(0);
    }

    /*---------------------fin de creation des tableaux dynamiques-------------------*/



    /*---------------------initialisation des tableaux dynamiques--------------------*/
    for(i=0; i<nbech; i++)
    {
        donnee[i]=0;
    }
    /*---------------------fin de initialisation des tableaux dynamiques-------------*/



    /*---------------------remplissage du tableau tab avec les echantillons----------*/
    i=0;
    short value=0;
    FILE *dat=fopen("son.dat","w"); //fichier data des echantillons
//    FILE *dat2=fopen("fabs_son.dat","w");//fichier.dat des valeurs absolues des echantillons
    FILE *dat3=fopen(fichierdat,"w");
    while( fread(&value,(header.bits_per_sample)/8,1,wav) )
    {
        //lecture des echantillons et enregistrement dans le tableau
        donnee[i]=value;
        i++;
    }
    printf("\nnombre d'echantillons lus : %d\n",i);
    printf("nombre de valeurs sauvegardees %d\n",i);
    for (i=0; i<nbech; i++)
    {
        fprintf(dat,"%lf %lf\n", donnee[i], (1.*i/header.frequency));
//permet de sauvegarder le tableau dans le fichier data.dat pour vérification manuelle des données
//        fprintf(dat2,"%lf %lf\n", fabs(data[i]), (1.*i/header.frequency));
        fprintf(dat3,"%lf %lf\n", 20*log10(fabs(donnee[i])), (1.*i/header.frequency));
    }
    /*-----------------fin de remplissage du tableau avec les echantillons-----------*/






    /*---------------------liberation de la memoire----------------------------------*/
    //liberation de la ram des malloc

    free(donnee);
    donnee = NULL;
    fclose(wav);
//    fclose(dat);
//    fclose(dat2);
    fclose(dat3);
    /*---------------------fin de liberation de la memoire---------------------------*/



    return 0;
}

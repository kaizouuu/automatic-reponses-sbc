#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
//void cherche_dans_un_fichier(FILE*);


int main()
{
    char nomrech[100];
    int recherche=-1; //Initialisation à une valeur de base
    PERS p;
    DONNEE mail_utilisateur;
    FILE * repertoire=NULL;
    FILE * donnee=NULL;
    FILE * mot_clef=NULL;
    menu(repertoire,donnee,mot_clef,&p,&mail_utilisateur,nomrech,recherche);

    return 0;
}






/*void cherche_dans_un_fichier(FILE *donne)
{
    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX

    donne = fopen("test.txt", "r");

    if (donne != NULL)
    {
        fgets(chaine, TAILLE_MAX, donne); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
        printf("%s", chaine); // On affiche la chaîne

        fclose(donne);
    }

    return 0;
}*/



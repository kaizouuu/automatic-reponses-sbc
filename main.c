#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
//void cherche_dans_un_fichier(FILE*);


int main()
{
    char nomrech[TCHAINE];
    int recherche=-1;
    PERS p;
    DONNEE mail_utilisateur;
    FILE * repertoire=NULL;
    FILE * donnee=NULL;
    FILE * motclef=NULL;
    menu(repertoire,donnee,motclef,&p,&mail_utilisateur,nomrech,recherche);

    return 0;
}




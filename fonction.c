#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonction.h"

void menu(FILE *repertoire, FILE *donnee, FILE *motclef, PERS *p, DONNEE *mail_utilisateur, char *nomrech, int *recherche)
{
    char mdp_admin[60] = "mdp";
    int i;
    int v;
    char mot_de_passe[60];
    do
    {
        printf("********** Bienvenu dans le promgramme de reponse automatique du SBC ***********\n");
        printf("0 pour le mode administrateur\n");
        printf("1 pour le mode utilisateur\n");
        scanf("%d", &v);
        switch (v)
        {
        case 0:
            printf("entrer le mot de passe:");
            scanf("%s", mot_de_passe);
            if ((strcmp(mdp_admin, mot_de_passe)) == 0)
            {
                do
                {
                    printf("\n********** VOUS ETES DANS LE MODE ADMINISTATEUR **********\n");
                    printf(" 0 pour quitter le programme\n");
                    printf(" 1 pour inserer une personne dans le repertoire\n");
                    printf(" 2 pour afficher le repertoire\n");
                    printf(" 3 pour rechercher une coordonnée\n");
                    printf(" 4 pour supprimer une coordonnée\n");
                    printf(" 5 pour inserer un mot clef\n");
                    printf(" 6 pour afficher l'ensemble des mots clef\n");
                    printf(" 7 pour rechercher un mot cle\n");
                    printf(" 8 pour supprimer un mot cle\n");
                    scanf("%d", &i);

                    switch (i)
                    {
                    case 0:
                        break;
                    case 1:
                        saisir_repertoire(repertoire, p); //Pas besoin de mettre &p ici. Pouquoi ? Aucune idée. A investiguer
                        break;
                    case 2:
                        affichage_repertoire(repertoire);
                        break;
                    case 3:
                        printf("Saisissez un nom a rechercher\n");
                        scanf("%s", nomrech);
                        *recherche = rechercher_personne(repertoire, nomrech);
                        break;
                    case 4:
                        break;
                    case 5:
                        ajout_mot_clef(motclef); //Pas besoin de mettre &tab_mot_clef
                        break;
                    case 6:
                        afficher_mot_clef(motclef);
                        break;
                    case 7:
                        recherche_mot_clef(motclef);
                        break;
                    case 8:
                        supprimer_mot_clef(motclef);
                        break;
                    default:
                        break;
                    }
                } while (i != 0);
                break;
            }
            else
            {
                printf("Erreur de mot de passe\n");
                break;
            }

            case 1:
            printf ("\n********** VOUS ETES DANS LE MODE UTILISATEUR **********\n");
            saisie_DT_Obj(donnee,mail_utilisateur,repertoire,motclef,&recherche,nomrech);
            //cherche_dans_un_fichier(donnee);
        break;
    default : break;
    }
    }while (i != 0);
}

void saisir_repertoire(FILE *repertoire, PERS *p)
{

    printf("Entrez le nom de la personne de votre choix: \n");
    lire(p->NOM,60);
    printf("Entrez le prenom de cette personne : \n");
    lire(p->PRENOM,60);
    printf("Entrez le adresse mail de cette personne : \n");
    lire(p->AdresseMail,60);
    printf("Entrez le classement de cette personne : \n");
    lire(p->Classement,1000);
    repertoire = fopen("repertoire.txt", "a+");
    fprintf(repertoire, "\n%s \n%s \n%s \n%s", p->NOM, p->PRENOM, p->AdresseMail, p->Classement);
    fclose(repertoire);
}
void affichage_repertoire(FILE *repertoire)
{
    PERS p;
    repertoire = fopen("repertoire.txt", "a+");
    while (fscanf(repertoire, "%s %s %s %s", p.NOM, p.PRENOM, p.AdresseMail, p.Classement) != EOF)
    {
        printf("\nAffichage du repertoire: Nom=%s, Prenom=%s, AdresseMail=%s, Classement=%s\n", p.NOM, p.PRENOM, p.AdresseMail, p.Classement);
    }
    fclose(repertoire);
}

void ajout_mot_clef(FILE *fichier) //Fonction ajoutant un seul mot clef
{
	MOT_CLEF tab_mot_clef;
	printf("Veuillez saisir le mot-clef à ajouter: ");
	lire(tab_mot_clef.mot,60);
	printf("\nVeuillez saisir l'annexe de votre mot-clef à ajouter: ");
	lire(tab_mot_clef.annexe_mot,500);
	fichier=fopen("mot_clef.txt","a+");
	fprintf(fichier,"\n%-20s\t%d ",tab_mot_clef.mot, tab_mot_clef.annexe_mot);
    fclose(fichier);
}
void afficher_mot_clef(FILE * fichier) //Afficher tous les mots-clefs présents dans le fichier mot_clef.txt
{	
	//***On réorganise le fichier et on le rend plus jolie***
	MOT_CLEF p;
	fichier=fopen("mot_clef.txt","a+");
	fseek(fichier, 0, SEEK_SET);
	FILE * fichier_temp=NULL;
	fichier_temp=fopen("temp.txt","w+");
	
	while (fscanf(fichier,"%s %d", p.mot, &p.annexe_mot) !=EOF)
		fprintf(fichier_temp, "\n%-20s %10d", p.mot, p.annexe_mot);
		
	fclose(fichier);
	fclose(fichier_temp);
	remove("mot_clef.txt");
	rename("temp.txt","mot_clef.txt");
	
	//***Affichage du fichier caractère par caractère***
	char car;
	fichier=fopen("mot_clef.txt","a+");

    printf("\n\nAffichage des mots clefs: \n");

    car = fgetc(fichier);
	while (car != EOF)    //Tant que le caractère lu n'est pas la fin du fichier, on continue de l'afficher
	{
		printf ("%c", car);
		car = fgetc(fichier);
	}
	fclose(fichier);
	printf("\n\n");
	
}

void recherche_mot_clef(FILE *fichier)
{
    /*Cette fonction a pour but de rechercher un mot en lisant le fichier
	 * D'abord on demande le mot recherché à l'utilisateur
	 * Ensuite on lit le fichier et on rentre chaque mot-clef et son annexe dans une structure
	 * On effectue la comparaision et on affiche si nécessaire
	 */
    MOT_CLEF p;
	char mot_recherche[60];
	int indicateur=0;
	printf("\n\nEntrez le mot recherché : ");
	scanf("%s", mot_recherche);
	fichier=fopen("mot_clef.txt","a+");
	fseek(fichier, 0, SEEK_SET);
	while (fscanf(fichier,"%s %d", p.mot, &p.annexe_mot) !=EOF)
		{
				
            if (strcmp(p.mot,mot_recherche)==0)
			{
				printf("\nMot-clef: %s\tAnnexe: %d\n",p.mot,p.annexe_mot);
				indicateur=1;
			}
		}
	if(indicateur==0)
		printf("\nErreur: Ce mot-clef n'existe pas.\n");
	fclose(fichier);
	
	
}

void supprimer_mot_clef(FILE * fichier)
{
	MOT_CLEF p;
	char mot_a_supprimer[60];
	int indicateur=0;
	printf("\n\nEntrez le mot à supprimer : ");
	scanf("%s", mot_a_supprimer);
	fichier=fopen("mot_clef.txt","a+");
	fseek(fichier, 0, SEEK_SET);
	FILE * fichier_temp=NULL;
	fichier_temp=fopen("temp.txt","w+");
	
	while (fscanf(fichier,"%s %s", p.mot, &p.annexe_mot) !=EOF)
		{
            if (strcmp(p.mot,mot_a_supprimer)!=0)
			{
				fprintf(fichier_temp, "\n%-20s %s", p.mot, p.annexe_mot);
			}
			else
			{
				indicateur=1;
			}	
		}
	if(indicateur==0)
		printf("\nErreur: Ce mot-clef n'existe pas.\n");
	fclose(fichier);
	fclose(fichier_temp);
	remove("mot_clef.txt");
	rename("temp.txt","mot_clef.txt");

}



void saisie_DT_Obj(FILE *donne, DONNEE* mail_utilisateur,FILE *repertoire,FILE *motclef, int *recherche,char *nomrech)
{
    printf ("Veuillez saisir votre adresse mail : \n");
    getchar (); //vider le buffer
    lire(mail_utilisateur->EM,60);
    printf ("Veuillez saisir l'asresse mail de votre destinataire : \n");
    lire(mail_utilisateur->DT,60);
    printf ("Entrez l'objet du mail : \n");
    lire(mail_utilisateur->OBJ,60);
    printf ("Entrez le message : \n");
    lire(mail_utilisateur->CORPS,1000);
    donne=fopen("donne.txt","a+");
    fprintf(donne,"\n%s \n%s \n%s \n%s",mail_utilisateur->EM,mail_utilisateur->DT,mail_utilisateur->OBJ ,mail_utilisateur->CORPS);
    strcpy(nomrech, mail_utilisateur->EM);
    *recherche=rechercher_EM(repertoire,nomrech);
    //recherche_mot(donne,motclef);
    fclose(donne);
}
int rechercher_personne(FILE *repertoire, char *nomrech)
{
    int trouve = 0;
    char classement_temp[TMAX]; // servira a stocker la chaine de caractere representant le num de la structure
    PERS p;
    repertoire = fopen("repertoire.txt", "a+");
    fseek(repertoire, 0, SEEK_SET);

    while (fscanf(repertoire, "%s %s %s %s", p.NOM, p.PRENOM, p.AdresseMail, classement_temp) != EOF)
    {
        if (strcmp(p.NOM, nomrech) == 0)
        {
            strcpy(p.Classement, classement_temp);
            printf("\nAffichage de la structure: Nom=%s, Prenom=%s, AdresseMail=%s, Classement=%s", p.NOM, p.PRENOM, p.AdresseMail, p.Classement);
            trouve = (strlen(classement_temp)); //determine la taille de la chaine de caractere num_temp pour la retourner et connaitre le nombre d'octect pour se deplacer
            fclose(repertoire);
            return trouve;
        }
    }
    return trouve;
}
int rechercher_EM(FILE *repertoire, char *nomrech)
{
    int trouve=0;
    char classement_temp[TMAX]; // servira a stocker la chaine de caractere representant le num de la structure
    PERS p;
    repertoire=fopen("repertoire.txt","a+");
    fseek(repertoire, 0, SEEK_SET);
    while (fscanf(repertoire,"%s %s %s %s", p.NOM, p.PRENOM,p.AdresseMail, classement_temp) !=EOF)
    {
        
        if (strcmp(p.AdresseMail,nomrech)==0)
        {
            strcpy(p.Classement,classement_temp);
            printf("\nProfil reconnu !\n");
            trouve=(strlen(classement_temp)); //determine la taille de la chaine de caractere num_temp pour la retourner et connaitre le nombre d'octect pour se deplacer
            fclose(repertoire);
            return trouve;
        }
        else
        {
            printf("\nProfil non reconnu veuillez enregistrer votre  profil");
        }
        
    }
    return trouve;
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur) // Fonction pour palier au Pb de Retour Chariot de fgets et pour que la recherche de mot cle fonctionne
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}
/*void recherche_mot(FILE *donne,FILE *motclef)
{
    int trouve=0;
    char classement_temp[TMAX]; // servira a stocker la chaine de caractere representant le num de la structure
    char mot_trouve[500];
    MOT_CLEF p;
    DONNEE mail_utilisateur;
    int i=0;
    int cpt=0;
    while (mail_utilisateur.CORPS !='\0')                                           //fonction pour compter le nbre de mot dans la  Corps de mail
    {                                                                               //
                                                                                    //
        if (mail_utilisateur.CORPS ==' '){                                          //
            while((mail_utilisateur.CORPS ==' ') && (mail_utilisateur.CORPS !='\0')){   //
                                                                                //
                if(mail_utilisateur.CORPS !=' ')
                {cpt++;}                            //
            }                                                                       //
        }                                                                           //
        i++;                                                                        //
    } 
    printf("%d",cpt);                                                                              //
    motclef=fopen("mot_clef.txt","a+");
    donne=fopen("donne.txt","a+");
    fseek(motclef, 0, SEEK_SET);
    fseek(donne, 0, SEEK_SET);

    while (fscanf(motclef,"%s %s", p.mot, p.annexe_mot) !=EOF)
    {
        while(fscanf(donne,"%s %s %s %s",mail_utilisateur.EM, mail_utilisateur.DT, mail_utilisateur.OBJ, mail_utilisateur.CORPS) != EOF)
        {    
            for (i=0; i<= cpt; i++)
            {    
                if (strstr(mail_utilisateur.CORPS,p.mot)==0)
                {
                    mot_trouve[i]=p.annexe_mot[i];
                    printf("\nProfil reconnu !\n");
                    trouve=(strlen(classement_temp)); //determine la taille de la chaine de caractere num_temp pour la retourner et connaitre le nombre d'octect pour se deplacer
                    fclose(motclef);
                    
                    return trouve;
                }
            }
        }                    
    }
printf(" reponse: %s", p.annexe_mot);

fclose(motclef);

}
*/

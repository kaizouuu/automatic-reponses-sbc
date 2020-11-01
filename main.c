#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TMAX 1000 // Tableau de taille 1000

typedef struct {
    char NOM[60];
    char PRENOM[60];
    char AdresseMail[60];
    char Classement[TMAX];
}PERS;

typedef struct {

    char EM[60];
    char DT[60];
    char OBJ[60];
    char CORPS[1000];

}DONNEE;

typedef struct {
    char mot[60];
    int annexe_mot;
}MOT_CLEF;


void menu(FILE*,FILE*,FILE*,PERS*,MOT_CLEF*,DONNEE*,char*,int*);

void saisir_repertoire (FILE*, PERS*); //fonction pour saisir les personne dans le fichier repertoire     //definition des fonctions
void affichage_repertoire(FILE*);  //fonction qui affiche le repertoire
int rechercher_personne(FILE*, char*); //fonction qui cherche une personne à partir de son nom dans le repertoire

void ajout_mot_clef(FILE *, MOT_CLEF *);//fonction pour saisir un nouveau mot cle
void afficher_mot_clef(FILE *);//fonction pour afficher le repertoire des mot cle

void saisie_DT_Obj(FILE*, DONNEE*);  //fonction pour saisir les caractéristisques du mail (emetteur destinataire obj...)
//void cherche_dans_un_fichier(FILE*);


int main()
{
    char nomrech[100];
    int recherhce;
    PERS p;
    DONNEE mail_utilisateur;
    MOT_CLEF tab_mot_clef;
    FILE * repertoire=NULL;
    FILE * donnee=NULL;
    FILE * mot_clef=NULL;
    menu(repertoire,donnee,mot_clef,&p,&tab_mot_clef,&mail_utilisateur,&nomrech,&recherhce);

    return 0;
}


void menu(FILE *repertoire,FILE *donnee,FILE *mot_clef,PERS *p, MOT_CLEF *tab_mot_clef,DONNEE *mail_utilisateur,char *nomrech,int *recherche)
{
    char mdp_admin[60]="mdp";
    int i;
    int v;
    char mot_de_passe[60];
    do{
    printf("********** Bienvenu dans le promgramme de reponse automatique du SBC ***********\n");
    printf("0 pour le mode administrateur\n");
    printf("1 pour le mode utulisateur\n");
    scanf("%d",&v);
    switch(v)
    {
    case 0:
    printf ("entrer le mot de passe:");
    scanf("%s",mot_de_passe);
    if ((strcmp(mdp_admin,mot_de_passe))==0)
    {
        do{
        printf("\n********** VOUS ETES DANS LE MODE ADMINISTATEUR **********\n");
        printf (" 0 pour quitter le programme\n");
        printf (" 1 pour inserer une personne dans le repertoire\n");
        printf (" 2 pour afficher le repertoire\n");
        printf (" 3 pour rechercher une coordonnée\n");
        printf (" 4 pour supprimer une coordonnée\n");
        printf (" 5 pour inserer un mot clef\n");
        printf (" 6 pour afficher l'ensemble des mots clef\n");
        printf (" 7 pour rechercher un mot cle\n");
        printf (" 8 pour supprimer un mot cle\n");
        scanf("%d",&i);

        switch(i)
        {
            case 0: break;
            case 1:
                    saisir_repertoire(repertoire,p); //Pas besoin de mettre &p ici. Pouquoi ? Aucune idée. A investiguer
                    break;
            case 2:
                    affichage_repertoire(repertoire);
                    break;
            case 3:
                    printf("Saisissez un nom a rechercher\n");
                    scanf("%s",nomrech);
                    recherche=rechercher_personne(repertoire,nomrech);
                    break;
            case 4: break;
            case 5:
					ajout_mot_clef(mot_clef, tab_mot_clef); //Pas besoin de mettre &tab_mot_clef
					break;
            case 6:
					afficher_mot_clef(mot_clef);
					break;
            case 7: break;
            case 8: break;
            default : break;
        }
        }while (i != 0);
        break;
    }
    else
    {
        printf ("Erreur de mot de passe\n");
        break;
    }
    case 1:
    printf ("\n********** VOUS ETES DANS LE MODE UTILISATEUR **********\n");
    saisie_DT_Obj(donnee, mail_utilisateur);
    //cherche_dans_un_fichier(donnee);
        break;
    default : break;
    }
    }while (i != 0);
}

void saisir_repertoire (FILE* repertoire, PERS *p)
{

            printf ("Entrez le nom de la personne de votre choix: \n");
            scanf ("%s",p->NOM);
            printf ("Entrez le prenom de cette personne : \n");
            scanf ("%s",p->PRENOM);
            printf ("Entrez le adresse mail de cette personne : \n");
            scanf ("%s",p->AdresseMail);
            printf ("Entrez le classement de cette personne : \n");
            scanf ("%s",p->Classement);
            repertoire=fopen("repertoire.txt","a+");
            fprintf(repertoire,"\n%s \n%s \n%s \n%s",p->NOM, p->PRENOM, p->AdresseMail , p->Classement);
            fclose(repertoire);

}
void affichage_repertoire(FILE *repertoire)
{
    PERS p;
    repertoire=fopen("repertoire.txt","a+");
    while(fscanf(repertoire,"%s %s %s %s", p.NOM, p.PRENOM, p.AdresseMail, p.Classement) !=EOF)
        printf("\nAffichage du repertoire: Nom=%s, Prenom=%s, AdresseMail=%s, Classement=%s\n", p.NOM,p.PRENOM, p.AdresseMail, p.Classement);
        fclose(repertoire);
}

void ajout_mot_clef(FILE * fichier, MOT_CLEF *tab_mot_clef) //Fonction ajoutant un seul mot clef
{
	printf("Veuillez saisir le mot-clef à ajouter: ");
	scanf("%s",tab_mot_clef->mot);
	printf("Veuillez saisir l'annexe de votre mot-clef à ajouter: ");
	scanf("%d",&tab_mot_clef->annexe_mot);
	fichier=fopen("mot_clef.txt","a+");
	fprintf(fichier,"\n%-20s\t%d ",tab_mot_clef->mot, tab_mot_clef->annexe_mot);
    fclose(fichier);
}
void afficher_mot_clef(FILE * fichier) //Afficher tous les mots-clefs présents dans le fichier mot_clef.txt
{
	char car;
	fichier=fopen("mot_clef.txt","a+");

    printf("\n\nAffichage des mots clefs: ");

    car = fgetc(fichier);
	while (car != EOF)    //Tant que le caractère lu n'est pas la fin du fichier, on continue de l'afficher
	{
		printf ("%c", car);
		car = fgetc(fichier);
	}
	fclose(fichier);
	printf("\n\n");
}
void saisie_DT_Obj(FILE *donne, DONNEE* mail_utilisateur)
{
        printf ("Veuillez saisir votre adresse mail : \n");
            scanf ("%s",mail_utilisateur->EM);
            printf ("Veuillez saisir l'asresse mail de votre destinataire : \n");
            scanf ("%s",mail_utilisateur->DT);
            printf ("Entrez l'objet du mail : \n");
            scanf ("%s",mail_utilisateur->OBJ);
            printf ("Entrez le message : \n");
            scanf ("%s",mail_utilisateur->CORPS);
            donne=fopen("donne.txt","a+");
            fprintf(donne,"\n%s \n%s \n%s \n%s",mail_utilisateur->EM,mail_utilisateur->DT,mail_utilisateur->OBJ ,mail_utilisateur->CORPS);
            fprintf(donne, "Le Monsieur qui utilise le programme");
            fclose(donne);
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
int rechercher_personne(FILE *repertoire, char *nomrech)
{
	int trouve=0;
    char classement_temp[TMAX]; // servira a stocker la chaine de caractere representant le num de la structure
	PERS p;
	repertoire=fopen("repertoire.txt","a+");
	fseek(repertoire, 0, SEEK_SET);
	while (fscanf(repertoire,"%s %s %s %s", p.NOM, p.PRENOM,p.AdresseMail, classement_temp) !=EOF)
		{
            if (strcmp(p.NOM,nomrech)==0)
			{
                strcpy(p.Classement,classement_temp);
				printf("\nAffichage de la structure: Nom=%s, Prenom=%s, AdresseMail=%s, Classement=%s", p.NOM, p.PRENOM, p.AdresseMail, p.Classement);
				trouve=(strlen(classement_temp)); //determine la taille de la chaine de caractere num_temp pour la retourner et connaitre le nombre d'octect pour se deplacer
				fclose(repertoire);
				return trouve;
			}
		}
	return trouve;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonction.h"

void menu(FILE *repertoire, FILE *donnee, FILE *motclef, PERS *p, DONNEE *mail_utilisateur, char *nomrech, int recherche)
{
    char mdp_admin[TCHAINE] = "mdp";
    int i;
    int v;
    char mot_de_passe[TCHAINE];
    do
    {
        printf("********** Bienvenu dans le promgramme de reponse automatique du SBC ***********\n");
        printf("0 pour le mode administrateur\n");
        printf("1 pour le mode utilisateur\n");
        printf("2 sortir du programme\n");
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
						printf ("\n********** AU REVOIR **********\n\n");
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
                        recherche = rechercher_personne(repertoire, nomrech);
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
                //saisie_DT_Obj(donnee,mail_utilisateur,repertoire,motclef,recherche,nomrech);
                fonction_utilisateur(donnee, mail_utilisateur, motclef);
                break;
            case 2:
                printf ("\n********** AU REVOIR **********\n\n");
                exit(0);
                break;
    default : break;
    }
    }while (v!= 0);
}

void saisir_repertoire(FILE *repertoire, PERS *p)
{
	printf("Entrez le prenom de cette personne : \n");
	getchar();
    lire(p->PRENOM,TCHAINE);
    printf("Entrez le nom de la personne de votre choix: \n");
    lire(p->NOM,TCHAINE);
    printf("Entrez le adresse mail de cette personne : \n");
    lire(p->AdresseMail,TCHAINE);
    printf("Entrez le classement de cette personne : \n");
    lire(p->Classement,TMAX);
    repertoire = fopen("repertoire.txt", "a+");
    fprintf(repertoire, "\n%s \n%s \n%s \n%s", p->NOM, p->PRENOM, p->AdresseMail, p->Classement);
    fclose(repertoire);
}
void affichage_repertoire(FILE *repertoire)
{
    PERS p;
    repertoire = fopen("repertoire.txt", "a+");
    printf("\nAffichage du répertoire: \n");
    while (fscanf(repertoire, "%s %s %s %s", p.NOM, p.PRENOM, p.AdresseMail, p.Classement) != EOF)
    {
        printf("Nom=%s, Prenom=%s, AdresseMail=%s, Classement=%s\n", p.NOM, p.PRENOM, p.AdresseMail, p.Classement);
    }
    fclose(repertoire);
}

/*Cette fonction a pour but d'ajouter un mot clef 
 * et sa réponse associé à notre fichier mot_clef.txt
 */
void ajout_mot_clef(FILE *fichier) 
{
	MOT_CLEF tab_mot_clef;
	printf("Veuillez saisir le mot-clef à ajouter (MOINS DE 30 CARACTERES): ");
    getchar();
	lire(tab_mot_clef.mot,TMOT);
	printf("\nVeuillez saisir la réponse appropriée (PLUS DE 30 CARACTERES): ");
	lire(tab_mot_clef.reponse,TMAX);
	fichier=fopen("mot_clef.txt","a+");
	fseek(fichier, 0, SEEK_END);
	fprintf(fichier,"\n%s\n%s\n",tab_mot_clef.mot, tab_mot_clef.reponse);
    fclose(fichier);
}

/*Cette fonction a pour but d'afficher tous les mot-clefs ainsi que les réponses associées
 * contenues dans mot_clef.txt. Ici on se contentera de recopier le fichier sur la sortie terminal
 * caractère par caractères en utilisant fgetc
 */
void afficher_mot_clef(FILE * fichier) 
{	
	char car;                                    //variable stockant le caractère "actuel"
	fichier=fopen("mot_clef.txt","a+");          //ouverture du fichier
	fseek(fichier, 0, SEEK_SET);

    printf("\n\nAffichage des mot-clefs et des réponses associées: \n");

    car = fgetc(fichier);                   //On commence à lire le fichier caractère par caractère
	while (car != EOF)    //Tant que le caractère lu n'est pas la fin du fichier, on continue 
	{
		printf ("%c", car);     //On afficher le caractère stocké
		car = fgetc(fichier);   //On lit le caractère suivant
	}
	
	fclose(fichier);
	printf("\n\n");
}

     /*Cette fonction a pour but de rechercher un mot en lisant le fichier
	 * D'abord on demande le mot recherché à l'utilisateur
	 * Ensuite on lit le fichier et on rentre chaque mot-clef et son annexe dans une structure
	 * On effectue la comparaision et on affiche si nécessaire
	 */
void recherche_mot_clef(FILE *fichier)
{
    MOT_CLEF p;
	char mot_recherche[TMOT];
	char ligne[TMAX];
	int indicateur=0;
	printf("\n\nEntrez le mot-clef recherché (MOINS DE 30 CARACTERES): ");
	scanf("%s", mot_recherche);
	fichier=fopen("mot_clef.txt","a+");
	fseek(fichier, 0, SEEK_SET);
	
	ici:
	while(fgets(ligne,TMAX,fichier)!=NULL)
	{	
		if (ligne[0]=='\n')
		{
			goto ici;
		}
		else
		{
			sscanf(ligne,"%s",p.mot);
			fgets(p.reponse,TMAX,fichier);
			if (strcmp(p.mot,mot_recherche)==0)
			{
				indicateur=1;
				printf("\nMot-clef: %s\nReponse: %s\n",p.mot,p.reponse);
			
			}
		}
	}
	
	if (indicateur==0)
		printf("\nCe mot-clef n'existe pas !\n");
	fclose(fichier);
	
	
}

void supprimer_mot_clef(FILE * fichier)
{
	MOT_CLEF p;
	char mot_a_supprimer[TMAX];
	int indicateur=0;
	char ligne[TMAX];
	printf("\n\nEntrez le mot-clef à supprimer : ");
	scanf("%s", mot_a_supprimer);
	fichier=fopen("mot_clef.txt","a+");
	fseek(fichier, 0, SEEK_SET);
	FILE * fichier_temp=NULL;
	fichier_temp=fopen("temp.txt","w+");
	
	retour:
	while(fgets(ligne,TMAX,fichier)!=NULL)
	{	
		if (ligne[0]=='\n')
		{
			fprintf(fichier_temp,"\n");
		}
		else
		{
			sscanf(ligne,"%s",p.mot);
			fgets(p.reponse,TMAX,fichier);
			if (strcmp(p.mot,mot_a_supprimer)==0)
			{
				indicateur=1;
				fgets(p.reponse,TMAX,fichier);
				goto retour;
			}
			else
			{
				fprintf(fichier_temp, "%s\n%s",p.mot,p.reponse);
			}
		}
	}
	
	if (indicateur==0)
		printf("\nCe mot-clef n'existe pas !\n");
	
	
	fclose(fichier);
	fclose(fichier_temp);
	remove("mot_clef.txt");
	rename("temp.txt","mot_clef.txt");

}



/*void saisie_DT_Obj(FILE *donne, DONNEE* mail_utilisateur,FILE *repertoire,FILE *motclef, int recherche,char *nomrech)
{
    printf ("Veuillez saisir votre adresse mail : \n");
    getchar (); //vider le buffer
    lire(mail_utilisateur->EM,TCHAINE);
    printf ("Veuillez saisir l'adresse mail de votre destinataire : \n");
    lire(mail_utilisateur->DT,TCHAINE);
    printf ("Entrez l'objet du mail : \n");
    lire(mail_utilisateur->OBJ,TCHAINE);
    printf ("Entrez le message : \n");
    lire(mail_utilisateur->CORPS,TMAX);
    donne=fopen("donne.txt","a+");
    fprintf(donne,"\n%s \n%s \n%s \n%s\n",mail_utilisateur->EM,mail_utilisateur->DT,mail_utilisateur->OBJ ,mail_utilisateur->CORPS);
    strcpy(nomrech, mail_utilisateur->EM);
    recherche=rechercher_EM(repertoire,nomrech);
    //recherche_mot(donne,motclef);
    fclose(donne);
}*/
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
            printf("\nVotre adresse mail n'est pas enregiste veuillez contacter le SBC\n");
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
    char mot_trouve[TMAX];
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
    printf("%d",cpt);    
                                                                              
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

}*/
void fonction_utilisateur(FILE *donne, DONNEE* mail_utilisateur, FILE *motclef)
{
	MOT_CLEF p;
    donne=fopen("donne.txt","a+");
    motclef=fopen("mot_clef.txt","a+");
	fseek(motclef, 0, SEEK_SET);
	char ligne[TMAX];
	int indicateur=0;
   
   
    printf ("Veuillez saisir votre adresse mail : \n");
    getchar ();                                                                                 //vider le buffer
    lire(mail_utilisateur->EM,TCHAINE);
    printf ("Veuillez saisir l'adresse mail de votre destinataire : \n");
    lire(mail_utilisateur->DT,TCHAINE);
    printf ("Entrez l'objet du mail : \n");
    lire(mail_utilisateur->OBJ,TCHAINE);
    printf ("Entrez le corps du mail : \n");
    lire(mail_utilisateur->CORPS,TMAX);
    fprintf(donne,"\n%s \n%s \n%s \n%s\n",mail_utilisateur->EM,mail_utilisateur->DT,mail_utilisateur->OBJ ,mail_utilisateur->CORPS);	
	
	
	arriere:
	while(fgets(ligne,TMAX,motclef)!=NULL)
	{	
		if (ligne[0]=='\n')
		{
			goto arriere;
		}
		else
		{
			sscanf(ligne,"%s",p.mot);
			fgets(p.reponse,TMAX,motclef);
			if (strstr(mail_utilisateur->CORPS,p.mot)!=NULL)
			{
				indicateur=1;
				printf("La réponse est: %s", p.reponse);
			}
		}
	}
	
	if (indicateur==0)
		printf("\nCe mot-clef n'existe pas !\n");
	fclose(motclef);
    fclose(donne);
}


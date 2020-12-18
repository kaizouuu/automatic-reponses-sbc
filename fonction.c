#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonction.h"

void menu(FILE *repertoire, FILE *donnee, FILE *motclef, PERS *p, DONNEE *mail_utilisateur, char *nomrech, int recherche)
{
    /*
     * Menu principale de lancement des fonctions
     */
    char mdp_admin[TCHAINE] = "mdp";
    int i;
    int v;
    char mot_de_passe[TCHAINE];
    menu:
    do
    {
        printf("********** Bienvenu dans le promgramme de reponse automatique du SBC ***********\n");
        /*
         * Choix du mode
         */
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
                    /*
                     * Choix adminitrateur
                     */
                    printf("\n********** VOUS ETES DANS LE MODE ADMINISTATEUR **********\n");
                    printf(" 0 pour retourner au premier menu\n");
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
						goto menu; //Ce goto nous permet de retourner sur le premier menu
                        break;
                    case 1:
                        saisir_repertoire(repertoire, p); 
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
                        printf("Saisissez un nom a suprimer\n");
                        scanf("%s", nomrech);
                        supprime_personne(repertoire, nomrech);
                        break;
                    case 5:
                        ajout_mot_clef(motclef); 
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
                /*
                 * Lancement de l'aplication utilisateur
                 */
                printf ("\n********** VOUS ETES DANS LE MODE UTILISATEUR **********\n");
                fonction_utilisateur(donnee, repertoire, motclef, mail_utilisateur, nomrech);
                break;
            case 2:
                /*
                 * Sortir du programme
                 */
                printf ("\n********** AU REVOIR **********\n\n");
                exit(0);
                break;
    default : break;
    }
    }while (v!= 0);
}

void saisir_repertoire(FILE *repertoire, PERS *p)
{
    
    /* Cette fonction repuère les informations (nom, prenom, adresse mail et Clasmment)
     * Elle recupère exactement les informations taper au clavier avec la fonction Lire
     * Elle ouvre et ferme le fichier pour stocker les informations
     */
	printf("Entrez le prenom de cette personne : \n");
	getchar(); /*Vider buffer*/
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
    /* Cette fonction vient faire une boucle sur le repertoire pour afficher la stucture
     * Elle ouvert le fichier et le ferme en fin de Lecture
     */
    PERS p;
    repertoire = fopen("repertoire.txt", "a+");
    printf("\nAffichage du répertoire: \n");
    while (fscanf(repertoire, "%s %s %s %s", p.NOM, p.PRENOM, p.AdresseMail, p.Classement) != EOF)
    {
        printf("Nom=%s, Prenom=%s, AdresseMail=%s, Classement=%s\n\n", p.NOM, p.PRENOM, p.AdresseMail, p.Classement);
    }
    fclose(repertoire);
}

int rechercher_personne(FILE *repertoire, char *nomrech)
{
    /* Cette fonction prend en parametre un nom à rechercher
     * Elle vient lire toutes les chaine de caractere contenu dans le fichier
     * Elle compare tout les nom au parametre passer en entre
     * Si il sont égaux affiche la structure associer
     * Sinon affiche l'adhérent n'existe pas
     */
    int trouve = 0;
    int indicateur=0;
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
            indicateur=1;
            return trouve;
        }
    }
    if (indicateur==0)
    {
		printf("\nCette personne n'est pas présente dans le répertoire !\n\n");
	}
    
    return trouve;
}

void supprime_personne(FILE *fichier, char *nomrech)
{
    /* Cette fonction nous permet de supprimer une personne de notre répertoire.
     * Pour cela on saisie le nom de la personne à supprimer.
     * On va ensuite comparer chaque contact avec ce nom, si le contact n'est pas le bon il est recopié dans un fichier temporaire
     * Si le contact est le bon alors il ne sera pas recopié. Ainsi, nous pouvons supprimé le premier fichier et garder le second
     * qui ne comporte pas la personne saisie
     */
    PERS p;
    int indicateur=0;
    fichier=fopen("repertoire.txt","a+");
    fseek(fichier, 0, SEEK_SET);
    FILE * fichier_temp=NULL;
    fichier_temp=fopen("temp.txt","w+");

    while (fscanf(fichier,"%s %s %s %s", p.NOM, p.PRENOM,p.AdresseMail,p.Classement) !=EOF) //On charge les élements du fichier répertoire dans notre structure PERS afin de faire la comparaison
    {
        if (strcmp(p.NOM,nomrech)!=0) //Comparaison entre le nom de la personne à supprimer et le nom actuellement dans la structure PERS
        {
            fprintf(fichier_temp, "\n%-20s %10s %10s %10s", p.NOM, p.PRENOM,p.AdresseMail,p.Classement); //Si ce n'est pas la bonne personne, on la recopie dans le nouveau fichier
        }
        else
        {
			printf("\nPersonne supprimée de notre répertoire.\n");
            indicateur=1; //Nous permet de savoir si la personne à été trouvé et ignoré (non recopié dans le nouveau fichier)
        }
    }
    if(indicateur==0)
        printf("\nErreur: Cette personne n'existe pas.\n");
    fclose(fichier); 
    fclose(fichier_temp);
    remove("repertoire.txt");              //On supprime le vieux fichier
    rename("temp.txt","repertoire.txt");   //On renome le nouveau fichier
}


void ajout_mot_clef(FILE *fichier)
{
    /* Cette fonction a pour but d'ajouter un mot clef et sa réponse associée à notre fichier mot_clef.txt
     * Pour cela nous utilisons la structure MOT_CLEF pour stocker ce que l'on saisie avant de l'ajouter à notre fichier 
     */
	MOT_CLEF tab_mot_clef;
	printf("Veuillez saisir le mot-clef à ajouter (MOINS DE 30 CARACTERES): ");     //On saisie le mot-clef
    getchar();
	lire(tab_mot_clef.mot,TMOT);                                                  
	printf("\nVeuillez saisir la réponse appropriée (PLUS DE 30 CARACTERES): ");    //On saisie la réponse associée
	lire(tab_mot_clef.reponse,TMAX);
	fichier=fopen("mot_clef.txt","a+");
	fseek(fichier, 0, SEEK_END);
	fprintf(fichier,"\n%s\n%s\n",tab_mot_clef.mot, tab_mot_clef.reponse);           //On recopie le contenue de notre structure dans le fichier
    fclose(fichier);
}

void afficher_mot_clef(FILE * fichier) 
{
    /*
     * Cette fonction a pour but d'afficher tous les mot-clefs ainsi que les réponses associées
     * contenues dans mot_clef.txt. Ici on se contentera de recopier le fichier sur la sortie terminal
     * caractère par caractères en utilisant fgetc
     */
	char car;                                    //variable stockant le caractère "actuel"
	fichier=fopen("mot_clef.txt","a+");          //ouverture du fichier
	fseek(fichier, 0, SEEK_SET);

    printf("\n\nAffichage des mot-clefs et des réponses associées: \n");

    car = fgetc(fichier);                   //On commence à lire le fichier caractère par caractère
	while (car != EOF)                      //Tant que le caractère lu n'est pas la fin du fichier, on continue 
	{
		printf ("%c", car);     //On afficher le caractère stocké
		car = fgetc(fichier);   //On lit le caractère suivant
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
	char mot_recherche[TMOT];
	char ligne[TMAX];
	int indicateur=0;                                                   //Nous permettra de savoir si le mot-clef n'existe pas
	printf("\n\nEntrez le mot-clef recherché (MOINS DE 30 CARACTERES): ");
	scanf("%s", mot_recherche);
	fichier=fopen("mot_clef.txt","a+");
	fseek(fichier, 0, SEEK_SET);
	
	ici:
	while(fgets(ligne,TMAX,fichier)!=NULL)  //Tant que le fichier n'est pas fini on copie la ligne actuelle avec fgets
	{	
		if (ligne[0]=='\n')                 //Cette boule if nous permet d'ignorer les lignes vides (les sauts de ligne)
		{
			goto ici;                       //Ce goto nous permet de repartir de zéro dans cette boucle une fois la ligne vide ignorée
		}
		else
		{
			sscanf(ligne,"%s",p.mot);               //sscanf nous permet de charger la ligne dans notre structure MOT_CLEF en tant que mot
			fgets(p.reponse,TMAX,fichier);          //Nous permet de lire la ligne suivante et de la stocker dans notre structure en tant que réponse (notre fichier est agencé de cette manière)
			if (strcmp(p.mot,mot_recherche)==0)     //Si il y a égalité entre le mot recherché et le mot actuel...
			{
				indicateur=1;                            
				printf("\nMot-clef: %s\nReponse: %s\n",p.mot,p.reponse);  //...alors on l'affiche à l'écran			
			}
		}
	}
	if (indicateur==0)
		printf("\nCe mot-clef n'existe pas !\n");
	fclose(fichier);	
}

void supprimer_mot_clef(FILE * fichier)
{
	/* Cette fonction marche selon le même principe que la fonction supprime_personne
	 * On saisie le mot clef à supprimer et on le compare avec les mot-clefs que l'on chargera un à un dans un structure MOT_CLEF
	 * Si ce n'est pas le bon mot clef, on recopie la structure (mot et réponse) dans un nouveau fichier
	 * Si c'est le bon mot_clef il ne sera pas recopié et sera perdu dans les limbes pour toujours !!!! >:-)
	 */
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
	while(fgets(ligne,TMAX,fichier)!=NULL)          //On place la ligne actuelle dans la chaine "ligne" grâce à fgets tant que le fichier n'est pas fini 
	{	
		if (ligne[0]=='\n')                         //Cette boucle if permet de recopier les sauts de ligne
		{
			fprintf(fichier_temp,"\n");             //Ici on remet le saut de ligne dans le nouveau fichier
		}
		else
		{
			sscanf(ligne,"%s",p.mot);               //On place notre ligne dans la structre MOT_CLEF pour faire une comparaison
			fgets(p.reponse,TMAX,fichier);          //On place la ligne suivante dans la structure en tant que réponse (c'est comme cela qu'est agencé notre fichier)
			if (strcmp(p.mot,mot_a_supprimer)==0)   //On compare nos deux chaines de caractères
			{
				indicateur=1;                       
				printf("\nMot-clef supprimé.\n");   //Ici on ne recopie pas la structure dans le nouveau fichier
				goto retour;                        //On retourne au début de la boucle while
			}
			else
			{
				fprintf(fichier_temp, "%s\n%s",p.mot,p.reponse);   //On recopie la structure dans le nouveau fichier
			}
		}
	}
	
	if (indicateur==0)
		printf("\nCe mot-clef n'existe pas !\n");
	
	
	fclose(fichier);
	fclose(fichier_temp);
	remove("mot_clef.txt");                  //On supprime le premier fichier
	rename("temp.txt","mot_clef.txt");       //On renomme le second fichier

}

int rechercher_EM(FILE *repertoire, char *nomrech)
{
    int trouve=0;
    char classement_temp[TMAX]; // servira a stocker la chaine de caractere representant le num de la structure
    PERS p;
    repertoire=fopen("repertoire.txt","a+");
    fseek(repertoire, 0, SEEK_SET);
    while (fscanf(repertoire,"%s %s %s %s", p.NOM, p.PRENOM,p.AdresseMail, classement_temp) !=EOF)  
    {       //tant que l'on atteind pas la fin du repertoire on affecte les chaines de caractères aux variables
        
        if (strcmp(p.AdresseMail,nomrech)==0)       //test si p.adressemail= nomrech
        {
            strcpy(p.Classement,classement_temp);
            trouve=(strlen(classement_temp)); //determine la taille de la chaine de caractere num_temp pour la retourner et connaitre le nombre d'octect pour se deplacer
            trouve=1;
        }
     
    }
    fclose(repertoire);
    return trouve;
}

void viderBuffer()  //fonction pour vider stdin
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
        positionEntree = strchr(chaine, '\n'); // cherche le caractère \n
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

void fonction_utilisateur(FILE *donne, FILE *repertoire, FILE *motclef, DONNEE* mail_utilisateur, char *nomrech)
{
	/* Cette fonction du mode utilisateur permet non seulement de saisir un mail, mais aussi d'y répondre en remplissant notre fichier donne.txt
	 *  Nous regardons d'abord si l'addresse mail entrée correspond à l'un des membres dans notre répertoire
	 * Si oui l'utilisateur peut entrer un objet et un corps de mail. On recopie le tout dans notre fichier donne.txt
	 * On lit ensuite le fichier mot clef et on place chaque mot clef et sa réponse associée dans une structure
	 */
	MOT_CLEF p;
    donne=fopen("donne.txt","a+");
    motclef=fopen("mot_clef.txt","a+");
	fseek(motclef, 0, SEEK_SET);
	char ligne[TMAX];
	int indicateur=0;
	int trouve=0;
   
   
    printf ("Veuillez saisir votre adresse mail : \n");
    getchar ();                                                                              
    lire(mail_utilisateur->EM,TCHAINE);
    trouve=rechercher_EM(repertoire, mail_utilisateur->EM);
    
      if (trouve==0)
      {
          printf("\nVotre adresse mail n'est pas enregistre, veuillez contacter le SBC\n\n");
          indicateur=1;
      }
      else
      {
            printf ("Entrez l'objet du mail : \n");
            lire(mail_utilisateur->OBJ,TCHAINE);
            printf ("Entrez le corps du mail : \n");
            lire(mail_utilisateur->CORPS,TMAX);
            fprintf(donne, "\n\n************************Mail recu sur la boite du club************************");
            fprintf(donne,"\nExpediteur: %s \nObjet: %s \nCorps: %s\n",mail_utilisateur->EM,mail_utilisateur->OBJ ,mail_utilisateur->CORPS);
		  
			arriere:
			while(fgets(ligne,TMAX,motclef)!=NULL)
			{	
				if (ligne[0]=='\n')                                       //Cas ou nous rencontrons une ligne vide dans le fichier mot_clef
				{
					goto arriere;                                         //On se contente de recommencer la boucle while avec une nouvelle ligne
				}
				else
				{
					sscanf(ligne,"%s",p.mot);
					fgets(p.reponse,TMAX,motclef);
					if (strstr(mail_utilisateur->CORPS,p.mot)!=NULL)      //Si mon corps de mail reçu contient le mot-clef recherché, alors on peut répondre
					{                                                     //Ici on affichera à la fois sur le terminal et dans notre fichier donne.txt
						indicateur=1;
						
						printf("\nMail automatique de reponse: ");
						fprintf(donne, "\nMail automatique de reponse: ");
						
						printf("\nExpediteur: club.sbc@gmail.com");
						fprintf(donne, "\nExpediteur: club.sbc@gmail.com");
						
						printf("\nObjet: Reponse a: %s", mail_utilisateur->OBJ);          //On recopie l'objet
						fprintf(donne, "\nObjet: Reponse a: %s", mail_utilisateur->OBJ);
						
						printf("\nCorps: %s\n Cordialement,\n Le SBC.\n\n", p.reponse);                             //On affiche notre réponse associée contenue dans notre fichier mot-clef
						fprintf(donne,"\nCorps: %s \n Cordialement,\n Le SBC.", p.reponse);
						
						printf("\nHistorique des mails disponibles dans le fichier \"donne.txt\"\n");  //Petite ligne d'information
					}
				}
			} 
      }
		
	if (indicateur==0)  //C'est dans le cas ou nous ne trouvons aucun mot-clef dans le texte reçu.
	{
		printf("\nMail automatique de reponse: ");
		fprintf(donne, "\nMail automatique de reponse: ");
		
		printf("\nExpediteur: club.sbc@gmail.com");
		fprintf(donne, "\nExpediteur: club.sbc@gmail.com");
		
		printf("\nObjet: Reponse a: %s", mail_utilisateur->OBJ);
		fprintf(donne, "\nObjet: Reponse a: %s", mail_utilisateur->OBJ);
		
		printf("\nCorps: Desole, votre demande n'entre pas dans le champ de competence de cet automate!\nVeuillez contacter notre equipe directement sur site (avec un masque!).\nMerci.\n\n");
		fprintf(donne,"\nCorps: Desole, votre demande n'entre pas dans le champ de competence de cet automate!\nVeuillez contacter notre equipe directement sur site (avec un masque!).\nMerci.\n\n");
	}
	fclose(motclef);
    fclose(donne);
}

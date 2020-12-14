#define TMAX 1000 // Tableau de taille 1000
#define TCHAINE 60
#define TMOT 30

typedef struct {
    char NOM[TCHAINE];
    char PRENOM[TCHAINE];
    char AdresseMail[TCHAINE];
    char Classement[TMAX];
}PERS;

typedef struct {

    char EM[TCHAINE];
    char OBJ[TCHAINE];
    char CORPS[TMAX];

}DONNEE;

typedef struct {
    char mot[TMOT];
    char reponse[TMAX];
}MOT_CLEF;


void menu(FILE*,FILE*,FILE*,PERS*,DONNEE*,char*,int);

void saisir_repertoire (FILE*, PERS*); //fonction pour saisir les personne dans le fichier repertoire     //definition des fonctions
void affichage_repertoire(FILE*);  //fonction qui affiche le repertoire
int rechercher_personne(FILE*, char*); //fonction qui cherche une personne à partir de son nom dans le repertoire
void supprime_personne (FILE*, char*); // fonction qui suprime une personne dans un fichier

//Les fonctions permettant la gestion des mots-clefs et des réponses associées
void ajout_mot_clef(FILE *);     
void afficher_mot_clef(FILE *);   
void recherche_mot_clef(FILE*);   
void supprimer_mot_clef(FILE*);


void fonction_utilisateur(FILE *donne, FILE *repertoire, FILE *motclef, DONNEE* mail_utilisateur, char *nomrech);//fonction pour saisir les caractéristisques du mail (emetteur destinataire obj...)
void viderBuffer();
int rechercher_EM(FILE*,char*);
int lire(char *chaine, int longueur);

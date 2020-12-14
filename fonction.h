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
    char DT[TCHAINE];
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
void suprime_personne (FILE*, char*); // fonction qui suprime une personne dans un fichier

void ajout_mot_clef(FILE *);//fonction pour saisir un nouveau mot cle
void afficher_mot_clef(FILE *);//fonction pour afficher le repertoire des mot cle
void recherche_mot_clef(FILE*);
void supprimer_mot_clef(FILE*);

void saisie_DT_Obj(FILE*, DONNEE*,FILE*,FILE*,int,char*);  //fonction pour saisir les caractéristisques du mail (emetteur destinataire obj...)
int rechercher_EM(FILE*,char*);
void viderBuffer();
int lire(char *chaine, int longueur);
void recherche_mot(FILE *donne,FILE *mot_clef);

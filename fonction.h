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


void menu(FILE*,FILE*,FILE*,PERS*,DONNEE*,char*,int);

void saisir_repertoire (FILE*, PERS*); //fonction pour saisir les personne dans le fichier repertoire     //definition des fonctions
void affichage_repertoire(FILE*);  //fonction qui affiche le repertoire
int rechercher_personne(FILE*, char*); //fonction qui cherche une personne à partir de son nom dans le repertoire
int rechercher_EM(FILE*, char*);

void ajout_mot_clef(FILE *);//fonction pour saisir un nouveau mot cle
void afficher_mot_clef(FILE *);//fonction pour afficher le repertoire des mot cle
void recherche_mot_clef(FILE*);
void supprimer_mot_clef(FILE*);

void saisie_DT_Obj(FILE*, DONNEE*,FILE*,int,char*);  //fonction pour saisir les caractéristisques du mail (emetteur destinataire obj...)
int rechercher_EM(FILE*,char*);
void viderBuffer();
int lire(char *chaine, int longueur);

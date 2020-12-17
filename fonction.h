#define TMAX 1000 // Tableau de taille 1000
#define TCHAINE 60
#define TMOT 30

//Structure utilisée pour stocker les données du répertoire
typedef struct {
    char NOM[TCHAINE];
    char PRENOM[TCHAINE];
    char AdresseMail[TCHAINE];
    char Classement[TMAX];
}PERS;

//Structure utilisée pour stocker les données entrées par l'utilisateur
typedef struct {

    char EM[TCHAINE];
    char OBJ[TCHAINE];
    char CORPS[TMAX];

}DONNEE;

//Structure utilisée pour stocker les mots-clefs et leurs réponses associées
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
void ajout_mot_clef(FILE *);       //Ajoute un mot-clef au fichier motclef.txt
void afficher_mot_clef(FILE *);    //Afficher tous les mots-clefs précedemment saisis
void recherche_mot_clef(FILE*);    //Recherche un mot-clef parmi les pré-existants
void supprimer_mot_clef(FILE*);    //Supprime un mot-clef particulier

//Cette fonction du mode utilisateur permet non seulement de saisir un mail, mais aussi d'y répondre en remplissant notre fichier donne.txt
void fonction_utilisateur(FILE *donne, FILE *repertoire, FILE *motclef, DONNEE* mail_utilisateur, char *nomrech);

void viderBuffer();
int rechercher_EM(FILE*,char*);
int lire(char *chaine, int longueur);

#define MAX_ELEM 100

typedef struct resultats
{
    int note[MAX_ELEM];
    int dernier_elem;
}resultats;

typedef struct etudiant{
    char nom[20];
    char prenom[20];
    char cin[20];
    char cne[20];
    resultats notes;
    enum Diplome {DUT, DEUG, DEUST, LICENCE, MAITRISE, MASTER, CPGE} diplome;
    char etablissement[30];
    int nbreAns;
    int anDiplome;
} etudiant;

typedef struct acces
{
    char cne[20];
    char password[30];
}acces;

typedef struct tableau
{
    etudiant elem[MAX_ELEM];
    int dernier_elem;
}tableau;

typedef struct authentification
{
    acces entree[MAX_ELEM];
    int derniere_entree;
}authentification;


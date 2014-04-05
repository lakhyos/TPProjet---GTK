#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

//Initialisation du tableau d'etudiants:

/* Nom de la fonction: creer_tableau
 * Entrees: NULL
 * Sorties: Tableau vide
 * Description: Cette fonction nous permer de creer un tebleau vide,
 *              ceci en initialisant dernier_elem a -1
 */
tableau *creer_tableau()
{
    tableau *tab = malloc(sizeof(tableau));
    if (!tab)   printf("Erreur allocation de memoire");//erreur
    tab->dernier_elem = -1;//initialisation de dernier_elem a 0
    return tab;
}

resultats *creer_tableau_resultats()
{
    resultats *tab = malloc(sizeof(resultats));
    if (!tab)   printf("Erreur allocation de memoire");//erreur
    tab->dernier_elem = -1;//initialisation de dernier_elem a -1
    return tab;
}

//Initialisation du tableau d'etudiants:
authentification *creer_tableau_authentification()
{
    authentification *tab = malloc(sizeof(authentification));
    if (!tab)   printf("Erreur allocation de memoire");//erreur
    tab->derniere_entree = -1;//initialisation de dernier_elem a 0
    return tab;
}
/* Nom de la fonction: ajout etudiant
 * Entrees: Tableau dans lequel on va ajouter un element
 * Sorties: Null
 * Description: Cette fonction nous permet d'ajouter une valeur dans un
 *              tableau donne,tout en incrementant la valeur du dernier
 *              elem a chaque ajout
 */
void ajout_note(resultats *notes, int nv_note)
{
    notes->note[++notes->dernier_elem]=nv_note;
}

/* Nom de la fonction: initialisation_etudiant
 */
etudiant *initialisation_etudiant(char *nom, char *prenom, char *cin,  char *cne, char *etablissement, int anDiplome, int nbreAns, int diplome, resultats notes)
{
    etudiant *nv_etudiant = malloc(sizeof (etudiant));
    if (nv_etudiant != NULL)
    {
        strcpy(nv_etudiant->nom, nom);
        strcpy(nv_etudiant->prenom, prenom);
        strcpy(nv_etudiant->cin, cin);
        strcpy(nv_etudiant->cne, cne);
        strcpy(nv_etudiant->etablissement, etablissement);
        nv_etudiant->anDiplome=anDiplome;
        nv_etudiant->nbreAns=nbreAns;
        nv_etudiant->diplome=diplome;
        for(int i=0; i<=notes.dernier_elem; i++)
            ajout_note(&nv_etudiant->notes, notes.note[i]);
    }
    return nv_etudiant;
}

/* Nom de la fonction: initialisation_acces
 */
acces *initialisation_acces(char *cne, char *password)
{
    acces *nv_acces = malloc(sizeof (acces));
    if (nv_acces != NULL)
    {
        strcpy(nv_acces->cne, cne);
        strcpy(nv_acces->password, password);
    }
    return nv_acces;
}


int rang_tableau_etudiants(tableau etudiants, char cne[20])
{
    int i=0;
    while (i<=etudiants.dernier_elem) {
        if (!strcmp(etudiants.elem[i].cne, cne))
            return i;
        else i++;
    }
    return -1;
}

int rang_tableau_authentification(authentification authentification, char cne[20])
{
    int i=0;
    while (i<=authentification.derniere_entree) {
        if (!strcmp(authentification.entree[i].cne, cne))
            return i;
        else i++;
    }
    return -1;
}

float moyenne_etudiant(tableau etudiants, char cne[20])
{
    int position=rang_tableau_etudiants(etudiants, cne);
    int somme = 0, i = 0;
    while (i<=etudiants.elem[position].notes.dernier_elem) {
        somme += etudiants.elem[position].notes.note[i];
        i++;
    }
    return (somme/(etudiants.elem[position].notes.dernier_elem+1));
}

int mention_assezbien(tableau etudiants, char cne[20])
{
    int i=0;
    int position=rang_tableau_etudiants(etudiants, cne);
    while (i<=etudiants.elem[position].notes.dernier_elem) {
        if (etudiants.elem[position].notes.note[i]>=13) return 1;
        else i++;
    }
    return 0;

}
/* Nom de la fonction: ajout etudiant
 * Entrees: Tableau dans lequel on va ajouter un element
 * Sorties: Null
 * Description: Cette fonction nous permet d'ajouter une valeur dans un
 *              tableau donne,tout en incrementant la valeur du dernier
 *              elem a chaque ajout
 */
void ajout_etudiant(tableau *etudiants, authentification *authentification, etudiant nv_etudiant, acces nv_acces)
{
    if (rang_tableau_etudiants(*etudiants, nv_etudiant.cne)==-1)//etudiant pas dans le tableau
    {
        etudiants->elem[++etudiants->dernier_elem]=nv_etudiant;
        authentification->entree[++authentification->derniere_entree]=nv_acces;
    }
}


void modification_etudiant(tableau *etudiants, etudiant nv_etudiant)
{
    int position=rang_tableau_etudiants(*etudiants, nv_etudiant.cne);
    
    strcpy(etudiants->elem[position].nom, nv_etudiant.nom);
    strcpy(etudiants->elem[position].prenom, nv_etudiant.prenom);
    strcpy(etudiants->elem[position].cin,nv_etudiant.cin);
    strcpy(etudiants->elem[position].cne,nv_etudiant.cne);
    strcpy(etudiants->elem[position].etablissement,nv_etudiant.etablissement);
    etudiants->elem[position].anDiplome=nv_etudiant.anDiplome;
    etudiants->elem[position].nbreAns=nv_etudiant.nbreAns;
    etudiants->elem[position].diplome=nv_etudiant.diplome;
    
    etudiants->elem[position].notes.dernier_elem = -1;
    for(int i=0; i<=nv_etudiant.notes.dernier_elem; i++)
        ajout_note(&etudiants->elem[position].notes, nv_etudiant.notes.note[i]);
}

int eligibilite_etudiant(tableau etudiants, etudiant etudiant)
{
    if (rang_tableau_etudiants(etudiants, etudiant.cne)==-1) return -1;//l'etudiant n'existe pas
    else
    {
        int position=rang_tableau_etudiants(etudiants, etudiant.cne);
        if ((etudiants.elem[position].anDiplome == 2014) &&
        (moyenne_etudiant(etudiants, etudiant.cne) >= 12) &&
        (mention_assezbien(etudiants, etudiant.cne)) &&
        (etudiant.nbreAns == 2)) return 1;
        else return 0;
    }
}

int authentification_etudiant(authentification authentification, acces element)
{
    if (rang_tableau_authentification(authentification, element.cne)==-1) return -1;//l'etudiant n'existe pas
    else
    {
        int position=rang_tableau_authentification(authentification, element.cne);
        if (!strcpy(authentification.entree[position].password, element.password)) return 1;
        else return 0;
    }
}



//Generation d'un fichier d'etudiants
void EnregistrerEtudiants(tableau etudiants)
{
    FILE *fic; //variable type fichier
    
        //ouverture ou creation du fichier en ecriture et test si probleme
    if((fic = fopen("ListeEtudiants.txt", "w+"))==NULL) printf("erreur d'ouverture");
    else //si pas de probleme
    {
        for (int i=0; i<=etudiants.dernier_elem; i++) {
            fprintf(fic,"%s ",etudiants.elem[i].nom);
            fprintf(fic,"%s ",etudiants.elem[i].prenom);
            fprintf(fic,"%s ",etudiants.elem[i].cne);
            fprintf(fic,"%s ",etudiants.elem[i].cin);
            fprintf(fic,"%u ",etudiants.elem[i].diplome);
            fprintf(fic,"%d ",etudiants.elem[i].nbreAns);
            fprintf(fic,"%d ",etudiants.elem[i].anDiplome);
            fprintf(fic,"%s ",etudiants.elem[i].etablissement);
            for(int j=0; i<=etudiants.elem[i].notes.dernier_elem; j++)
               fprintf(fic,"%d ",etudiants.elem[i].notes.note[j]);
            fprintf(fic,"\n");
        }
    }
    fclose(fic); //fermer le fichier
}

//Generation d'un fichier de mots de pass
void EnregistrerPassword(authentification authenti)
{
    FILE *fic; //variable type fichier
    
    //ouverture ou creation du fichier en ecriture et test si probleme
    if((fic = fopen("ListePassword.txt", "w+"))==NULL) printf("erreur d'ouverture");
    else //si pas de probleme
    {
        for (int i=0; i<=authenti.derniere_entree; i++) {
            fprintf(fic,"%s ",authenti.entree[i].cne);
            fprintf(fic,"%s ",authenti.entree[i].password);
            fprintf(fic,"\n");
          }
    }
    fclose(fic); //fermer le fichier
}



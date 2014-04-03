#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "gtk/gtk.h"
#include "liste.h"
GtkWidget *p_window= NULL;
GtkWidget *pVBox[2];
GtkWidget *pHBox[4];
GtkWidget *pButton[4];
GtkWidget *pButton1[4];
GtkWidget *pMenuBar;
GtkWidget *pMenu;
GtkWidget *pMenuItem;
GtkWidget *pLabel[6];
GtkWidget *pEntry[6];
GtkWidget *pFrame[3];
GtkWidget *pVBoxFrame;
GtkWidget *pSeparator;
GtkWidget *pLabel1;
GtkWidget *pEntry1;
GtkWidget *pSpin;
etudiants *etud1=NULL;
etudiants *et;
Dlist *list;
gchar *sUtf8;
int i,found = 0;

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

//Initialise la liste
etudiants *etudiant_nouv (void)
{
    return (NULL);
}

Dlist *dlist_new(void)
{
    Dlist *p_new = malloc(sizeof *p_new);
    if (p_new != NULL)
    {
        p_new->length = 0;
        p_new->p_head = NULL;
        p_new->p_tail = NULL;
    }
    return p_new;
}

int siVide()
{
    int d,d1,d2,d3,d4;
    char *str = gtk_entry_get_text(pEntry[0]);
    char *str1 = gtk_entry_get_text(pEntry[1]);
    char *str2 = gtk_entry_get_text(pEntry[2]);
    char *str3 = gtk_entry_get_text(pEntry[3]);
    char *str4 = gtk_entry_get_text(pEntry[4]);
    d=strlen(str);
    d1=strlen(str1);
    d2=strlen(str2);
    d3=strlen(str3);
    d4=strlen(str4);
    if (d*d1*d2*d3*d4==0)
        return 1;
    else
        return 0;
    
}

// Supprimer un element
void etudiant_suppr(etudiants ** pp_dll)
{
    if (pp_dll != NULL && *pp_dll != NULL)
    {
        /* (2) */
        etudiants *p_l = *pp_dll;
        /* (3) */
        etudiants *p_p = p_l->prec;
        /* (4) */
        etudiants *p_n = p_l->suiv;
        
        /* (5) */
        if (p_p != NULL)
            p_p->suiv = p_n;
        if (p_n != NULL)
            p_n->prec = p_p;
        /* (6) */
        free (p_l);
        p_l = NULL;
        if (p_n != NULL)
            *pp_dll = p_n;
        else
            *pp_dll = p_p;
    }
}


//Ajout d'un etudiant
Dlist *dlist_append(Dlist *p_list, char *nom, char *prenom, char *adresse,  char *tel, char *filiere, int niveau )
{
    if (p_list != NULL) /* On vérifie si notre liste a été allouée */
    {
        etudiants *p_new = malloc(sizeof (etudiants)); /* Création d'un nouveau node */
        if (p_new != NULL) /* On vérifie si le malloc n'a pas échoué */
        {
            //p_new->data = data; /* On 'enregistre' notre donnée */
            strcpy(p_new->nom , nom);
            strcpy(p_new->prenom,prenom);
            strcpy(p_new->adresse,adresse);
            strcpy(p_new->filiere,filiere);
            strcpy(p_new->tel,tel);
            p_new->niveau = niveau;
            p_new->suiv = NULL; /* On fait pointer p_next vers NULL */
            if (p_list->p_tail == NULL) /* Cas où notre liste est vide (pointeur vers fin de liste à  NULL) */
            {
                p_new->prec = NULL; /* On fait pointer p_prev vers NULL */
                p_list->p_head = p_new; /* On fait pointer la tête de liste vers le nouvel élément */
                p_list->p_tail = p_new; /* On fait pointer la fin de liste vers le nouvel élément */
            }
            else /* Cas où des éléments sont déjà présents dans notre liste */
            {
                p_list->p_tail->suiv = p_new; /* On relie le dernier élément de la liste vers notre nouvel élément (début du chaînage) */
                p_new->prec = p_list->p_tail; /* On fait pointer p_prev vers le dernier élément de la liste */
                p_list->p_tail = p_new; /* On fait pointer la fin de liste vers notre nouvel élément (fin du chaînage: 3 étapes) */
            }
            p_list->length++; /* Incrémentation de la taille de la liste */
        }
    }
    return p_list; /* on retourne notre nouvelle liste */
}


//acces à l element suivant
void etudiant_suiv(etudiants **pp_dll)
{
    if (pp_dll != NULL && *pp_dll != NULL)
        *pp_dll = (*pp_dll)->suiv;
}
//acces à l element precedent
void etudiant_prec(etudiants **pp_dll)
{
    if (pp_dll != NULL && *pp_dll != NULL)
        *pp_dll = (*pp_dll)->prec;
}
//acces au premier element
void etudiant_premier(etudiants ** pp_dll)
{
    if (pp_dll != NULL && *pp_dll != NULL)
    {
        while ((*pp_dll)->prec != NULL)
            etudiant_prec(pp_dll);
    }
}

void etudiant_dernier(etudiants ** pp_dll)
{
    if (pp_dll != NULL && *pp_dll != NULL)
    {
        while ((*pp_dll)->suiv != NULL)
            etudiant_suiv(pp_dll);
    }
}

//Supprimer la liste
void etudiant_effacer (etudiants ** pp_dll)
{
    if (pp_dll != NULL && *pp_dll != NULL)
    {
        etudiant_premier(pp_dll);
        while (*pp_dll != NULL)
            etudiant_suppr(pp_dll);
    }
}


//Vidage de la mémoire
void dlist_delete(Dlist *p_list)
{
    if (p_list != NULL)
    {
        etudiants *p_temp = (p_list)->p_head;
        while (p_temp != NULL)
        {
            etudiants *p_del = p_temp;
            p_temp = p_temp->suiv;
            free(p_del);
        }
        free(p_list), p_list = NULL;
    }
}


void OnPremier()
{
    et=list->p_head;
    gtk_entry_set_text(pEntry[0],et->nom);
    gtk_entry_set_text(pEntry[1],et->prenom);
    gtk_entry_set_text(pEntry[2],et->adresse);
    gtk_entry_set_text(pEntry[3],et->tel);
    gtk_entry_set_text(pEntry[4],et->filiere);
    gtk_spin_button_set_value(pSpin,et->niveau);
}
void OnDernier()
{
    et=list->p_tail;
    gtk_entry_set_text(pEntry[0],et->nom);
    gtk_entry_set_text(pEntry[1],et->prenom);
    gtk_entry_set_text(pEntry[2],et->adresse);
    gtk_entry_set_text(pEntry[3],et->tel);
    gtk_entry_set_text(pEntry[4],et->filiere);
    gtk_spin_button_set_value(pSpin,et->niveau);
}
void effacer()
{
    gtk_entry_set_text(pEntry[0],"");
    gtk_entry_set_text(pEntry[1],"");
    gtk_entry_set_text(pEntry[2],"");
    gtk_entry_set_text(pEntry[3],"");
    gtk_entry_set_text(pEntry[4],"");
    gtk_spin_button_set_value(pSpin,1);
    
}

void afficher(etudiants *l)
{
    if (l != NULL)
    {
        gtk_entry_set_text(pEntry[0],l->nom);
        gtk_entry_set_text(pEntry[1],l->prenom);
        gtk_entry_set_text(pEntry[2],l->adresse);
        gtk_entry_set_text(pEntry[3],l->tel);
        gtk_entry_set_text(pEntry[4],l->filiere);
        gtk_entry_set_text(pSpin,l->niveau);
    }
}
void affichertous(Dlist *p_list) //affiche tout le monde
{
    if (p_list != NULL)
    {
        etudiants *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            printf("nom: %s\n",p_temp->nom); //affiche a l'ecran le nom de famille
            printf("prenom: %s\n",p_temp->prenom);
            printf("adresse: %s\n",p_temp->adresse);
            printf("TEL: %s\n",p_temp->tel);
            printf("filiere: %s\n",(p_temp)->filiere);
            printf("niveau: %d\n",(p_temp)->niveau);
            fflush(stdout);
            p_temp = p_temp->suiv;
        }
    }
    printf("NULL\n");
}

//sauvegarde dans un fichier
void EnregistrerListe(Dlist *l)
{
    Dlist *tmp=l;
    //etudiants *node;
    
    FILE *fic; //variable type fichier
    //int cpt;
    
    if (tmp != NULL) //si la liste existe
    {
        //ouverture ou creation du fichier en ecriture et test si probleme
        if((fic = fopen("GestionEtudiants.txt", "w+"))==NULL) printf("erreur d'ouverture");
        else //si pas de probleme
        {
            
            etudiants *p_temp = tmp->p_head;
            while (p_temp != NULL)
            {
                fprintf(fic,"%s\n",p_temp->nom); //affiche a l'ecran le nom de famille
                fprintf(fic,"%s\n",p_temp->prenom);
                fprintf(fic,"%s\n",p_temp->adresse);
                fprintf(fic,"%s\n",p_temp->tel);
                fprintf(fic,"%s\n",(p_temp)->filiere);
                fprintf(fic,"%d\n",(p_temp)->niveau);
                p_temp = p_temp->suiv;
            }
            
            
        }
        fclose(fic); //ferme le fichier
        
    }
}


Dlist *dlist_remove(Dlist *p_list, char * nom)
{
    //nom = malloc (sizeof (*nom) * 15);
    
    if (p_list != NULL)
    {
        etudiants *p_temp = p_list->p_head;
        int d;
        while (p_temp != NULL && !found)
        {
            d=strcmp(p_temp->nom,nom);
            if (d ==0)
            {
                if (p_temp->suiv == NULL)
                {
                    p_list->p_tail = p_temp->prec;
                    p_list->p_tail->suiv = NULL;
                    et=p_list->p_tail;
                }
                else if (p_temp->prec == NULL)
                {
                    p_list->p_head = p_temp->suiv;
                    p_list->p_head->prec = NULL;
                    et=p_list->p_head;
                }
                else
                {
                    p_temp->suiv->prec = p_temp->prec;
                    p_temp->prec->suiv = p_temp->suiv;
                }
                free(p_temp);
                p_list->length--;
                found = 1;
            }
            else
            {
                p_temp = p_temp->suiv;
            }
        }
    }
    return p_list;
}

//Rechercher un etudiant
void dlist_find(Dlist *p_list, char * nom)
{
    if (p_list != NULL)
    {
        etudiants *p_temp = p_list->p_head;
        int d;
        
        while (p_temp != NULL && !found)
        {
            d=strcmp(p_temp->nom,nom);
            if (d==0)
            {
                et=p_temp;
                strcpy(et->nom,p_temp->nom);
                strcpy(et->prenom,p_temp->prenom);
                strcpy(et->adresse,p_temp->adresse);
                strcpy(et->tel,p_temp->tel);
                strcpy(et->filiere,p_temp->filiere);
                et->niveau=p_temp->niveau;
                found = 1;
            }
            else
            {
                p_temp = p_temp->suiv;
            }
        }
    }
}

void dlist_modify(Dlist *p_list, char * nom)
{
    if (p_list != NULL)
    {
        etudiants *p_temp = p_list->p_head;
        int d;
        
        while (p_temp != NULL && !found)
        {
            d=strcmp(p_temp->nom,nom);
            if (d==0)
            {
                strcpy(p_temp->nom,gtk_entry_get_text(pEntry[0]));
                strcpy(p_temp->prenom,gtk_entry_get_text(pEntry[1]));
                strcpy(p_temp->adresse,gtk_entry_get_text(pEntry[2]));
                strcpy(p_temp->tel,gtk_entry_get_text(pEntry[3]));
                strcpy(p_temp->filiere,gtk_entry_get_text(pEntry[4]));
                p_temp->niveau= gtk_spin_button_get_value(pSpin);
                et=p_temp;
                found = 1;
            }
            else
            {
                p_temp = p_temp->suiv;
            }
        }
    }
}

//Récupération du fichier
Dlist **recupfichier(etudiants *pers) //recuperation du fichier
{
    etudiants *nouvo, *tmp;
    
    FILE *fic; //variable type fichier
    char nom[15],prenom[15],filiere[15],adresse[30], tel[10];
    int niveau;
    int cmpt=1;
    
    if(!(pers)) //si la liste n'existe pas
    {
        pers = malloc(sizeof(etudiants));
        list->p_head=pers;
        pers->prec = NULL;
        nouvo= pers;
        //ouverture ou creation du fichier en ecriture et test si probleme
        if((fic = fopen("GestionEtudiants.txt", "r"))==NULL) printf("erreur d'ouverture");
        else //si pas de probleme
        {
            while(fscanf(fic, "%s\n", nom)!=-1) //si il y a encore un nom de famille
            {
                strcpy(nouvo->nom, nom);
                fscanf(fic, "%s\n", prenom); //lit un prenom et le met dans variable
                strcpy(nouvo->prenom, prenom); //met dans la cellule
                fscanf(fic, "%s\n", adresse);
                strcpy(nouvo->adresse, adresse);
                fscanf(fic, "%s\n", tel);
                strcpy(nouvo->tel, tel);
                fscanf(fic, "%s\n", filiere);
                strcpy(nouvo->filiere, filiere);
                fscanf(fic, "%d\n", &niveau);
                nouvo->niveau=niveau;
                
                //cree une nouvelle cellule
                tmp=malloc(sizeof(etudiants));
                tmp = nouvo;
                nouvo = malloc(sizeof(etudiants));
                tmp->suiv = nouvo;
                nouvo->prec = tmp;
            }
            //efface la derniere cellule cree car ne sert a rien
            free(nouvo);
            tmp->suiv = NULL;
            list->p_tail=tmp;
        }
        
        fclose(fic); //ferme le fichier
        
    }
    else printf("\n###  impossible de charger le fichier, une liste existe deja...  ###\n");
    
    affichertous(list);
    return list; //renvoi l'adresse de la liste
}


void cb_quit (GtkWidget *p_widget, gpointer user_data)
{
    gtk_main_quit();
}

void OnQuitter(GtkWidget* widget, gpointer data)
{
    GtkWidget *pQuestion;
    
    pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
                                       GTK_DIALOG_MODAL,
                                       GTK_MESSAGE_QUESTION,
                                       GTK_BUTTONS_YES_NO,
                                       "Voulez vous vraiment\n"
                                       "quitter le programme?");
    
    switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
        case GTK_RESPONSE_YES:
            gtk_main_quit();
            break;
        case GTK_RESPONSE_NONE:
        case GTK_RESPONSE_NO:
            gtk_widget_destroy(pQuestion);
            break;
    }
}

void OnEnregistrer()
{
    EnregistrerListe(list);
    GtkWidget *pAbout;
    sUtf8 = g_locale_to_utf8("Liste enregistrée avec succé sous le nom GestionEtudiants.txt", -1, NULL, NULL, NULL);
    pAbout = gtk_message_dialog_new (p_window,
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,sUtf8);
    gtk_dialog_run(GTK_DIALOG(pAbout));
    gtk_widget_destroy(pAbout);
}

void OnRecuperer()
{
    list=recupfichier(etud1);
    GtkWidget *pAbout;
    sUtf8 = g_locale_to_utf8("Liste récupérée avec succés", -1, NULL, NULL, NULL);
    pAbout = gtk_message_dialog_new (p_window,
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,sUtf8);
    gtk_dialog_run(GTK_DIALOG(pAbout));
    gtk_widget_destroy(pAbout);
    OnPremier();
}
void OnAbout(GtkWidget* widget, gpointer data)
{
    GtkWidget *pAbout;
    gchar *sUtf8;
    sUtf8 = g_locale_to_utf8("MiniProjet\n Gestion des étudiants avec une liste chainée double", -1, NULL, NULL, NULL);
    pAbout = gtk_message_dialog_new (GTK_WINDOW(data),
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,sUtf8);
    
    gtk_dialog_run(GTK_DIALOG(pAbout));
    
    gtk_widget_destroy(pAbout);
}

void OnAjouter()
{
    char nom[10],prenom[10],filiere[10],adresse[30], tel[10];
    int niveau;
    int d,j;
    etudiants *test;
    GtkWidget *pAbout;
    j=siVide();
    if(j==0)
    {
        char *str = gtk_entry_get_text(pEntry[0]);
        d=strlen(str);
        if (d==0)
        {
            sUtf8 = g_locale_to_utf8("Veuillez remplir les champs des données et cliquer sur ajouter", -1, NULL, NULL, NULL);
            pAbout = gtk_message_dialog_new (p_window,
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,sUtf8);
            gtk_dialog_run(GTK_DIALOG(pAbout));
            gtk_widget_destroy(pAbout);
        }
        else{
            strcpy(nom,gtk_entry_get_text(pEntry[0]));
            strcpy(prenom,gtk_entry_get_text(pEntry[1]));
            strcpy(adresse,gtk_entry_get_text(pEntry[2]));
            strcpy(tel,gtk_entry_get_text(pEntry[3]));
            strcpy(filiere,gtk_entry_get_text(pEntry[4]));
            niveau= gtk_spin_button_get_value(pSpin);
            list= dlist_append(list,nom,prenom,adresse,tel,filiere,niveau);
            sUtf8 = g_locale_to_utf8("l'enregistrement a été ajouté avec succés", -1, NULL, NULL, NULL);
            pAbout = gtk_message_dialog_new (p_window,
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,sUtf8);
            gtk_dialog_run(GTK_DIALOG(pAbout));
            gtk_widget_destroy(pAbout);
            effacer();
        }
    }else
    {
        sUtf8 = g_locale_to_utf8("Veuillez entrer tous les champs", -1, NULL, NULL, NULL);
        pAbout = gtk_message_dialog_new (p_window,
                                         GTK_DIALOG_MODAL,
                                         GTK_MESSAGE_INFO,
                                         GTK_BUTTONS_OK,sUtf8);
        gtk_dialog_run(GTK_DIALOG(pAbout));
        gtk_widget_destroy(pAbout);
        
    }
}

//Pour rechercher un etudiant

void OnRechercher()
{
    GtkWidget *pAbout;
    int k;
    char *str = gtk_entry_get_text(pEntry[0]);
    k=strlen(str);
    if (k==0)
    {
        sUtf8 = g_locale_to_utf8("Veuillez remplir le champs nom pour \n effectuer la recherche", -1, NULL, NULL, NULL);
        pAbout = gtk_message_dialog_new (p_window,
                                         GTK_DIALOG_MODAL,
                                         GTK_MESSAGE_INFO,
                                         GTK_BUTTONS_OK,sUtf8);
        gtk_dialog_run(GTK_DIALOG(pAbout));
        gtk_widget_destroy(pAbout);
    }
    else{
        dlist_find(list, str);
        if (found!=0)
        {
            gtk_entry_set_text(pEntry[0],et->nom);
            gtk_entry_set_text(pEntry[1],et->prenom);
            gtk_entry_set_text(pEntry[2],et->adresse);
            gtk_entry_set_text(pEntry[3],et->tel);
            gtk_entry_set_text(pEntry[4],et->filiere);
            found=0;
        }
        else
        {
            sUtf8 = g_locale_to_utf8("Aucun enregistrement trouvé avec ce critère\n Entre un différent nom ", -1, NULL, NULL, NULL);
            pAbout = gtk_message_dialog_new (p_window,
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,sUtf8);
            gtk_dialog_run(GTK_DIALOG(pAbout));
            gtk_widget_destroy(pAbout);
            
        }
    }
    
}

//Pour Supprimer un étudiant
void OnSupprimer()
{
    GtkWidget *pAbout;
    int k;
    char *str = gtk_entry_get_text(pEntry[0]);
    k=strlen(str);
    if (k==0)
    {
        sUtf8 = g_locale_to_utf8("Veuillez remplir le champs nom pour \n supprimer l'étudiant de la liste", -1, NULL, NULL, NULL);
        pAbout = gtk_message_dialog_new (p_window,
                                         GTK_DIALOG_MODAL,
                                         GTK_MESSAGE_INFO,
                                         GTK_BUTTONS_OK,sUtf8);
        gtk_dialog_run(GTK_DIALOG(pAbout));
        gtk_widget_destroy(pAbout);
    }
    else{
        list=dlist_remove(list,gtk_entry_get_text(pEntry[0]));
        if (found!=0)
        {
            sUtf8 = g_locale_to_utf8("Suppression avec succés ", -1, NULL, NULL, NULL);
            pAbout = gtk_message_dialog_new (p_window,
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,sUtf8);
            gtk_dialog_run(GTK_DIALOG(pAbout));
            gtk_widget_destroy(pAbout);
            gtk_entry_set_text(pEntry[0],et->nom);
            gtk_entry_set_text(pEntry[1],et->prenom);
            gtk_entry_set_text(pEntry[2],et->adresse);
            gtk_entry_set_text(pEntry[3],et->tel);
            gtk_entry_set_text(pEntry[4],et->filiere);
            gtk_spin_button_set_value(pSpin,et->niveau);
            
            found=0;
        }
        else
        {
            sUtf8 = g_locale_to_utf8("Aucun enregistrement trouvé avec ce critère\n Entre un différent nom ", -1, NULL, NULL, NULL);
            pAbout = gtk_message_dialog_new (p_window,
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,sUtf8);
            gtk_dialog_run(GTK_DIALOG(pAbout));
            gtk_widget_destroy(pAbout);
            
        }
    }
    
    
}
//Pour Modifier les infos d'un etudiant
void OnModifier()
{
    GtkWidget *pAbout;
    int k;
    char *str = gtk_entry_get_text(pEntry[0]);
    k=strlen(str);
    if (k==0)
    {
        sUtf8 = g_locale_to_utf8("Veuillez remplir le champs nom pour \n modifier l'étudiant de la liste", -1, NULL, NULL, NULL);
        pAbout = gtk_message_dialog_new (p_window,
                                         GTK_DIALOG_MODAL,
                                         GTK_MESSAGE_INFO,
                                         GTK_BUTTONS_OK,sUtf8);
        gtk_dialog_run(GTK_DIALOG(pAbout));
        gtk_widget_destroy(pAbout);
    }
    else{
        dlist_modify(list,gtk_entry_get_text(pEntry[0]));
        if (found!=0)
        {
            gtk_entry_set_text(pEntry[0],et->nom);
            gtk_entry_set_text(pEntry[1],et->prenom);
            gtk_entry_set_text(pEntry[2],et->adresse);
            gtk_entry_set_text(pEntry[3],et->tel);
            gtk_entry_set_text(pEntry[4],et->filiere);
            gtk_spin_button_set_value(pSpin,et->niveau);
            sUtf8 = g_locale_to_utf8("Modification avec succés ", -1, NULL, NULL, NULL);
            pAbout = gtk_message_dialog_new (p_window,
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,sUtf8);
            gtk_dialog_run(GTK_DIALOG(pAbout));
            gtk_widget_destroy(pAbout);
            
            
            found=0;
        }
        else
        {
            sUtf8 = g_locale_to_utf8("Aucun enregistrement trouvé avec ce critère\n Entre un nom différent  ", -1, NULL, NULL, NULL);
            pAbout = gtk_message_dialog_new (p_window,
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,sUtf8);
            gtk_dialog_run(GTK_DIALOG(pAbout));
            gtk_widget_destroy(pAbout);
            
        }
    }
    
}


static void menu_item_new (GtkMenu *p_menu, const gchar *title, GCallback callback, gpointer user_data)
{
    GtkWidget *p_menu_item = NULL;
    
    p_menu_item = gtk_menu_item_new_with_mnemonic (title);
    gtk_menu_shell_append (GTK_MENU_SHELL (p_menu), p_menu_item);
    g_signal_connect (G_OBJECT (p_menu_item), "activate", callback, user_data);
}


void CreerMenu()
{
    /**** Creation du menu ****/
    
    /* ETAPE 1 */
    pMenuBar = gtk_menu_bar_new();
    /** Premier sous-menu **/
    /* ETAPE 2 */
    pMenu = gtk_menu_new();
    /* ETAPE 3 */
    
    sUtf8 = g_locale_to_utf8("Récupérer une liste ...", -1, NULL, NULL, NULL);
    menu_item_new (GTK_MENU (pMenu), "Enregister la liste", G_CALLBACK (OnEnregistrer),(GtkWidget*) p_window);
    menu_item_new (GTK_MENU (pMenu), sUtf8, G_CALLBACK (OnRecuperer),(GtkWidget*) p_window);
    pMenuItem = gtk_menu_item_new_with_label("Quitter");
    g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnQuitter), (GtkWidget*) p_window);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
    
    /* ETAPE 4 */
    pMenuItem = gtk_menu_item_new_with_mnemonic ("_Fichier");
    /* ETAPE 5 */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
    
    /* ETAPE 6 */
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);
    
    
    /** Second sous-menu **/
    /* ETAPE 2 */
    pMenu = gtk_menu_new();
    pMenuItem = gtk_menu_item_new_with_mnemonic ("_Gestion");
    menu_item_new (GTK_MENU (pMenu), "_Nouveau Etudiant", G_CALLBACK (OnAjouter),(GtkWidget*) p_window);
    menu_item_new (GTK_MENU (pMenu), "_Rechercher un Etudiant", G_CALLBACK (OnRechercher),(GtkWidget*) p_window);
    menu_item_new (GTK_MENU (pMenu), "_Modifier", G_CALLBACK (OnModifier),(GtkWidget*) p_window);
    
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (pMenuItem), pMenu);
    gtk_menu_shell_append (GTK_MENU_SHELL (pMenuBar), pMenuItem);
    
    
    
    /** 3eme sous-menu **/
    /* ETAPE 2 */
    pMenu = gtk_menu_new();
    /* ETAPE 3 */
    pMenuItem = gtk_menu_item_new_with_label("A propos de...");
    g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnAbout), (GtkWidget*) p_window);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
    /* ETAPE 4 */
    pMenuItem = gtk_menu_item_new_with_label("?");
    /* ETAPE 5 */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
    /* ETAPE 6 */
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);
}


//Création de l'interface principale
void CreerInterface()
{ /* Creation de la fenetre principale de notre application */
    p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);
    /* Gestion de la fenetre */
    pVBox[0] = gtk_vbox_new(FALSE, 5);
    pVBox[1] = gtk_vbox_new(FALSE, 0);
    pHBox[0] = gtk_hbox_new(FALSE,0);
    pHBox[1] = gtk_hbox_new(FALSE,0);
    gtk_window_set_default_size(p_window, 600, 480);
    gtk_window_set_title(GTK_WINDOW(p_window), "GESTION DES ETUDIANTS");
    gtk_window_set_position(p_window, GTK_WIN_POS_CENTER);
    gtk_container_add(GTK_CONTAINER(p_window), pVBox[0]);
    CreerMenu();
    gtk_box_pack_start(GTK_BOX(pVBox[0]), pMenuBar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox[0]), pVBox[1], FALSE, FALSE, 0);
    
    /********************************/
    /* Creation du premier GtkFrame */
    pFrame[0] = gtk_frame_new("Informations :");
    gtk_frame_set_shadow_type(pFrame, GTK_SHADOW_IN);
    gtk_box_pack_start(GTK_BOX(pVBox[1]), pFrame[0], TRUE, FALSE, 0);
    
    /* Creation et insertion d une boite pour le premier GtkFrame */
    pVBoxFrame = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pFrame[0]), pVBoxFrame);
    
    /* Creation et insertion des elements contenus dans le premier GtkFrame */
    pLabel[0] = gtk_label_new("Nom :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel[0], TRUE, FALSE, 0);
    pEntry[0] = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry[0], FALSE, FALSE, 0);
    
    sUtf8 = g_locale_to_utf8("Prénom :", -1, NULL, NULL, NULL);
    pLabel[1] = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel[1], TRUE, FALSE, 0);
    pEntry[1] = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry[1], TRUE, FALSE, 0);
    
    /* Creation d un GtkHSeparator */
    pSeparator = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pSeparator, TRUE, FALSE, 0);
    
    pLabel[2] = gtk_label_new("Adresse :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel[2], TRUE, FALSE, 0);
    pEntry[2] = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry[2], TRUE, FALSE, 0);
    
    sUtf8 = g_locale_to_utf8("Téléphone :", -1, NULL, NULL, NULL);
    pLabel[3] = gtk_label_new(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel[3], TRUE, FALSE, 0);
    pEntry[3] = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry[3], TRUE, FALSE, 0);
    
    /* Creation d un GtkHSeparator */
    pSeparator = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pSeparator, TRUE, FALSE, 0);
    
    sUtf8 = g_locale_to_utf8("Filière :", -1, NULL, NULL, NULL);
    pLabel[4] = gtk_label_new(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel[4], TRUE, FALSE, 0);
    pEntry[4] = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry[4], TRUE, FALSE, 0);
    
    pLabel[5] = gtk_label_new("Niveau :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel[5], TRUE, FALSE, 0);
    //pEntry[5] = gtk_entry_new();
    //gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry[5], TRUE, FALSE, 0);
    pSpin = gtk_spin_button_new_with_range(1, 2, 1);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pSpin, TRUE, FALSE, 0);
    
    pFrame[1] = gtk_frame_new("Gestion :");
    gtk_frame_set_shadow_type(pFrame, GTK_SHADOW_IN);
    gtk_box_pack_start(GTK_BOX(pVBox[1]), pFrame[1], FALSE, FALSE, 0);
    
    /* Creation et insertion d une boite pour le premier GtkFrame */
    gtk_container_add(GTK_CONTAINER(pFrame[1]), pHBox[0]);
    pButton[0] = gtk_button_new_with_label("Ajouter");
    sUtf8 = g_locale_to_utf8("Mise à jour", -1, NULL, NULL, NULL);
    pButton[1] = gtk_button_new_with_label(sUtf8);
    pButton[2] = gtk_button_new_with_label("Supprimer");
    pButton[3] = gtk_button_new_with_label("Rechercher");
    
    for(i=0;i<4;i++)
        gtk_box_pack_start(GTK_BOX(pHBox[0]), pButton[i], TRUE, TRUE, 0);
    /* Connexion du signal "clicked" du bouton */
    g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(OnAjouter), NULL);
    g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(OnModifier), NULL);
    g_signal_connect(G_OBJECT(pButton[2]), "clicked", G_CALLBACK(OnSupprimer), NULL);
    g_signal_connect(G_OBJECT(pButton[3]), "clicked", G_CALLBACK(OnRechercher), NULL);
    pFrame[2] = gtk_frame_new("Gestion :");
    gtk_frame_set_shadow_type(pFrame, GTK_SHADOW_IN);
    gtk_box_pack_start(GTK_BOX(pVBox[1]), pFrame[2], FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(pFrame[2]), pHBox[1]);
    pButton1[0] = gtk_button_new_with_label("Premier");
    pButton1[1] = gtk_button_new_with_label("Dernier");
    g_signal_connect(G_OBJECT(pButton1[0]), "clicked", G_CALLBACK(OnPremier), NULL);
    g_signal_connect(G_OBJECT(pButton1[1]), "clicked", G_CALLBACK(OnDernier), NULL);
    
    for(i=0;i<2;i++)
        gtk_box_pack_start(GTK_BOX(pHBox[1]), pButton1[i], TRUE, TRUE, 0);
    
    
    /* Affichage de la fenetre principale */
    gtk_widget_show_all(p_window);
    
}


/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////void CreerInterfaces();
int main (int argc, char **argv)
{
    
    /* Initialisation de GTK+ */
    //dblist *pdbListe = malloc(sizeof(dblist));
    list = dlist_new();
    list=malloc(sizeof(Dlist));
    et=malloc(sizeof(etudiants));
    gtk_init (&argc, &argv);
    CreerInterface();
    
    
    /* Lancement de la boucle principale */
    gtk_main ();
    dlist_delete(list);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// D�finir les diff�rents statuts qu'une t�che peut avoir
typedef enum
{
    A_REALISER,
    EN_COURS,
    FINALISEE
} StatutTache;
// D�finir une structure pour la date
typedef struct
{
    int jour;
    int mois;
    int annee;
} Date;
// D�finir une structure pour la nouvelle t�che
typedef struct
{                         // struct NouvelleTache{
    int id;               //		int id;
    char titre[20];       //		char titre[20];
    char description[50]; //		char description[50];
    Date deadline;        //		Date deadline;
    StatutTache statut;   //		StatutTache statut;
} NouvelleTache;          //}; typedef struct NouvelleTache NouvelleTache;
// Initialiser un identifiant global pour chaque t�che
idantifiant = 0;
// Fonction pour ajouter une nouvelle t�che
NouvelleTache ajouterNouvelleTache()
{

    NouvelleTache nouvelleTache;

    idantifiant++;
    nouvelleTache.id = idantifiant;
    // printf("Quel est l'identifiant de la tache ? \n");
    // scanf("%d", &nouvelleTache.id);
    printf("Entrez le titre de la tache : \n");
    scanf(" %[^\n]s", nouvelleTache.titre);
    printf("Entrez la description de la tache : \n");
    scanf(" %[^\n]s", nouvelleTache.description);
    printf("Entrez la date limite de la tache (JJ MM AA) : ");
    scanf(" %d%d%d", &nouvelleTache.deadline.jour, &nouvelleTache.deadline.mois, &nouvelleTache.deadline.annee);

    printf("Choisissez le statut de la tache :\n");
    printf("1. A realiser\n");
    printf("2. En cours de realisation\n");
    printf("3. Finalisee\n");
    int choixStatut;
    scanf("%d", &choixStatut);

    switch (choixStatut)
    {
    case 1:
        nouvelleTache.statut = A_REALISER;
        break;
    case 2:
        nouvelleTache.statut = EN_COURS;
        break;
    case 3:
        nouvelleTache.statut = FINALISEE;
        break;
    default:
        nouvelleTache.statut = A_REALISER;
        break;
    }
    return nouvelleTache;
}
// Fonction pour ajouter plusieurs t�ches � la fois
void ajouterPlusieursNouvellesTaches(NouvelleTache taches[], int capacite, int *nombre)
{
    int n, i;
    printf("Combien de nouvelles taches voulez-vous ajouter ?\n");
    scanf("%d", &n);

    if (n > capacite)
    {
        printf("Pas assez d'espace pour ajouter autant de taches!\n");
        return;
    }

    for (i = *nombre; i < *nombre + n; i++)
    {
        taches[i] = ajouterNouvelleTache();
    }
    *nombre += n;
}
// Fonction pour trier les t�ches par titre
void trierTachesParTitre(NouvelleTache taches[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (strcmp(taches[j].titre, taches[j + 1].titre) > 0)
            {
                NouvelleTache temp = taches[j];
                taches[j] = taches[j + 1];
                taches[j + 1] = temp;
            }
        }
    }
}
// Fonction pour trier les t�ches par date limite
void trierTachesParDeadline(NouvelleTache taches[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if ((taches[j].deadline.annee > taches[j + 1].deadline.annee) || (taches[j].deadline.annee == taches[j + 1].deadline.annee && (taches[j].deadline.mois > taches[j + 1].deadline.mois || (taches[j].deadline.mois == taches[j + 1].deadline.mois && taches[j].deadline.jour > taches[j + 1].deadline.jour))))
            {
                NouvelleTache temp = taches[j];
                taches[j] = taches[j + 1];
                taches[j + 1] = temp;
            }
        }
    }
}
// Fonction pour afficher la liste des t�ches
void afficherTaches(NouvelleTache taches[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Identifiant : %d\n", taches[i].id);
        printf("Titre : %s\n", taches[i].titre);
        printf("Description : %s\n", taches[i].description);
        printf("Deadline : %d/%d/%d\n", taches[i].deadline.jour, taches[i].deadline.mois, taches[i].deadline.annee);
        switch (taches[i].statut)
        {
        case A_REALISER:
            printf("Statut : A realiser\n");
            break;
        case EN_COURS:
            printf("Statut : En cours de realisation\n");
            break;
        case FINALISEE:
            printf("Statut : Finalisee\n");
            break;
        }
        printf("\n");
    }
}
// Fonction pour afficher le menu des choix pour les t�ches
void afficherDeChoix(NouvelleTache taches[], int nombre)
{

    int choix;

    do
    {
        printf("************* MENU ****************\n");
        printf("1 ----------> Trier les taches par ordre alphabique\n");
        printf("2 ----------> Trier les taches par deadline\n");
        printf("3 ----------> Afficher les taches avec deadline dans 3 jours ou moins\n");
        printf("4 ----------> Quitter\n");
        printf("*********************************\n");
        printf("Entrez votre choix (1, 2, 3, 4) : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            trierTachesParTitre(taches, nombre);
            afficherTaches(taches, nombre);
            break;
        case 2:
            trierTachesParDeadline(taches, nombre);
            afficherTaches(taches, nombre);
            break;
        case 3:
            // Code pour afficher les taches avec une deadline dans 3 jours ou moins
            for (int i = 0; i < nombre; i++)
            {
                int JJ, MM, AA;
                time_t t = time(NULL);
                struct tm *date = localtime(&t);
                JJ = date->tm_mday;
                MM = date->tm_mon + 1;
                AA = date->tm_year + 1900;
                printf("%d/%d/%d\n", MM, JJ, AA);
                if (((taches[i].deadline.jour + taches[i].deadline.mois * 30 + taches[i].deadline.annee * 365) - (JJ + MM * 30 + AA * 365)) <= 3)
                {
                    afficherTaches(taches, nombre);
                }
                else
                {
                    printf("riene de tache avec une deadline dans 3 jours ou moins");
                }
            }
                break;
            case 4:
                printf("Au revoir!\n");
            default:
                printf("Choix invalide\n");
                break;
            }
        }
        while (choix != 4);

    }
// Fonction pour modifier une tâche existante
void modifierTache(NouvelleTache taches[], int nombre)
    {
        int id, choix, i, trouve = 0;
        printf("Entrez l'identifiant de la tache a modifier: ");
        scanf("%d", &id);

        for (i = 0; i < nombre; i++)
        {
            if (taches[i].id == id)
            {
                trouve = 1;
                break;
            }
        }

        if (!trouve)
        {
            printf("Tache non trouvee.\n");
            return;
        }

        printf("Que voulez-vous modifier?\n");
        printf("1. Description\n");
        printf("2. Statut\n");
        printf("3. Deadline\n");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("Entrez la nouvelle description: ");
            scanf(" %[^\n]s", taches[i].description);
            break;
        case 2:
            printf("Choisissez le nouveau statut:\n");
            printf("1. A realiser\n");
            printf("2. En cours de realisation\n");
            printf("3. Finalisee\n");
            int nouveauStatut;
            scanf("%d", &nouveauStatut);

            switch (nouveauStatut)
            {
            case 1:
                taches[i].statut = A_REALISER;
                break;
            case 2:
                taches[i].statut = EN_COURS;
                break;
            case 3:
                taches[i].statut = FINALISEE;
                break;
            default:
                printf("Choix de statut invalide!\n");
                break;
            }
            break;
        case 3:
            printf("Entrez la nouvelle deadline (JJ MM AA): ");
            scanf(" %d%d%d", &taches[i].deadline.jour, &taches[i].deadline.mois, &taches[i].deadline.annee);
            break;
        default:
            printf("Choix invalide.\n");
            break;
        }
    }

    void supprimerTache(NouvelleTache taches[], int *nombre)
    {
        int id, i, trouve = 0;
        printf("Entrez l'identifiant de la tache a supprimer: ");
        scanf("%d", &id);

        for (i = 0; i < *nombre; i++)
        {
            if (taches[i].id == id)
            {
                trouve = 1;
                break;
            }
        }

        if (!trouve)
        {
            printf("Tache non trouvee.\n");
            return;
        }

        for (int j = i; j < *nombre - 1; j++)
        {
            taches[j] = taches[j + 1];
        }
        (*nombre)--;
    }
// Fonction pour rechercher une tâche par identifiant
    void rechercherTacheParIdentifiant(NouvelleTache taches[], int nombre)
    {
        int id, i, trouve = 0;
        printf("Entrez l'identifiant de la tache a rechercher: ");
        scanf("%d", &id);

        for (i = 0; i < nombre; i++)
        {
            if (taches[i].id == id)
            {
                trouve = 1;
                printf("Tache trouvee :\n");
                printf("Identifiant : %d\n", taches[i].id);
                printf("Titre : %s\n", taches[i].titre);
                printf("Description : %s\n", taches[i].description);
                printf("Deadline : %d/%d/%d\n", taches[i].deadline.jour, taches[i].deadline.mois, taches[i].deadline.annee);
                switch (taches[i].statut)
                {
                case A_REALISER:
                    printf("Statut : A realiser\n");
                    break;
                case EN_COURS:
                    printf("Statut : En cours de realisation\n");
                    break;
                case FINALISEE:
                    printf("Statut : Finalisee\n");
                    break;
                }
                break;
            }
        }

        if (!trouve)
        {
            printf("Tache non trouvee.\n");
        }
    }
// Fonction pour rechercher une tâche par titre
    void rechercherTacheParTitre(NouvelleTache taches[], int nombre)
    {
        char titreRecherche[20];
        printf("Entrez le titre de la tache a rechercher: ");
        scanf(" %[^\n]s", titreRecherche);

        int i, trouve = 0;
        printf("Taches avec le titre \"%s\" :\n", titreRecherche);

        for (i = 0; i < nombre; i++)
        {
            if (strcmp(taches[i].titre, titreRecherche) == 0)
            {
                trouve = 1;
                printf("Identifiant : %d\n", taches[i].id);
                printf("Titre : %s\n", taches[i].titre);
                printf("Description : %s\n", taches[i].description);
                printf("Deadline : %d/%d/%d\n", taches[i].deadline.jour, taches[i].deadline.mois, taches[i].deadline.annee);
                switch (taches[i].statut)
                {
                case A_REALISER:
                    printf("Statut : A realiser\n");
                    break;
                case EN_COURS:
                    printf("Statut : En cours de realisation\n");
                    break;
                case FINALISEE:
                    printf("Statut : Finalisee\n");
                    break;
                }
                break;
            }
        }

        if (!trouve)
        {
            printf("Aucune tache avec ce titre n'a ete trouvee.\n");
        }
    }
// Fonction pour afficher le menu de recherche des tâches
    void rechercherDeChoix(NouvelleTache taches[], int nombre)
    {

        int choix;

        do
        {
            printf("************* MENU ****************\n");
            printf("1 ----------> Rechercher une tache par son Identifiant.\n");
            printf("2 ----------> Rechercher une tache par son Titre\n");
            printf("3 ----------> Quitter\n");
            printf("*********************************\n");
            printf("Entrez votre choix (1, 2, 3) : ");
            scanf("%d", &choix);

            switch (choix)
            {
            case 1:
                rechercherTacheParIdentifiant(taches, nombre);
                break;
            case 2:
                rechercherTacheParTitre(taches, nombre);
                break;
            case 3:
                printf("Au revoir!\n");
            default:
                printf("Choix invalide\n");
                break;
            }
        } while (choix != 3);
    }
// Fonction pour afficher le total des tâches
    void afficherStatistiquesTotal(NouvelleTache taches[], int nombre)
    {
        printf("Nombre total de taches : %d\n", nombre);
    }
// Fonction pour afficher les statistiques des tâches complétées et incomplètes
    void afficherStatistiquesComp(NouvelleTache taches[], int nombre)
    {
        int completes = 0;
        int incompletes = 0;

        for (int i = 0; i < nombre; i++)
        {
            if (taches[i].statut == FINALISEE)
            {
                completes++;
            }
            else
            {
                incompletes++;
            }
        }

        printf("Nombre de taches completes : %d\n", completes);
        printf("Nombre de taches incompletes : %d\n", incompletes);
    }
// Fonction pour afficher le menu des statistiques des tâches
    void afficherStatistiques(NouvelleTache taches[], int nombre)
    {

        int choix;

        do
        {
            printf("************* MENU ****************\n");
            printf("1 ----------> Afficher le nombre total des taches.\n");
            printf("2 ----------> Afficher le nombre de taches completes et incompletes.\n");
            printf("3 ----------> Afficher le nombre de jours restants jusqu'au delai de chaque tache.\n");
            printf("4 ----------> Quitter\n");
            printf("*********************************\n");
            printf("Entrez votre choix (1, 2, 3, 4) : ");
            scanf("%d", &choix);

            switch (choix)
            {
            case 1:
                afficherStatistiquesTotal(taches, nombre);
                break;
            case 2:
                afficherStatistiquesComp(taches, nombre);
                break;
            case 3:

                for (int i = 0; i < nombre; i++)
                {
                    int JJ, MM, AA;
                    time_t t = time(NULL);
                    struct tm *date = localtime(&t);
                    JJ = date->tm_mday;
                    MM = date->tm_mon + 1;
                    AA = date->tm_year + 1900;
                    printf("%d/%d/%d\n", MM, JJ, AA);
                    int joursRest = (taches[i].deadline.jour + taches[i].deadline.mois * 30 + taches[i].deadline.annee * 365) - (JJ + MM * 30 + AA * 365);

                    printf("Tache %d - Jours restants jusqu'au delai : %d\n", taches[i].id, joursRest);
                }
                break;
            case 4:
                printf("Au revoir!\n");
            default:
                printf("Choix invalide\n");
                break;
            }
        } while (choix != 4);
    }
// Fonction principale du programme
    int main()
    {
        // Initialisation des variables nécessaires
        int choix;
        const int capacite = 10;
        int nombre = 0;
// Tableau pour stocker les tâches
        NouvelleTache taches[capacite];
// Boucle principale du programme pour afficher le menu et traiter les choix
        do
        {
            printf("************* MENU ****************\n");
            printf("1 ----------> Ajouter une nouvelle tache\n");
            printf("2 ----------> Ajouter plusieurs nouvelles taches\n");
            printf("3 ----------> Afficher la liste de toutes les taches\n");
            printf("4 ----------> Modifier une tache\n");
            printf("5 ----------> Supprimer une tache par identifiant.\n");
            printf("6 ----------> Rechercher les Taches\n");
            printf("7 ----------> Statistiques d'afficher\n");
            printf("*********************************\n");
            printf("Entrez votre choix (1,2,3,4,5,6,7) et 8 pour quitter le programme \n");
            scanf("%d", &choix);

            switch (choix)
            {
            case 1:
                if (nombre < capacite)
                {
                    taches[nombre] = ajouterNouvelleTache();
                    nombre++;
                }
                else
                {
                    printf("Le tableau est plein.\n");
                }
                break;
            case 2:
                ajouterPlusieursNouvellesTaches(taches, capacite, &nombre);
                break;
            case 3:
                afficherDeChoix(taches, nombre);
                break;
            case 4:
                modifierTache(taches, nombre);
                break;
            case 5:
                supprimerTache(taches, &nombre);
                break;
            case 6:
                rechercherDeChoix(taches, nombre);
                break;
            case 7:
                afficherStatistiques(taches, nombre);
                break;
            case 8:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide\n");
                break;
            }
        } while (choix != 8);

        return 0;
    }

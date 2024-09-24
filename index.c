#include <stdio.h> // Standard Input/Output library Contains functions for input and output, including:printf - scanf  - fgets
#include <stdlib.h> // Standard Library Provides functions for memory allocation, process control, and conversions:rand - srand - malloc
#include <string.h>  // String handling library Contains functions for manipulating C strings:strcpy - strlen - strstr - strcmp
#include <time.h> // Time library Contains functions for working with time and dates:time - localtime
#include <unistd.h> // POSIX Standard Library Provides access to the operating system's POSIX API, including: sleep: pauses the execution of the program 
#include <ctype.h>

#define MAX_UTILISATEUR 20
#define MAX_RECLAMATION 10
#define ID_LENGTH 20

typedef struct{
    char name_User[20];
    char password_User[20];
    char role[20];
}User;

typedef struct{
    char id[20];
    char categorie[30];
    char motif[50];
    char description[100];
    char status[10];
    char date[20];
    char priorite[20];
    char note[150];
    char name_utilisateur[20];
    char date_Traitement_resolu[20];
    char date_Traitement_rejecter[20];
}Reclamation;

User users[MAX_UTILISATEUR];
Reclamation reclamations[MAX_RECLAMATION];
User Admin;
User nouvelle_Utilisateur;
Reclamation nouvelle_Reclamation;

int user_Conteur = 0;
int reclamations_Conteur = 0;
int password_Incorrect_Conteur = 0;

int isAdmin = 0;
int isSignedIn = 0;
int isAgent = 0;
int isEnCours = 0;

int user_Index = -1;


void DateDuMoment(char date[20]) {
    // Obtenir l'heure actuelle
    time_t now = time(NULL);

    // Convertir l'heure actuelle en une structure tm, qui décompose le temps en composants
    // tels que l'année, le mois, le jour, l'heure, les minutes, les secondes, etc.
    struct tm *tm_now = localtime(&now);

    // Formater la date et l'heure actuelles dans une chaîne de caractères en utilisant le format
    // "%Y-%m-%d %H:%M:%S", ce qui donne un résultat du type "2024-09-24 14:53:34".
    strftime(date, 20, "%Y-%m-%d %H:%M:%S", tm_now);
}


void generateRandomID(char id[ID_LENGTH]) {
    // Ensemble de caractères possibles pour générer l'ID (lettres majuscules, minuscules et chiffres)
    char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    
    // Obtenir la longueur de la chaîne de caractères 'characters'
    int char_count = strlen(characters);

    // Générer un ID aléatoire de longueur ID_LENGTH - 1
    for (int i = 0; i < ID_LENGTH - 1; i++) { 
        // Sélectionner un caractère aléatoire parmi 'characters' et l'ajouter à l'ID
        id[i] = characters[rand() % char_count];
    }
    
    // Ajouter le caractère de fin de chaîne '\0' pour indiquer la fin de l'ID
    id[ID_LENGTH - 1] = '\0'; 
}


void miniscule(char *str) {
    // Parcourt chaque caractère de la chaîne de caractères 'str'
    for (int i = 0; str[i]; i++) {
        // Convertit le caractère en minuscule si c'est une lettre majuscule
        // (On passe chaque caractère à la fonction 'tolower')
        str[i] = tolower((unsigned char)str[i]);
    }
}


int checkPassword(char utilisateur[20], char password_Utilisateur[20]) {
    int isUpper = 0;        // Vérifie la présence d'une lettre majuscule
    int isLower = 0;        // Vérifie la présence d'une lettre minuscule
    int isNumber = 0;       // Vérifie la présence d'un chiffre
    int isSpecial = 0;      // Vérifie la présence d'un caractère spécial
    int isMinuLength = 8;   // Longueur minimale requise pour le mot de passe
    int passLength = strlen(password_Utilisateur); // Longueur du mot de passe
    int isValid = 1;        // Drapeau pour indiquer si le mot de passe est valide

    // Vérifie si la longueur du mot de passe est inférieure à 8 caractères
    if (passLength < isMinuLength) {
        printf("Le mot de passe doit contenir au moins 8 caracteres.\n");
        isValid = 0;
    }

    // Boucle à travers chaque caractère du mot de passe pour vérifier les critères
    for (int i = 0; i < passLength; i++) {
        if (password_Utilisateur[i] >= 'A' && password_Utilisateur[i] <= 'Z') {
            isUpper = 1; // Présence de majuscule
        } else if (password_Utilisateur[i] >= 'a' && password_Utilisateur[i] <= 'z') {
            isLower = 1; // Présence de minuscule
        } else if (password_Utilisateur[i] >= '0' && password_Utilisateur[i] <= '9') {
            isNumber = 1; // Présence de chiffre
        } else {
            isSpecial = 1; // Présence de caractère spécial (tout autre caractère)
        }
    }
    
    // Vérifie si une majuscule est absente
    if (!isUpper) {
        printf("Le mot de passe doit contenir au moins une lettre majuscule.\n");
        isValid = 0;
    }

    // Vérifie si une minuscule est absente
    if (!isLower) {
        printf("Le mot de passe doit contenir au moins une lettre minuscule.\n");
        isValid = 0;
    }

    // Vérifie si un chiffre est absent
    if (!isNumber) {
        printf("Le mot de passe doit contenir au moins un chiffre.\n");
        isValid = 0;
    }

    // Vérifie si un caractère spécial est absent
    if (!isSpecial) {
        printf("Le mot de passe doit contenir au moins un caractere special.\n");
        isValid = 0;
    }

    // Copie du nom d'utilisateur et du mot de passe en minuscules pour comparer
    char miniscule_utilisateur[20];
    char miniscule_password_Utilisateur[20];

    strcpy(miniscule_utilisateur, utilisateur);                // Copie du nom d'utilisateur
    strcpy(miniscule_password_Utilisateur, password_Utilisateur);  // Copie du mot de passe

    miniscule(miniscule_utilisateur);  // Conversion du nom d'utilisateur en minuscules
    miniscule(miniscule_password_Utilisateur); // Conversion du mot de passe en minuscules

    // Vérifie si le mot de passe contient le nom d'utilisateur
    if (strstr(miniscule_password_Utilisateur, miniscule_utilisateur) != NULL) {
        printf("Le mot de passe ne doit pas contenir le nom d'utilisateur.\n");
        isValid = 0;
    }

    return isValid; // Retourne 1 si le mot de passe est valide, 0 sinon
}


int UserCheck(char utilisateur[20], char password_Utilisateur[20]) {
    // Boucle à travers tous les utilisateurs enregistrés dans le tableau 'users'
    for (int i = 0; i < user_Conteur; i++) {

        // Comparaison du nom d'utilisateur avec celui stocké dans la structure 'users'
        // Si le nom d'utilisateur et le mot de passe correspondent
        if (strcmp(users[i].name_User, utilisateur) == 0 && 
            strcmp(users[i].password_User, password_Utilisateur) == 0) {
                
            // Retourne l'indice de l'utilisateur trouvé dans le tableau
            return i;
        }
    }

    // Si aucun utilisateur ne correspond, retourne -1
    return -1;
}


void MenuSignIn() {
    char utilisateur[20]; // Stocke le nom d'utilisateur
    char password_Utilisateur[20]; // Stocke le mot de passe de l'utilisateur
    int isUser = 0;  // Indique si l'utilisateur a réussi à se connecter
    int utilisateur_trouver = 0;  // Indique si le nom d'utilisateur a été trouvé
    int User_index_sign_in_function; // Contient l'indice de l'utilisateur dans le tableau

    printf("========== Sign In ==========\n");

    // Boucle jusqu'à ce que l'utilisateur entre des informations valides
    while (isUser == 0) {
        printf("Entrez votre nom du compte : ");
        scanf("%s", utilisateur);  // Saisir le nom d'utilisateur
        
        // Recherche du nom d'utilisateur dans la liste des utilisateurs
        for (int i = 0; i < user_Conteur; i++) {
            if (strcmp(users[i].name_User, utilisateur) == 0) {
                utilisateur_trouver = 1;  // L'utilisateur a été trouvé
                User_index_sign_in_function = i; // Stocke l'indice de l'utilisateur
                break; // Sortir de la boucle une fois trouvé
            }
        }

        // Si le nom d'utilisateur est incorrect, on redemande à l'utilisateur de réessayer
        if (utilisateur_trouver == 0) {
            printf("Le nom d'utilisateur est incorrect.\n");
            continue;  // Recommence la boucle
        }

        printf("Entrez votre Mode de Passe : ");
        scanf("%s", password_Utilisateur); // Saisir le mot de passe

        // Vérifie si le nom d'utilisateur et le mot de passe correspondent
        User_index_sign_in_function = UserCheck(utilisateur, password_Utilisateur);

        if (User_index_sign_in_function != -1) {  // Si l'utilisateur est valide
            user_Index = User_index_sign_in_function; // Sauvegarde l'indice de l'utilisateur
            isAdmin = 0;  // Réinitialise le rôle admin
            isAgent = 0;  // Réinitialise le rôle agent
            printf("\n");

            // Vérifie si l'utilisateur est administrateur
            if (strcmp(users[User_index_sign_in_function].role, "administrateur") == 0) {
                isAdmin = 1; // Active le rôle administrateur
                printf("Bienvenue, Administrateur.\n");
            }
            // Vérifie si l'utilisateur est un agent
            else if (strcmp(users[User_index_sign_in_function].role, "Agent") == 0) {
                isAgent = 1; // Active le rôle agent
                printf("Bienvenue, Agent.\n");
            }
            // Si l'utilisateur est un simple utilisateur
            else {
                printf("Bienvenue, Utilisateur.\n");
            }

            isUser = 1; // Indique que l'utilisateur est connecté

        } else {  // Si le mot de passe est incorrect
            printf("Le nom d'utilisateur ou le mot de passe est incorrect.\n");
            password_Incorrect_Conteur++; // Incrémente le compteur d'erreurs

            // Si l'utilisateur échoue 3 fois
            if (password_Incorrect_Conteur == 3) {
                printf("Vous avez atteint le nombre maximum de tentatives. Veuillez attendre 30 secondes.\n");
                sleep(30); // Attente de 30 secondes
                password_Incorrect_Conteur = 0; // Réinitialise le compteur d'erreurs
            }
        }
    }

    isSignedIn = 1; // Marque l'utilisateur comme connecté
    password_Incorrect_Conteur = 0; // Réinitialise le compteur d'erreurs
    printf("\n");
}


int UtilisateurExiste(char utilisateur[20]) {
    // Parcourt la liste des utilisateurs enregistrés
    for (int i = 0; i < user_Conteur; i++) {
        // Compare le nom d'utilisateur fourni avec chaque utilisateur de la liste
        if (strcmp(users[i].name_User, utilisateur) == 0) {
            return 1;  // L'utilisateur existe déjà
        }
    }
    return 0;  // L'utilisateur n'existe pas
}


void MenuSignUp() {
    char utilisateur[20];  // Stocke le nom d'utilisateur
    char password_Utilisateur[20];  // Stocke le mot de passe
    int i = 0;  // Variable de contrôle pour la validation du mot de passe

    printf("========== Sign Up ==========\n");

    // Boucle pour obtenir un nom d'utilisateur valide
    while (1) { 
        printf("Entrez votre nom du compte : ");
        scanf(" %s", utilisateur);

        // Vérifie si le nom d'utilisateur existe déjà
        if (UtilisateurExiste(utilisateur)) {
            printf("Ce compte existe deja. Veuillez entrer un autre nom d'utilisateur.\n");
        } else {
            break;  // Si le nom d'utilisateur est unique, sortir de la boucle
        }
    }

    // Boucle pour obtenir un mot de passe valide
    do {
        printf("Entrez votre Mode de Passe : ");
        scanf(" %s", password_Utilisateur);
        i = checkPassword(utilisateur, password_Utilisateur);  // Vérifie les critères du mot de passe
    } while (i != 1);  // Continue jusqu'à ce qu'un mot de passe valide soit entré

    // Sauvegarde les informations du nouvel utilisateur
    strcpy(nouvelle_Utilisateur.name_User, utilisateur);
    strcpy(nouvelle_Utilisateur.password_User, password_Utilisateur);
    strcpy(nouvelle_Utilisateur.role, "Client");  // Définit le rôle par défaut en tant que "Client"

    users[user_Conteur++] = nouvelle_Utilisateur;  // Ajoute le nouvel utilisateur au tableau des utilisateurs

    printf("Inscription reussie pour %s.\n", utilisateur);  // Confirmation de l'inscription
}


void GestionUtilisateurs() {
    char nom_utilisateur[30];  // Variable pour stocker le nom de l'utilisateur à supprimer
    int delete_Another = 1;  // Variable de contrôle pour savoir si on souhaite supprimer un autre utilisateur
    int trouver = 0;  // Indicateur pour vérifier si l'utilisateur a été trouvé

    do {
        getchar();  // Nettoie le buffer d'entrée
        printf("Les Utilisateurs sont : \n");
        // Affiche la liste actuelle des utilisateurs
        for (int i = 0; i < user_Conteur; i++) {
            printf("Utilisateur %d: Nom: %s, Role: %s\n", i + 1, users[i].name_User, users[i].role);
        }
        printf("\n");

        printf("Entrez le nom d'utilisateur a Supprimer : ");
        fgets(nom_utilisateur, 30, stdin);  // Lit le nom de l'utilisateur à supprimer

        nom_utilisateur[strcspn(nom_utilisateur, "\n")] = 0;  // Enlève le caractère de nouvelle ligne

        // Vérifie si l'utilisateur à supprimer est l'administrateur
        if (strcmp(nom_utilisateur, users[0].name_User) == 0) {
            printf("Vous ne pouvez pas supprimer l'administrateur.\n");
        } else {
            // Cherche l'utilisateur dans la liste
            for (int i = 0; i < user_Conteur; i++) {
                if (strcmp(users[i].name_User, nom_utilisateur) == 0) {
                    trouver = 1;  // Utilisateur trouvé

                    // Décale tous les utilisateurs suivants vers le haut pour supprimer l'utilisateur
                    for (int j = i; j < user_Conteur - 1; j++) {
                        strcpy(users[j].name_User, users[j + 1].name_User);
                        strcpy(users[j].password_User, users[j + 1].password_User);
                        strcpy(users[j].role, users[j + 1].role);
                    }
                    user_Conteur--;  // Décrémente le compteur d'utilisateurs
                    printf("Utilisateur %s supprime.\n\n", nom_utilisateur);
                    break;  // Sort de la boucle après suppression
                }
            }

            // Si l'utilisateur n'a pas été trouvé
            if (!trouver) {
                printf("L'utilisateur n'existe pas ou le nom est incorrect.\n\n");
            }
        }

        // Affiche la nouvelle liste des utilisateurs
        printf("Nouvelle liste des utilisateurs : \n");
        for (int i = 0; i < user_Conteur; i++) {
            printf("Utilisateur %d: Nom: %s, Role: %s\n", i + 1, users[i].name_User, users[i].role);
        }
        
        printf("\n");
      
        // Demande si l'utilisateur souhaite supprimer un autre utilisateur
        printf("Voulez-vous supprimer un autre utilisateur ? (1 pour OUI, 0 pour NON) : ");
        scanf("%d", &delete_Another);

        printf("\n\n");

    } while (delete_Another == 1);  // Continue tant que l'utilisateur veut supprimer d'autres comptes

}


void afficherLesReclamations() {
    int reclamation_En_Cours = 0;  // Indicateur pour savoir si des réclamations sont en cours
    int conteur_En_Cours = 0;  // Compteur pour les réclamations en cours

    // Vérifie si l'on veut afficher toutes les réclamations (isEnCours == 0)
    if (isEnCours == 0) {
        // Si aucune réclamation n'a été soumise
        if (reclamations_Conteur == 0) {
            printf("Aucune reclamation n'a ete soumise.\n");
            return;  // Quitte la fonction si aucune réclamation n'existe
        }  
        printf("Les reclamations sont : \n");
        // Affiche toutes les réclamations soumises
        for (int i = 0; i < reclamations_Conteur; i++) {
            printf("- Reclamation %d: ID: %s ", i + 1, reclamations[i].id);
            printf("- Categorie: %s ", reclamations[i].categorie);
            printf("- Motif: %s\n", reclamations[i].motif);
            printf("- Description: %s\n", reclamations[i].description);
            printf("- Statut: %s\n", reclamations[i].status);
            printf("- Date: %s\n", reclamations[i].date);
            printf("- Client : %s\n", reclamations[i].name_utilisateur);
            printf("==========================================\n\n");
        }
    }
    
    // Vérifie si l'on veut afficher les réclamations en cours (isEnCours != 0)
    if (isEnCours) {
        // Parcourt les réclamations pour trouver celles en cours
        for (int i = 0; i < reclamations_Conteur; i++) {
            if (strcmp(reclamations[i].status, "En Cours") == 0) {
                reclamation_En_Cours = 1;  // Marque qu'il y a au moins une réclamation en cours
                conteur_En_Cours++;  // Incrémente le compteur des réclamations en cours
                printf("- Reclamation %d: ID: %s ", conteur_En_Cours, reclamations[i].id);
                printf("- Categorie: %s ", reclamations[i].categorie);
                printf("- Motif: %s\n", reclamations[i].motif);
                printf("- Description: %s\n", reclamations[i].description);
                printf("- Statut: %s\n", reclamations[i].status);
                printf("- Date: %s\n", reclamations[i].date);
                printf("- Client : %s\n", reclamations[i].name_utilisateur);
                printf("==========================================\n\n");
            }
        }
        // Si aucune réclamation en cours n'est trouvée
        if (!reclamation_En_Cours) {
            printf("Aucune reclamation n'est en cours.\n\n");
        }
    }
}


void GestionReclamations() {
    int choix_Supprimer;  // Variable pour stocker le numéro de la réclamation à supprimer
    char annuler_choix[10];  // Buffer pour la saisie utilisateur

    // Vérifie s'il y a des réclamations à gérer
    if (reclamations_Conteur == 0) {
        printf("Aucune reclamation pour le Moment.\n\n");  // Aucune réclamation à afficher
    } else {
        afficherLesReclamations();  // Affiche toutes les réclamations
        
        getchar();  // Nettoie le buffer d'entrée
        while (1) {  // Boucle infinie jusqu'à ce qu'une action soit validée ou annulée
            printf("Entrez le numero de la reclamation que vous voulez supprimer ou entrez '.' pour annuler l'action : ");
            fgets(annuler_choix, sizeof(annuler_choix), stdin);  // Lit l'entrée utilisateur

            // Vérifie si l'utilisateur veut annuler l'action
            if (annuler_choix[0] == '.' && annuler_choix[1] == '\n') {
                printf("Action annulee.\n");  // Informe l'utilisateur que l'action est annulée
                return;  // Quitte la fonction
            }

            // Essaye de convertir l'entrée en entier
            if (sscanf(annuler_choix, "%d", &choix_Supprimer) == 1) {
                
                // Vérifie si le numéro de la réclamation est valide
                if (choix_Supprimer > 0 && choix_Supprimer <= reclamations_Conteur) {
                    
                    // Supprime la réclamation choisie en décalant les suivantes
                    for (int i = choix_Supprimer - 1; i < reclamations_Conteur - 1; i++) {
                        reclamations[i] = reclamations[i + 1];  // Décalage des réclamations
                    }
                    reclamations_Conteur--;  // Décrémente le compteur de réclamations
                    printf("Reclamation %d supprimee avec succes.\n", choix_Supprimer);  // Confirmation de la suppression
                    break;  // Sort de la boucle
                } else {
                    // Informe l'utilisateur que le numéro de réclamation est invalide
                    printf("Numero de reclamation invalide. Veuillez reessayer.\n");
                }
            } else {
                // Informe l'utilisateur que l'entrée est invalide
                printf("Entree invalide. Veuillez entrer un numero de reclamation valide ou '.' pour annuler.\n");
            }
        }
    }
}


void AttribuerRoles() {
    char nom_utilisateur[30];  // Variable pour stocker le nom de l'utilisateur
    int Choix_New_Role;  // Variable pour stocker le choix de rôle
    char Nouveau_Role[30];  // Variable pour stocker le nouveau rôle (non utilisée)
    int trouver = 0;  // Indicateur pour vérifier si l'utilisateur a été trouvé

    getchar();  // Nettoie le buffer d'entrée
    printf("Les Utilisateurs sont : \n");
    // Affiche la liste des utilisateurs avec leurs rôles
    for (int i = 0; i < user_Conteur; i++) {
        printf("Utilisateur %d: Nom: %s, Role: %s\n", i + 1, users[i].name_User, users[i].role);
    }
    printf("\n");

    // Boucle pour obtenir un nom d'utilisateur valide
    while (1) { 
        printf("Entrez le nom d'utilisateur pour changer leur role : ");
        scanf(" %s", nom_utilisateur);  // Lecture du nom d'utilisateur

        // Vérifie si l'utilisateur est l'administrateur
        if (strcmp(nom_utilisateur, users[0].name_User) == 0) {
            printf("Vous ne pouvez pas changer le role de l'administrateur.\n\n");
            return;  // Quitte la fonction si c'est l'administrateur
        }

        // Vérifie si l'utilisateur existe
        if (UtilisateurExiste(nom_utilisateur)) {
            break;  // Sort de la boucle si l'utilisateur existe
        } else {
            printf("Ce compte n'existe pas. Veuillez entrer un autre nom d'utilisateur.\n");
        }
    }
    
    // Propose les choix de rôle à l'utilisateur
    printf("Choisir le nouveau role : 1 - Administrateur, 2 - Agent, 3 - Client\n");
    scanf(" %d", &Choix_New_Role);  // Lecture du choix de rôle

    // Boucle pour trouver l'utilisateur correspondant
    for (int i = 0; i < user_Conteur; i++) {
        if (strcmp(users[i].name_User, nom_utilisateur) == 0) {
            trouver = 1;  // Marque que l'utilisateur a été trouvé
            
            // Changement de rôle basé sur le choix
            switch (Choix_New_Role) {
                case 1:
                    strcpy(users[i].role, "administrateur");  // Attribue le rôle d'administrateur
                    isAdmin = 1;  // Met à jour l'indicateur d'administrateur
                    break;
                case 2:
                    strcpy(users[i].role, "Agent");  // Attribue le rôle d'agent
                    isAgent = 1;  // Met à jour l'indicateur d'agent
                    break;
                case 3:
                    strcpy(users[i].role, "client");  // Attribue le rôle de client
                    break;
                default:
                    printf("Choix de role invalide.\n");
                    return;  // Quitte la fonction si le choix est invalide
            }
            
            // Affiche un message de confirmation
            printf("Le role de l'utilisateur %s a ete change en %s.\n\n", nom_utilisateur, users[i].role);
            break;  // Sort de la boucle après avoir changé le rôle
        }
    }
    
    // Si l'utilisateur n'a pas été trouvé, affiche un message d'erreur
    if (!trouver) {
        printf("L'utilisateur n'existe pas ou le nom est incorrect.\n\n");
    }
}


void parseDateTime(const char* dateString, struct tm* tm) {
    memset(tm, 0, sizeof(struct tm));  // Initialise la structure à zéro
    // Utilise sscanf pour extraire les composants de la date et de l'heure
    sscanf(dateString, "%d-%d-%d %d:%d:%d",
           &tm->tm_year, &tm->tm_mon, &tm->tm_mday,  // Récupération de l'année, du mois et du jour
           &tm->tm_hour, &tm->tm_min, &tm->tm_sec);  // Récupération de l'heure, des minutes et des secondes

    tm->tm_year -= 1900;  // Ajuste l'année (nombre d'années depuis 1900)
    tm->tm_mon -= 1;      // Ajuste le mois (0-11 pour janvier à décembre)
    tm->tm_isdst = -1;    // Permet au système de déterminer si l'heure d'été est en vigueur
}


void GenererRapportQuotidien(float Ratio_Resolution, double moyenne) {
    // Ouvre ou crée le fichier "rapport_quotidien.txt" en mode écriture
    FILE *file = fopen("rapport_quotidien.txt", "w");
    if (!file) {
        printf("Erreur lors de la création du fichier.\n");
        return;  // Retourne si l'ouverture du fichier échoue
    }

    // Écrit l'en-tête du rapport
    fprintf(file, "Rapport Quotidien des Réclamations\n");
    fprintf(file, "=================================\n\n");

    // Écrit les informations de base sur les réclamations
    fprintf(file, "Nombre total de réclamations : %d\n", reclamations_Conteur);
    fprintf(file, "Taux de resolution des réclamations : %.2f%%\n", Ratio_Resolution);
    fprintf(file, "Delai moyen de traitement des reclamations resolues : %.2f secondes\n", moyenne);

    fprintf(file, "=================================\n\n");

    // Vérifie et imprime "Nouvelles Réclamations" s'il y a des réclamations "En Cours"
    int nouvelles_found = 0; // Indicateur pour vérifier si des réclamations en cours ont été trouvées
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].status, "En Cours") == 0) {
            if (!nouvelles_found) {
                fprintf(file, "Nouvelles Réclamations:\n\n");
                nouvelles_found = 1; // Marque que nous avons trouvé des réclamations en cours
            }
            // Écrit les détails de la réclamation
            fprintf(file, "%d - ID: %s, Catégorie: %s, Motif: %s, Description: %s, Date: %s\n", i+1,
                    reclamations[i].id, reclamations[i].categorie, 
                    reclamations[i].motif, reclamations[i].description,
                    reclamations[i].date);
        }
    }

    // Vérifie et imprime "Réclamations Résolues" s'il y a des réclamations "resolu"
    int resolues_found = 0; // Indicateur pour les réclamations résolues
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].status, "resolu") == 0) {
            if (!resolues_found) {
                fprintf(file, "\nRéclamations Résolues:\n\n");
                resolues_found = 1; // Marque que nous avons trouvé des réclamations résolues
            }
            // Écrit les détails de la réclamation résolue
            fprintf(file, "%d - ID: %s, Catégorie: %s, Motif: %s, Description: %s, Date de Resolution: %s\n", i+1,
                    reclamations[i].id, reclamations[i].categorie, 
                    reclamations[i].motif, reclamations[i].description,
                    reclamations[i].date_Traitement_resolu);
        }
    }

    // Vérifie et imprime "Réclamations Rejetées" s'il y a des réclamations "rejecter"
    int rejectees_found = 0; // Indicateur pour les réclamations rejetées
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].status, "rejecter") == 0) {
            if (!rejectees_found) {
                fprintf(file, "\nRéclamations Rejectées:\n\n");
                rejectees_found = 1; // Marque que nous avons trouvé des réclamations rejetées
            }
            // Écrit les détails de la réclamation rejetée
            fprintf(file, "%d - ID: %s, Catégorie: %s, Motif: %s, Description: %s, Date de Rejet: %s\n", i+1,
                    reclamations[i].id, reclamations[i].categorie, 
                    reclamations[i].motif, reclamations[i].description,
                    reclamations[i].date_Traitement_rejecter);
        }
    }

    fclose(file);  // Ferme le fichier
    printf("Rapport quotidien genere avec succes.\n");  // Message de succès
}


void GenerationStatistiques() {
    int resolution_Conteur = 0; // Compteur pour le nombre de réclamations résolues
    double total_time = 0; // Temps total de traitement des réclamations résolues

    printf("Nombre total de reclamations : %d\n", reclamations_Conteur);

    // Parcourt toutes les réclamations
    for (int i = 0; i < reclamations_Conteur; i++) {
        // Vérifie si la réclamation est résolue
        if (strcmp(reclamations[i].status, "resolu") == 0) {
            resolution_Conteur++; // Incrémente le compteur de réclamations résolues

            struct tm tm_creation = {0}, tm_resolution = {0}; // Structures pour stocker les dates
            time_t claimTime, resolutionTime;

            // Analyse les dates des réclamations
            parseDateTime(reclamations[i].date, &tm_creation);
            parseDateTime(reclamations[i].date_Traitement_resolu, &tm_resolution);

            // Convertit les structures tm en time_t
            claimTime = mktime(&tm_creation);
            resolutionTime = mktime(&tm_resolution);

            // Calcule la durée en secondes entre la création et la résolution
            double duration = difftime(resolutionTime, claimTime);
            total_time += duration; // Ajoute la durée totale
        }
    }

    // Vérifie si des réclamations ont été soumises
    if (reclamations_Conteur == 0) {
        printf("Aucune reclamation soumise.\n");
        return; // Retourne si aucune réclamation n'est soumise
    }

    // Calcule le taux de résolution
    float Ratio_Resolution = (float)resolution_Conteur / reclamations_Conteur * 100;
    printf("Taux de resolution des reclamations : %.2f%%\n", Ratio_Resolution);

    // Calcule le délai moyen de traitement des réclamations résolues
    double moyenne = total_time / resolution_Conteur; 
    if (resolution_Conteur > 0) {
        printf("Delai moyen de traitement des reclamations resolues : %.2f secondes\n", moyenne);
    } else {
        printf("Aucune reclamation resolue pour le calcul du delai.\n");
    }

    // Génère le rapport quotidien avec les statistiques calculées
    GenererRapportQuotidien(Ratio_Resolution, moyenne);
}


void TraiterReclamation() {
    int choix_reclamation; // Choix de la réclamation à traiter
    int nouvelle_status;   // Nouveau statut de la réclamation
    int note_choix;        // Choix pour ajouter une note
    char note[150];        // Note à ajouter
    char continuer[10];    // Variable pour continuer ou non

    printf("Traiter Les reclamations : \n\n");

    while (1) {
        // Affiche toutes les réclamations
        printf("Liste de toutes les reclamations :\n");
        for (int i = 0; i < reclamations_Conteur; i++) {
            printf("%d. ID: %d, Status: %s, Description: %s, Note de Traitement : %s\n", 
                   i + 1, reclamations[i].id, reclamations[i].status, reclamations[i].description,
                   (strlen(reclamations[i].note) == 0 ? "-----" : reclamations[i].note));
        }

        // Affiche les réclamations en cours
        printf("\nReclamations en cours :\n");
        int j = 1;
        for (int i = 0; i < reclamations_Conteur; i++) {
            if (strcmp(reclamations[i].status, "En Cours") == 0) {
                printf("%d. ID: %d, Description: %s\n", 
                       j++, reclamations[i].id, reclamations[i].description);
            }
        }

        // Demande à l'utilisateur d'entrer le numéro de la réclamation à traiter
        printf("\nEntrez le numero de la reclamation que vous voulez traiter (0 pour quitter) : ");
        if (scanf("%d", &choix_reclamation) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n'); 
            continue;
        }

        // Quitte si l'utilisateur entre 0
        if (choix_reclamation == 0) {
            printf("Retour au menu principal.\n");
            break;
        }

        // Recherche l'index de la réclamation sélectionnée
        int claim_index = -1;
        j = 1;
        for (int i = 0; i < reclamations_Conteur; i++) {
            if (strcmp(reclamations[i].status, "En Cours") == 0) {
                if (j == choix_reclamation) {
                    claim_index = i; // Trouvé
                    break;
                }
                j++;
            }
        }

        // Vérifie si la réclamation est valide
        if (claim_index == -1) {
            printf("Numero de reclamation invalide ou la reclamation n'est pas en cours. Veuillez reessayer.\n");
            continue;
        }

        // Demande à l'utilisateur d'entrer le nouveau statut
        printf("Entrez le nouveau statut de la reclamation (1 - Resolue, 2 - Rejecter) : ");
        while (scanf("%d", &nouvelle_status) != 1 || (nouvelle_status != 1 && nouvelle_status != 2)) {
            printf("Statut non valide. Veuillez entrer 1 (Resolue) ou 2 (Rejecter) : ");
            while (getchar() != '\n');
        }

        // Demande si l'utilisateur veut ajouter une note
        printf("Voulez-vous entrer une note sur le traitement ? (1 - Oui, 2 - Non) : ");
        while (scanf("%d", &note_choix) != 1 || (note_choix != 1 && note_choix != 2)) {
            printf("Entree non valide. Veuillez entrer 1 (Oui) ou 2 (Non) : ");
            while (getchar() != '\n');
        }

        // Si l'utilisateur choisit d'ajouter une note, lit la note
        if (note_choix == 1) {
            printf("Entrez votre note : ");
            getchar(); // Vide le buffer
            fgets(note, sizeof(note), stdin); // Lit la note
            note[strcspn(note, "\n")] = '\0'; // Enlève le saut de ligne
            strcpy(reclamations[claim_index].note, note); // Stocke la note
        }

        // Change le statut de la réclamation
        switch (nouvelle_status) {
            case 1:
                strcpy(reclamations[claim_index].status, "resolu");
                DateDuMoment(reclamations[claim_index].date_Traitement_resolu); // Met à jour la date de traitement
                printf("La reclamation numero %d a ete resolue.\n", choix_reclamation);
                break;
            case 2:
                strcpy(reclamations[claim_index].status, "rejecter");
                DateDuMoment(reclamations[claim_index].date_Traitement_rejecter); // Met à jour la date de rejet
                printf("La reclamation numero %d a ete rejecter.\n", choix_reclamation);
                break;
        }

        // Affiche si une note a été ajoutée
        if (note_choix == 1) {
            printf("Note ajoutee : %s\n", reclamations[claim_index].note);
        } else {
            printf("Aucune note n'a ete ajoutee.\n");
        }

        // Demande si l'utilisateur veut traiter une autre réclamation
        printf("\nVoulez-vous traiter une autre reclamation ? (o/n) : ");
        scanf("%s", continuer);
        if (strcmp(continuer, "n") == 0) {
            break; // Sort de la boucle
        }
    }
}

void AjouterReclamation() {
    int categorie_choix; // Variable pour choisir la catégorie de la réclamation
    char *high[] = {"urgent", "critique", "importante"}; // Mots-clés pour priorité élevée
    char *moyen[] = {"asap", "modere", "rapide"}; // Mots-clés pour priorité moyenne
    char miniscule_description[100], miniscule_motif[50]; // Buffers pour stocker description et motif en minuscules
    int trouver_high = 0, trouver_moyen = 0; // Flags pour déterminer la priorité

    // Générer un nouvel ID pour la réclamation et enregistrer la date actuelle
    generateRandomID(nouvelle_Reclamation.id);
    DateDuMoment(nouvelle_Reclamation.date);

    // Enregistrer le nom de l'utilisateur qui soumet la réclamation
    strcpy(nouvelle_Reclamation.name_utilisateur, users[user_Index].name_User);
    
    do {
        // Afficher les options de catégories pour la réclamation
        printf("Entrez la categorie de votre Reclamation 1 - Financier , 2 - Technique, 3 - Service 4 - Autre \n");
        scanf(" %d", &categorie_choix);

        // Déterminer la catégorie choisie
        switch (categorie_choix) {
            case 1:
                strcpy(nouvelle_Reclamation.categorie, "financier");
                break;
            case 2:
                strcpy(nouvelle_Reclamation.categorie, "technique");
                break;
            case 3:
                strcpy(nouvelle_Reclamation.categorie, "service");
                break;
            case 4:
                strcpy(nouvelle_Reclamation.categorie, "autre");
                break;
            default:
                printf("choix invalide\n\n"); 
                break;
        }

    } while (categorie_choix < 1 || categorie_choix > 4); // Répéter jusqu'à un choix valide

    // Demander le motif de la réclamation
    printf("Entrez le Motif du reclamation : ");
    getchar(); // Pour vider le buffer avant de lire une chaîne
    fgets(nouvelle_Reclamation.motif, sizeof(nouvelle_Reclamation.motif), stdin);
    nouvelle_Reclamation.motif[strcspn(nouvelle_Reclamation.motif, "\n")] = 0; // Enlever le saut de ligne

    // Demander la description de la réclamation
    printf("Entrez la description du reclamation : ");
    fgets(nouvelle_Reclamation.description, sizeof(nouvelle_Reclamation.description), stdin);
    nouvelle_Reclamation.description[strcspn(nouvelle_Reclamation.description, "\n")] = 0; // Enlever le saut de ligne

    // Initialiser le statut de la réclamation à "En Cours"
    strcpy(nouvelle_Reclamation.status, "En Cours");

    // Copier la description et le motif pour les transformer en minuscules
    strcpy(miniscule_description, nouvelle_Reclamation.description);
    strcpy(miniscule_motif, nouvelle_Reclamation.motif);
    miniscule(miniscule_description); // Convertir en minuscules
    miniscule(miniscule_motif); // Convertir en minuscules

    // Vérifier si des mots-clés pour priorité élevée sont présents
    for (int i = 0; i < sizeof(high) / sizeof(high[0]); i++) {
        if (strstr(miniscule_description, high[i]) != NULL || strstr(miniscule_motif, high[i]) != NULL) {
            trouver_high = 1; // Trouvé un mot-clé pour priorité élevée
            break;
        }
    }

    // Si aucun mot-clé élevé trouvé, vérifier pour les mots-clés moyens
    if (!trouver_high) {
        for (int i = 0; i < sizeof(moyen) / sizeof(moyen[0]); i++) {
            if (strstr(miniscule_description, moyen[i]) != NULL || strstr(miniscule_motif, moyen[i]) != NULL) {
                trouver_moyen = 1; // Trouvé un mot-clé pour priorité moyenne
                break;
            }
        }
    }

    // Déterminer la priorité en fonction des mots-clés trouvés
    if (trouver_high) {
        strcpy(nouvelle_Reclamation.priorite, "High");
    } else if (trouver_moyen) {
        strcpy(nouvelle_Reclamation.priorite, "Moyen");
    } else {
        strcpy(nouvelle_Reclamation.priorite, "Basse");
    }

    // Ajouter la nouvelle réclamation au tableau des réclamations
    reclamations[reclamations_Conteur++] = nouvelle_Reclamation;

    // Confirmer que la réclamation a été ajoutée avec succès
    printf("Reclamation ajoutee avec succes. ID: %s\n", nouvelle_Reclamation.id);
}

int apres24Heures(const char* dateString) {
    struct tm tm = {0}; // Structure pour stocker la date et l'heure
    time_t claimTime, currentTime; // Variables pour stocker le temps sous forme de time_t

    // Convertit la chaîne de caractères en une structure tm
    parseDateTime(dateString, &tm);

    // Convertit la structure tm en time_t (temps en secondes depuis l'époque)
    claimTime = mktime(&tm);
    
    // Obtient le temps actuel
    time(&currentTime);
    
    // Calcule la différence entre l'heure actuelle et le temps de la réclamation
    double diff = difftime(currentTime, claimTime);
    printf("Debug: Time difference = %.2f seconds\n\n", diff); // Affiche la différence de temps pour le débogage

    // Vérifie si la différence est supérieure à 86400 secondes (24 heures)
    return diff > 86400.0; // Retourne vrai si plus de 24 heures se sont écoulées
}


int ReclamationPrecisDuClient(int valid_claims[]) {
    int Index_reclamation_utilisateur = 0; // Compteur pour les réclamations valides

    // Affiche le nom de l'utilisateur dont on va afficher les réclamations
    printf("Les reclamations pour l'utilisateur %s sont : \n", users[user_Index].name_User);
    
    // Itération à travers toutes les réclamations
    for (int i = 0; i < reclamations_Conteur; i++) {
        // Vérifie si la réclamation appartient à l'utilisateur actuel
        if (strcmp(reclamations[i].name_utilisateur, users[user_Index].name_User) == 0) {
            // Vérifie si la réclamation a été faite il y a plus de 24 heures
            int is_after_24_hours = apres24Heures(reclamations[i].date);

            // Affiche la date de la réclamation
            printf("Reclamation %d - Date: %s\n", i, reclamations[i].date);
            // Indique si la réclamation a été faite il y a plus de 24 heures
            printf("Is after 24 hours (40 seconds)? %s\n\n", is_after_24_hours ? "Oui" : "Non");

            // Si la réclamation est récente (moins de 24 heures) et est en cours
            if (!is_after_24_hours && strcmp(reclamations[i].status, "En Cours") == 0) {
                // Ajoute l'index de la réclamation valide au tableau
                valid_claims[Index_reclamation_utilisateur] = i;
                Index_reclamation_utilisateur++;

                // Affiche les détails de la réclamation
                printf("- Reclamation %d: ID: %s ", Index_reclamation_utilisateur, reclamations[i].id);
                printf("- Categorie: %s ", reclamations[i].categorie);
                printf("- Motif: %s\n", reclamations[i].motif);
                printf("- Description: %s\n", reclamations[i].description);
                printf("- Statut: %s\n", reclamations[i].status);
                printf("- Date: %s\n", reclamations[i].date);
                printf("==========================================\n\n");
            } 
        }
    }
    
    // Si aucune réclamation valide n'est trouvée pour l'utilisateur
    if (Index_reclamation_utilisateur == 0) {
        printf("Aucune reclamation trouvee pour cet utilisateur.\n");
    } 
    
    // Retourne le nombre de réclamations valides trouvées
    return Index_reclamation_utilisateur;
}


void ConsulterReclamation() {
    int choix_Consultation_reclamation = 0; // Variable pour stocker le choix de l'utilisateur
    int num_valid_claims; // Nombre de réclamations valides
    int valid_claims[MAX_RECLAMATION]; // Tableau pour stocker les indices des réclamations valides
    
    // Appel de la fonction pour obtenir les réclamations de l'utilisateur
    num_valid_claims = ReclamationPrecisDuClient(valid_claims);
    
    // Si l'utilisateur a des réclamations valides
    if (num_valid_claims > 0) {
        // Demande à l'utilisateur de choisir une réclamation à modifier ou supprimer
        printf("Entrez le numero de la reclamation que vous souhaitez modifier ou supprimer (1 - %d) ou 0 pour revenir : ", num_valid_claims);
        scanf("%d", &choix_Consultation_reclamation);
        
        // Vérifie si le choix est valide
        if (choix_Consultation_reclamation > 0 && choix_Consultation_reclamation <= num_valid_claims) {
            int claim_index = valid_claims[choix_Consultation_reclamation - 1]; // Récupère l'indice de la réclamation choisie
            
            // Affiche la description de la réclamation actuelle
            printf("Reclamation actuelle :\n");
            printf("Description: %s\n", reclamations[claim_index].description);
            
            // Demande à l'utilisateur quelle action il souhaite effectuer
            printf("Que voulez-vous faire ?\n");
            printf("1. Modifier la description\n");
            printf("2. Supprimer la reclamation\n");
            printf("3. Revenir au menu precedent\n");
            
            int action_choice; // Variable pour le choix de l'action
            scanf("%d", &action_choice);
            getchar(); // Consomme le caractère de nouvelle ligne
            
            switch (action_choice) {
                case 1: // Modifier la description
                    printf("Entrez la nouvelle description (ou appuyez sur Entree pour ne pas modifier) :\n");
                    char new_description[100]; // Tableau pour stocker la nouvelle description
                    fgets(new_description, sizeof(new_description), stdin);
                    
                    // Supprime le caractère de nouvelle ligne à la fin de la chaîne, le cas échéant
                    size_t len = strlen(new_description);
                    if (len > 0 && new_description[len-1] == '\n') {
                        new_description[len-1] = '\0';
                    }
                    
                    // Si une nouvelle description a été fournie, met à jour la réclamation
                    if (strlen(new_description) > 0) {
                        strcpy(reclamations[claim_index].description, new_description);
                        printf("La description a ete mise a jour avec succes.\n");
                    } else {
                        printf("Aucune modification n'a ete apportee.\n");
                    }
                    break;
                
                case 2: // Supprimer la réclamation
                    printf("Etes-vous sur de vouloir supprimer cette reclamation ? (O/N) : ");
                    char confirm; // Variable pour confirmer la suppression
                    scanf(" %c", &confirm);
                    if (confirm == 'O' || confirm == 'o') {
                        // Décale les réclamations pour supprimer l'élément choisi
                        for (int i = claim_index; i < reclamations_Conteur - 1; i++) {
                            reclamations[i] = reclamations[i + 1];
                        }
                        reclamations_Conteur--; // Diminue le compteur de réclamations
                        printf("La reclamation a ete supprimee avec succes.\n");
                    } else {
                        printf("Suppression annulee.\n");
                    }
                    break;
                
                case 3: // Revenir au menu précédent
                    printf("Retour au menu precedent.\n");
                    break;
                
                default: // Gestion d'un choix invalide
                    printf("Choix invalide.\n");
                    break;
            }
        } else if (choix_Consultation_reclamation != 0) {
            printf("Choix invalide.\n");
        }
    }
}


void print_reclamation(int i) {
    // Affiche l'ID de la réclamation
    printf("- Reclamation ID: %s ", reclamations[i].id);
    // Affiche la catégorie de la réclamation
    printf("- Categorie: %s ", reclamations[i].categorie);
    // Affiche le motif de la réclamation
    printf("- Motif: %s\n", reclamations[i].motif);
    // Affiche la description de la réclamation
    printf("- Description: %s\n", reclamations[i].description);
    // Affiche le statut de la réclamation
    printf("- Statut: %s\n", reclamations[i].status);
    // Affiche la date de la réclamation
    printf("- Date: %s\n", reclamations[i].date);
    // Affiche la priorité de la réclamation
    printf("- Priorite: %s\n", reclamations[i].priorite);
    // Affiche le nom du client qui a soumis la réclamation
    printf("- Client : %s\n", reclamations[i].name_utilisateur);
    // Ligne de séparation pour une meilleure lisibilité
    printf("==========================================\n\n");
}


void OrdreParPriorite() {
    // Affiche les réclamations avec priorité "High"
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].priorite, "High") == 0) {
            print_reclamation(i);
        }
    }
    // Affiche les réclamations avec priorité "Moyen"
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].priorite, "Moyen") == 0) {
            print_reclamation(i);
        }
    }
    // Affiche les réclamations avec priorité "Basse"
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].priorite, "Basse") == 0) {
            print_reclamation(i);
        }
    }
}

void RechercheUneReclamations() {
    int choix_recherche = 0;
    char recherche_Id[20];
    char recherche_Categorie[30];
    char recherche_Name_Utilisateur[20];
    char recherche_Date[20];
    char recherche_Status[10];

    do {
        printf("Voici les Reclamations : \n\n");

        // Affiche toutes les réclamations
        for (int i = 0; i < reclamations_Conteur; i++) {
            print_reclamation(i);
        }

        // Menu de recherche
        printf("Veuillez entrer le choix de recherche de la reclamation que vous souhaitez utiliser : \n");
        printf("1 - Recherche par ID\n");
        printf("2 - Recherche par Categorie\n");
        printf("3 - Recherche par Nom du Client\n");
        printf("4 - Recherche par Status\n");
        printf("5 - Recherche par Date\n");
        printf("6 - Quitter\n");

        scanf(" %d", &choix_recherche);
        getchar();

        // Vérifie si le choix est valide
        if (choix_recherche < 1 || choix_recherche > 6) {
            printf("Veuillez choisir un choix valide entre 1 - 6.\n");
            continue;
        }

        int found = 0;  // Indicateur si une réclamation a été trouvée

        switch (choix_recherche) {
            case 1:  // Recherche par ID
                printf("Entrez l'id de la Reclamation : ");
                scanf(" %s", recherche_Id);
                getchar();

                for (int i = 0; i < reclamations_Conteur; i++) {
                    if (strcmp(reclamations[i].id, recherche_Id) == 0) {
                        print_reclamation(i);
                        found = 1;
                    }
                }
            break;

            case 2:  // Recherche par Catégorie
                printf("Entrez la Categorie de la Reclamation (Financier - Technique - Service - Autre) : ");
                scanf(" %s", recherche_Categorie);
                getchar();
                char miniscule_Categorie[30];
                strcpy(miniscule_Categorie, recherche_Categorie);
                miniscule(miniscule_Categorie);
               
                for (int i = 0; i < reclamations_Conteur; i++) {
                    if (strcmp(reclamations[i].categorie, miniscule_Categorie) == 0) {
                        print_reclamation(i);
                        found = 1;
                    }
                }
            break;

            case 3:  // Recherche par Nom du Client
                printf("Entrez le nom du Client : ");
                scanf(" %s", recherche_Name_Utilisateur);
                getchar();

                for (int i = 0; i < reclamations_Conteur; i++) {
                    if (strcmp(reclamations[i].name_utilisateur, recherche_Name_Utilisateur) == 0) {
                        print_reclamation(i);
                        found = 1;
                    }
                }
            break;

            case 4:  // Recherche par Statut
                printf("Entrez le Status de la Reclamation (En Cours - Resolu - Rejecte) : ");
                scanf(" %s", recherche_Status);
                getchar();

                for (int i = 0; i < reclamations_Conteur; i++) {
                    if (strcmp(reclamations[i].status, recherche_Status) == 0) {
                        print_reclamation(i);
                        found = 1;
                    }
                }
            break;

            case 5:  // Recherche par Date
                printf("Entrez la Date de la Reclamation (format YYYY-MM-DD): ");
                scanf(" %s", recherche_Date);
                getchar();
                for (int i = 0; i < reclamations_Conteur; i++) {
                    char date_part[11];
                    strncpy(date_part, reclamations[i].date, 10);
                    date_part[10] = '\0';  // Null-terminate the string
                    if (strcmp(date_part, recherche_Date) == 0) {
                        print_reclamation(i);
                        found = 1;
                    }
                }
            break;

            case 6:  // Quitter
                printf("Au revoir !\n");
                return; 
        }

        // Gestion de la recherche suivante
        if (found) {
            char choix;
            printf("Voulez-vous chercher a nouveau ? (o/n) : ");
            scanf(" %c", &choix);
            getchar(); 

            if (choix == 'n' || choix == 'N') {
                printf("Retour au menu principal.\n");
                break; 
            }
        } else {
            printf("Aucune reclamation trouvée pour cette recherche.\n");
        }

    } while (1); 
}


void MenuAdministrateur(){
    int choix_Menu_Administrateur = 0; // Variable pour stocker le choix de l'administrateur
    
    printf("Bienvenue dans votre espace Administrateur.\n");

    do{
        // Affichage des options disponibles
        printf("1 - Gestion des utilisateurs.\t          2 - Gestion des Reclamations.\n");
        printf("3 - Attribue les roles.\t                  4 - Traiter les reclamations.\n");
        printf("5 - Generation des Statistiques. \t  6 - Afficher les reclamations ordonnees par priorite\n");
        printf("7 - Recherche d'une Reclamation. \n8 - Quittez\n");
        printf("Quelle est votre choix : ");
        scanf(" %d",&choix_Menu_Administrateur);
        printf("\n");

        // Vérifie si le choix est valide
        if(choix_Menu_Administrateur < 1 || choix_Menu_Administrateur > 8 ){
            printf("Veuillez choisir un choix valide entre 1 - 8.\n");
            continue;
        }

        // Exécution de l'action correspondant au choix de l'utilisateur
        switch (choix_Menu_Administrateur) {
            case 1:
                GestionUtilisateurs(); // Gérer les utilisateurs
                break;
            case 2:
                GestionReclamations(); // Gérer les réclamations
                break;
            case 3:
                AttribuerRoles(); // Attribuer des rôles aux utilisateurs
                break;
            case 4:
                TraiterReclamation(); // Traiter les réclamations
                break;
            case 5:
                GenerationStatistiques(); // Générer des statistiques
                break;
            case 6:
                OrdreParPriorite(); // Afficher les réclamations par priorité
                break;
            case 7:
                RechercheUneReclamations(); // Rechercher une réclamation
                break;
            default:
                printf("Au revoir.\n"); // Quitter le programme
                break;
        }

    } while (choix_Menu_Administrateur != 8); // Continue tant que l'utilisateur ne choisit pas de quitter
}

void MenuAgent(){
    int choix_Menu_Agent = 0; // Variable pour stocker le choix de l'agent

    printf("Bienvenue dans votre espace Agent.\n");

    do {
        // Affichage du menu des options
        printf("=========== Menu ===========\n");
        printf("1 - Gerer les reclamations \t 2 - Traiter les reclamations \t 3 - Recherche d'une Reclamation.\n");
        printf("4 - Quittez.\n");
        printf("Quelle est votre choix : ");
        scanf(" %d",&choix_Menu_Agent);
        getchar(); // Pour consommer le caractère de nouvelle ligne

        // Vérifie si le choix est valide
        if(choix_Menu_Agent < 1 || choix_Menu_Agent > 4){
            printf("Veuillez choisir un choix valide entre 1 - 4.\n");
        }
    } while (choix_Menu_Agent < 1 || choix_Menu_Agent > 4);

    // Exécution de l'action correspondant au choix de l'agent
    if(choix_Menu_Agent == 1){
        GestionReclamations(); // Gérer les réclamations
    } else if(choix_Menu_Agent == 2){
        TraiterReclamation(); // Traiter les réclamations
    } else if(choix_Menu_Agent == 3){
        RechercheUneReclamations(); // Rechercher une réclamation
    }
}


void MenuUtilisateur() {
    int choix_Menu_utilisateur; // Variable pour stocker le choix de l'utilisateur
    printf("Bienvenue dans votre espace utilisateur!\n");
    
    do {
        // Affichage du menu des options
        printf("=========== Menu ===========\n");
        printf("1 - Ajouter une reclamation \t 2 - Consulter tes reclamations \t 3 - Quittez \n");
        printf("Quelle est votre choix : ");
        scanf(" %d", &choix_Menu_utilisateur);
        getchar(); // Pour consommer le caractère de nouvelle ligne

        // Vérifie si le choix est valide
        if (choix_Menu_utilisateur < 1 || choix_Menu_utilisateur > 3) {
            printf("Veuillez choisir un choix valide entre 1 -3.\n");
        }
    } while (choix_Menu_utilisateur < 1 || choix_Menu_utilisateur > 3); // Boucle jusqu'à obtenir un choix valide

    // Exécution de l'action correspondant au choix de l'utilisateur
    if (choix_Menu_utilisateur == 1) {
        AjouterReclamation(); // Ajouter une réclamation
    } else if (choix_Menu_utilisateur == 2) {
        ConsulterReclamation(); // Consulter les réclamations
    } else {
        printf("Au revoir!\n\n"); // Sortir du menu
    }
}


void Role_Menu() {
    if (isAdmin) {
        MenuAdministrateur(); // Si l'utilisateur est un administrateur, afficher le menu administrateur
    } else if (isAgent) {
        MenuAgent(); // Si l'utilisateur est un agent, afficher le menu agent
    } else {
        MenuUtilisateur(); // Sinon, afficher le menu utilisateur
    }
}


void logOut() {
    isSignedIn = 0; // Indique que l'utilisateur est déconnecté
    isAdmin = 0;    // Réinitialise le statut d'administrateur
    isAgent = 0;    // Réinitialise le statut d'agent
    printf("Vous êtes déconnecté.\n\n"); // Affiche un message de déconnexion
}


void MenuPrincipal() {
    int choix_Menu_Pricipale; // Variable pour stocker le choix de l'utilisateur
    do {
        if (!isSignedIn) { 
            // Affiche le menu de connexion si l'utilisateur n'est pas connecté
            printf("========== Menu Principal ==========\n");
            printf("1 - Sign In\t 2 - Sign Up\n");
        }
        if (isSignedIn) {
            // Affiche les options pour les utilisateurs connectés
            printf("1 - Accéder au Menu en fonction de votre rôle.\n");
            printf("2 - Log Out.\n\n");
        }

        printf("Quelle est votre choix : ");
        scanf(" %d", &choix_Menu_Pricipale); // Lit le choix de l'utilisateur

        // Vérifie la validité du choix en fonction de l'état de connexion
        if (!isSignedIn && choix_Menu_Pricipale != 1 && choix_Menu_Pricipale != 2) {
            printf("Entrez un Nombre entre 1 - 2.\n");
        } else if (isSignedIn && (choix_Menu_Pricipale < 1 || choix_Menu_Pricipale > 2)) {
            printf("Entrez un Nombre entre 1 - 2.\n");
        }

        printf("\n\n");

        // Exécute les actions en fonction du choix de l'utilisateur
        if (!isSignedIn) {
            if (choix_Menu_Pricipale == 1) {
                MenuSignIn(); // Appelle la fonction de connexion
            } else if (choix_Menu_Pricipale == 2) {
                MenuSignUp(); // Appelle la fonction d'inscription
            }
        } else {
            if (choix_Menu_Pricipale == 1) {
                Role_Menu(); // Accède au menu en fonction du rôle de l'utilisateur
            } else if (choix_Menu_Pricipale == 2) {
                logOut(); // Déconnecte l'utilisateur
            }
        }
    } while (!isSignedIn || (isSignedIn && choix_Menu_Pricipale != 2)); // Continue jusqu'à déconnexion
}


void admin() {
    // Initialise l'utilisateur administrateur avec des identifiants par défaut
    strcpy(Admin.name_User, "admin");
    strcpy(Admin.password_User, "admin");
    strcpy(Admin.role, "administrateur");

    // Ajoute l'administrateur au tableau des utilisateurs
    users[user_Conteur++] = Admin;
}

int main() {
    srand(time(NULL)); // Initialise le générateur de nombres aléatoires
    admin(); // Crée et ajoute l'administrateur
    MenuPrincipal(); // Lance le menu principal
    return 0; // Fin du programme
}

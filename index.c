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
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    strftime(date, 20, "%Y-%m-%d %H:%M:%S", tm_now);
}

void generateRandomID(char id[ID_LENGTH]) {
    char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int char_count = strlen(characters);

    for (int i = 0; i < ID_LENGTH - 1; i++) { 
        id[i] = characters[rand() % char_count];
    }
    id[ID_LENGTH - 1] = '\0'; 
}

int checkPassword(char utilisateur[20], char password_Utilisateur[20]) {
    int isUpper = 0;
    int isLower = 0;
    int isNumber = 0;
    int isSpecial = 0;
    int isMinuLength = 8;
    int passLength = strlen(password_Utilisateur);
    int isValid = 1;

    if (passLength < isMinuLength) {
        printf("Le mot de passe doit contenir au moins 8 caracteres.\n");
        isValid = 0;
    }

    for (int i = 0; i < passLength; i++) {
        if (password_Utilisateur[i] >= 'A' && password_Utilisateur[i] <= 'Z') {
            isUpper = 1;
        } else if (password_Utilisateur[i] >= 'a' && password_Utilisateur[i] <= 'z') {
            isLower = 1;
        } else if (password_Utilisateur[i] >= '0' && password_Utilisateur[i] <= '9') {
            isNumber = 1;
        } else {
            isSpecial = 1;
        }
    }
    
    if (!isUpper) {
        printf("Le mot de passe doit contenir au moins une lettre majuscule.\n");
        isValid = 0;
    }
    if (!isLower) {
        printf("Le mot de passe doit contenir au moins une lettre minuscule.\n");
        isValid = 0;
    }
    if (!isNumber) {
        printf("Le mot de passe doit contenir au moins un chiffre.\n");
        isValid = 0;
    }
    if (!isSpecial) {
        printf("Le mot de passe doit contenir au moins un caractere special.\n");
        isValid = 0;
    }

    if (strstr(password_Utilisateur, utilisateur) != NULL) {
        printf("Le mot de passe ne doit pas contenir le nom d'utilisateur.\n");
        isValid = 0;
    }

    return isValid;
}

int UserCheck (char utilisateur[20], char password_Utilisateur[20]){
    for (int i = 0; i < user_Conteur ; i++){
        if(strcmp(users[i].name_User, utilisateur) == 0 && strcmp(users[i].password_User,password_Utilisateur) == 0){
                return i;
            }
    }
    return -1;
}

void MenuSignIn() {
    char utilisateur[20];
    char password_Utilisateur[20];
    int isUser = 0; 
    int utilisateur_trouver = 0; 
    int User_index_sign_in_function;

    printf("========== Sign In ==========\n");

    while (isUser == 0) {
        printf("Entrez votre nom du compte : ");
        scanf("%s", utilisateur);
        
        for (int i = 0; i < user_Conteur; i++) {
            if (strcmp(users[i].name_User, utilisateur) == 0) {
                utilisateur_trouver = 1; 
                User_index_sign_in_function = i;
                break;
            }
        }

        if (utilisateur_trouver == 0) {
            printf("Le nom d'utilisateur est incorrect.\n");
            continue; 
        }

        printf("Entrez votre Mode de Passe : ");
        scanf("%s", password_Utilisateur);

        User_index_sign_in_function = UserCheck(utilisateur, password_Utilisateur);

        if (User_index_sign_in_function != -1) {

            user_Index = User_index_sign_in_function;
            isAdmin = 0;  
            isAgent = 0;  
            printf("\n");
            
            if (strcmp(users[User_index_sign_in_function].role, "administrateur") == 0) {
                isAdmin = 1;
                printf("Bienvenue, Administrateur.\n");
            } 
            
            else if (strcmp(users[User_index_sign_in_function].role, "Agent") == 0) {
                isAgent = 1;
                printf("Bienvenue, Agent.\n");
            } 
            
            else {
                printf("Bienvenue, Utilisateur.\n");
            }

            isUser = 1; 

        } else {

            printf("Le nom d'utilisateur ou le mot de passe est incorrect.\n");
            password_Incorrect_Conteur++;

            if (password_Incorrect_Conteur == 3) {
                printf("Vous avez atteint le nombre maximum de tentatives. Veuillez attendre 30 secondes.\n");
                sleep(5); 
                password_Incorrect_Conteur = 0; 
            }
        }
    }

    isSignedIn = 1;
    password_Incorrect_Conteur = 0; 
    printf("\n");

}

int UtilisateurExiste(char utilisateur[20]) {
    for (int i = 0; i < user_Conteur; i++) {
        if (strcmp(users[i].name_User, utilisateur) == 0) {
            return 1; 
        }
    }
    return 0; 
}

void MenuSignUp() {
    char utilisateur[20];
    char password_Utilisateur[20];
    int i = 0;

    printf("========== Sign Up ==========\n");
    
    while (1) { 
        printf("Entrez votre nom du compte : ");
        scanf(" %s", utilisateur);

        if (UtilisateurExiste(utilisateur)) {
            printf("Ce compte existe deja. Veuillez entrer un autre nom d'utilisateur.\n");
        } else {
            break; 
        }
    }

    do {
        printf("Entrez votre Mode de Passe : ");
        scanf(" %s", password_Utilisateur);
        i = checkPassword(utilisateur, password_Utilisateur);
    } while (i != 1);

    strcpy(nouvelle_Utilisateur.name_User, utilisateur);
    strcpy(nouvelle_Utilisateur.password_User, password_Utilisateur);
    strcpy(nouvelle_Utilisateur.role,"Client");
    users[user_Conteur++] = nouvelle_Utilisateur;

    printf("Inscription reussie pour %s.\n", utilisateur);
}

void GestionUtilisateurs(){
    char nom_utilisateur[30];
    int delete_Another = 1;
    int trouver = 0;  

    do {

        getchar();
        printf("Les Utilisateurs sont : \n");
        for (int i = 0; i < user_Conteur; i++) {
            printf("Utilisateur %d: Nom: %s, Role: %s\n", i + 1, users[i].name_User, users[i].role);
        }
        printf("\n");

        printf("Entrez le nom d'utilisateur a Supprimer : ");
        fgets(nom_utilisateur, 30,stdin);

        nom_utilisateur[strcspn(nom_utilisateur, "\n")] = 0;

        if(strcmp(nom_utilisateur, users[0].name_User) == 0){
            printf("Vous ne pouvez pas supprimer l'administrateur.\n");

        }else{
            for (int i = 0; i < user_Conteur; i++) {
                if (strcmp(users[i].name_User, nom_utilisateur) == 0) {
                    trouver = 1;  

                    for (int j = i; j < user_Conteur - 1; j++) {
                        strcpy(users[j].name_User, users[j + 1].name_User);
                        strcpy(users[j].password_User, users[j + 1].password_User);
                        strcpy(users[j].role, users[j + 1].role);
                    }
                    user_Conteur--;  
                    printf("Utilisateur %s supprime.\n\n", nom_utilisateur);
                    break;  
                }
            }

            if (!trouver) {
                printf("L'utilisateur n'existe pas ou le nom est incorrect.\n\n");
            }
        }

        printf("Nouvelle liste des utilisateurs : \n");
        for (int i = 0; i < user_Conteur; i++) {
            printf("Utilisateur %d: Nom: %s, Role: %s\n", i + 1, users[i].name_User, users[i].role);
        }
        
        printf("\n");
      
        printf("Voulez -vous supprimer un autre utilisateur ? (1 pour OUI, 0 pour NON) : ");
        scanf("%d", &delete_Another);

        printf("\n\n");

    }while(delete_Another == 1);

}

void afficherLesReclamations() {
    int reclamation_En_Cours = 0;
    int conteur_En_Cours = 0;
    if (isEnCours == 0) {
        if (reclamations_Conteur == 0) {
            printf("Aucune reclamation n'a ete soumise.\n");
            return;
        }  
        printf("Les  reclamations sont : \n");
        for (int i = 0; i < reclamations_Conteur; i++) {
            printf("- Reclamation %d: ID: %s ", i + 1, reclamations[i].id);
            printf("- Categorie: %s ", reclamations[i].categorie);
            printf("- Motif: %s\n", reclamations[i].motif);
            printf("- Description: %s\n", reclamations[i].description);
            printf("- Statut: %s\n", reclamations[i].status);
            printf("- Date: %s\n", reclamations[i].date);
            printf("- Client : %s\n",reclamations[i].name_utilisateur);
            printf("==========================================\n\n");
        }
    }
    if (isEnCours) {
        for (int i = 0; i < reclamations_Conteur; i++) {
            if (strcmp(reclamations[i].status, "En Cours") == 0) {
                reclamation_En_Cours = 1;
                conteur_En_Cours++;
                printf("- Reclamation %d: ID: %s ", conteur_En_Cours, reclamations[i].id);
                printf("- Categorie: %s ", reclamations[i].categorie);
                printf("- Motif: %s\n", reclamations[i].motif);
                printf("- Description: %s\n", reclamations[i].description);
                printf("- Statut: %s\n", reclamations[i].status);
                printf("- Date: %s\n", reclamations[i].date);
                printf("- Client : %s\n",reclamations[i].name_utilisateur);
                printf("==========================================\n\n");
            }
        }
        if (!reclamation_En_Cours) {
            printf("Aucune reclamation n'est en cours.\n\n");
        }
    }
}

void GestionReclamations(){
    int choix_Supprimer;
    char annuler_choix[10];

    if (reclamations_Conteur  == 0){
        printf("Aucune reclamation pour le Moment.\n\n");
    }else{

        afficherLesReclamations();
        
        getchar();
        while (1) {
            printf("Entrez le numero de la reclamation que vous voulez supprimer ou entrez '.' pour annuler l'action : ");
            fgets(annuler_choix, sizeof(annuler_choix), stdin); 

            
            if (annuler_choix[0] == '.' && annuler_choix[1] == '\n') {
                printf("Action annulee.\n");
                return;
            }

            if (sscanf(annuler_choix, "%d", &choix_Supprimer) == 1) {
                
                if (choix_Supprimer > 0 && choix_Supprimer <= reclamations_Conteur) {
                    
                    for (int i = choix_Supprimer - 1; i < reclamations_Conteur - 1; i++) {
                        reclamations[i] = reclamations[i + 1];
                    }
                    reclamations_Conteur--;  
                    printf("Reclamation %d supprimee avec succes.\n", choix_Supprimer);
                    break;  
                } else {
                    printf("Numero de reclamation invalide. Veuillez reessayer.\n");
                }
            } else {
                printf("Entree invalide. Veuillez entrer un numero de reclamation valide ou '.' pour annuler.\n");
            }
        }
    }
}

void AttribuerRoles() {
    char nom_utilisateur[30];
    int Choix_New_Role;
    char Nouveau_Role[30];
    int trouver = 0;

    getchar();
    printf("Les Utilisateurs sont : \n");
    for (int i = 0; i < user_Conteur; i++) {
        printf("Utilisateur %d: Nom: %s, Role: %s\n", i + 1, users[i].name_User, users[i].role);
    }
    printf("\n");

    while (1) { 
        printf("Entrez le nom d'utilisateur pour changer leur role : ");
        scanf(" %s", nom_utilisateur);

        if(strstr(nom_utilisateur,users[0].role) == NULL){
            printf("Vous ne pouvez pas changer le role de l'administrateur.\n\n");
            continue;
        }

        if (UtilisateurExiste(nom_utilisateur)) {
            break; 
        } else {
            printf("Ce compte n'existe pas. Veuillez entrer un autre nom d'utilisateur.\n");
        }
    }
    
    printf("Choisir le nouveau role : 1 - Administrateur, 2 - Agent, 3 - Client\n");
    scanf(" %d", &Choix_New_Role);



    for (int i = 0; i < user_Conteur; i++) {
        if (strcmp(users[i].name_User, nom_utilisateur) == 0) {
            trouver = 1;  
            
            switch (Choix_New_Role) {
                case 1:
                    strcpy(users[i].role, "administrateur");
                    isAdmin = 1;
                    break;
                case 2:
                    strcpy(users[i].role, "Agent");
                    isAgent = 1;
                    break;
                case 3:
                    strcpy(users[i].role, "client"); 
                    break;
                default:
                    printf("Choix de role invalide.\n");
                    return; 
            }
            
            printf("Le role de l'utilisateur %s a ete change en %s.\n\n", nom_utilisateur, users[i].role);
            break;  
        }
    }
    
    if (!trouver) {
        printf("L'utilisateur n'existe pas ou le nom est incorrect.\n\n");
    }
}

void parseDateTime(const char* dateString, struct tm* tm) {
    memset(tm, 0, sizeof(struct tm));  // Initialize the struct to zero
    sscanf(dateString, "%d-%d-%d %d:%d:%d",
           &tm->tm_year, &tm->tm_mon, &tm->tm_mday,
           &tm->tm_hour, &tm->tm_min, &tm->tm_sec);
    tm->tm_year -= 1900;  // Adjust year (years since 1900)
    tm->tm_mon -= 1;      // Adjust month (0-11)
    tm->tm_isdst = -1;    // Let the system determine DST
}

void GenererRapportQuotidien(float Ratio_Resolution) {
    FILE *file = fopen("rapport_quotidien.txt", "w");
    if (!file) {
        printf("Erreur lors de la création du fichier.\n");
        return;
    }


    fprintf(file, "Rapport Quotidien des Réclamations\n");
    fprintf(file, "=================================\n\n");
    
    fprintf(file,"Nombre total de réclamations : %d\n", reclamations_Conteur);
    fprintf(file,"Taux de resolution des réclamations : %.2f%%\n", Ratio_Resolution);

    fprintf(file, "=================================\n\n");


    fprintf(file, "Nouvelles Réclamations:\n\n");
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].status, "En Cours") == 0) {
            fprintf(file, "%d - ID: %s, Catégorie: %s, Motif: %s, Description: %s, Date: %s\n",i+1,
                    reclamations[i].id, reclamations[i].categorie, 
                    reclamations[i].motif, reclamations[i].description,
                    reclamations[i].date);
        }
    }

    fprintf(file, "\nRéclamations Résolues:\n\n");
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].status, "resolu") == 0) {
            fprintf(file, "%d - ID: %s, Catégorie: %s, Motif: %s, Description: %s, Date de Resolution: %s\n",i+1,
                    reclamations[i].id, reclamations[i].categorie, 
                    reclamations[i].motif, reclamations[i].description,
                    reclamations[i].date_Traitement_resolu);
        }
    }

    fprintf(file, "\nRéclamations Rejectées:\n\n");
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].status, "rejecter") == 0) {
            fprintf(file, "%d - ID: %s, Catégorie: %s, Motif: %s, Description: %s, Date de Rejet: %s\n",i+1,
                    reclamations[i].id, reclamations[i].categorie, 
                    reclamations[i].motif, reclamations[i].description,
                    reclamations[i].date_Traitement_rejecter);
        }
    }

    fclose(file);
    printf("Rapport quotidien genere avec succes.\n");
}

void GenerationStatistiques() {
    int resolution_Conteur = 0;
    double total_time = 0; 

    printf("Nombre total de reclamations : %d\n", reclamations_Conteur);

    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].status, "resolu") == 0) {
            resolution_Conteur++;

            struct tm tm_creation = {0}, tm_resolution = {0};
            time_t claimTime, resolutionTime;

            parseDateTime(reclamations[i].date, &tm_creation);
            parseDateTime(reclamations[i].date_Traitement_resolu, &tm_resolution);

            // Convert to time_t
            claimTime = mktime(&tm_creation);
            resolutionTime = mktime(&tm_resolution);

            // Calculate the duration in seconds
            double duration = difftime(resolutionTime, claimTime);
            total_time += duration;
        }
    }

    if (reclamations_Conteur == 0) {
        printf("Aucune reclamation soumise.\n");
        return;
    }

    float Ratio_Resolution = (float)resolution_Conteur / reclamations_Conteur * 100;
    printf("Taux de resolution des reclamations : %.2f%%\n", Ratio_Resolution);

    if (resolution_Conteur > 0) {
        double moyenne = total_time / resolution_Conteur; 
        printf("Delai moyen de traitement des reclamations resolues : %.2f secondes\n", moyenne);
    } else {
        printf("Aucune reclamation resolue pour le calcul du delai.\n");
    }
    GenererRapportQuotidien(Ratio_Resolution);
}

void TraiterReclamation() {
    int choix_reclamation;
    int nouvelle_status;
    int note_choix;
    char note[150];
    char continuer[10];

    printf("Traiter Les reclamations : \n\n");

    while (1) {

        printf("Liste de toutes les reclamations :\n");
        for (int i = 0; i < reclamations_Conteur; i++) {
            printf("%d. ID: %d, Status: %s, Description: %s, Note de Traitement : %s\n", 
                   i + 1, reclamations[i].id, reclamations[i].status, reclamations[i].description,
                   (strlen(reclamations[i].note) == 0 ? "-----" : reclamations[i].note));
        }


        printf("\nReclamations en cours :\n");
        int j = 1;
        for (int i = 0; i < reclamations_Conteur; i++) {
            if (strcmp(reclamations[i].status, "En Cours") == 0) {
                printf("%d. ID: %d, Description: %s\n", 
                       j++, reclamations[i].id, reclamations[i].description);
            }
        }

        printf("\nEntrez le numero de la reclamation que vous voulez traiter (0 pour quitter) : ");
        if (scanf("%d", &choix_reclamation) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (choix_reclamation == 0) {
            printf("Retour au menu principal.\n");
            break;
        }

        
        int claim_index = -1;
        j = 1;
        for (int i = 0; i < reclamations_Conteur; i++) {
            if (strcmp(reclamations[i].status, "En Cours") == 0) {
                if (j == choix_reclamation) {
                    claim_index = i;
                    break;
                }
                j++;
            }
        }

        if (claim_index == -1) {
            printf("Numero de reclamation invalide ou la reclamation n'est pas en cours. Veuillez reessayer.\n");
            continue;
        }

        printf("Entrez le nouveau statut de la reclamation (1 - Resolue, 2 - Rejecter) : ");
        while (scanf("%d", &nouvelle_status) != 1 || (nouvelle_status != 1 && nouvelle_status != 2)) {
            printf("Statut non valide. Veuillez entrer 1 (Resolue) ou 2 (Rejecter) : ");
            while (getchar() != '\n');
        }

        printf("Voulez-vous entrer une note sur le traitement ? (1 - Oui, 2 - Non) : ");
        while (scanf("%d", &note_choix) != 1 || (note_choix != 1 && note_choix != 2)) {
            printf("Entree non valide. Veuillez entrer 1 (Oui) ou 2 (Non) : ");
            while (getchar() != '\n');
        }

        if (note_choix == 1) {
            printf("Entrez votre note : ");
            getchar(); 
            fgets(note, sizeof(note), stdin);
            note[strcspn(note, "\n")] = '\0';
            strcpy(reclamations[claim_index].note, note);
        }

        
        switch (nouvelle_status) {
            case 1:
                strcpy(reclamations[claim_index].status, "resolu");
                DateDuMoment(reclamations[claim_index].date_Traitement_resolu);
                printf("La reclamation numero %d a ete resolue.\n", choix_reclamation);
                break;
            case 2:
                strcpy(reclamations[claim_index].status, "rejecter");
                DateDuMoment(reclamations[claim_index].date_Traitement_rejecter);
                printf("La reclamation numero %d a ete rejecter.\n", choix_reclamation);
                break;
        }

        if (note_choix == 1) {
            printf("Note ajoutee : %s\n", reclamations[claim_index].note);
        } else {
            printf("Aucune note n'a ete ajoutee.\n");
        }

        printf("\nVoulez-vous traiter une autre reclamation ? (o/n) : ");
        scanf("%s", continuer);
        if (strcmp(continuer, "n") == 0) {
            break;
        }
    }
}



void miniscule(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void AjouterReclamation(){
    int categorie_choix;
    char *high[] = {"urgent", "critique", "importante"};
    char *moyen[] = {"asap", "modere", "rapide"};
    char miniscule_description[100], miniscule_motif[50];
    int trouver_high = 0, trouver_moyen = 0;
    
    generateRandomID(nouvelle_Reclamation.id);
    DateDuMoment(nouvelle_Reclamation.date);

    strcpy(nouvelle_Reclamation.name_utilisateur, users[user_Index].name_User);
    do{

        printf("Entrez la categorie de votre Reclamation 1 - Financier , 2 - Technique, 3 - Service 4 - autre \n");
        scanf(" %d", &categorie_choix);

        switch (categorie_choix) {
            case 1:
                strcpy(nouvelle_Reclamation.categorie, "Financier");
                break;
            case 2:
                strcpy(nouvelle_Reclamation.categorie, "Technique");
                break;
            case 3:
                strcpy(nouvelle_Reclamation.categorie, "Service");
                break;
            case 4:
                strcpy(nouvelle_Reclamation.categorie, "Autre");
                break;
            default:
                printf("choix invalide\n\n"); 
                break;
        }

    }while(categorie_choix  < 1 || categorie_choix > 4);

    printf("Entrez le Motif du reclamation : ");
    getchar(); 
    fgets(nouvelle_Reclamation.motif, sizeof(nouvelle_Reclamation.motif), stdin);
    nouvelle_Reclamation.motif[strcspn(nouvelle_Reclamation.motif, "\n")] = 0;
    
    printf("Entrez la description du reclamation : ");
    fgets(nouvelle_Reclamation.description, sizeof(nouvelle_Reclamation.description), stdin);
    nouvelle_Reclamation.description[strcspn(nouvelle_Reclamation.description, "\n")] = 0; 

    strcpy(nouvelle_Reclamation.status, "En Cours");

    strcpy(miniscule_description, nouvelle_Reclamation.description);
    strcpy(miniscule_motif, nouvelle_Reclamation.motif);
    miniscule(miniscule_description);
    miniscule(miniscule_motif);
    
    for (int i = 0; i < sizeof(high) / sizeof(high[0]); i++) {
        if (strstr(miniscule_description, high[i]) != NULL || strstr(miniscule_motif, high[i]) != NULL) {
            trouver_high = 1;
            break;
        }
    }
    if (!trouver_high) {
        for (int i = 0; i < sizeof(moyen) / sizeof(moyen[0]); i++) {
            if (strstr(miniscule_description, moyen[i]) != NULL || strstr(miniscule_motif, moyen[i]) != NULL) {
                trouver_moyen = 1;
                break;
            }
        }
    }
    if (trouver_high) {
        strcpy(nouvelle_Reclamation.priorite, "High");
    } else if (trouver_moyen) {
        strcpy(nouvelle_Reclamation.priorite, "Moyen");
    } else {
        strcpy(nouvelle_Reclamation.priorite, "Basse");
    }

    reclamations[reclamations_Conteur++] = nouvelle_Reclamation;

    printf("Reclamation ajoutee avec succes. ID: %s\n", nouvelle_Reclamation.id);

}




int apres24Heures(const char* dateString) {
    struct tm tm = {0};
    time_t claimTime, currentTime;
    
    parseDateTime(dateString, &tm);
    
    claimTime = mktime(&tm);
    
    time(&currentTime);
    
    double diff = difftime(currentTime, claimTime);
    printf("Debug: Time difference = %.2f seconds\n\n", diff);
    // 86400 second / jour
    return diff > 40.0;
}

int ReclamationPrecisDuClient(int valid_claims[]) {
    int Index_reclamation_utilisateur = 0;

    printf("Les reclamations pour l'utilisateur %s sont : \n", users[user_Index].name_User);
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].name_utilisateur, users[user_Index].name_User) == 0) {
            int is_after_24_hours = apres24Heures(reclamations[i].date);
            printf("Reclamation %d - Date: %s\n", i, reclamations[i].date);
            printf("Is after 24 hours (40 seconds)? %s\n\n", is_after_24_hours ? "Oui" : "Non");

            if (!is_after_24_hours && strcmp(reclamations[i].status, "En Cours") == 0) {
                valid_claims[Index_reclamation_utilisateur] = i;
                Index_reclamation_utilisateur++;

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
    
    if (Index_reclamation_utilisateur == 0) {
        printf("Aucune reclamation trouvee pour cet utilisateur.\n");
    } 
    
    return Index_reclamation_utilisateur;
}

void ConsulterReclamation() {
    int choix_Consultation_reclamation = 0;
    int num_valid_claims;
    int valid_claims[MAX_RECLAMATION];
    
    num_valid_claims = ReclamationPrecisDuClient(valid_claims);
    
    if (num_valid_claims > 0) {
        printf("Entrez le numero de la reclamation que vous souhaitez modifier ou supprimer (1 - %d) ou 0 pour revenir : ", num_valid_claims);
        scanf("%d", &choix_Consultation_reclamation);
        
        if (choix_Consultation_reclamation > 0 && choix_Consultation_reclamation <= num_valid_claims) {
            int claim_index = valid_claims[choix_Consultation_reclamation - 1];
            
            printf("Reclamation actuelle :\n");
            printf("Description: %s\n", reclamations[claim_index].description);
            
            printf("Que voulez-vous faire ?\n");
            printf("1. Modifier la description\n");
            printf("2. Supprimer la reclamation\n");
            printf("3. Revenir au menu precedent\n");
            
            int action_choice;
            scanf("%d", &action_choice);
            getchar();  
            
            switch (action_choice) {
                case 1:
                    printf("Entrez la nouvelle description (ou appuyez sur Entree pour ne pas modifier) :\n");
                    char new_description[100];
                    fgets(new_description, sizeof(new_description), stdin);
                    
                    
                    size_t len = strlen(new_description);

                    if (len > 0 && new_description[len-1] == '\n') {
                        new_description[len-1] = '\0';
                    }
                    
                    if (strlen(new_description) > 0) {
                        strcpy(reclamations[claim_index].description, new_description);
                        printf("La description a ete mise a jour avec succes.\n");
                    } else {
                        printf("Aucune modification n'a ete apportee.\n");
                    }
                    break;
                
                case 2:
                    printf("Etes-vous sur de vouloir supprimer cette reclamation ? (O/N) : ");
                    char confirm;
                    scanf(" %c", &confirm);
                    if (confirm == 'O' || confirm == 'o') {
                        for (int i = claim_index; i < reclamations_Conteur - 1; i++) {
                            reclamations[i] = reclamations[i + 1];
                        }
                        reclamations_Conteur--;
                        printf("La reclamation a ete supprimee avec succes.\n");
                    } else {
                        printf("Suppression annulee.\n");
                    }
                    break;
                
                case 3:
                    printf("Retour au menu precedent.\n");
                    break;
                
                default:
                    printf("Choix invalide.\n");
                    break;
            }
        } else if (choix_Consultation_reclamation != 0) {
            printf("Choix invalide.\n");
        }
    }
}

void print_reclamation(int i){

    printf("- Reclamation ID: %s ", reclamations[i].id);
    printf("- Categorie: %s ", reclamations[i].categorie);
    printf("- Motif: %s\n", reclamations[i].motif);
    printf("- Description: %s\n", reclamations[i].description);
    printf("- Statut: %s\n", reclamations[i].status);
    printf("- Date: %s\n", reclamations[i].date);
    printf("- Priorite: %s\n", reclamations[i].priorite);
    printf("- Client : %s\n",reclamations[i].name_utilisateur);
    printf("==========================================\n\n");
}

void OrdreParPriorite() {
    
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].priorite, "High") == 0) {
            print_reclamation(i);
        }
    }
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].priorite, "Moyen") == 0) {
            print_reclamation(i);
        }
    }
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

        for (int i = 0; i < reclamations_Conteur; i++) {
            print_reclamation(i);
        }

        printf("Veuillez entrer le choix de recherche de la reclamation que vous souhaitez utiliser : \n");
        printf("1 - Recherche par ID\n");
        printf("2 - Recherche par Categorie\n");
        printf("3 - Recherche par Nom du Client\n");
        printf("4 - Recherche par Status\n");
        printf("5 - Recherche par Date\n");
        printf("6 - Quitter\n");

        scanf(" %d", &choix_recherche);
        getchar();

        if (choix_recherche < 1 || choix_recherche > 6) {
            printf("Veuillez choisir un choix valide entre 1 - 6.\n");
            continue;
        }

        int found = 0; 

        switch (choix_recherche) {
            case 1:
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
            case 2:
                printf("Entrez la Categorie de la Reclamation (Financier - Technique - Service - Autre) : ");
                scanf(" %s", recherche_Categorie);
                getchar();
                for (int i = 0; i < reclamations_Conteur; i++) {
                    if (strcmp(reclamations[i].categorie, recherche_Categorie) == 0) {
                        print_reclamation(i);
                        found = 1;
                    }
                }
            break;
            case 3:
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
            case 4:
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
            case 5:
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
            case 6:
                printf("Au revoir !\n");
            return; 
        }

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
    int choix_Menu_Administrateur = 0;
    
    printf("Bienvenue dans votre espace Administrateur.\n");

    do{
        printf("1 - Gestion des  utilisateurs.\t          2 - Gestion des Reclamations.\n");
        printf("3 - Attribue les roles.\t                  4 - Traiter les reclamations.\n");
        printf("5 - Generation des Statistiques. \t  6 - Afficher les reclamations ordonnees par priorite\n");
        printf("7 - Recherche d'une Reclamation. \n8 - Quittez\n");
        printf("Quelle est votre choix : ");
        scanf(" %d",&choix_Menu_Administrateur);
        printf("\n");

        if(choix_Menu_Administrateur  < 1 || choix_Menu_Administrateur > 8 ){
            printf("Veuillez choisir un choix valide entre 1 - 8.\n");
            continue;
        }

        switch (choix_Menu_Administrateur) {
            case 1:
                GestionUtilisateurs();
                break;
            case 2:
                GestionReclamations();
                break;
            case 3:
                AttribuerRoles();
                break;
            case 4:
                TraiterReclamation();
                break;
            case 5:
                GenerationStatistiques();
                break;
            case 6:
                OrdreParPriorite();
                break;
            case 7:
                RechercheUneReclamations();
                break;
            default:
                printf("Au revoir.\n");
                break;

        }

    }while (choix_Menu_Administrateur != 8);
}
void MenuAgent(){
    int choix_Menu_Agent = 0;

    printf("Bienvenue dans votre espace Agent.\n");

    do{
        printf("=========== Menu ===========\n");
        printf("1 - Gerer les reclamations \t 2 - Traiter les reclamations \t 3 -  - Recherche d'une Reclamation. \n");
        printf("4 - Quittez.\n");
        printf("Quelle est votre choix : ");
        scanf(" %d",&choix_Menu_Agent);
        getchar();
        if(choix_Menu_Agent  < 1 || choix_Menu_Agent > 4 ){
            printf("Veuillez choisir un choix valide entre 1 - 4.\n");
        }
    }while (choix_Menu_Agent  < 1 || choix_Menu_Agent > 4);

    if(choix_Menu_Agent == 1){
        GestionReclamations();
    }else if(choix_Menu_Agent == 2){
        TraiterReclamation();
    }else if(choix_Menu_Agent == 3){
        RechercheUneReclamations();
    }

}

void  MenuUtilisateur() {
    int choix_Menu_utilisateur;
    printf("Bienvenue dans votre espace utilisateur!\n");
    do{

        printf("=========== Menu ===========\n");
        printf("1 - Ajouter une reclamation \t 2 - Consulter tes reclamations \t 3 - Quittez \n");
        printf("Quelle est votre choix : ");
        scanf(" %d",&choix_Menu_utilisateur);
        getchar();
        if(choix_Menu_utilisateur  < 1 || choix_Menu_utilisateur > 3 ){
            printf("Veuillez choisir un choix valide entre 1 -3.\n");
        }
    }while (choix_Menu_utilisateur  < 1 || choix_Menu_utilisateur > 3);


    if(choix_Menu_utilisateur == 1){
        AjouterReclamation();
    }else if (choix_Menu_utilisateur == 2){
        ConsulterReclamation();
    }else{
        printf("Au revoir!\n\n");
        
    }
}

void  Role_Menu(){

    if (isAdmin){
        MenuAdministrateur();
    }else if (isAgent) {
        MenuAgent();
    }else {
        MenuUtilisateur();
    }
}

void logOut(){
    isSignedIn = 0;
    isAdmin = 0;
    isAgent = 0;
    printf("Vous ete Deconnecte.\n\n");
}

void MenuPrincipal(){
    int choix_Menu_Pricipale;
    do{
        if(!isSignedIn){ 
            printf("========== Menu Pricipal ==========\n");
            printf("1 - Sign In\t 2 - Sign Up\n");
        }
        if(isSignedIn){
            printf("1 - Acceder au Menu en fonction de votre role.\n");
            printf("2 - Log Out.\n\n");
        }
        printf("Quelle est votre choix : ");
        scanf(" %d",&choix_Menu_Pricipale);


        if(!isSignedIn && choix_Menu_Pricipale != 1 && choix_Menu_Pricipale != 2){
            printf("Entrez un Nombre entre 1 - 2.\n");
        }else if(isSignedIn && (choix_Menu_Pricipale < 1 || choix_Menu_Pricipale > 4)){
            printf("Entrez un Nombre entre 1 - 2.\n");
        }

        printf("\n\n");
        
        if (!isSignedIn) {
            if (choix_Menu_Pricipale == 1) {
                MenuSignIn();
            } else if (choix_Menu_Pricipale == 2) {
                MenuSignUp();
            }
        } else {
            if (choix_Menu_Pricipale == 1) {
                Role_Menu();
            } else if (choix_Menu_Pricipale == 2) {
                logOut();
            }
        }
    }while(!isSignedIn || (isSignedIn && choix_Menu_Pricipale != 2));
}

void admin(){
    strcpy(Admin.name_User,"admin");
    strcpy(Admin.password_User,"admin");
    strcpy(Admin.role,"administrateur");

    users[user_Conteur++] = Admin;
}


int main(){
    srand(time(NULL));
    admin();
    MenuPrincipal();
    return 0;
}
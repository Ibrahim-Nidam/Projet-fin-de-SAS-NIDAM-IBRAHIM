#include <stdio.h> // Standard Input/Output library Contains functions for input and output, including:printf - scanf  - fgets
#include <stdlib.h> // Standard Library Provides functions for memory allocation, process control, and conversions:rand - srand - malloc
#include <string.h>  // String handling library Contains functions for manipulating C strings:strcpy - strlen - strstr - strcmp
#include <math.h> // Mathematical library Provides mathematical functions for performing calculations:sqrt - pow - ceil - floor
#include <time.h> // Time library Contains functions for working with time and dates:time - localtime
#include <unistd.h> // POSIX Standard Library Provides access to the operating system's POSIX API, including: sleep: pauses the execution of the program 

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
    int priorite;
    char note[150];
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
        // printf("Checking user: %s, Password: %s\n", users[i].name_User, users[i].password_User); // Debugging
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
    int user_Index;

    printf("========== Sign In ==========\n");

    while (isUser == 0) {
        printf("Entrez votre nom du compte : ");
        scanf("%s", utilisateur);

        
        for (int i = 0; i < user_Conteur; i++) {
            if (strcmp(users[i].name_User, utilisateur) == 0) {
                utilisateur_trouver = 1; 
                break;
            }
        }

        if (utilisateur_trouver == 0) {
            printf("Le nom d'utilisateur est incorrect.\n");
            continue; 
        }

        printf("Entrez votre Mode de Passe : ");
        scanf("%s", password_Utilisateur);

        user_Index = UserCheck(utilisateur, password_Utilisateur);

        if (user_Index != -1) {
            isAdmin = 0;  
            isAgent = 0;  
            printf("\n");
            
            if (strcmp(users[user_Index].role, "administrateur") == 0) {
                isAdmin = 1;
                printf("Bienvenue, Administrateur.\n");
            } 
            
            else if (strcmp(users[user_Index].role, "Agent") == 0) {
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

        if(strcmp(nom_utilisateur,"admin") == 0){
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
        
        while (1) {
            printf("Entrez le numero de la reclamation que vous voulez supprimer ou entrez '.' pour annuler l'action : ");
            getchar();
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

void GenerationStatistiques(){
    int resolution_Conteur = 0;

    printf("Nombre total de reclamations : %d\n", reclamations_Conteur);


    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].status, "resolu") == 0) {
            resolution_Conteur++;
        }
    }

    if (reclamations_Conteur == 0) {
        printf("Aucune reclamation soumise.\n");
        return;
    }

    float Ratio_Resolution = (float)resolution_Conteur / reclamations_Conteur * 100;
    printf("Taux de resolution des reclamations : %.2f%%\n", Ratio_Resolution);

}

void TraiterReclamation() {
    char annuler_choix[10];
    int choix_reclamation;
    int nouvelle_status;
    int note_choix;
    char note[150];
    printf("Traiter Les reclamations : \n\n");
    isEnCours = 1;
    afficherLesReclamations();
       
    getchar();
    while (1) {
        printf("Entrez le numero de la reclamation que vous voulez Traiter ou entrez '.' pour annuler l'action : ");
        fgets(annuler_choix, sizeof(annuler_choix), stdin);
        annuler_choix[strcspn(annuler_choix, "\n")] = '\0';
        
        if (strcmp(annuler_choix, ".") == 0) {
            printf("Action annulee.\n");
            return;
        }
        
        if (sscanf(annuler_choix, "%d", &choix_reclamation) == 1) {
            int valid_choice = 0;
            int claim_index = -1;
            for (int i = 0, j = 0; i < reclamations_Conteur; i++) {
                if (strcmp(reclamations[i].status, "En Cours") == 0) {
                    j++;
                    if (j == choix_reclamation) {
                        valid_choice = 1;
                        claim_index = i;
                        break;
                    }
                }
            }
            
            if (valid_choice) {
                printf("Entrez le nouveau statut de la reclamation 1 - Resolue, 2 - Rejecter : ");
                while (scanf(" %d", &nouvelle_status) != 1 || (nouvelle_status != 1 && nouvelle_status != 2)) {
                    printf("Statut non valide. Veuillez entrer 1 (Resolue) ou 2 (Rejecter) : ");
                    while (getchar() != '\n');  
                }
                
                printf("Voulez vous entrez une note sur le traitement 1 - Oui, 2 - Non : ");
                while (scanf(" %d", &note_choix) != 1 || (note_choix != 1 && note_choix != 2)) {
                    printf("Entree non valide. Veuillez entrer 1 (Oui) ou 2 (Non) : ");
                    while (getchar() != '\n');  
                }
                
                if (note_choix == 1) {
                    printf("Entrez votre note : ");
                    getchar();
                    fgets(note, sizeof(note), stdin);
                    note[strcspn(note, "\n")] = '\0';  
                    strcpy(reclamations[claim_index].note, note);
                    printf("\n");
                }
                
                switch (nouvelle_status) {
                    case 1:
                        strcpy(reclamations[claim_index].status, "resolu");
                        printf("La reclamation numero %d a ete resolue.\n", choix_reclamation);
                        break;
                    case 2:
                        strcpy(reclamations[claim_index].status, "rejecter");
                        printf("La reclamation numero %d a ete rejecter.\n", choix_reclamation);
                        break;
                }
                
                if (note_choix == 1) {
                    printf("La note saisie : %s\n\n", note);
                } else {
                    printf("Aucun note a ete saisie.\n\n");
                }
                
                printf("\nLes reclamations encore en cours : \n");
                afficherLesReclamations();
            } else {
                printf("Numero de reclamation invalide. Veuillez reessayer.\n");
            }
        } else {
            printf("Entree invalide. Veuillez entrer un numero de reclamation valide ou '.' pour annuler.\n");
        }
    }
    isEnCours = 0;
}

void AjouterReclamation(){
    int categorie_choix;

    generateRandomID(nouvelle_Reclamation.id);
    DateDuMoment(nouvelle_Reclamation.date);
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

    printf("Entrez la description du reclamation : ");
    getchar(); 
    fgets(nouvelle_Reclamation.description, sizeof(nouvelle_Reclamation.description), stdin);

    strcpy(nouvelle_Reclamation.status, "En Cours");

    reclamations[reclamations_Conteur++] = nouvelle_Reclamation;

    printf("Reclamation ajoutee avec succes. ID: %s\n", nouvelle_Reclamation.id);

}

void ConsulterReclamation(){

}

void OrdreParPriorite(){

}

void MenuAdministrateur(){
    int choix_Menu_Administrateur = 0;
    
    printf("Bienvenue dans votre espace Administrateur.\n");

    do{
        printf("1 - Gestion des  utilisateurs.\t          2 - Gestion des Reclamations.\n");
        printf("3 - Attribue les roles.\t                  4 - Traiter les reclamations.\n");
        printf("5 - Generation des Statistiques. \t  6 - Afficher les réclamations ordonnées par priorite\n");
        printf("7 - Quittez\n");
        printf("Quelle est votre choix : ");
        scanf(" %d",&choix_Menu_Administrateur);
        printf("\n");

        if(choix_Menu_Administrateur  < 1 || choix_Menu_Administrateur > 7 ){
            printf("Veuillez choisir un choix valide entre 1 - 7.\n");
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
                printf("Au revoir.\n");
                break;
        }

    }while (choix_Menu_Administrateur != 7);
}


void MenuAgent(){
    int choix_Menu_Agent = 0;

    printf("Bienvenue dans votre espace Agent.\n");

    do{
        printf("=========== Menu ===========\n");
        printf("1 - Gerer les reclamations \t 2 - Traiter les reclamations \t 3 - Quittez \n");
        printf("Quelle est votre choix : ");
        scanf(" %d",&choix_Menu_Agent);
        if(choix_Menu_Agent  < 1 || choix_Menu_Agent > 3 ){
            printf("Veuillez choisir un choix valide entre 1 - 3.\n");
        }
    }while (choix_Menu_Agent  < 1 || choix_Menu_Agent > 3);

    if(choix_Menu_Agent == 1){
        GestionReclamations();
    }else if(choix_Menu_Agent == 2){
        TraiterReclamation();
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




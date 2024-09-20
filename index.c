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

void DateDuMoment(char buffer[20], size_t length) {
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    strftime(buffer, length, "%Y-%m-%d %H:%M:%S", tm_now);
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

    printf("Inscription réussie pour %s.\n", utilisateur);
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
                    printf("Utilisateur %s supprimé.\n\n", nom_utilisateur);
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

void GestionReclamations(){

    printf("Les  reclamations sont : \n");

    for(int i =  0; i < reclamations_Conteur; i++){

        printf("- Reclamation %d: ID: %s",i + 1,  reclamations[i].id);
        printf("- Categorie: %s", reclamations[i].categorie);
        printf("- Motif: %s\n", reclamations[i].motif);
        printf("- Description: %s\n", reclamations[i].description);
        printf("- Statut: %s\n", reclamations[i].status);
        printf("- Date: %s\n", reclamations[i].date);
        printf("\n\n");

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
        printf("Entrez le nom d'utilisateur pour changer leur rôle : ");
        scanf(" %s", nom_utilisateur);

        if (UtilisateurExiste(nom_utilisateur)) {
            break; 
        } else {
            printf("Ce compte n'existe pas. Veuillez entrer un autre nom d'utilisateur.\n");
        }
    }

    
    printf("Choisir le nouveau rôle : 1 - Administrateur, 2 - Agent, 3 - Client\n");
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

}

void TraiterReclamation(){

    printf("Traiter Les reclamations. \n");




}

void AjouterReclamation(){

    

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




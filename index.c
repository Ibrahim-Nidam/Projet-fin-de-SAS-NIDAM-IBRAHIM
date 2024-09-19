#include <stdio.h> // Standard Input/Output library Contains functions for input and output, including:printf - scanf  - fgets
#include <stdlib.h> // Standard Library Provides functions for memory allocation, process control, and conversions:rand - srand - malloc
#include <string.h>  // String handling library Contains functions for manipulating C strings:strcpy - strlen - strstr - strcmp
#include <math.h> // Mathematical library Provides mathematical functions for performing calculations:sqrt - pow - ceil - floor
#include <time.h> // Time library Contains functions for working with time and dates:time - localtime
#include <unistd.h> // POSIX Standard Library Provides access to the operating system's POSIX API, including: sleep: pauses the execution of the program 

#define MAX_UTILISATEUR 20
#define MAX_RECLAMATION 10

typedef struct{
    char name_User[20];
    char password_User[20];
    char role[20];
}User;

typedef struct{
    char id;
    char user_Name[30];
    char motif[50];
    char description[100];
    char status[10];
    char date[12];
    int priorite;
}Reclamation;


User users[MAX_UTILISATEUR];
Reclamation reclamations[MAX_RECLAMATION];
User Admin;
User nouvelle_Utilisateur;

int user_Conteur = 0;
int reclamations_Conteur = 0;
int password_Incorrect_Conteur = 0;

int isAdmin = 0;
int isSignedIn = 0;
int isAgent = 0;










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
                return 1;
            }
    }
    return 0;
}


void MenuSignIn() {
    char utilisateur[20];
    char password_Utilisateur[20];
    int isUser = 0; 
    int utilisateur_trouver = 0; 

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

        if (UserCheck(utilisateur, password_Utilisateur)) {

            if (strcmp(password_Utilisateur, Admin.password_User) == 0 && strcmp(utilisateur, Admin.name_User) == 0) {

                isAdmin = 1;
                printf("Bienvenue, Administrateur.\n");

            } else {

                isAdmin = 0; 
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
    users[user_Conteur++] = nouvelle_Utilisateur;

    printf("Inscription réussie pour %s.\n", utilisateur);
     for (int i = 0; i < user_Conteur; i++) {
        printf("Utilisateur %d: Nom: %s, Mot de Passe: %s\n", 
               i + 1, users[i].name_User, users[i].password_User);
    }
}

void MenuAdministrateur(){

}

void MenuAgent(){

}

void  MenuUtilisateur() {

}


void  Role_Menu(){

    if (isAdmin){
        printf("Bienvenue dans le menu Administrateur.\n");
        MenuAdministrateur();
    }else if (isAgent) {
        printf("Bienvenue dans le menu Agent .\n");
        MenuAgent();
    }else {
        printf("Bienvenue dans le menu Utilisateur.\n");
        MenuUtilisateur();
    }
}

void logOut(){
    isSignedIn = 0;
    isAdmin = 0;

    printf("Vous ete Deconnecte.\n\n");
}

void MenuPrincipal(){
    int choix_Menu_Pricipale;
    do{
        if(!isSignedIn){ // finish this tomorrow
            printf("========== Menu Pricipal ==========\n");
            printf("1 - Sign In\t 2 - Sign Up\n");
        }
        if(isSignedIn){
            printf("3 - Acceder au Menu en fonction de votre role.\n");
            printf("4 - Log Out.\n\n");
        }
        printf("Quelle est votre choix : ");
        scanf(" %d",&choix_Menu_Pricipale);


        if(!isSignedIn && choix_Menu_Pricipale != 1 && choix_Menu_Pricipale != 2){
            printf("Entrez un Nombre entre 1 - 2.\n");
        }else if(isSignedIn && (choix_Menu_Pricipale < 1 || choix_Menu_Pricipale > 4)){
            printf("Entrez un Nombre entre 1 - 4.\n");
        }

        printf("\n\n");
        
        if(choix_Menu_Pricipale == 1){
            MenuSignIn();
        }else if(choix_Menu_Pricipale == 2){
            MenuSignUp();
        }else if(isSignedIn && choix_Menu_Pricipale == 3){
            Role_Menu();
        }else if(isSignedIn && choix_Menu_Pricipale == 4){
            logOut();
        }
    }while(!isSignedIn || choix_Menu_Pricipale != 3);


}

void admin(){
    strcpy(Admin.name_User,"admin");
    strcpy(Admin.password_User,"admin");
    strcpy(Admin.role,"administrateur");

    users[user_Conteur++] = Admin;
}


int main(){
    admin();
    MenuPrincipal();
    return 0;
}




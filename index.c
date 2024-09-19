#include <stdio.h> // Standard Input/Output library Contains functions for input and output, including:printf - scanf  - fgets
#include <stdlib.h> // Standard Library Provides functions for memory allocation, process control, and conversions:rand - srand - malloc
#include <string.h>  // String handling library Contains functions for manipulating C strings:strcpy - strlen - strstr - strcmp
#include <math.h> // Mathematical library Provides mathematical functions for performing calculations:sqrt - pow - ceil - floor
#include <time.h> // Time library Contains functions for working with time and dates:time - localtime
#include <unistd.h>

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


User Admin;
User users[MAX_UTILISATEUR];
Reclamation reclamations[MAX_RECLAMATION];

int user_Conteur = 0;
int reclamations_Conteur = 0;
int password_Incorrect_Conteur = 0;

int isAdmin = 0;
int isSignedIn = 0;

void admin(){
    strcpy(Admin.name_User,"admin");
    strcpy(Admin.password_User,"admin");
    strcpy(Admin.role,"administrator");

    users[user_Conteur++] = Admin;
}

void MenuPrincipal(){
    int choix_Menu_Pricipale;
    do{
        printf("========== Menu Pricipal ==========\n");
        printf("1 - Sign In\t 2 - Sign Up\n");
        printf("Quelle est votre choix : ");
        scanf(" %d",&choix_Menu_Pricipale);
        if(choix_Menu_Pricipale != 1 && choix_Menu_Pricipale != 2){
            printf("Entrez un Nombre entre 1 - 2.\n");
        }
        if(isSignedIn == 1){
            printf("3 - Log Out.\n");
        }
        printf("\n\n");
        if(choix_Menu_Pricipale == 1){
            MenuSignIn();
        }else if(choix_Menu_Pricipale == 2){
            MenuSignUp();
        }
    }while(choix_Menu_Pricipale != 1 &&  choix_Menu_Pricipale != 2);


}

int checkPassword (char utilisateur[20],char password_Utilisateur[20]){
    int isUpper = 0;
    int isLower = 0;
    int isNumber = 0;
    int isSpecial = 0;
    int isMinuLength = 8;

    int passLength = strlen(password_Utilisateur);

    if(passLength < isMinuLength){
        printf("Password must be at least 8 characters long.\n");
    }

    for (int i = 0; i < passLength; i++){
        if (password_Utilisateur[i] >= 'A' && password_Utilisateur[i] <= 'Z'){
            isUpper = 1;
        }else if (password_Utilisateur[i] >= 'a' && password_Utilisateur[i] <='z'){
            isLower = 1;
        }else if (password_Utilisateur[i] >= '0' && password_Utilisateur[i] <= '9'){
            isNumber = 1;
        }else {
            isSpecial = 1;
        }
    }

    if (strstr(password_Utilisateur, utilisateur) != NULL){
        printf("Password must not contain the username.\n");
    }

    return isUpper && isLower && isNumber && isSpecial;
}

int UserCheck (char utilisateur[20], char password_Utilisateur[20]){

    for (int i = 0; i < user_Conteur ; i++){
        if(strcmp(users[i].name_User, utilisateur) == 0 && strcmp(users[i].password_User,password_Utilisateur) == 0){
                return 1;
            }else if(strcmp(users[i].name_User, utilisateur) != 0 || strcmp(users[i].password_User,password_Utilisateur) != 0){
                return 0;
            }

    }
}


void MenuSignIn() {
    char utilisateur[20];
    char password_Utilisateur[20];
    int isUser = 0; 
    int utilisateur_trouver = 0; 

    while (isUser == 0) {
        printf("Entrez votre nom du compte : ");
        scanf("%s", utilisateur);

        
        utilisateur_trouver = 0;
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
                printf("Bienvenue, Administrateur %s.\n", Admin.name_User);
            } else {
                isAdmin = 0; 
            }
            isUser = 1; 
        } else {
            printf("Mot de passe incorrect.\n");
            password_Incorrect_Conteur++;

            if (password_Incorrect_Conteur == 3) {
                printf("Vous avez atteint le nombre maximum de tentatives. Veuillez attendre 30 secondes.\n");
                sleep(5); 
                password_Incorrect_Conteur = 0; 
            }
        }
    }

    isSignedIn = 1;
}



void MenuSignUp(){
    char utilisateur[20];
    char password_Utilisateur[20];
    int is_Deja_Utilisateur = 0;
    
    printf("Entrez votre nom du compte : ");
    scanf(" %s", utilisateur);
    printf("Entrez votre Mode de Passe : ");
    scanf(" %s", password_Utilisateur);

    is_Deja_Utilisateur = UserCheck(utilisateur,password_Utilisateur);

    if(is_Deja_Utilisateur == 1 ){
        printf("Ce compte existe deja");
    }else{
        strcpy(utilisateur,users[user_Conteur+1].name_User);
        strcpy(password_Utilisateur,users[user_Conteur+1].password_User);
    }

    

}



int main(){
    admin();

    MenuPrincipal();
    

    


    return 0;
}




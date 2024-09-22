
### Flow Chart for SAS Project: Gestion des Réclamations

1. **Main Menu**
   - Gestion des utilisateurs
   - Gestion des réclamations
   - Statistiques et Rapports

---

2. **Gestion des utilisateurs**
   - **Sign Up**
     - Input: Identifiant, Mot de passe, Informations pertinentes ✅
     - Constraints: 
       - Longueur min: 8 caractères ✅
       - Contient: 1 majuscule, 1 minuscule, 1 chiffre, 1 caractère spécial ✅
       - Ne doit pas contenir le nom d'utilisateur ✅
   - **Sign In**
     - Input: Identifiant, Mot de passe ✅
     - Action: Authentification ✅
     - Lock Account: After failed attempts ✅
   - **Gérer les rôles des utilisateurs**
     - Rôles: Administrateur, Agent de Réclamation, Client
       - **Administrateur**: Accès complet
       - **Agent de Réclamation**: Gère les réclamations ✅
       - **Client**: Soumet et consulte ses réclamations

---

3. **Gestion des réclamations**
   - **Ajouter une réclamation**
     - Input: ID (généré), Motif, Description, Catégorie, Status (auto), Date (auto) ✅
   - **Afficher la liste des réclamations**
     - Access: Administrateurs, Agents de Réclamation ✅
   - **Modifier/Supprimer une réclamation**
     - Conditions: 
       - Administrateurs/Agents: Toutes ✅
       - Clients: Seulement leurs réclamations, sous conditions
   - **Traiter une réclamation**
     - Actions: Marquer comme "en cours", "résolue", "fermée" ✅
     - Ajout de notes internes ✅
   - **Rechercher une réclamation**
     - Criteria: ID, nom du client, date, statut, catégorie
   - **Système de priorité**
     - Attribuer priorité (basse, moyenne, haute)
     - Afficher réclamations par priorité (accessible aux administrateurs)

---

4. **Statistiques et Rapports**
   - **Afficher le nombre total de réclamations**
     - Access: Administrateurs ✅
   - **Afficher le taux de résolution**
     - Access: Administrateurs ✅
   - **Calculer le délai moyen de traitement**
     - Access: Administrateurs
   - **Générer un rapport journalier**
     - Liste: Nouvelles réclamations et celles résolues

---



i have a problem with showing just the claims of the user that made them.
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
    char name_utilisateur[20];
}Reclamation;

User users[MAX_UTILISATEUR];
Reclamation reclamations[MAX_RECLAMATION];
User Admin;
User nouvelle_Utilisateur;
Reclamation nouvelle_Reclamation;

int user_Index = -1;
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
                user_Index = i;
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

void AjouterReclamation(){
    int categorie_choix;
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
    }while(categorie_choix  < 1 || categorie_choix > 4);
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
void ReclamationPrecisDuClient(){
     int Index_reclamation_utilisateur = 1;
    // Display claims belonging to the signed-in user
    printf("Les reclamations pour l'utilisateur %s sont : \n", users[user_Index].name_User);
    for (int i = 0; i < reclamations_Conteur; i++) {
        if (strcmp(reclamations[i].name_utilisateur, users[user_Index].name_User) == 0) {
            printf("- Reclamation %d: ID: %s ", Index_reclamation_utilisateur++, reclamations[i].id);
            printf("- Categorie: %s ", reclamations[i].categorie);
            printf("- Motif: %s\n", reclamations[i].motif);
            printf("- Description: %s\n", reclamations[i].description);
            printf("- Statut: %s\n", reclamations[i].status);
            printf("- Date: %s\n", reclamations[i].date);
            printf("==========================================\n\n");
        }
    }
    if  (Index_reclamation_utilisateur == 1) {
        printf("Aucune reclamation trouvee pour cet utilisateur.\n");
    }
}
void ConsulterReclamation(){
    ReclamationPrecisDuClient();
}
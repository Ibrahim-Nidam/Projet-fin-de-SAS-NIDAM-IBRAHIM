
### Flow Chart for SAS Project: Gestion des Réclamations

1. **Main Menu**
   - Gestion des utilisateurs
   - Gestion des réclamations
   - Statistiques et Rapports

---

2. **Gestion des utilisateurs**
   - **Sign Up**
     - Input: Identifiant, Mot de passe, Informations pertinentes
     - Constraints: 
       - Longueur min: 8 caractères
       - Contient: 1 majuscule, 1 minuscule, 1 chiffre, 1 caractère spécial
       - Ne doit pas contenir le nom d'utilisateur
   - **Sign In**
     - Input: Identifiant, Mot de passe
     - Action: Authentification
     - Lock Account: After failed attempts
   - **Gérer les rôles des utilisateurs**
     - Rôles: Administrateur, Agent de Réclamation, Client
       - **Administrateur**: Accès complet
       - **Agent de Réclamation**: Gère les réclamations
       - **Client**: Soumet et consulte ses réclamations

---

3. **Gestion des réclamations**
   - **Ajouter une réclamation**
     - Input: ID (généré), Motif, Description, Catégorie, Status (auto), Date (auto)
   - **Afficher la liste des réclamations**
     - Access: Administrateurs, Agents de Réclamation
   - **Modifier/Supprimer une réclamation**
     - Conditions: 
       - Administrateurs/Agents: Toutes
       - Clients: Seulement leurs réclamations, sous conditions
   - **Traiter une réclamation**
     - Actions: Marquer comme "en cours", "résolue", "fermée"
     - Ajout de notes internes
   - **Rechercher une réclamation**
     - Criteria: ID, nom du client, date, statut, catégorie
   - **Système de priorité**
     - Attribuer priorité (basse, moyenne, haute)
     - Afficher réclamations par priorité (accessible aux administrateurs)

---

4. **Statistiques et Rapports**
   - **Afficher le nombre total de réclamations**
     - Access: Administrateurs
   - **Afficher le taux de résolution**
     - Access: Administrateurs
   - **Calculer le délai moyen de traitement**
     - Access: Administrateurs
   - **Générer un rapport journalier**
     - Liste: Nouvelles réclamations et celles résolues

---


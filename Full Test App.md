# Plan de Test du Systeme de Gestion des Reclamations

## I. Test des Fonctionnalites Administrateur

1. Se connecter en tant qu'administrateur
2. Tester toutes les fonctions disponibles pour l'administrateur

## II. Gestion des Comptes Utilisateurs

1. Tester le mot de passe avec le meme nom d'utilisateur
2. Essayer de creer un autre compte avec le meme nom d'utilisateur
3. Creer 4 comptes : ibra, hamid, omar, mohammed
4. Tester le mot de passe (cas de verrouillage)

## III. Gestion des Roles Administrateur et Agent

1. Se connecter en tant qu'administrateur :
   - Acceder a la gestion des utilisateurs
   - Supprimer le compte d'mohammed

2. Se connecter en tant qu'administrateur :
   - Acceder a l'attribution des roles
   - Promouvoir ibra au role d'Agent

3. Se connecter en tant qu'agent (ibra) :
   - Tester toutes les fonctions de l'agent

## IV. Gestion des Reclamations pour Invites et Utilisateurs

1. Se connecter en tant qu'invite :
   - Tester la fonction de consultation

2. Se connecter en tant qu'utilisateur **OMAR** :
   - Creer 5 reclamations (dont 3 principales pour le test) :

     a) Reclamation 1 (priorite basse) : [Details a definir] 
         **supprimer sur place**

     b) Reclamation 2 : [Details a definir]
         **modifier sur place**
     
     c) Reclamation 3 (pour test de modification) :
     ```
     Categorie : Financier
     Motif     : Action critique requise.
     Description : Ce probleme est urgent.
     ```
     **prioriter : high**

     d) Reclamation 4 :
     ```
     Categorie : Autre
     Motif     : Traitement ASAP necessaire.
     Description : C'est un probleme importante.
     ```
     **prioriter :Mix - high**

     e) Reclamation 5 :
     ```
     Categorie : Service
     Motif     : Peut attendre un peu.
     Description : Il est rapide a resoudre.
     ```
      **prioriter : moyen**
     

## V. Traitement des Reclamations par l'Agent et l'Administrateur

1. **Se connecter en tant qu'agent (ibra)** :
   - Supprimer la Reclamation 1 (utilisee pour tester la modification)
   - Traiter les reclamations :
     a. Resoudre la Reclamation 2 avec une note
     b. Rejeter la Reclamation 3 sans commentaire

2. **Se connecter en tant qu'utilisateur (hamid)** :
   - Creer 2 reclamations supplementaires :
     a) Reclamation 6 :
     ```
     Categorie : Service
     Motif     : Un probleme critique.
     Description : Peut etre resolu rapidement.
     ```
     **prioriter : Mix - high**

     b) Reclamation 7 :
     ```
     Categorie : Technique
     Motif     : Elle est moderee.
     Description : Cette tache peut etre faite ASAP.
      
     ```
     **prioriter : moyen**

     e) Reclamation 8 : [Details a definir]
      **pour prioriter basse**

3. **Se connecter en tant qu'administrateur** :
   - Gerer les reclamations :
     a. Resoudre 1 reclamation avec une note
     b. Rejeter 2 reclamations sans notes

   - Rechercher des reclamations :
     - Par ID
     - Par categorie : Service
     - Par nom : mohammed

   - **Afficher les reclamations par priorite** :
     - Mots-cles de haute priorite : "Urgent", "Critique", "Importante"
     - Mots-cles de priorite moyenne : "ASAP", "Moderee", "Rapide"

   - **Generer des statistiques**
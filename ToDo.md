Projet SAS : Gestion des réclamations
Introduction :

Créez une application console pour gérer les réclamations des clients. Cette application permet de gérer les réclamations soumises par les clients, de les traiter, de les modifier si nécessaire, d'afficher les détails des réclamations, et de générer des statistiques sur les réclamations résolues ou en attente.

Contexte du projet :
L’application doit inclure un menu principal qui permet de :

I- Gestion des utilisateurs :

1. Créer des comptes utilisateurs :
Sign Up (Inscription) : Permet aux nouveaux utilisateurs de créer un compte en fournissant un identifiant, un mot de passe, et d'autres informations pertinentes.

2. Ajout de contraintes pour le mot de passe :
Définition des contraintes de mot de passe :
Longueur minimale : 8 caractères
Doit contenir au moins :
Une lettre majuscule
Une lettre minuscule
Un chiffre
Un caractère spécial (par exemple : !@#$%^&*)
Ne doit pas contenir le nom d'utilisateur

3. Sign In (Connexion) : Permet aux utilisateurs enregistrés de se connecter à l'application en utilisant leur identifiant et mot de passe.

4. Système de verrouillage : Mettez en place un système de verrouillage de compte après plusieurs tentatives de connexion échouées.

Gérer les rôles des utilisateurs :
Définir différents rôles tels que Administrateur, Agent de Réclamation, et Client.
- Administrateur : A tous les droits d'accès, y compris la gestion des réclamations, des utilisateurs, et la génération de statistiques, et l'attribution des rôles.
- Agent de Réclamation : Peut gérer les réclamations, traiter les réclamations des clients, mais ne peut pas gérer les utilisateurs.
- Client : Peut uniquement soumettre et consulter ses propres réclamations, ainsi que suivre leur état.

II- Gestion des réclamations :

1. Ajouter une réclamation :
Les clients peuvent soumettre une réclamation,

Une réclamation doit contenir les informations suivantes :
ID : Un identifiant unique, généré aléatoirement par le programme.
Motif : Le motif de la réclamation (par exemple : produit défectueux, service client, facturation).
Description : Une description détaillée du problème rencontré.
Catégorie : La catégorie de la réclamation.
Status : Le statut de la réclamation (par exemple : en cours, résolu, rejeté).
Date : La date de soumission, auto-insérée comme la date du jour.
L'ID doit être unique et généré automatiquement, tandis que la date sera insérée automatiquement en tant que date du jour lors de la soumission.

2. Afficher la liste des réclamations :
Accessible aux administrateurs et agents de réclamation. Affiche toutes les réclamations soumises, avec leurs détails (client, date, description, et statut).

3. Modifier ou supprimer une réclamation :
Les administrateurs et agents de réclamation peuvent modifier ou supprimer n'importe quelle réclamation.
Les clients peuvent uniquement modifier ou supprimer leurs propres réclamations tant qu'elles n'ont pas été traitées et que moins de 24 heures se sont écoulées depuis la soumission de la réclamation.

4. Traiter une réclamation :
Les administrateurs et agents de réclamation peuvent marquer une réclamation comme "en cours", "résolue", ou "fermée". Ils peuvent aussi ajouter des notes internes sur les étapes de traitement.

5. Rechercher une réclamation :
Accessible aux administrateurs et agents de réclamation. Recherche par identifiant de réclamation, nom du client, ou date de soumission pour afficher les détails associés.
Ajouter la recherche par statut (en attente, en cours, résolu) ou par catégorie de réclamation. Accessible aux administrateurs et agents de réclamation.

6. Système de priorité :
Attribuer automatiquement une priorité (basse, moyenne, haute) aux réclamations basée sur des mots-clés dans la description.

7. Afficher les réclamations ordonnées par priorité :
Accessible aux administrateurs. Afficher les réclamations triées en fonction de leur priorité (basse, moyenne, haute) pour faciliter le traitement en fonction de l'urgence.

III- Statistiques et Rapports :

1. Afficher le nombre total de réclamations :
Seuls les administrateurs peuvent accéder à cette section.

2. Afficher le taux de résolution des réclamations :
Seuls les administrateurs peuvent voir combien de réclamations ont été résolues par rapport au nombre total soumises.

3. Calculer le délai moyen de traitement des réclamations :
Les administrateurs peuvent analyser combien de temps en moyenne il faut pour traiter une réclamation.

4. Rapport journalier:
Générez un rapport texte quotidien listant les nouvelles réclamations et celles résolues.


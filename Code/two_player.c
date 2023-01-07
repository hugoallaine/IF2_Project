// © Hugo Allainé - Léo Angonnet
//
//          Projet IF2B
//          Jeu Mefuhva
//
// Mode 2 joueurs
// two_player.c

/* Bibliothèques */

#include "two_player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include "tableau.h"
#include "save.h"


/* Prototypes */

void two_player(int plateau_de_jeu[][6], int nb_tour_2j);


/* Code */

void two_player(int plateau_de_jeu[][6], int nb_tour_2j){
    // Fonction de jeu contre un autre joueur
    int partie_en_cours=1, code_fin=0;
    Coord coord_j1, coord_j2;

    while(partie_en_cours){
        printf("############## Tour n°%d ##############\n\n",nb_tour_2j);
        /* Joueur 1 */
        printf("C'est au tour du Joueur 1 !\n");
        do{
            printf("[Joueur 1] Sélectionne la ligne (0,1) --> ");
            scanf("%d",&coord_j1.ligne);
            fflush(stdin);
            printf("[Joueur 1] Sélectionne la colonne (0,5) --> ");
            scanf("%d",&coord_j1.colonne);
            fflush(stdin);
        }while(dans_tableau(coord_j1,1,plateau_de_jeu)==0); // Vérifie si les coordonnées sont bien dans le camp du joueur
        printf("Déplacement de vos graines en cours...\n");
        coord_j1 = deplacement_graine(coord_j1,plateau_de_jeu);
        printf("[Joueur 1] Vous vous arrêtez en coordonnée (%d,%d).\n",coord_j1.ligne,coord_j1.colonne);
        afficher_tableau(plateau_de_jeu);

        sleep(3);   // Permet une meilleure lisibilité du jeu (peut être encore + optimisé)

        // Vérifie si la capture de graine est possible
        if(capture_possible(coord_j1,1,plateau_de_jeu)){
            printf("[Joueur 1] Tu as capturé des graines de ton adversaire.\n");
            capture_graine(coord_j1,1,plateau_de_jeu);
            afficher_tableau(plateau_de_jeu);
        }
        else{
            printf("[Joueur 1] Tu n'as pas pu capturer des graines de ton adversaire.\n");
        }

        // Vérification s'il y a un gagnant
        code_fin = is_finish(plateau_de_jeu);
        if(code_fin == 1){
            printf("Joueur 1 n'a plus de graine sur son plateau.\nJoueur 2 gagne la partie !\n");
            partie_en_cours=0;
            break;
        }
        if(code_fin == 2){
            printf("Joueur 2 n'a plus de graine sur son plateau.\nJoueur 1 gagne la partie !\n");
            partie_en_cours=0;
            break;
        }

        sleep(3);

        /* Joueur 2 */
        printf("\nC'est au tour du Joueur 2 !\n");
        do{
            printf("[Joueur 2] Sélectionne la ligne (2,3) --> ");
            scanf("%d",&coord_j2.ligne);
            fflush(stdin);
            printf("[Joueur 2] Sélectionne la colonne (0,5) --> ");
            scanf("%d",&coord_j2.colonne);
            fflush(stdin);
        }while(dans_tableau(coord_j2,2,plateau_de_jeu)==0); // Vérifie si les coordonnées sont bien dans le camp du joueur
        printf("Déplacement de vos graines en cours...\n");
        coord_j2 = deplacement_graine(coord_j2,plateau_de_jeu);
        printf("[Joueur 2] Vous vous arrêtez en coordonnée (%d,%d).\n",coord_j2.ligne,coord_j2.colonne);
        afficher_tableau(plateau_de_jeu);

        sleep(3);

        // Vérifie si la capture de graine est possible
        if(capture_possible(coord_j2,2,plateau_de_jeu)){
            printf("[Joueur 2] Tu as capturé des graines de ton adversaire.\n");
            capture_graine(coord_j2,2,plateau_de_jeu);
            afficher_tableau(plateau_de_jeu);
        }
        else{
            printf("[Joueur 2] Tu n'as pas pu capturer des graines de ton adversaire.\n");
        }

        // Vérification s'il y a un gagnant
        code_fin = is_finish(plateau_de_jeu);
        if(code_fin == 1){
            printf("Joueur 1 n'a plus de graine sur son plateau.\nJoueur 2 gagne la partie !\n");
            partie_en_cours=0;
            break;
        }
        if(code_fin == 2){
            printf("Joueur 2 n'a plus de graine sur son plateau.\nJoueur 1 gagne la partie !\n");
            partie_en_cours=0;
            break;
        }

        // Demande pour continuer ou sauvegarder
        char continuer;
        printf("\nFin du tour, Si vous souhaitez arrêter et sauvegarder, entrez *, sinon appuyez sur Entrée --> ");
        scanf("%c",&continuer);
        fflush(stdin);
        if(continuer=='*'){
            save(2,nb_tour_2j,plateau_de_jeu);
            partie_en_cours=0;
            break;
        }
        else{
            printf("Très bien, continuons.\n\n");
        }

        nb_tour_2j+=1;
    }
    sleep(3);
}

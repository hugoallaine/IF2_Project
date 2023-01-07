// © Hugo Allainé - Léo Angonnet
//
//          Projet IF2B
//          Jeu Mefuhva
//

// Programme principal
// main.c

/* Bibliothèques */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "save.h"
#include "tableau.h"
#include "one_player.h"
#include "two_player.h"

// Commandes expliquées dans le livrable
#ifdef _WIN32
#include <windows.h>
#define START UINT default_codepage = GetConsoleOutputCP();SetConsoleOutputCP(65001);
#define CLOSE SetConsoleOutputCP(default_codepage)
#else
#define START
#define CLOSE
#endif


/* Code */

void selection_option(int *answer){
    // Variable du plateau de jeu
    int plateau_de_jeu[4][6];

    // Fonction du menu du jeu
    char choix;
    do{
        printf("#########################################\n");
        printf("Menu Principal\n\nSélectionne une option :\n\n");
        printf("  (a) Mode 1 Joueur (contre l'ordinateur)\n  (b) Mode 2 Joueur\n  (c) Reprendre une partie\n  (d) Quitter le jeu\n\n--> ");
        scanf("%c",&choix);
        fflush(stdin);
        switch(choix){
            case 'a':
                // Mode 1 Joueur (contre ordi)
                printf("Vous avez choisis le mode 1 Joueur.\n");

                /* one_player.c */
                // Configuration de la partie
                printf("\n#########################################\n\n");
                printf("Vous allez jouer à tour de role contre l'ordinateur.\nLorsque c'est à vous de jouer, votre identifiant apparait avant de répondre. (Exemple: '[Joueur 1] --> ')\nL'ordinateur jouera automatiquement après vous.\nSi vous faites une erreur, les coordonnées vous seront demandées à nouveau.\n\nVoici le plateau :\n");
                remplir_tableau(plateau_de_jeu);
                afficher_tableau(plateau_de_jeu);
                printf("\n");

                // Début de la partie
                one_player(plateau_de_jeu,1);

                break;

            case 'b':
                // Mode 2 Joueurs
                printf("Vous avez choisis le mode 2 Joueurs.\n");

                /* two_player.c */
                // Configuration de la partie
                printf("\n#########################################\n\n");
                printf("Vous allez jouer à tour de role l'un contre l'autre.\nLorsque c'est à vous de jouer, votre identifiant apparait avant de répondre. (Exemple: '[Joueur 1] --> ')\nChoisissez parmis vous qui sera le joueur 1 et le joueur 2.\nSi vous faites une erreur, les coordonnées vous seront demandées à nouveau.\n\nVoici le plateau :\n");
                remplir_tableau(plateau_de_jeu);
                afficher_tableau(plateau_de_jeu);
                printf("\n");

                // Début de la partie
                two_player(plateau_de_jeu,1);

                break;

            case 'c':
                // Reprendre la partie
                printf("Vous avez choisis de Reprendre une partie.\n");

                int type_of_game, nb_tour_2j=1;

                load(&type_of_game,&nb_tour_2j,plateau_de_jeu); //Charge la sauvegarde

                if(type_of_game == 1){  // Sélectionne le mode de jeu à lancer en fonction de ce qu'il y a dans le fichier de sauvegarde
                    afficher_tableau(plateau_de_jeu);
                    one_player(plateau_de_jeu,nb_tour_2j);
                }
                if(type_of_game == 2){
                    afficher_tableau(plateau_de_jeu);
                    two_player(plateau_de_jeu,nb_tour_2j);
                }

                break;

            case 'd':
                // Quitter le jeu
                printf("À très bientôt !\n");
                *answer = 1;
                break;

            default:
                printf("\nErreur, vous n'avez pas compris. Entrez la lettre correspondante à l'option souhaitée\n\n");
        }
    }while(choix!='a' && choix!='b' && choix!='c' && choix!='d'); // Affiche le menu tant que l'utilisateur n'a pas rentré une de ces lettres
}

int main(){
    START; // Cette partie permet de changer la table de caractère de la console Windows en utf-8 afin d'afficher les caractères accentués.

    printf("Bienvenue dans le jeu du Mefuhva !\n© Hugo Allainé - Léo Angonnet\n");
    int answer = 0;
    do{
        selection_option(&answer); // Lancement du menu
    }while(answer==0);

    CLOSE; // Reset de la table de caractère de la console Windows par défaut ou ne fait rien si exécuter sur linux/macOS
    return 0;
}

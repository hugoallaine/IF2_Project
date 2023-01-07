// © Hugo Allainé - Léo Angonnet
//
//          Projet IF2B
//          Jeu Mefuhva
//
// Module tableau
// tableau.c

/* Bibliothèques */

#include "tableau.h"
#include <stdio.h>
#include <stdlib.h>


/* Prototypes */

/*struct Coordonnees{
    int ligne;
    int colonne;
};*/
typedef struct Coordonnees Coord;

void remplir_tableau(int tableau[][6]);
void afficher_tableau(int tableau[][6]);
Coord case_suivante(Coord c);
int dans_tableau(Coord c, int joueur, int tab[][6]);
Coord deplacement_graine(Coord c, int tab[][6]);
int capture_possible(Coord c, int joueur, int tab[][6]);
void capture_graine(Coord c, int joueur, int tab[][6]);
int is_finish(int tab[][6]);


/* Code */

void remplir_tableau(int tableau[][6]){
    // Fonction de remplissage du plateau de jeu (configuration de début de partie)
    for(int i = 0;i<4;i++){
        for(int j = 0;j<6;j++){
            tableau[i][j] = 2;  // Remplissage de toutes les cases avec des 2
        }
    }
    tableau[1][4] = 1,tableau[1][5] = 0;    // Remplissage de certaines cases avec un 1 et un 0
    tableau[2][0] = 0,tableau[2][1] = 1;
}

void afficher_tableau(int tableau[][6]){
    // Fonction affichant le plateau de jeu
    int i = 0, j = 0;
    printf("---------- Joueur 1 ----------\n");
    for(i = 0;i<4;i++){
        if(i == 2 ){
            printf("------------------------------\n");
        }
        for(j = 0;j<6;j++){
            printf(" [%d] ",tableau[i][j]);
        }
        printf("\n");
    }
    printf("---------- Joueur 2 ----------\n");
}

Coord case_suivante(Coord c){
    // Fonction retournant les coordonnées de la case suivante pour les déplacements du jeu
    if(c.ligne == 0){
        if(c.colonne == 0){
            c.ligne = 1;
            c.colonne = 0;
            return c;
        }
        else{
            c.ligne = 0;
            c.colonne -= 1;
            return c;
        }
    }
    if(c.ligne == 1){
        if(c.colonne == 5){
            c.ligne = 0;
            c.colonne = 5;
            return c;
        }
        else{
            c.ligne = 1;
            c.colonne += 1;
            return c;
        }
    }
    if(c.ligne == 2){
        if(c.colonne == 0){
            c.ligne = 3;
            c.colonne = 0;
            return c;
        }
        else{
            c.ligne = 2;
            c.colonne -= 1;
            return c;
        }
    }
    if(c.ligne == 3){
        if(c.colonne == 5){
            c.ligne = 2;
            c.colonne = 5;
            return c;
        }
        else{
            c.ligne = 3;
            c.colonne += 1;
            return c;
        }
    }
}

int dans_tableau(Coord c, int joueur, int tab[][6]){
    // Fonction indiquant si le joueur a rentré des coordonnées se trouvant dans sa zone de jeu
    if(c.colonne >= 0 && c.colonne <= 5){
        if(joueur == 1 && c.ligne >= 0 && c.ligne <= 1 && tab[c.ligne][c.colonne]!=0){
            return 1;
        }
        if(joueur == 2 && c.ligne >= 2 && c.ligne <= 3 && tab[c.ligne][c.colonne]!=0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

Coord deplacement_graine(Coord c, int tab[][6]){
    // Fonction permettant de déplacer ces graines une à une
    int nb_graine = tab[c.ligne][c.colonne];
    while(nb_graine != 0){
        tab[c.ligne][c.colonne] = 0;
        for(int j=0;j<nb_graine;j++){
            c = case_suivante(c);
            tab[c.ligne][c.colonne] += 1;
        }
        if(tab[c.ligne][c.colonne]>1){
            nb_graine = tab[c.ligne][c.colonne];
        }
        else{
            nb_graine = 0;
        }
    }
    return c;
}

int capture_possible(Coord c, int joueur, int tab[][6]){
    // Fonction indiquant si la dernière graine se trouve en bordure extérieur ou intérieur (donc si la capture est possible ou non)
    if(c.colonne >= 0 && c.colonne <= 5){
        if(joueur == 1 && c.ligne == 1 && tab[c.ligne+1][c.colonne] != 0){
            return 1;
        }
        if(joueur == 2 && c.ligne == 2 && tab[c.ligne-1][c.colonne] != 0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

void capture_graine(Coord c, int joueur, int tab[][6]){
    // Fonction permettant de capturer les graines de l'adversaire
    int recolte = 0;
    if(joueur==1){
        recolte = tab[c.ligne+1][c.colonne] + tab[c.ligne+2][c.colonne];
        tab[c.ligne+1][c.colonne] = 0;
        tab[c.ligne+2][c.colonne] = 0;
    }
    if(joueur==2){
        recolte = tab[c.ligne-1][c.colonne] + tab[c.ligne-2][c.colonne];
        tab[c.ligne-1][c.colonne] = 0;
        tab[c.ligne-2][c.colonne] = 0;
    }
    tab[c.ligne][c.colonne] += recolte;
}

int is_finish(int tab[][6]){
    // Fonction indiquant s'il reste encore des graines sur les camps des joueurs.
    // Retourne 0 si les deux joueurs ont encore des graines ; 1 si Joueur 1 n'a plus de graine ; 2 si Joueur 2 n'a plus de graine
    int compteur_j1=0, compteur_j2=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<6;j++){
            if(i==0 || i==1){
                if(tab[i][j]!=0){
                    i+=1;
                    compteur_j1 = 1;
                    break;
                }
            }
            if(i==2 || i==3){
                if(tab[i][j]!=0){
                    i+=1;
                    compteur_j2 = 1;
                    break;
                }
            }
        }
    }
    if(compteur_j1 == 1 && compteur_j2 == 1){
        return 0;
    }
    else{
        if(compteur_j1 == 0 && compteur_j2 == 1){
            return 1;
        }
        if(compteur_j1 == 1 && compteur_j2 == 0){
            return 2;
        }
        else{
            printf("[DEBUG][is_finish] Bug\n");
        }
    }
}
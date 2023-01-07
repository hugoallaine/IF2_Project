// © Hugo Allainé - Léo Angonnet
//
//          Projet IF2A
//          Jeu Mefuhva
//
// Header tableau.h

#ifndef _tableau_h_
#define _tableau_h_

struct Coordonnees{
    int ligne;
    int colonne;
};
typedef struct Coordonnees Coord;

void remplir_tableau(int tableau[][6]);
void afficher_tableau(int tableau[][6]);
Coord case_suivante(Coord c);
int dans_tableau(Coord c, int joueur, int tab[][6]);
Coord deplacement_graine(Coord c, int tab[][6]);
int capture_possible(Coord c, int joueur, int tab[][6]);
void capture_graine(Coord c, int joueur, int tab[][6]);
int is_finish(int tab[][6]);

#endif // tableau.h
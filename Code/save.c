// © Hugo Allainé - Léo Angonnet
//
//          Projet IF2A
//          Jeu Mefuhva
//

// Programme de sauvegarde
// save.c

/* Bibliothèques */

#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* Prototypes */

void save(int type_of_game, int nb_tour, int tab[][6]);
void load(int *type_of_game, int *nb_tour, int tab[][6]);


/* Code */

void save(int type_of_game, int nb_tour, int tab[][6]){
    // Fonction permettant de sauvegarder le plateau de jeu actuel dans un fichier txt
    printf("Sauvegarde de la partie en cours...\n");
    FILE* f = fopen("save.txt","w");    // Ouverture du fichier de sauvegarde en mode écriture
    if(f != NULL){
        int h, m, s, jour, mois, an;
        time_t now = time(NULL);
        struct tm *local = localtime(&now); // Module time permet d'obtenir l'heure et la date actuelle
        h = local->tm_hour;
        m = local->tm_min;
        s = local->tm_sec;
        jour = local->tm_mday;
        mois = local->tm_mon + 1;
        an = local->tm_year + 1900;
        fprintf(f,"Sauvegarde du %02d/%02d/%d à %02d:%02d:%02d\n\n",jour,mois,an,h,m,s);    // Ecrit la date et l'heure de la sauvegarde
        fprintf(f,"%d\n",type_of_game); // Ecrit le mode de jeu de la partie à sauvegarder
        fprintf(f,"%d\n",nb_tour);      // Ecrit le nombre de tour où la partie s'est arrêté
        for(int i=0;i<4;i++){
            for(int j=0;j<6;j++){
                fprintf(f,"%d ",tab[i][j]); // Ecrit le plateau de jeu
            }
            fprintf(f,"\n");
        }
        printf("Sauvegarde effectuée avec succès !\n\n");
    }else{
        printf("[DEBUG][save] Erreur, fichier non trouvé.\n");
    }
    fclose(f);  // Fermeture du fichier de sauvegarde
}

void load(int *type_of_game, int *nb_tour, int tab[][6]){
    // Fonction permettant de charger la sauvegarde du plateau de jeu depuis un fichier txt
    printf("Chargement de la partie en cours...\n");
    char buffer[256];
    int t, nb;
    FILE* f = fopen("save.txt","r");    // Ouverture du fichier de sauvegarde en mode lecture
    if(f != NULL){
        for(int k=0;k<2;k++){
            fgets(buffer,256,f);    // Lis les deux premières lignes pour sauter l'entête 
        }
        fscanf(f,"%d",&t);  // Lis le mode de jeu
        *type_of_game = t;
        fscanf(f,"%d",&nb); // Lis le nombre de tour
        *nb_tour = nb;
        for(int i=0;i<4;i++){
            fscanf(f,"%d %d %d %d %d %d ",&tab[i][0],&tab[i][1],&tab[i][2],&tab[i][3],&tab[i][4],&tab[i][5]); // Lis le plateau de jeu
        }
        printf("Chargement effectué avec succès !\n\n");
    }else{
        printf("[DEBUG][load] Erreur, fichier non trouvé.\n");
    }
    fclose(f);   // Fermeture du fichier de sauvegarde
}
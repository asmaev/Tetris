#ifndef _SCORE_H_
#define _SCORE_H_
#include<stdlib.h>
#include<stdio.h>
#include<MLV/MLV_all.h>

int ecrire_score(char[][25], int[]);
int lire_score(char[][25], int[]);
void afficher_score(char[][25], int[]);
void ajouter_score(char[][25]);
void msg_erreur(char*);
void tri(char[][25], int[]);
void assigner(char[][25], char[][25], int, int);
void ajouter_scorej1(char[][25]);
void ajouter_scorej2(char[][25]);

#endif

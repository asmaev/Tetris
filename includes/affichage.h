#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_
#include<stdlib.h>
#include<stdio.h>
#include<MLV/MLV_all.h>
#include"types.h"

#define COTE 40
#define JAUNE MLV_rgba(255,215,0,255)
#define CIEL MLV_rgba(60,175,240,255)
#define BLEU MLV_rgba(10,55,200,255)
#define ORANGE MLV_rgba(255,160,0,255)
#define VERT MLV_rgba(50,205,50,255)
#define ROUGE MLV_rgba(255,0,0,255)
#define VIOLET MLV_rgba(120,0,180,255)

MLV_Color couleur(int);
void cube(int, int, int, int);
void affiche_fond(int, int);
void affiche_matrice(config*, int, int, int);
void affiche_score(config *, int, int, int);
void affiche_suiv(config *, int, int, int, int);
void affiche_1j(config*, int, int);
void affiche_2j(config*, config*, int, int);

#endif

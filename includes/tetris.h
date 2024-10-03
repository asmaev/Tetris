#ifndef _TETRIS_H_
#define _TETRIS_H_
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"types.h"


config initialiser();
int actu_suiv(config*);
int est_pleine(config*, int);
void supprimer_ligne(config*, int);
void decalage(config*, int);
int piece(int[5][2], int);
int rotate(config*, int[5][2]);
int rotation(config*, int[5][2]);
int estfini(config*, int[5][2]);
void inserer(config*, int[5][2]);
int descendre(config*, int[5][2]);
int decaler_g(config*, int[5][2]);
int decaler_d(config*, int[5][2]);



#endif

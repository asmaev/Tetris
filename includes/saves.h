#ifndef _SAVES_H_
#define _SAVES_H_
#include<stdlib.h>
#include<stdio.h>
#include"types.h"

void enregistrer(config*, FILE*);
void load(config*, FILE*);
void enregistrer_1j(config*);
void load_1j(config*);
void enregistrer_2j(config*, config*);
void load_2j(config*, config*);



#endif

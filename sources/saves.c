#include"saves.h"

void enregistrer(config *c, FILE *f){
  int i, j;
  for(i=0; i<20; i++){ /*ecriture de la matrice de jeu*/
    for(j=0; j<10; j++)
      fputc(c->tab[i][j]+'0',f);
    fputc('\n', f);
  }
  fprintf(f, "%d\n", c->score); /*ecriture du score*/
  fprintf(f, "%d\n", c->speed); /*ecriture de la vitesse*/
  for(i=0; i<4; i++)            /*ecriture des pièces suivante*/
    fputc(c->suiv[i]+'0', f);
  fputc('\n', f);
  for(i=0; i<5; i++){          /*ecriture de l'emplacement de la pièce*/
    fprintf(f, "%d ", c->coord[i][0]);
    fprintf(f, "%d\n", c->coord[i][1]);
  }
}

void load(config *c, FILE *f){
  int i, j, g;
  for(i=0; i<20; i++){  /*lecture de la matrice*/
    for(j=0; j<11; j++)
      if((g = fgetc(f)) != '\n'){
	g -= '0';
	c->tab[i][j] = g;
      }
  }
  if(fscanf(f, "%d", &c->score)!=1)  /*lecture du score*/
    printf("erreur\n");
  if(fscanf(f, "%d", &c->speed)!=1) /*lecture speed*/
    printf("erreurbis\n");
  for(i=0; i<4; i++){   /*lecture des pièces prévues*/
    g = fgetc(f)-'0';
    c->suiv[i] = g;
  }
  fgetc(f);
  for(i=0; i<5; i++)   /*lecture le l'emplacement*/
    if(fscanf(f, "%d %d", &c->coord[i][0], &c->coord[i][1])!=2)
      printf("erreur %d\n", i);
}

void enregistrer_1j(config *c){
  FILE *f=NULL;
  if((f = fopen("data/saves/save1j.txt", "w")) == NULL) /*ouverture*/
    printf("erreur ouverture");
  enregistrer(c,f);  /*enregistrer*/
  fclose(f); /*fermeture*/
}

void load_1j(config *c){
  FILE *f=NULL;
  if((f = fopen("data/saves/save1j.txt", "r")) == NULL) /*ouverture*/
    printf("erreur ouverture");
  load(c,f); /*lecture*/
  fclose(f); /*fermeture*/
}

void enregistrer_2j(config *c, config *d){
  FILE *f=NULL;
  if((f = fopen("data/saves/save2j.txt", "w")) == NULL) /*ouverture*/
    printf("erreur ouverture");
  enregistrer(c,f);
  fprintf(f, "|\n"); /*ecriture 2 fois*/
  enregistrer(d,f);
  fclose(f); /*fermeture*/
}

void load_2j(config *c, config *d){
  FILE *f=NULL;
  if((f = fopen("data/saves/save2j.txt", "r")) == NULL) /*ouverture*/
    printf("erreur ouverture");
  load(c,f);
  fgetc(f);
  fgetc(f);  /*double lecture*/
  fgetc(f);
  load(d,f);
  fclose(f); /*fermeture*/
}

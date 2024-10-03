#include"affichage.h"
#include"tetris.h"

MLV_Color couleur(int c){ /*Grace au switch on convertit un int en MLV_Color*/
  switch(c){
  case 0:
    return MLV_COLOR_SNOW;
  case 1:
    return JAUNE; 
  case 2:
    return CIEL;
  case 3:
    return BLEU;
  case 4:
    return ORANGE;
  case 5:
    return VERT;
  case 6:
    return ROUGE;
  case 7:
    return VIOLET;
  case 8:
    return MLV_COLOR_NAVY;
  case 9:
    return MLV_COLOR_PINK;
  }
  return MLV_COLOR_BLACK;
}


void cube(int c, int x, int y, int b){ /*La fonction affiche un carré avec des reflets*/
  int xg[4];
  int xd[4];
  int yt[4];
  int yh[4];
  int yb[4];
  int xt[4];
  xg[0] = x+b;
  xg[1] = x;
  xg[2] = x;
  xg[3] = x+b;
  xd[0] = x+COTE-b;     /*mise en place des tableaux de coordonnées*/
  xd[1] = x+COTE;       /*pour tracer les reflets (polygone */
  xd[2] = x+COTE;
  xd[3] = x+COTE-b;
  yt[0] = y+b;
  yt[1] = y;
  yt[2] = y+COTE;
  yt[3] = y+COTE-b;
  yh[0] = y;
  yh[1] = y+b;
  yh[2] = y+b;
  yh[3] = y;
  yb[0] = y+COTE;
  yb[1] = y+COTE-b;
  yb[2] = y+COTE-b;
  yb[3] = y+COTE;
  xt[0] = x;
  xt[1] = x+b;
  xt[2] = x+COTE-b;
  xt[3] = x+COTE;
  MLV_draw_filled_rectangle(x, y, COTE, COTE, couleur(c)); /*Cube de base*/
  MLV_draw_filled_polygon(xt, yh, 4, MLV_rgba(255,255,255,50)); /*reflet haut*/
  MLV_draw_filled_polygon(xt, yb, 4, MLV_rgba(0,0,0,20)); /*reflet bas */
  MLV_draw_filled_polygon(xg,yt,4, MLV_rgba(255,255,255,25)); /*reflet gauche*/
  MLV_draw_filled_polygon(xd,yt,4, MLV_rgba(0,0,0,10)); /*reflet droit*/
}

void affiche_fond(int c, int b){/*rempli la fenetre de carrés */
  int i, j;
  for(i=0; i<22; i++)
    for(j=0; j<40; j++)
      cube(c, j*COTE, i*COTE, b);
}

void affiche_matrice(config *c, int x, int y, int b){
  int i, j;
  MLV_draw_filled_rectangle(x-5,y-5, 10*COTE+10, 20*COTE+10, MLV_COLOR_WHITE); 
  MLV_draw_filled_rectangle(x,y, 10*COTE, 20*COTE, MLV_COLOR_BLACK);
  for(i=0; i<20; i++)  /*affiche la matrice aux coordonnées*/
    for(j=0; j<10; j++)
      if(c->tab[i][j]!=0)
	cube(c->tab[i][j], x+COTE*(j), y+COTE*(i), b);
}

void affiche_score(config *c, int x, int y, int t){
  char s[20];
  MLV_Font* font;
  MLV_Font* font2;
  font = MLV_load_font("data/fonts/SCOREBOARD.ttf",40);
  font2 = MLV_load_font("data/fonts/SCOREBOARD.ttf",130);
  /*usage des fonts*/
  sprintf(s, "%d", c->score);
  MLV_draw_filled_rectangle(x-5, y-5, 2*t*COTE+10, t*COTE+10, MLV_COLOR_WHITE);
  MLV_draw_filled_rectangle(x, y, 2*t*COTE, t*COTE, MLV_COLOR_BLACK);
  /*boite d'affichage*/ 
  MLV_draw_text_with_font(x+(t-3)*COTE, y-(0.9*COTE), "@", font2, MLV_COLOR_WHITE);
  /*la font utiliser marque 'scoreboardé pour le charactère '@'*/
  MLV_draw_text_with_font(x+(t-1)*COTE, y+(t*COTE/7)*4, s, font, MLV_COLOR_WHITE);
  MLV_free_font(font);
  MLV_free_font(font2);
  /*fermeture*/
}

void affiche_suiv(config *c, int x, int y, int t, int b){
  int i, j;
  int p[5][2];
  MLV_Font *font;
  config n = initialiser();
  config m = initialiser();
  config o = initialiser();
  /*on initialise*/
  font = MLV_load_font("data/fonts/Banda.ttf", 25);
  piece(p, c->suiv[1]);/*modifie une matrice en fct du num de la piece suivante*/
  inserer(&n, p); /*insert dans une config la pièce*/
  piece(p, c->suiv[2]);
  inserer(&m, p);
  piece(p, c->suiv[3]);
  inserer(&o, p);
  MLV_draw_filled_rectangle(x-5, y-5, t*COTE+10, 3*t*COTE+10, MLV_COLOR_WHITE);
  MLV_draw_filled_rectangle(x, y, t*COTE, 3*t*COTE, MLV_COLOR_BLACK);
  for(i=0; i<20; i++)                  /*affiche les configs*/
    for(j=0; j<10; j++)
      if(n.tab[i][j]!=0)
	cube(c->suiv[1], x+COTE*(j-3), y+COTE*(i+1), b);
  for(i=0; i<20; i++)
    for(j=0; j<10; j++)
      if(m.tab[i][j]!=0)
	cube(c->suiv[2], x+COTE*(j-3), y+COTE*(i+6), b);
  for(i=0; i<20; i++)
    for(j=0; j<10; j++)
      if(o.tab[i][j]!=0)
	cube(c->suiv[3], x+COTE*(j-3), y+COTE*(i+11), b); 
  MLV_draw_text_with_font(x+4*COTE, y+4*COTE, "1", font, MLV_COLOR_WHITE); /*affiche ordre*/
  MLV_draw_text_with_font(x+4*COTE, y+9*COTE, "2", font, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(x+4*COTE, y+14*COTE, "3", font, MLV_COLOR_WHITE);
  MLV_free_font(font);
}

void affiche_1j(config *c, int f, int b){ /*on crée une fonction qui vas afficher le*/
  MLV_clear_window(MLV_COLOR_BLACK); /*nécessaire pour un joueur*/
  affiche_fond(f, b);
  affiche_matrice(c, 240, 40, b);
  affiche_score(c, 1120, 120, 3);
  affiche_suiv(c, 760, 80, 5, b);
  MLV_actualise_window();
}

void affiche_2j(config *c, config *d, int f, int b){ /*on crée une fonction qui vas afficher le*/
  MLV_clear_window(MLV_COLOR_BLACK);        /*nécessaire pour deux joueurs*/
  affiche_fond(f, b);
  affiche_matrice(c, 40, 40, b);
  affiche_score(c, 485, 715, 3);
  affiche_suiv(c, 485, 40, 5, b);
  affiche_matrice(d, 1165, 40, b);
  affiche_score(d, 880, 715, 3);
  affiche_suiv(d, 920, 40, 5, b);
  MLV_actualise_window();
}

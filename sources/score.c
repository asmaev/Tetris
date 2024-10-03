#include"score.h"

int ecrire_score(char p[10][25], int s[10]){
  int i;
  FILE * fic = NULL;
  fic = fopen("data/scores/score.txt", "w");
  if(fic == NULL){      /*ouverture du fichier*/
    msg_erreur("echec ouverture du score");
    return 0;
  }
  for(i=0; i<10; i++)
    fprintf(fic, "%d|%s\n", s[i], p[i]); /*enregistrement*/
  fclose(fic);
  return 1;
}

int lire_score(char p[10][25], int s[10]){
  int l, m, acc=0, i=0, j=0;
  char c;
  char x[100];
  FILE * fic = NULL;
  for(l=0; l<10; l++) /*init*/
    for(m=0; m<25; m++)
      p[l][m] = ' ';
  fic = fopen("data/scores/score.txt", "r");  /*ouverture*/
  if(fic == NULL){
    msg_erreur("echec ouverture du score");
    return 0;
  }
  while((c=fgetc(fic))!= EOF){ /*parcours*/
    if(c=='\n'){ /* test si fin du nom*/
	p[i][j] = '\0';
	i++;
	j=0;
	acc++;
	for(l=0; l<100; l++)
	  x[l] = ' ';
      }
    if(c=='|'){ /*test si fin du score*/
	j=0;
	acc++;
	s[i] = atoi(x);
      }
    if(c!='|' && c!='\n'){ /*enregistrement des caractères*/
	if(acc%2 == 0)
	  x[j] = c;
	if(acc%2 == 1)
	  p[i][j] = c;
	j++;
      }
    }
  fclose(fic); /*fermeture*/
    return s[0];
}
  
void afficher_score(char p[10][25], int s[10]){
  int i;
  char t[25];
  MLV_Font *font; /*init*/
  MLV_clear_window(MLV_COLOR_BLACK);
  font = MLV_load_font("data/fonts/Megatech.ttf",50);
  MLV_draw_text_with_font(320, 80, "MEILLEURS SCORES", font, MLV_COLOR_WHITE);
  MLV_free_font(font);
  sprintf(t, "1 - %d", s[0]);
  font = MLV_load_font("data/fonts/CHEQ_TT.TTF",25);
  MLV_draw_text_with_font(473, 208, "w", font, MLV_COLOR_YELLOW); /*affichage top 1*/
  
  MLV_free_font(font);
  font = MLV_load_font("data/fonts/Banda.ttf",25);
  MLV_draw_text_with_font(1065, 210, p[0], font, MLV_COLOR_YELLOW);
  MLV_draw_text_with_font(503, 210, t, font, MLV_COLOR_YELLOW);
  for(i=1; i<10; i++){    /*affichage 2 - 10*/
    sprintf(t, "%d - %d", i+1, s[i]);
    MLV_draw_text_with_font(1065, 210+i*60, p[i], font, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(503, 210+i*60, t, font, MLV_COLOR_WHITE);
    }
  MLV_free_font(font);
  MLV_actualise_window();
}

void ajouter_score(char p[10][25]){
  char c[10][25];
  char *k = &c[0][0];
  MLV_Font *font;
  font = MLV_load_font("data/fonts/Megatech.ttf", 30);
  MLV_draw_filled_rectangle(0, 0, 1600, 880, MLV_rgba(0,0,0,150)); /*affichage*/
  MLV_draw_filled_rectangle(402, 225, 841, 255, MLV_COLOR_WHITE);
  MLV_draw_filled_rectangle(407, 230, 831, 245, MLV_COLOR_BLACK);
  MLV_draw_text_with_font(500, 253, "FELICITATIONS !!!", font, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(500, 293, "VOUS ÊTES DANS", font, MLV_COLOR_WHITE);
   MLV_draw_text_with_font(500, 333, "LE CLASSEMENT !!!", font, MLV_COLOR_WHITE);
  MLV_free_font(font);
  font = MLV_load_font("data/fonts/Banda.ttf", 30);
  MLV_wait_input_box_with_font(422,385,732,40,MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, "   ENTREZ VOTRE PSEUDO : ", &k, font);
  strcpy(c[0],k); /*boite d'entrer pour le pseudo*/
  assigner(p,c,9,0);
  MLV_free_font(font);
}

void msg_erreur(char *s){ 
  MLV_draw_filled_rectangle(790, 390, 198, 109, MLV_COLOR_RED);
  MLV_draw_filled_rectangle(800, 400, 178, 89, MLV_COLOR_BLACK);
  MLV_draw_text(818, 445, s, MLV_COLOR_RED); /*affiche d'erreur*/
  MLV_actualise_window();
  MLV_wait_seconds(3);
}


void tri(char p[10][25], int s[10]){ /*fonction de tri, pseudo et score, en fonction du score décroissant*/
  int i, j, tmp2;
  char tmp[10][25];
  for(i=10; i>0; i--) /*reprise du tri bulle*/
    for(j=0; j<i-1; j++)
      if(s[j+1]>s[j]){
	assigner(tmp, p, j, j);
	tmp2 = s[j];
	assigner(p, p, j, j+1);
	s[j] = s[j+1];
	assigner(p, tmp, j+1, j);
	s[j+1] = tmp2;
      }
}

void assigner(char a[10][25], char c[10][25], int j, int k){ 
  int i;
  for(i=0; i<25; i++) /*fonction assignation de tableau*/
    a[j][i] = c[k][i];
}

void ajouter_scorej1(char p[10][25]){ /*même fonction mais pour 1joueur sur 2*/
  char c[10][25];
  char *k = &c[0][0];
  MLV_Font *font;
  font = MLV_load_font("data/fonts/Megatech.ttf", 30);
  MLV_draw_filled_rectangle(0, 0, 1950, 990, MLV_rgba(0,0,0,150));
  MLV_draw_filled_rectangle(402, 225, 841, 255, MLV_COLOR_WHITE);
  MLV_draw_filled_rectangle(407, 230, 831, 245, MLV_COLOR_BLACK);
  MLV_draw_text_with_font(450, 253, "FELICITATIONS JOUEUR 1", font, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(500, 293, "VOUS ÊTES DANS", font, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(500, 333, "LE CLASSEMENT !!!", font, MLV_COLOR_WHITE);
  MLV_free_font(font);
  font = MLV_load_font("data/fonts/Banda.ttf", 30);
  MLV_wait_input_box_with_font(422,385,732,40,MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, "   ENTREZ VOTRE PSEUDO : ", &k, font);
  strcpy(c[0],k);
  assigner(p,c,9,0);
  MLV_free_font(font);
}

void ajouter_scorej2(char p[10][25]){ /*même fonction pour 2 joueurs sur 2*/
  char c[10][25];
  char *k = &c[0][0];
  MLV_Font *font;
  font = MLV_load_font("data/fonts/Megatech.ttf", 30);
  MLV_draw_filled_rectangle(0, 0, 1950, 990, MLV_rgba(0,0,0,150));
  MLV_draw_filled_rectangle(402, 225, 841, 255, MLV_COLOR_WHITE);
  MLV_draw_filled_rectangle(407, 230, 831, 245, MLV_COLOR_BLACK);
  MLV_draw_text_with_font(450, 253, "FELICITATIONS JOUEUR 2", font, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(500, 293, "VOUS ÊTES DANS", font, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(500, 333, "LE CLASSEMENT !!!", font, MLV_COLOR_WHITE);
  MLV_free_font(font);
  font = MLV_load_font("data/fonts/Banda.ttf", 30);
  MLV_wait_input_box_with_font(422,385,732,40,MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, "   ENTREZ VOTRE PSEUDO : ", &k, font);
  strcpy(c[0],k);
  assigner(p,c,9,0);
  MLV_free_font(font);
}

#include"menu.h"
#include"jeux.h"
#include"score.h"
#include"option.h"
#include"tetris.h"
#include"saves.h"

int start(){
  /*initialisation*/
  char pseudo[10][25];
  int score[10];
  int x, y, z, f;
  MLV_Font *font;
  MLV_Image *image;
  MLV_Music *musik;
  MLV_Sound* select = MLV_load_sound("data/sounds/select.ogg");
  int ret[2];
  ret[0]=8;
  ret[1]=8;
  image = MLV_load_image("data/textures/fond.png");
  MLV_resize_image(image ,1600, 880);
  musik = MLV_load_music("data/sounds/base.ogg");
  /*début du menu*/
  MLV_play_music(musik, 0.5, -1);
  do{
    
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_image(image, 0, 0);
    font = MLV_load_font("data/fonts/Megatech.ttf",100);
    MLV_draw_text_with_font(480, 50, "T", font, MLV_COLOR_RED);  /*affichage logo*/
    MLV_draw_text_with_font(580, 50, "E", font, MLV_COLOR_ORANGE);
    MLV_draw_text_with_font(680, 50, "T", font, MLV_COLOR_YELLOW);
    MLV_draw_text_with_font(780, 50, "R", font, MLV_COLOR_GREEN);
    MLV_draw_text_with_font(880, 50, "I", font, MLV_COLOR_CYAN);
    MLV_draw_text_with_font(980, 50, "S", font, MLV_COLOR_PURPLE);
    MLV_free_font(font);
    
    bouton(585, 250, 400, 100, "JOUER");  /*affichage des boutons*/
    bouton(585, 400, 400, 100, "OPTION");
    bouton(585, 550, 400, 100, " SCORE");
    bouton(585, 700, 400, 100, "   EXIT");
    
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y); /*test des coord du click*/
    if(x<985 && x>585 && y>250 && y<350){ /*mode jouer*/
      MLV_play_sound(select, 1.0);
      select_mod(ret);
    }
    if(x<985 && x>585 && y>400 && y<500){ /*mode option*/
      MLV_play_sound(select, 1.0);
      option(ret);
      MLV_play_sound(select, 1.0);
    }
    if(x<985 && x>585 && y>550 && y<650){ /*mode score*/
      MLV_play_sound(select, 1.0);
      lire_score(pseudo, score);
      afficher_score(pseudo, score);
      MLV_wait_mouse(&z, &f);
      MLV_play_sound(select, 1.0);
    }
  }
  while(x>985 || x<585 || y<700 || y>800); /*si on clique sur exit, on sort et le programme se ferme*/
  MLV_play_sound(select, 1.0);
  MLV_wait_milliseconds(600);
  MLV_stop_music();
  MLV_free_music(musik);  /*fin de musique*/
  return 1;
}

void bouton(int x, int y, int l, int h, char *s){ /*création d'un bouton assez simple*/
  MLV_Font *font;
  font = MLV_load_font("data/fonts/Banda.ttf",25);
  MLV_draw_filled_rectangle(x+10, y+10, l, h, MLV_COLOR_BLACK);
  MLV_draw_filled_rectangle(x, y, l, h, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(x+l/2-40, y+h/2-10, s, font, MLV_COLOR_BLACK);
  MLV_free_font(font);
}

void select_mod(int ret[2]){
  /*initialisation*/
  config c, d;
  int x, y;
  MLV_Image *image;
  MLV_Font *font;
  MLV_Sound* select = MLV_load_sound("data/sounds/select.ogg");
  image = MLV_load_image("data/textures/fond.png");
  MLV_resize_image(image ,1600, 880);
  MLV_clear_window(MLV_COLOR_BLACK);
  /*affichage*/
  MLV_draw_image(image, 0, 0);
  font = MLV_load_font("data/fonts/Megatech.ttf",70);
  MLV_draw_text_with_font(575, 50, "JOUER", font, MLV_COLOR_SNOW);
  MLV_free_font(font);
  bouton(585, 400, 400, 100, "1 JOUEUR");
  bouton(585, 550, 400, 100, "2 JOUEURS");
  /*affichage menu jouer*/
  MLV_actualise_window();
  MLV_wait_mouse(&x, &y); /*test des coord*/
  if(x<985 && x>585 && y>400 && y<500){ /*selection 1 joueur*/
    /*init*/
    MLV_play_sound(select, 1.0);
    c = initialiser();
    /*affichage*/
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_image(image, 0, 0);
    font = MLV_load_font("data/fonts/Megatech.ttf",70);
    MLV_draw_text_with_font(460, 50, "1 JOUEUR", font, MLV_COLOR_SNOW);
    MLV_free_font(font);
    bouton(585, 400, 400, 100, "   NEW");
    bouton(585, 550, 400, 100, "   LOAD");
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y); /*test new ou load*/
    if(x<985 && x>585 && y>400 && y<500){ /*new*/
      MLV_play_sound(select, 1.0);
      piece(c.coord, c.suiv[0]); /*init*/
      jeux1j(c, ret); /*play*/
    }
    if(x<985 && x>585 && y>550 && y<650){ /*load*/
      MLV_play_sound(select, 1.0);
      load_1j(&c);
      actu_suiv(&c);  /*init*/
      jeux1j(c, ret); /*play*/
    }
  }
  else if(x<985 && x>585 && y>550 && y<650){ /*selection 2j*/
    MLV_play_sound(select, 1.0);
    c = initialiser(); /*init*/
    d = initialiser();
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_image(image, 0, 0);
    font = MLV_load_font("data/fonts/Megatech.ttf",70);
    MLV_draw_text_with_font(450, 50, "2 JOUEURS", font, MLV_COLOR_SNOW);
    MLV_free_font(font);
    bouton(585, 400, 400, 100, "  NEW");
    bouton(585, 550, 400, 100, "  LOAD");
    /*affichage*/
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y); /*test*/
    if(x<985 && x>585 && y>400 && y<500){ /*new*/
      MLV_play_sound(select, 1.0);
      piece(d.coord, d.suiv[0]);
      piece(c.coord, c.suiv[0]);
      jeux2j(c, d, ret);
    }
    if(x<985 && x>585 && y>550 && y<650){ /*load*/
      MLV_play_sound(select, 1.0);
      load_2j(&c, &d);
      actu_suiv(&c);
      actu_suiv(&d);
      jeux2j(c, d, ret);
    }
  }
  /*aucun des choix ou fin, on retourn au menu*/
  MLV_play_sound(select, 1.0);
}

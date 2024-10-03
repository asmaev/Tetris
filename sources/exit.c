#include"exit.h"
#include"menu.h"
#include"saves.h"
#include"tetris.h"

int exitmenu(config *c){
  /*initialiser*/
  int x, y;
  MLV_Font *font;
  MLV_Sound* select = MLV_load_sound("data/sounds/select.ogg");
  MLV_draw_filled_rectangle(0, 0, 1735, 880, MLV_rgba(0,0,0,150)); /*assombris le fond*/
  MLV_play_sound(select, 1.0);
  do{ /*boucle d'interaction de bouton*/
    font = MLV_load_font("data/fonts/Megatech.ttf", 30);
    MLV_draw_filled_rectangle(429, 215, 877, 450, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(434, 220, 867, 440, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(460, 269, "QUE VOULEZ-VOUS FAIRE ?", font, MLV_COLOR_WHITE);
    MLV_free_font(font);
    
    font = MLV_load_font("data/fonts/Banda.ttf", 25);
    MLV_draw_filled_rectangle(568, 337, 618, 71, MLV_COLOR_GREY);
    MLV_draw_filled_rectangle(558, 327, 618, 71, MLV_COLOR_SNOW);
    MLV_draw_text_with_font(816, 355, "CONTINUER", font, MLV_COLOR_BLACK);

    MLV_draw_filled_rectangle(568, 444, 618, 71, MLV_COLOR_GREY);
    MLV_draw_filled_rectangle(558, 434, 618, 71, MLV_COLOR_SNOW);
    MLV_draw_text_with_font(800, 455, "SAUVEGARDER", font, MLV_COLOR_BLACK);

    MLV_draw_filled_rectangle(577, 550, 618, 71, MLV_COLOR_GREY);
    MLV_draw_filled_rectangle(567, 540, 618, 71, MLV_COLOR_SNOW);
    MLV_draw_text_with_font(846, 568, "EXIT", font, MLV_COLOR_BLACK);
    MLV_free_font(font);
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y);
    if(x<1176 && x>558 && y<398 && y>327) /*bouton continuer*/
      return 0;      
    if(x<1176 && x>558 && y<505 && y>433){ /*bouton save*/
      enregistrer_1j(c);
      MLV_play_sound(select, 1.0);
      MLV_draw_filled_rectangle(753, 429, 268, 71, MLV_COLOR_BLACK);
      MLV_draw_filled_rectangle(758, 424, 258, 61, MLV_COLOR_RED);
      font = MLV_load_font("data/fonts/Banda.ttf", 25);
      MLV_draw_text_with_font(765, 445, "SAUVEGARDE EFFECTUÉ", font, MLV_COLOR_BLACK); /*message save*/
      MLV_free_font(font);
      MLV_actualise_window();
      MLV_wait_seconds(1);
    }

    if(x<1176 && x>558 && y<611 && y>540) /*bouton exit*/
      return 1;
  }
  while(1);
}



int exitmenu2j(config *c, config *d){ /*meme principe mais appel d'une sauvegarde pour 2j*/
  int x, y;
  MLV_Font *font;
  MLV_Sound* select = MLV_load_sound("data/sounds/select.ogg");
  MLV_draw_filled_rectangle(0, 0, 1735, 880, MLV_rgba(0,0,0,150));
  MLV_play_sound(select, 1.0);
  do{
    font = MLV_load_font("data/fonts/Megatech.ttf", 30);
    MLV_draw_filled_rectangle(429, 215, 877, 450, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(434, 220, 867, 440, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(460, 269, "QUE VOULEZ-VOUS FAIRE ?", font, MLV_COLOR_WHITE);
    MLV_free_font(font);
    
    font = MLV_load_font("data/fonts/Banda.ttf", 25);
    MLV_draw_filled_rectangle(568, 337, 618, 71, MLV_COLOR_GREY);
    MLV_draw_filled_rectangle(558, 327, 618, 71, MLV_COLOR_SNOW);
    MLV_draw_text_with_font(816, 355, "CONTINUER", font, MLV_COLOR_BLACK);


    MLV_draw_filled_rectangle(568, 444, 618, 71, MLV_COLOR_GREY);
    MLV_draw_filled_rectangle(558, 434, 618, 71, MLV_COLOR_SNOW);
    MLV_draw_text_with_font(800, 455, "SAUVEGARDER", font, MLV_COLOR_BLACK);

    MLV_draw_filled_rectangle(577, 550, 618, 71, MLV_COLOR_GREY);
    MLV_draw_filled_rectangle(567, 540, 618, 71, MLV_COLOR_SNOW);
    MLV_draw_text_with_font(846, 568, "EXIT", font, MLV_COLOR_BLACK);
    MLV_free_font(font);
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y);
    if(x<1176 && x>558 && y<398 && y>327)
      return 0;      
    if(x<1176 && x>558 && y<505 && y>433){
      enregistrer_2j(c, d);
      MLV_play_sound(select, 1.0);
      MLV_draw_filled_rectangle(753, 429, 268, 71, MLV_COLOR_BLACK);
      MLV_draw_filled_rectangle(758, 424, 258, 61, MLV_COLOR_RED);
      font = MLV_load_font("data/fonts/Banda.ttf", 25);
      MLV_draw_text_with_font(765, 445, "SAUVEGARDE EFFECTUÉ", font, MLV_COLOR_BLACK);
      MLV_free_font(font);
      MLV_actualise_window();
      MLV_wait_seconds(1);
    }

    if(x<1176 && x>558 && y<611 && y>540)
      return 1;
  }
  while(1);
}

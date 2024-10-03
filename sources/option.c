#include"option.h"

int option(int ret[2]){
  /* initialisation*/
  int x, y;
  MLV_Font *font;
  MLV_Image *image;
  MLV_Music *musik;
  MLV_Sound* select = MLV_load_sound("data/sounds/select.ogg");
  image = MLV_load_image("data/textures/fond.png");
  MLV_resize_image(image ,1600, 880);
  /*affichage*/
  MLV_clear_window(MLV_COLOR_BLACK);
  MLV_draw_image(image, 0, 0);

  font = MLV_load_font("data/fonts/Megatech.ttf",30);
  MLV_draw_text_with_font(655, 100, "MUSIQUE : ", font, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(210, 100, "THÈME : ", font, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(1150, 100, "BRIQUES : ", font, MLV_COLOR_WHITE);
  MLV_free_font(font);
  
  bouton(735, 250, 100, 100, "  Base");
  bouton(735, 400, 100, 100, "  Piano");    /*musique*/
  bouton(735, 550, 100, 100, "  8-bits");
  bouton(735, 700, 100, 100, "no Song");

  bouton(235, 250, 100, 100, "   Clair");
  bouton(235, 400, 100, 100, "Sombre");   /*thème*/
  bouton(235, 550, 100, 100, " Simple");
  bouton(235, 700, 100, 100, "   Rose");

  bouton(1235, 250, 100, 100, "  Lisse");
  bouton(1235, 400, 100, 100, "   Fine");  /*briques*/
  bouton(1235, 550, 100, 100, "  Large");
  bouton(1235, 700, 100, 100, "  Pleine");

  MLV_actualise_window();
  /*selection*/
  do{
    /*MUSIQUE*/
    MLV_wait_mouse(&x, &y);
    if(x<835 && x>735 && y<350 && y> 250){  /*musique tetris*/
      MLV_stop_music();
      musik = MLV_load_music("data/sounds/base.ogg"); 
      MLV_play_sound(select, 1.0);
      MLV_play_music(musik, 0.5, -1);
    }
    else if(x<835 && x>735 && y<800 && y> 700){ /*sans musique*/
      MLV_stop_music();
      MLV_play_sound(select, 1.0);
    }
    else if(x<835 && x>735 && y<650 && y> 550){ /*8bit*/
      MLV_stop_music();
      musik = MLV_load_music("data/sounds/8bits.ogg");
      MLV_play_sound(select, 1.0);
      MLV_play_music(musik, 0.5, -1);
    }
    else if(x<900 && x>655 && y<130 && y> 100){ /*musique secrete*/
      MLV_stop_music();
      musik = MLV_load_music("data/sounds/easteregg.ogg");
      MLV_play_sound(select, 1.0);
      MLV_play_music(musik, 0.5, -1);
    }
    else if(x<835 && x>735 && y<500 && y> 400){ /*piano*/
      MLV_stop_music();
      musik = MLV_load_music("data/sounds/piano.ogg");
      MLV_play_sound(select, 1.0);
      MLV_play_music(musik, 0.5, -1);
    }
    /*COULEUR*/
    else if(x<335 && x>235 && y<350 && y> 250){ /*couleur blanche*/
      ret[0] = 0;
      MLV_play_sound(select, 1.0);
    }
    else if(x<335 && x>235 && y<800 && y> 700){ /*couleur rose*/
      ret[0] = 9;
      MLV_play_sound(select, 1.0);
    }
    else if(x<335 && x>235 && y<650 && y> 550){ /*couleur grise*/
      ret[0] = 8;
      MLV_play_sound(select, 1.0);
    }
    else if(x<335 && x>235 && y<500 && y> 400){ /*couleur noir*/
      ret[0] = 10;
      MLV_play_sound(select, 1.0);
    }
    /*BRIQUES*/
    else if(x<1335 && x>1235 && y<350 && y> 250){  /*brique lisse*/
      ret[1] = 2;
      MLV_play_sound(select, 1.0);
    }
    else if(x<1335 && x>1235 && y<800 && y> 700){ /*brique pleine*/
      ret[1] = 20;
      MLV_play_sound(select, 1.0);
    }
    else if(x<1335 && x>1235 && y<650 && y> 550){  /*brique moyenne*/
      ret[1] = 15;
      MLV_play_sound(select, 1.0);
    }
    else if(x<1335 && x>1235 && y<500 && y> 400){  /*brique fine*/
      ret[1] = 8;
      MLV_play_sound(select, 1.0);
    }
    /*EXIT*/
    else
      return 1;
  }
  while(1);
}


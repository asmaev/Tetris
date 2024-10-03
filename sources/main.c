#include"tetris.h"
#include"affichage.h"
#include"jeux.h"
#include"menu.h"

int main(){
  MLV_create_window("TETRIS", "tetris", 1600, 880);
  MLV_init_audio();
  srand(time(NULL)); /*initialisation de base*/
  start(); /*le jeu*/
  MLV_free_audio(); /*fermeture*/
  MLV_free_window();
  exit(EXIT_SUCCESS);
}

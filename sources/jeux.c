#include"tetris.h"
#include"affichage.h"
#include"exit.h"
#include"score.h"

int jeux1j(config c,int ret[2]){
  /*initialisation*/
  char pseudo[10][25];
  int score[10];
  int i, b, x, y, j, a = 0;
  MLV_Event event = MLV_NONE;
  MLV_Button_state state;
  MLV_Keyboard_button sym;
  MLV_Sound* desc = MLV_load_sound("data/sounds/laser.ogg");
  MLV_Sound* supr = MLV_load_sound("data/sounds/ligne.ogg");
  MLV_Sound* select = MLV_load_sound("data/sounds/select.ogg");
  MLV_change_frame_rate(24);
  /*début*/
  affiche_1j(&c, ret[0], ret[1]);
  while(a == 0){
    MLV_delay_according_to_frame_rate();
    for(i=0; i<c.speed; i++){ /*boucle de commande, en attente d'une touche*/
      event = MLV_get_event(&sym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
      if(event == MLV_KEY && sym == MLV_KEYBOARD_DOWN && state == MLV_PRESSED){ /*descendre*/
	while(descendre(&c, c.coord)==1) /*boucle pour descendre tout en bas*/
	  ;
	MLV_play_sound(desc, 1.0);
	break;
      }
      if(event == MLV_KEY && sym == MLV_KEYBOARD_LEFT && state == MLV_PRESSED) /*gauche*/
	decaler_g(&c, c.coord);
      if(event == MLV_KEY && sym == MLV_KEYBOARD_RIGHT && state == MLV_PRESSED) /*droite*/
	decaler_d(&c, c.coord);
      if(event == MLV_KEY && sym == MLV_KEYBOARD_UP && state == MLV_PRESSED) /*rotate*/
	rotation(&c, c.coord);
      if(event == MLV_KEY && sym == MLV_KEYBOARD_ESCAPE && state == MLV_PRESSED){ /*exit*/
	a = exitmenu(&c);
	MLV_play_sound(select, 1.0);
      }
      inserer(&c, c.coord);
      MLV_clear_window(MLV_COLOR_BLACK);   /*affichage*/
      affiche_1j(&c, ret[0], ret[1]);
    }
    if(descendre(&c, c.coord)==0){ /*on descend après x execution, si on peux pas on rentre dans le if*/
      for(j=0, b=0; j<20; j++) /*test si on a rempli des lignes*/
	if(est_pleine(&c, j)){
	  b++;
	  decalage(&c, j); /*on suprimes les lignes pleine*/
	  j=0;
	  MLV_play_sound(supr, 1.0);
	}
      if(b==1)
	c.score += 100;
      if(b>1 && b<4)  /*on compte le nombre de lignes suprimé*/
	c.score += b*200;
      if(b>=4)
	c.score += b*300;
      actu_suiv(&c);
      piece(c.coord, c.suiv[0]); /*on passe à la piece suivante*/
      a = estfini(&c, c.coord); /*en verifiant si le jeu peut continuer*/
      inserer(&c, c.coord);
      c.score += 5;
      if(c.score < 500)  /*ajustement de la speed en fonction du score*/
	c.speed = 60;
      else if(c.score < 1000)
	c.speed = 55;
      else if(c.score < 1500)
	c.speed = 45;
      else if(c.score < 3000) 
	c.speed = 35;
      else if(c.score < 5000) 
	c.speed = 30;
      else if(c.score < 7000)
	c.speed = 25;
      else if(c.score < 10000)
	c.speed = 20;
      else if(c.score < 15000)
	c.speed = 15;
      else
	c.speed = 10;
    }
  }
  lire_score(pseudo, score); 
  if(c.score>score[9]){ /*on test si le score peut-être classé*/
    score[9] = c.score; 
    ajouter_score(pseudo); /*on l'insert*/
    tri(pseudo, score);  /*et on tri*/
    ecrire_score(pseudo, score);
  }
  MLV_play_sound(select, 1.0);
  afficher_score(pseudo, score); /*on affiche le resultat*/
  MLV_wait_mouse(&x, &y);
  return 1;
}


  int jeux2j(config c, config d, int ret[2]){/* même principe à quelques détails près*/
  char pseudo[10][25];
  int score[10];
  int i, b, x, y, j, j2, b2, a = 0, f = 0, h = 0, s;
  MLV_Event event = MLV_NONE;
  MLV_Button_state state;
  MLV_Keyboard_button sym;
  MLV_Sound* select = MLV_load_sound("data/sounds/select.ogg");
  MLV_Sound* supr = MLV_load_sound("data/sounds/ligne.ogg");
  MLV_Sound* desc = MLV_load_sound("data/sounds/laser.ogg");
  srand(time(NULL));
  MLV_change_frame_rate(24);
  affiche_2j(&c, &d, ret[0], ret[1]);
  while(a == 0){
    MLV_delay_according_to_frame_rate();
    if(c.speed<d.speed) /*on vas prendre la speed la plus avancé*/
      s = d.speed;
    else
      s = c.speed;
    for(i=0; i<s; i++){
      event = MLV_get_event(&sym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
      
      if(h != 1 && event == MLV_KEY && sym == MLV_KEYBOARD_DOWN && state == MLV_PRESSED){ /*on inclu les touches du joueurs et si sa parti est toujours en jeux*/
	while(h == 0 && descendre(&d, d.coord)==1)
	  ;
	MLV_play_sound(desc, 1.0);
	break;
      }
      else if(h != 1 && event == MLV_KEY && sym == MLV_KEYBOARD_LEFT && state == MLV_PRESSED)
	decaler_g(&d, d.coord);
      else if(h != 1 && event == MLV_KEY && sym == MLV_KEYBOARD_RIGHT && state == MLV_PRESSED)
	decaler_d(&d, d.coord);
      else if(h != 1 && event == MLV_KEY && sym == MLV_KEYBOARD_UP && state == MLV_PRESSED)
	rotation(&d, d.coord);
      
      else if(f != 1 && event == MLV_KEY && sym == MLV_KEYBOARD_s && state == MLV_PRESSED){
	while(f == 0 && descendre(&c, c.coord)==1)
	  ;
	MLV_play_sound(desc, 1.0);
	break;
      }
      else if(f != 1 && event == MLV_KEY && sym == MLV_KEYBOARD_q && state == MLV_PRESSED)
	decaler_g(&c, c.coord);
      else if(f != 1 && event == MLV_KEY && sym == MLV_KEYBOARD_d && state == MLV_PRESSED)
	decaler_d(&c, c.coord);
      else if(f != 1 && event == MLV_KEY && sym == MLV_KEYBOARD_z && state == MLV_PRESSED)
	rotation(&c, c.coord);
    
      if(event == MLV_KEY && sym == MLV_KEYBOARD_ESCAPE && state == MLV_PRESSED){
	a = exitmenu2j(&c, &d);
	MLV_play_sound(select, 1.0);
    }
      inserer(&c, c.coord); /*on double les insertion etc*/
      inserer(&d, d.coord);
      MLV_clear_window(MLV_COLOR_BLACK);
      affiche_2j(&c, &d, ret[0], ret[1]);
    }
    if(f != 1 && descendre(&c, c.coord)==0){ /*si le ta partie est tjr en cours en plus du classique*/
      for(j=0, b=0; j<20; j++)
	if(est_pleine(&c, j)){
	  b++;
	  decalage(&c, j);
	  j=0;
	  MLV_play_sound(supr, 1.0);
	}
      if(b==1)
	c.score += 100;
      if(b>1 && b<4)
	c.score += b*200;
      if(b>=4)
	c.score += b*300;
      actu_suiv(&c);
      piece(c.coord, c.suiv[0]);
      if(estfini(&c, c.coord))
	f = 1;
      if(f==0)
	inserer(&c, c.coord);
      c.score += 5;
      if(c.score < 500)
	c.speed = 60;
      else if(c.score < 1000)
	c.speed = 55;
      else if(c.score < 1500)
	c.speed = 45;
      else if(c.score < 3000) 
	c.speed = 35;
      else if(c.score < 5000) 
	c.speed = 30;
      else if(c.score < 7000)
	c.speed = 25;
      else if(c.score < 10000)
	c.speed = 20;
      else if(c.score < 15000)
	c.speed = 15;
      else
	c.speed = 10;
    }
    if(h != 1 && descendre(&d, d.coord) == 0){ /*test si la 2nd parti est tjr en cours et pareil*/
      for(j2=0, b2=0; j2<20; j2++)
	if(est_pleine(&d, j2)){
	  b2++;
	  decalage(&d, j2);
	  j2=0;
	  MLV_play_sound(supr, 1.0);
	}
      if(b2==1)
	d.score += 100;
      if(b2>1 && b2<4)
	d.score += b2*200;
      if(b2>=4)
	d.score += b2*300;
      actu_suiv(&d);
      piece(d.coord, d.suiv[0]);
      if(estfini(&d, d.coord))
	h = 1;
      if(h==0)
	inserer(&d, d.coord);
      d.score += 5;
      if(d.score < 500)
	d.speed = 60;
      else if(d.score < 1000)
	d.speed = 55;
      else if(d.score < 1500)
	d.speed = 45;
      else if(d.score < 3000) 
	d.speed = 35;
      else if(d.score < 5000)
	d.speed = 30;
      else if(d.score < 7000)
	d.speed = 25;
      else if(d.score < 10000)
	d.speed = 20;
      else if(d.score < 15000)
	d.speed = 15;
      else
	d.speed = 10;
    }
    if(h == 1 && f == 1) /*si les 2parties sont fini, fin du jeux */
      a = 1;
  }
  lire_score(pseudo, score);
  if(c.score>score[9]){
    score[9] = c.score;
    ajouter_scorej1(pseudo);
    tri(pseudo, score);
    ecrire_score(pseudo, score);
  }                       /* on test pour les 2 joueurs*/
  if(d.score>score[9]){
    score[9] = d.score;
    ajouter_scorej2(pseudo);
    tri(pseudo, score);
    ecrire_score(pseudo, score);
  }
  MLV_play_sound(select, 1.0);
  afficher_score(pseudo, score);
  MLV_wait_mouse(&x, &y);
  return 1;
}

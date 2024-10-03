#include"tetris.h"

void supprimer_ligne(config *c, int i){
  int j;
  for(j=0; j<L; j++)
    c->tab[i][j] = 0;
}

config initialiser(){
  int i, j;
  config c;
  c.score = 0;
  c.speed = 70;
  for(i=0; i<4; i++)
    c.suiv[i] = (rand()%7)+1; /*tirage de 3 nb alea entre 1 et 7*/
  for(i=0; i<H; i++) /*initialise la matrice*/
    supprimer_ligne(&c, i);
  for(i=0; i<5; i++)
    for(j=0; j<2; j++)
      c.coord[i][j] = 0;
  return c;
}

int actu_suiv(config *c){
  int res, i;
  res = c->suiv[0];
  for(i=0; i<3; i++)
    c->suiv[i] = c->suiv[i+1];/*deplacement des valeurs*/
  c->suiv[3] = (rand()%7)+1;
  return res;/*renvoie le nb efface*/
}

int est_pleine(config *c, int i){/*test si la ligne est pleine*/
  int j;
  for(j =0; j<L; j++)
    if(c->tab[i][j] == 0)
      return 0;
  return 1;
}

void decalage(config *c, int k){/*decalage de ttes le lignes en dessus de k */
  int i,j;
  for(i=k; i>0; i--)
    for(j=0; j<L; j++)
      c->tab[i][j] = c->tab[i-1][j];
  supprimer_ligne(c, 0);/*suppression de la 1ere ligne*/
}

int piece(int p[5][2], int t){
  p[0][0] = 0;
  p[0][1] = 0;
  switch(t){/*matrice de coordonnees [tq x[num du blocs][x ou y]*/
  case 1 :
    p[1][0] = 0;
    p[1][1] = 4;
    p[2][0] = 0;
    p[2][1] = 5;
    p[3][0] = 1;
    p[3][1] = 4;
    p[4][0] = 1;
    p[4][1] = 5;
    return 1;
  case 2 :
    p[1][0] = 0;
    p[1][1] = 3;
    p[2][0] = 0;
    p[2][1] = 4;
    p[3][0] = 0;
    p[3][1] = 5;
    p[4][0] = 0;
    p[4][1] = 6;
    return 1;
  case 3 :
    p[1][0] = 0;
    p[1][1] = 4;
    p[2][0] = 1;
    p[2][1] = 4;
    p[3][0] = 2;
    p[3][1] = 4;
    p[4][0] = 0;
    p[4][1] = 5;
    return 1;
  case 4 :
    p[1][0] = 0;
    p[1][1] = 5;
    p[2][0] = 1;
    p[2][1] = 5;
    p[3][0] = 2;
    p[3][1] = 5;
    p[4][0] = 0;
    p[4][1] = 4;
    return 1;
  case 5 :
    p[1][0] = 0;
    p[1][1] = 4;
    p[2][0] = 1;
    p[2][1] = 4;
    p[3][0] = 1;
    p[3][1] = 5;
    p[4][0] = 2;
    p[4][1] = 5;
    return 1;
  case 6 :
    p[1][0] = 0;
    p[1][1] = 5;
    p[2][0] = 1;
    p[2][1] = 5;
    p[3][0] = 1;
    p[3][1] = 4;
    p[4][0] = 2;
    p[4][1] = 4;
    return 1;
  case 7 :
    p[1][0] = 0;
    p[1][1] = 4;
    p[2][0] = 1;
    p[2][1] = 4;
    p[3][0] = 2;
    p[3][1] = 4;
    p[4][0] = 1;
    p[4][1] = 5;
    return 1;
  }
  return 0;
}

int rotate(config *c, int p[5][2]){ /*rotation manuel*/
  int k = p[2][0];  
  int j = p[2][1];
  switch(c->suiv[0]){
  case 1:
    break;
  case 2:
    if(p[0][0]==0){
      p[1][0] = k-1;
      p[1][1] = j;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k+1;
      p[3][1] = j;
      p[4][0] = k+2;
      p[4][1] = j;
      p[0][0]++;
    }
    else{
      p[1][0] = k;
      p[1][1] = j-1;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k;
      p[3][1] = j+1;
      p[4][0] = k;
      p[4][1] = j+2;
      p[0][0]--;
    }
    break;
  case 3:
    if(p[0][0]==0){
      p[1][0] = k;
      p[1][1] = j-1;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k;
      p[3][1] = j+1;
      p[4][0] = k+1;
      p[4][1] = j+1;
      p[0][0]++;
    }
    else if(p[0][0]==1){
      p[1][0] = k+1;
      p[1][1] = j;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k-1;
      p[3][1] = j;
      p[4][0] = k+1;
      p[4][1] = j-1;
      p[0][0]++;
    }
    else if(p[0][0]==2){
      p[1][0] = k;
      p[1][1] = j-1;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k;
      p[3][1] = j+1;
      p[4][0] = k-1;
      p[4][1] = j-1;
      p[0][0]++;
    }
    else{
      p[1][0] = k-1;
      p[1][1] = j;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k+1;
      p[3][1] = j;
      p[4][0] = k-1;
      p[4][1] = j+1;
      p[0][0] = 0;
    }   
    break;
  case 4:
    if(p[0][0]==0){
      p[1][0] = k;
      p[1][1] = j-1;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k;
      p[3][1] = j+1;
      p[4][0] = k-1;
      p[4][1] = j+1;
      p[0][0]++;
    }
    else if(p[0][0]==1){
      p[1][0] = k+1;
      p[1][1] = j;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k-1;
      p[3][1] = j;
      p[4][0] = k+1;
      p[4][1] = j+1;
      p[0][0]++;
    }
    else if(p[0][0]==2){
      p[1][0] = k;
      p[1][1] = j-1;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k;
      p[3][1] = j+1;
      p[4][0] = k+1;
      p[4][1] = j-1;
      p[0][0]++;
    }
    else{
      p[1][0] = k-1;
      p[1][1] = j;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k+1;
      p[3][1] = j;
      p[4][0] = k-1;
      p[4][1] = j-1;
      p[0][0] = 0;
    }   
    break;
  case 5:
    if(p[0][0]==0){
      p[1][0] = k;
      p[1][1] = j-1;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k-1;
      p[3][1] = j;
      p[4][0] = k-1;
      p[4][1] = j+1;
      p[0][0]++;
    }
    else{
      p[1][0] = k-1;
      p[1][1] = j;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k;
      p[3][1] = j+1;
      p[4][0] = k+1;
      p[4][1] = j+1;
      p[0][0]--;
    }
    break;
  case 6:
    if(p[0][0]==0){
      p[1][0] = k;
      p[1][1] = j+1;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k-1;
      p[3][1] = j;
      p[4][0] = k-1;
      p[4][1] = j-1;
      p[0][0]++;
    }
    else{
      p[1][0] = k-1;
      p[1][1] = j;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k;
      p[3][1] = j-1;
      p[4][0] = k+1;
      p[4][1] = j-1;
      p[0][0]--;
    }
    break;
  case 7:
    if(p[0][0]==2){
      p[1][0] = k;
      p[1][1] = j-1;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k;
      p[3][1] = j+1;
      p[4][0] = k-1;
      p[4][1] = j;
      p[0][0]--;
    }
    else if(p[0][0]==3){
      p[1][0] = k+1;
      p[1][1] = j;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k-1;
      p[3][1] = j;
      p[4][0] = k;
      p[4][1] = j-1;
      p[0][0]--;
    }
    else if(p[0][0]==0){
      p[1][0] = k;
      p[1][1] = j+1;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k;
      p[3][1] = j-1;
      p[4][0] = k+1;
      p[4][1] = j;
      p[0][0] = 3;
    }
    else{
      p[1][0] = k-1;
      p[1][1] = j;
      p[2][0] = k;
      p[2][1] = j;
      p[3][0] = k+1;
      p[3][1] = j;
      p[4][0] = k;
      p[4][1] = j+1;
      p[0][0]--;
    }
    break;
  }
  return 1;
}

int rotation(config *c, int p[5][2]){
  int i;
  for(i=1; i<5; i++)
    c->tab[p[i][0]][p[i][1]] = 0;/*mise a 0 de la piece*/
  rotate(c,p);
  for(i=1; i<5; i++)
    if(c->tab[p[i][0]][p[i][1]] != 0 || p[i][0] > 19 || p[i][1] > 9 || p[i][1] < 0 || p[i][0] < 0){
      rotate(c, p);
      rotate(c, p);
      rotate(c, p);
      for(i=1; i<5; i++)
	c->tab[p[i][0]][p[i][1]] = c->suiv[0];
      return 0;
    }
  for(i=1; i<5; i++)
    c->tab[p[i][0]][p[i][1]] = c->suiv[0];
  return 1;
}



int estfini(config *c, int p[5][2]){
  int i;
  for(i=1;i<5;i++)
    if(c->tab[p[i][0]][p[i][1]] != 0)/*test si l'emplacement est vide*/
      return 1;
  return 0;
}/*apres generation de la piece*/


void inserer(config *c, int p[5][2]){
  int i;
  for(i=1;i<5;i++)
      c->tab[p[i][0]][p[i][1]] = c->suiv[0];
}/*suiv[0] la piece qui est actuellement en train d'etre joue;
p[i][0] = le x du bloc numéro i de la piece suiv[0] , et p[i][1] le y*/

int descendre(config *c, int p[5][2]){
  int i;
  for(i=1; i<5; i++)
    c->tab[p[i][0]][p[i][1]] = 0;/*mise a 0 de la piece*/
  for(i=1; i<5; i++)  
    if(c->tab[p[i][0]+1][p[i][1]] != 0 || p[i][0] == 19){ /*test si c'est legal de descencdre ou pas*/
      for(i=1; i<5; i++)
	c->tab[p[i][0]][p[i][1]] = c->suiv[0];
      return 0;
    }
  for(i=1; i<5; i++)    
    p[i][0]++;/*augmentation du x des blocs; effet:descend la piece*/
  return 1;
}

int decaler_d(config *c, int p[5][2]){/*meme principe de descendre*/
  int i;
  for(i=1; i<5; i++)
    c->tab[p[i][0]][p[i][1]] = 0;
  for(i=1; i<5; i++)  
    if(c->tab[p[i][0]][p[i][1]+1] != 0 || p[i][1] == 9) 
      return 0;
  for(i=1; i<5; i++)    
    p[i][1]++;
  return 1;
}

int decaler_g(config *c, int p[5][2]){
  int i;
  for(i=1; i<5; i++)
    c->tab[p[i][0]][p[i][1]] = 0;
  for(i=1; i<5; i++)  
    if(c->tab[p[i][0]][p[i][1]-1] != 0 || p[i][1] == 0) 
      return 0;
  for(i=1; i<5; i++)    
    p[i][1]--;
  return 1;
}

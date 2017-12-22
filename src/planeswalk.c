/*
Copyright (c) Thiago "Harry" Leucz Astrizi, 2017

This file is part of magic.

magic is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

magic is distributed in the hope that it will be useful,
but WITHOUT ANY  WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS  FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more  details.

You should have received a copy of the GNU Affero General Public License
along with magic. If not, see <http://www.gnu.org/licenses/>.
*/

#include "planeswalk.h"

static struct interface *mapa_eternidade[7][7];
static struct interface *plano_destacado, *plano_maior;
static struct interface *plano_destacado2, *plano_maior2;
static bool escolhido;

struct interface *obtem_medio(int tipo, float x, float y, int n){
  char nome[256];
  strcpy(nome, nomes[n]);
  nome[strlen(nome) - 4] = '\0';
  strcat(nome, "_medio.gif");
  return W.new_interface(tipo, x, y,
                         W.width / 3, W.height / 3, nome);
}

struct interface *obtem_pequeno(float x, float y, int n){
  char nome[256];
  strcpy(nome, nomes[n]);
  nome[strlen(nome) - 4] = '\0';
  strcat(nome, "_pequeno.gif");
  return W.new_interface(1, x, y,
                         W.width / 7, W.height / 7, nome);
}

MAIN_LOOP planeswalk(void){
 LOOP_INIT: // Code executed during loop initialization
  escolhido = false;
  plano_destacado = NULL;
  plano_maior = NULL;
  {
    int i, j;
    for(i = 2; i < 5; i ++)
      for(j = 2; j < 5; j ++)
        if(W.game -> mapa[i][j] != -1)
          mapa_eternidade[i][j] = obtem_medio(1,
                                              (1 + ((4 - i) * 2)) * W.width / 6,
                                              (1 + ((4 - j) * 2)) * W.height / 6,
                                              W.game -> mapa[i][j]);
        else
          mapa_eternidade[i][j] = NULL;
  }
 LOOP_BODY: // Code executed every loop iteration
  if(escolhido)
    Wexit_loop();
  if((W.keyboard[W_ESC] || W.keyboard[W_DOWN]) && W.game -> pode_mudar == false){
    Wexit_loop();
  }
  else if(W.keyboard[W_UP] == 1){
    Wloop(zoom);
  }
  {
    int i, j;
    i = 4 - (3 * W.mouse.x / W.width);
    j = 4 - (3 * W.mouse.y / W.height);
    if(mapa_eternidade[i][j] != plano_destacado){
      plano_destacado = mapa_eternidade[i][j];
      if(plano_maior != NULL)
        W.destroy_interface(plano_maior);
      if(plano_destacado == NULL)
        plano_maior = NULL;
      else{
        plano_maior = W.new_interface(W_INTERFACE_IMAGE,
                                      (1 + ((4 - i) * 2)) * W.width / 6,
                                      (1 + ((4 - j) * 2)) * W.height / 6,
                                      0.45 * W.width, 0.45 * W.height,
                                      nomes[W.game -> mapa[i][j]]);
        if(plano_maior -> x - plano_maior -> width / 2 < 0)
          W.move_interface(plano_maior, plano_maior -> width / 2,
                           plano_maior -> y);
        else if(plano_maior -> x + plano_maior -> width / 2 > W.width)
          W.move_interface(plano_maior, W.width - plano_maior -> width / 2,
                           plano_maior -> y);
        if(plano_maior -> y - plano_maior -> height / 2 < 0)
          W.move_interface(plano_maior, plano_maior -> x,
                           plano_maior -> height / 2);
        else if(plano_maior -> y + plano_maior -> height / 2 > W.height)
          W.move_interface(plano_maior, plano_maior -> x,
                           W.height - plano_maior -> height / 2);
      }
    }
    if((W.mouse.buttons[W_MOUSE_LEFT] == 1 ||
        W.mouse.buttons[W_MOUSE_LEFT] == -1) && W.game -> pode_mudar &&
       (i != 3 || j != 3) && (i == 3 || j == 3 || W.game -> mapa[i][j] == -1)){
      escolhido = true;
      if(i == 2) move_oeste();
      else if(i == 4) move_leste();
      if(j == 2) move_norte();
      else if(j == 4) move_sul();
      if(W.game -> mapa[3][3] == -1){
        gera_vizinhanca();
        W.game -> pode_mudar = false;
        if(checa_fenomeno())
          Wsubloop(fenomeno);
      }
      else{
        W.game -> pode_mudar = false;
        gera_vizinhanca();
      }
      Wexit_loop();
    }
  }
 LOOP_END: // Code executed at the end of the loop
  return;
}

void move_norte(void){
  int i, j;
  for(i = 0; i < 7; i ++)
    for(j = 6; j > 0; j --)
      W.game -> mapa[i][j] = W.game -> mapa[i][j - 1];
  W.game -> mapa[3][0] = -1;
  W.game -> mapa[0][4] = W.game -> mapa[6][4] = -1;
  W.game -> mapa[1][5] = W.game -> mapa[5][5] = -1;
  W.game -> mapa[2][6] = W.game -> mapa[4][6] = -1;
}

void move_sul(void){
  int i, j;
  for(i = 0; i < 7; i ++)
    for(j = 0; j < 6; j ++)
      W.game -> mapa[i][j] = W.game -> mapa[i][j + 1];
  W.game -> mapa[3][6] = -1;
  W.game -> mapa[0][2] = W.game -> mapa[6][2] = -1;
  W.game -> mapa[1][1] = W.game -> mapa[5][1] = -1;
  W.game -> mapa[2][0] = W.game -> mapa[4][0] = -1;
}

void move_oeste(void){
  int i, j;
  for(i = 6; i > 0; i --)
    for(j = 0; j < 7; j ++)
      W.game -> mapa[i][j] = W.game -> mapa[i - 1][j];
  W.game -> mapa[0][3] = -1;
  W.game -> mapa[4][0] = W.game -> mapa[4][6] = -1;
  W.game -> mapa[5][1] = W.game -> mapa[5][5] = -1;
  W.game -> mapa[6][2] = W.game -> mapa[6][4] = -1;
}

void move_leste(void){
  int i, j;
  for(i = 0; i < 6; i ++)
    for(j = 0; j < 7; j ++)
      W.game -> mapa[i][j] = W.game -> mapa[i + 1][j];
  W.game -> mapa[6][3] = -1;
  W.game -> mapa[2][0] = W.game -> mapa[2][6] = -1;
  W.game -> mapa[1][1] = W.game -> mapa[1][5] = -1;
  W.game -> mapa[0][2] = W.game -> mapa[0][4] = -1;
}


MAIN_LOOP zoom(void){
 LOOP_INIT: // Code executed during loop initialization
  plano_destacado2 = NULL;
  plano_maior2 = NULL;
  {
    int i, j;
    for(i = 0; i < 7; i ++)
      for(j = 0; j < 7; j ++)
        if(W.game -> mapa[i][j] != -1)
          mapa_eternidade[i][j] = obtem_pequeno((1 + ((6 - i) * 2)) * W.width / 14,
                                              (1 + ((6 - j) * 2)) * W.height / 14,
                                              W.game -> mapa[i][j]);
        else
          mapa_eternidade[i][j] = NULL;
  }
 LOOP_BODY: // Code executed every loop iteration
  if(W.keyboard[W_ESC] && W.game -> pode_mudar == false){
    Wexit_loop();
  }
  else if(W.keyboard[W_DOWN] == 1){
    Wloop(planeswalk);
  }
  {
    int i, j;
    i = 6 - (7 * W.mouse.x / W.width);
    j = 6 - (7 * W.mouse.y / W.height);
    if(mapa_eternidade[i][j] != plano_destacado2){
      plano_destacado2 = mapa_eternidade[i][j];
      if(plano_maior2 != NULL)
        W.destroy_interface(plano_maior2);
      if(plano_destacado2 == NULL)
        plano_maior2 = NULL;
      else if(W.game -> mapa[i][j] != -1){
        plano_maior2 = W.new_interface(W_INTERFACE_IMAGE,
                                      (1 + ((6 - i) * 2)) * W.width / 14,
                                      (1 + ((6 - j) * 2)) * W.height / 14,
                                      0.25 * W.width, 0.25 * W.height,
                                      nomes[W.game -> mapa[i][j]]);
        if(plano_maior2 -> x - plano_maior2 -> width / 2 < 0)
          W.move_interface(plano_maior2, plano_maior2 -> width / 2,
                           plano_maior2 -> y);
        else if(plano_maior2 -> x + plano_maior2 -> width / 2 > W.width)
          W.move_interface(plano_maior2, W.width - plano_maior2 -> width / 2,
                           plano_maior2 -> y);
        if(plano_maior2 -> y - plano_maior2 -> height / 2 < 0)
          W.move_interface(plano_maior2, plano_maior2 -> x,
                           plano_maior2 -> height / 2);
        else if(plano_maior2 -> y + plano_maior2 -> height / 2 > W.height)
          W.move_interface(plano_maior2, plano_maior2 -> x,
                           W.height - plano_maior2 -> height / 2);
      }
    }
  }
 LOOP_END: // Code executed at the end of the loop
  return;
}

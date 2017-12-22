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

#include "tunel.h"

static struct interface *fundo, *opcoes[5];
static bool escolhido;

MAIN_LOOP tunel(void){
 LOOP_INIT:
  fundo = W.new_interface(1, W.width / 2, W.height / 2,
                          W.width, W.height, "tunel_fundo.gif");
  gera_proximas_cartas();
  escolhido = false;
  opcoes[0] = obtem_medio(W_INTERFACE_IMAGE,
                          W.width / 2, 5 * W.height / 6, W.game -> proximo[0]);
  opcoes[1] = obtem_medio(W_INTERFACE_IMAGE,
                          W.width / 6, W.height / 2, W.game -> proximo[1]);
  opcoes[2] = obtem_medio(W_INTERFACE_IMAGE,
                          W.width / 2, W.height / 2, W.game -> proximo[2]);
  opcoes[3] = obtem_medio(W_INTERFACE_IMAGE,
                          5 * W.width / 6, W.height / 2, W.game -> proximo[3]);
  opcoes[4] = obtem_medio(W_INTERFACE_IMAGE,
                          W.width / 2, W.height / 6, W.game -> proximo[4]);
 LOOP_BODY:
  if(W.mouse.buttons[W_MOUSE_LEFT] == 1 ||
     W.mouse.buttons[W_MOUSE_LEFT] == -1){
    if(W.mouse.x > W.width / 3 && W.mouse.x < 2 * W.width / 3 &&
       W.mouse.y > 2 * W.height / 3){
      W.game -> mapa[3][3] = W.game -> proximo[0];
      escolhido = true;
    }
    else if(W.mouse.x < W.width / 3 && W.mouse.y > W.height / 3 &&
            W.mouse.y < 2 * W.height / 3){
      W.game -> mapa[3][3] = W.game -> proximo[1];
      escolhido = true;
    }
    else if(W.mouse.x > W.width / 3 && W.mouse.x < 2 * W.width / 3 &&
            W.mouse.y > W.height / 3 && W.mouse.y < 2 * W.height / 3){
      W.game -> mapa[3][3] = W.game -> proximo[2];
      escolhido = true;
    }
    else if(W.mouse.x > 2 * W.width / 3 && W.mouse.y > W.height / 3 &&
            W.mouse.y < 2 * W.height / 3){
      W.game -> mapa[3][3] = W.game -> proximo[3];
      escolhido = true;
    }
    else if(W.mouse.x > W.width / 3 && W.mouse.x < 2 * W.width / 3 &&
            W.mouse.y < W.height / 3){
      W.game -> mapa[3][3] = W.game -> proximo[4];
      escolhido = true;
    }
    if(escolhido){
      int i;
      if(W.game -> modo_mapa == false)
        W.game -> tunel_interplanar = true;
      for(i = 0; i < 5; i ++)
        W.game -> proximo[i] = W.game -> proximo[i + 5];
      for(i = 5; i < 10; i ++)
        W.game -> proximo[i] = -1;
      Wexit_loop();
    }
  }
 LOOP_END:
  return;
}

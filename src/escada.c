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

#include "escada.h"

static struct interface *fundo, *planechase, *carta;

MAIN_LOOP escada(void){
 LOOP_INIT:
  fundo = W.new_interface(1, W.width / 2, W.height / 2, W.width, W.height,
                          "menu_escada.gif");
  planechase = W.new_interface(8,
                               3 * W.width / 4, W.height / 2,
                               W.width / 2, W.height / 2,
                               "planechase_medio.gif");
  if(W.game -> proximo[0] == -1)
    W.game -> proximo[0] = gera_carta();
  carta = W.new_interface(8,
                          W.width / 4, W.height / 2,
                          W.width / 2, W.height / 2,
                          nomes[W.game -> proximo[0]]);
 LOOP_BODY:
  if(W.mouse.buttons[W_MOUSE_LEFT] == 1 ||
     W.mouse.buttons[W_MOUSE_LEFT] == -1){
    if(W.mouse.x < W.width / 2 &&
       W.mouse.y > W.height / 4 &&
       W.mouse.y < 3 * W.height / 4){
      Wexit_loop();
    }
    else if(W.mouse.x > W.width / 2 &&
            W.mouse.y > W.height / 4 &&
            W.mouse.y < 3 * W.height / 4){
      gera_proximas_cartas();
      Wexit_loop();
    }
  }
 LOOP_END:
  return;
}

void gera_proximas_cartas(void){
  int i;
  int proibida = W.game -> proximo[0];
  for(i = 0; i < 10; i ++){
    do{
      W.game -> proximo[i] = gera_carta();
    } while(W.game -> proximo[i] == proibida);
  }
}

void descarta_carta(void){
  int i;
  for(i = 0; i < 9; i ++)
    W.game -> proximo[i] = W.game -> proximo[i + 1];
  W.game -> proximo[9] = -1;
}

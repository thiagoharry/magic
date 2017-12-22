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

#include "fenomeno.h"

const char *fenomenos[] = {"caotico.gif", "tunel.gif", "mare.gif",
                           "epifania.gif", "desastre.gif", "moldando.gif",
                           "espacial.gif", "temporal.gif"};

static struct interface *carta;
static bool sair;
static int num;
static float tempo;

void sair_fenomeno(void){
  sair = true;
}

MAIN_LOOP fenomeno(void){
 LOOP_INIT:
  sair = false;
  num = W.random() % F;
  carta = W.new_interface(1, W.width / 2, W.height / 2,
                          W.width, W.height, fenomenos[num]);
  switch(num){
  case 0:
    W.game -> aether_caotico = true;
    tempo = 5.0;
    break;
  case 2:
    tempo = 20.0;
    break;
  case 6:
    tempo = 5.0;
    W.game -> fusao_espacial = true;
    break;
  case 3:
  case 4:
  case 5:
  case 7:
    tempo = 10.0;
    break;
  default:
    tempo = 5.0;
    break;
  }
  W.run_futurelly(sair_fenomeno, tempo);
 LOOP_BODY:
  if(sair){
    if(num == 1)
      Wloop(tunel);
    else
      Wexit_loop();
  }
 LOOP_END:
  return;
}

bool checa_fenomeno(void){
  int resultado = W.random() % 10000;
  if(resultado < W.game -> probabilidade_fenomeno)
    return true;
  return false;
}

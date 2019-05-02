/*
Copyright (c) harry, 2019

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

#include "garruk.h"

struct interface *garruk_matador;
static struct interface *digitos[2];
static struct interface *lobos[20], *lobo_mau;
static struct sound *clique, *novo_lobo, *fim_lobo, *uivo_mau, *ultimate, *machado;

void conjura_lobo(void){
  int i;
  for(i = 0; i < 20; i ++)
    if(lobos[i] -> visible == false){
      lobos[i] -> visible = true;
      W.play_sound(novo_lobo);
      break;
    }
}

void deixa_lobo_mau(void){
  int i;
  if(lobo_mau -> visible)
    return;
  for(i = 0; i < 20; i ++)
    if(lobos[i] -> visible == true){
      W.move_interface(lobo_mau, lobos[i] -> x, lobos[i] -> y);
      lobo_mau -> visible = true;
      digitos[1] -> integer += 4;
      if(digitos[1] -> integer >= 10){
	digitos[1] -> integer -= 10;
	digitos[0] ++;
      }
      W.play_sound(uivo_mau);
      break;
    }
}

void novo_turno(void){
  int i;
  for(i = 0; i < 20; i ++)
    W.rotate_interface(lobos[i], 0.0);
  W.rotate_interface(lobo_mau, 0.0);
  lobo_mau -> visible = false;
}

void remove_lobo(void){
  int i;
  for(i = 0; i < 20; i ++)
    if(W.mouse.x > lobos[i] -> x - 0.5 * lobos[i] -> width &&
       W.mouse.x < lobos[i] -> x + 0.5 * lobos[i] -> width &&
       W.mouse.y > lobos[i] -> y - 0.5 * lobos[i] -> height &&
       W.mouse.y < lobos[i] -> y + 0.5 * lobos[i] -> height){
      lobos[i] -> visible = false;
      W.play_sound(fim_lobo);
      break;
    }
}

void vira_lobo(void){
  int i;
  if(W.mouse.x > lobo_mau -> x - 0.5 * lobo_mau -> width &&
     W.mouse.x < lobo_mau -> x + 0.5 * lobo_mau -> width &&
     W.mouse.y > lobo_mau -> y - 0.5 * lobo_mau -> height &&
     W.mouse.y < lobo_mau -> y + 0.5 * lobo_mau -> height){
    if(lobo_mau -> visible == true){
      W.rotate_interface(lobo_mau, -1.5);
    }
  }
  for(i = 0; i < 20; i ++)
    if(W.mouse.x > lobos[i] -> x - 0.5 * lobos[i] -> width &&
       W.mouse.x < lobos[i] -> x + 0.5 * lobos[i] -> width &&
       W.mouse.y > lobos[i] -> y - 0.5 * lobos[i] -> height &&
       W.mouse.y < lobos[i] -> y + 0.5 * lobos[i] -> height){
      if(lobos[i] -> visible == true){
	W.rotate_interface(lobos[i], -1.5);
	break;
      }
    }
}


MAIN_LOOP garruk(void){
  int i;
 LOOP_INIT:
  garruk_matador = W.new_interface(W_INTERFACE_IMAGE, W.width / 4, W.height / 2,
				   W.width / 2, W.height,
				   "desafios/garruk_matador.gif");
  digitos[0] = W.new_interface(9, 0.435 * W.width, W.height / 10,
                               W.width / 45, W.height / 25,
                               "digitos.gif");
  digitos[1] = W.new_interface(9, 0.45 * W.width, W.height / 10,
                               W.width / 45, W.height / 25,
                               "digitos.gif");
  for(i = 0; i < 20; i ++){
    lobos[i] = W.new_interface(W_INTERFACE_IMAGE,
			       W.width / 2 + W.width / 16 + ((i % 4) * W.width/8),
			       W.height - W.height / 8 - ((i / 4) * W.height / 4),
			       W.width / 8, W.height / 4,
			       "desafios/lobo.gif");
    lobos[i] -> visible = false;
  }
  lobo_mau = W.new_interface(W_INTERFACE_IMAGE, 0, 0,
			     W.width / 8, W.height / 4,
			     "desafios/lobo_mau.gif");
  lobo_mau -> visible = false;
  clique = W.new_sound("click.wav");
  novo_lobo = W.new_sound("novo_lobo.wav");
  fim_lobo = W.new_sound("fim_lobo.wav");
  uivo_mau = W.new_sound("lobo_mau.wav");
  ultimate = W.new_sound("ultimate_garruk.wav");
  machado = W.new_sound("machado.wav");
  digitos[0] -> integer = 2;
  digitos[1] -> integer = 0;
  digitos[0] -> r = digitos[0] -> g = digitos[0] -> b =  digitos[0] -> a = 1.0;
  digitos[1] -> r = digitos[1] -> g = digitos[1] -> b =  digitos[1] -> a = 1.0;
  W.play_music("garruk.mp3", true);
 LOOP_BODY:
  if(W.keyboard[W_ESC])
    Wloop(intro);
  if(W.keyboard[W_DOWN] == 1){
    if(digitos[1] -> integer > 0){
      W.play_sound(clique);
      digitos[1] -> integer --;
    }
    else{
      if(digitos[0] -> integer > 0){
        W.play_sound(clique);
        digitos[1] -> integer = 9;
        digitos[0] -> integer --;
      }
    }
  }
  else if(W.keyboard[W_UP] == 1){
    if(digitos[1] -> integer < 9){
      W.play_sound(clique);
      digitos[1] -> integer ++;
    }
    else{
      if(digitos[0] -> integer < 9){
        W.play_sound(clique);
        digitos[1] -> integer = 0;
        digitos[0] -> integer ++;
      }
    }
  }
  else if(W.keyboard[W_DELETE] == 1){
    remove_lobo();
  }
  else if(W.keyboard[W_1] == 1){
    conjura_lobo();
  }
  else if(W.keyboard[W_2]){
    deixa_lobo_mau();
  }
  else if(W.keyboard[W_3]){
    if(digitos[0] -> integer * 10 + digitos[1] -> integer > 10){
      digitos[0] -> integer --;
      W.play_sound(machado);
    }
  }
  else if(W.keyboard[W_4]){
    if(digitos[0] -> integer * 10 + digitos[1] -> integer > 25){
      digitos[1] -> integer -= 5;
      if(digitos[1] -> integer < 0){
	digitos[1] -> integer = 10 - digitos[1] -> integer;
	digitos[0] -> integer --;
      }
      digitos[0] -> integer -= 2;
      W.play_sound(ultimate);
    }
  }
  else if(W.mouse.buttons[W_MOUSE_LEFT] == 1){
    vira_lobo();
  }
  else if(W.keyboard[W_ENTER] == 1){
    novo_turno();
  }
 LOOP_END:
  return;
}

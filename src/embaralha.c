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

#include "embaralha.h"

static struct interface *escolha1, *escolha2, *selecao, *pausado;
static struct interface *primeira, *segunda, *terceira, *ultima, *penultima,
  *antepenultima;
static struct interface *pilhas[10];
static int total_pilha[10];
static int cartas = 0;
static bool paused, terminou;
static struct sound *pause_sound, *avanca_som;

MAIN_LOOP menu_embaralha(void){
 LOOP_INIT:
  escolha1 = W.new_interface(W_INTERFACE_IMAGE,
                             W.width / 4, W.height / 2,
                             W.width / 4, W.height / 2,
                             "40_cartas.gif");
  escolha2 = W.new_interface(W_INTERFACE_IMAGE,
                             3 * W.width / 4, W.height / 2,
                             W.width / 4, W.height / 2,
                             "60_cartas.gif");
  selecao = W.new_interface(W_INTERFACE_PERIMETER, 3 * W.width / 4, W.height / 2,
                            W.width / 3 - 2, W.height - 2,
                            1.0, 1.0, 0.0, 1.0);
  selecao -> visible = false;
 LOOP_BODY:
  if(W.keyboard[W_ESC])
    Wexit_loop();
  if(W.mouse.x > escolha1 -> x - escolha1 -> width / 2 &&
     W.mouse.x < escolha1 -> x + escolha1 -> width / 2 &&
     W.mouse.y > escolha1 -> y - escolha1 -> height / 2 &&
     W.mouse.y < escolha1 -> y + escolha1 -> height / 2){
    W.move_interface(selecao, escolha1 -> x, escolha1 -> y);
    selecao -> visible = true;
  }
  else if(W.mouse.x > escolha2 -> x - escolha2 -> width / 2 &&
          W.mouse.x < escolha2 -> x + escolha2 -> width / 2 &&
          W.mouse.y > escolha2 -> y - escolha2 -> height / 2 &&
          W.mouse.y < escolha2 -> y + escolha2 -> height / 2){
    W.move_interface(selecao, escolha2 -> x, escolha2 -> y);
    selecao -> visible = true;
  }
  else
    selecao -> visible = false;
  if(W.mouse.buttons[W_MOUSE_LEFT] == 1 ||
     W.mouse.buttons[W_MOUSE_LEFT] == -1)
    if(selecao -> visible){
      if(selecao -> x == escolha1 -> x)
        cartas = 40;
      else
        cartas = 60;
    }
  if(cartas != 0){
    Wloop(embaralha);
  }
 LOOP_END:
  return;
}

static void executa(void){
  int pilha_escolhida, carta_escolhida = 0, soma = 0;
  struct interface *p;
  int escolha = W.random() % cartas;
  printf("ESCOLHA: %d\n", escolha);
  if(paused || terminou || W.pending_files)
    return;
  for(pilha_escolhida = 0; pilha_escolhida < 10; pilha_escolhida ++){
    if(soma + total_pilha[pilha_escolhida] > escolha){
      carta_escolhida = soma + total_pilha[pilha_escolhida] - escolha;
      break;
    }
    else
      soma += total_pilha[pilha_escolhida];
  }
  if(pilha_escolhida == 10)
    return;
  primeira -> visible = false;
  segunda -> visible = false;
  terceira -> visible = false;
  ultima -> visible = false;
  penultima -> visible = false;
  antepenultima -> visible = false;
  if(carta_escolhida == 1)
    p = primeira;
  else if(carta_escolhida == total_pilha[pilha_escolhida])
    p = ultima;
  else if(carta_escolhida == 2)
    p = segunda;
  else if(carta_escolhida == total_pilha[pilha_escolhida] - 1)
    p = penultima;
  else if(carta_escolhida == 3)
    p = terceira;
  else
    p = antepenultima;
  printf("Pilha: %d Carta: %d/%d\n", pilha_escolhida, carta_escolhida,
         total_pilha[pilha_escolhida]);
  W.move_interface(p,
                   (pilha_escolhida % 5) * W.width * 0.2 + W.width * 0.1,
                   (pilha_escolhida / 5) * 0.5 * W.height + W.height * 0.25);
  p -> visible = true;
  total_pilha[pilha_escolhida] --;
  cartas --;
  if(total_pilha[pilha_escolhida] == 0)
    pilhas[pilha_escolhida] -> visible = false;
  W.play_sound(avanca_som);
  if(cartas == 0)
    terminou = true;
}

MAIN_LOOP embaralha(void){
 LOOP_INIT:
  terminou = false;
  pause_sound = W.new_sound("fail.wav");
  avanca_som = W.new_sound("click.wav");
  paused = false;
  pausado = W.new_interface(W_INTERFACE_IMAGE,
                            W.width / 2, W.height / 2,
                            80, 30, "pausado.gif");
  pausado -> visible = false;
  primeira = W.new_interface(W_INTERFACE_IMAGE, 0, 0, 100, 80, "1.gif");
  primeira -> visible = false;
  segunda = W.new_interface(W_INTERFACE_IMAGE, 0, 0, 100, 80, "2.gif");
  segunda -> visible = false;
  terceira = W.new_interface(W_INTERFACE_IMAGE, 0, 0, 100, 80, "3.gif");
  terceira -> visible = false;
  antepenultima = W.new_interface(W_INTERFACE_IMAGE, 0, 0, 100, 80, "6.gif");
  antepenultima -> visible = false;
  penultima = W.new_interface(W_INTERFACE_IMAGE, 0, 0, 100, 80, "5.gif");
  penultima -> visible = false;
  ultima = W.new_interface(W_INTERFACE_IMAGE, 0, 0, 100, 80, "4.gif");
  ultima -> visible = false;
  {
    int i;
    for(i = 0; i < 10; i ++){
      pilhas[i] = W.new_interface(5,
                                  (i % 5) * W.width * 0.2 + W.width * 0.1,
                                  (i / 5) * 0.5 * W.height + W.height * 0.25,
                                  200, 277, "carta.gif");
      total_pilha[i] = cartas / 10;
    }
  }
  executa();
  W.run_periodically(executa, 5.0);
 LOOP_BODY:
  if(W.keyboard[W_ESC] || terminou)
    Wexit_loop();
  else if(W.keyboard[W_SPACEBAR] == 1){
    paused = !paused;
    pausado -> visible = paused;
    W.play_sound(pause_sound);
  }
 LOOP_END:
  return;
}

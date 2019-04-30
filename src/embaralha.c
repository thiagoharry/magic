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

static struct interface *escolha1, *escolha2, *escolha3, *selecao, *pausado;
static struct interface *primeira, *segunda, *terceira, *ultima, *penultima,
  *antepenultima;
static struct interface *pilhas[20];
static int total_pilha[20];
static int numero_de_pilhas;
static int cartas;
static bool paused, terminou;
static struct sound *pause_sound, *avanca_som;

MAIN_LOOP menu_embaralha(void){
 LOOP_INIT:
  cartas = 0;
  escolha1 = W.new_interface(W_INTERFACE_IMAGE,
                             W.width / 6, W.height / 2,
                             W.width / 4, W.height / 2,
                             "40_cartas.gif");
  escolha2 = W.new_interface(W_INTERFACE_IMAGE,
                             3 * W.width / 6, W.height / 2,
                             W.width / 4, W.height / 2,
                             "60_cartas.gif");
  escolha3 = W.new_interface(W_INTERFACE_IMAGE,
                             5 * W.width / 6, W.height / 2,
                             W.width / 4, W.height / 2,
                             "100_cartas.gif");
  selecao = W.new_interface(W_INTERFACE_PERIMETER, 3 * W.width / 4, W.height / 2,
                            W.width / 3 - 2, W.height - 2,
                            1.0, 1.0, 0.0, 1.0);
  selecao -> visible = false;
 LOOP_BODY:
  if(W.keyboard[W_ESC])
    Wexit_loop();
  selecao -> visible = false;
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
  else if(W.mouse.x > escolha3 -> x - escolha3 -> width / 2 &&
          W.mouse.x < escolha3 -> x + escolha3 -> width / 2 &&
          W.mouse.y > escolha3 -> y - escolha3 -> height / 2 &&
          W.mouse.y < escolha3 -> y + escolha3 -> height / 2){
        W.move_interface(selecao, escolha3 -> x, escolha3 -> y);
        selecao -> visible = true;
  }
  if(W.mouse.buttons[W_MOUSE_LEFT] == 1 ||
     W.mouse.buttons[W_MOUSE_LEFT] == -1)
    if(selecao -> visible && !W.pending_files){
      if(selecao -> x == escolha1 -> x){
        cartas = 40;
        numero_de_pilhas = 20;
      }
      else if(selecao -> x == escolha2 -> x){
        cartas = 60;
        numero_de_pilhas = 20;
      }
      else{
        cartas = 100;
        numero_de_pilhas = 20;
      }
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
  if(paused || terminou || W.pending_files)
    return;
  for(pilha_escolhida = 0; pilha_escolhida < numero_de_pilhas;
      pilha_escolhida ++){
    if(soma + total_pilha[pilha_escolhida] > escolha){
      carta_escolhida = soma + total_pilha[pilha_escolhida] - escolha;
      break;
    }
    else
      soma += total_pilha[pilha_escolhida];
  }
  if(pilha_escolhida == numero_de_pilhas)
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
  W.move_interface(p,
                   pilhas[pilha_escolhida] -> x,
                   pilhas[pilha_escolhida] -> y);
  p -> visible = true;
  total_pilha[pilha_escolhida] --;
  cartas --;
  if(total_pilha[pilha_escolhida] == 0)
    pilhas[pilha_escolhida] -> visible = false;
  W.play_sound(avanca_som);
  if(cartas == 0)
    terminou = true;
  if(!terminou){
    if(carta_escolhida == 1)
      W.run_futurelly(executa, 2.5);
    else if(p == ultima)
      W.run_futurelly(executa, 4.0);
    else
      W.run_futurelly(executa, 5.0);
  }
}

MAIN_LOOP embaralha(void){
 LOOP_INIT:
  terminou = false;
  pause_sound = W.new_sound("fail.wav");
  printf("%p\n", pause_sound);
  avanca_som = W.new_sound("click.wav");
  paused = false;
  pausado = W.new_interface(5,
                            W.width / 2, W.height / 2,
                            80, 30, "pausado.gif");
  pausado -> visible = false;
  primeira = W.new_interface(5, 0, 0, 100, 80, "1.gif");
  primeira -> visible = false;
  segunda = W.new_interface(5, 0, 0, 100, 80, "2.gif");
  segunda -> visible = false;
  terceira = W.new_interface(5, 0, 0, 100, 80, "3.gif");
  terceira -> visible = false;
  antepenultima = W.new_interface(5, 0, 0, 100, 80, "6.gif");
  antepenultima -> visible = false;
  penultima = W.new_interface(5, 0, 0, 100, 80, "5.gif");
  penultima -> visible = false;
  ultima = W.new_interface(5, 0, 0, 100, 80, "4.gif");
  ultima -> visible = false;
  {
    int i;
    int card_width, card_height;
    float y_div;
    if(numero_de_pilhas <= 10){
      card_width = 200;
      card_height = 277;
      y_div = 0.5;
    }
    else{
        card_width = 124;
        card_height = 172;
        y_div = 0.25;
    }
    for(i = 0; i < numero_de_pilhas; i ++){
      pilhas[i] = W.new_interface(W_INTERFACE_IMAGE,
                                  (i % 5) * W.width * 0.2 + W.width * 0.1,
                                  (i / 5) * y_div * W.height + W.height * y_div * 0.5,
                                  card_width, card_height, "carta.gif");
      total_pilha[i] = cartas / numero_de_pilhas;
    }
  }
  executa();
  //W.run_periodically(executa, 5.0);
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

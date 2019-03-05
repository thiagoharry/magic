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

#include "vida.h"

#define AVATARS 33

static struct interface *opcoes[3], *selecao;
static struct interface *avatar[4];
static struct interface *fundo[4];
static struct interface *digitos[4][2];


static struct sound *clique;

static int escolha;

static void decrementa(int i){
  int total;
  float r, g, b;
  if(digitos[i][0] -> integer != 0 ||
     digitos[i][1] -> integer != 0){
    if(digitos[i][1] -> integer == 0){
      digitos[i][1] -> integer = 9;
      digitos[i][0] -> integer --;
    }
    else{
      digitos[i][1] -> integer --;
    }
    W.play_sound(clique);
  }
  total = digitos[i][0] -> integer * 10 + digitos[i][1] -> integer;
  if(total >= 20){
    r = 0.0;
    g = 1.0;
    b = 0.0;
  }
  else if(total >= 10){
    r = 1.0 * (20.0-total)/10.0;
    g = 1.0;
    b = 0.0;
  }
  else{
    r = 1.0;
    g = 1.0 * (total)/10.0;
    b = 0.0;
  }
  W.game -> vida_de_jogadores[i] = total;
  digitos[i][0] -> r = digitos[i][1] -> r = r;
  digitos[i][0] -> g = digitos[i][1] -> g = g;
  digitos[i][0] -> b = digitos[i][1] -> b = b;
}

static void incrementa(int i){
  int total;
  float r, g, b;
  if(digitos[i][0] -> integer != 9 ||
     digitos[i][1] -> integer != 9){
    if(digitos[i][1] -> integer == 9){
      digitos[i][1] -> integer = 0;
      digitos[i][0] -> integer ++;
    }
    else{
      digitos[i][1] -> integer ++;
    }
    W.play_sound(clique);
  }
  total = digitos[i][0] -> integer * 10 + digitos[i][1] -> integer;
  if(total >= 20){
    r = 0.0;
    g = 1.0;
    b = 0.0;
  }
  else if(total >= 10){
    r = 1.0 * (20.0-total)/10.0;
    g = 1.0;
    b = 0.0;
  }
  else{
    r = 1.0;
    g = 1.0 * (total)/10.0;
    b = 0.0;
  }
  W.game -> vida_de_jogadores[i] = total;
  digitos[i][0] -> r = digitos[i][1] -> r = r;
  digitos[i][0] -> g = digitos[i][1] -> g = g;
  digitos[i][0] -> b = digitos[i][1] -> b = b;
}

static void restaura_vida(void){
  int i;
  float r, g, b;
  char nome[16];
  for(i = 0; i < W.game -> numero_de_jogadores; i ++){
    snprintf(nome, 16, "vida/%d.gif", W.game -> avatar_de_jogadores[i]);
    avatar[i] = W.new_interface(10,
                                W.width * ((i % 2) * 0.5 + 0.25),
                                W.height * ((1-i / 2) * 0.5 + 0.5) - 70,
                                140, 140, nome);
    avatar[i] -> integer = 7;
    avatar[i] -> r = avatar[i] -> g = avatar[i] -> b = avatar[i] -> a = 1.0;
    r = g = b = 0.8;
    switch(i){
    case 0:
      r = 1.0;
      break;
    case 1:
      g = 1.0;
      break;
    case 2:
      b = 1.0;
      break;
    default:
      r = 1.0;
      g = 1.0;
      break;
    }
    fundo[i] = W.new_interface(7,
                               (W.width * ((i % 2) * 0.5 + 0.25)),
                               (W.game -> numero_de_jogadores == 2)?
                               (W.height/2):(W.height * ((1-i / 2) * 0.5 + 0.25)),
                               W.width / 2,
                               (W.game -> numero_de_jogadores == 2)?
                               (W.height):(W.height / 2),
                               NULL);
    fundo[i] -> r = r;
    fundo[i] -> g = g;
    fundo[i] -> b = b;
    fundo[i] -> a = 1.0;
    digitos[i][0] = W.new_interface(9,
                                    W.width * ((i % 2) * 0.5 + 0.24),
                                    W.height * ((1-i / 2) * 0.5 + 0.25),
                                    W.width / 20, W.height / 10,
                                    "digitos.gif");
    digitos[i][1] = W.new_interface(9,
                                    W.width * ((i % 2) * 0.5 + 0.27),
                                    W.height * ((1-i / 2) * 0.5 + 0.25),
                                    W.width / 20, W.height / 10,
                                    "digitos.gif");
    if(W.game -> vida_de_jogadores[i] >= 20){
      r = 0.0;
      g = 1.0;
      b = 0.0;
    }
    else if(W.game -> vida_de_jogadores[i] >= 10){
      r = 1.0 * (20.0-(W.game -> vida_de_jogadores[i]))/10.0;
      g = 1.0;
      b = 0.0;
    }
    else{
      r = 1.0;
      g = 1.0 * (W.game -> vida_de_jogadores[i])/10.0;
      b = 0.0;
    }
    digitos[i][0] -> integer = W.game -> vida_de_jogadores[i] / 10;
    digitos[i][0] -> r = r;
    digitos[i][0] -> g = g;
    digitos[i][0] -> b = b;
    digitos[i][1] -> integer = W.game -> vida_de_jogadores[i] % 10;
    digitos[i][1] -> r = r;
    digitos[i][1] -> g = g;
    digitos[i][1] -> b = b;
  }
}

static void inicializa_vida(void){
  int i, j;
  bool repetido;
  for(i = 0; i < W.game -> numero_de_jogadores; i ++){
    do{ // Gera avatar único para o jogador
      repetido = false;
      W.game -> avatar_de_jogadores[i] = W.random() % AVATARS + 1;
      for(j = 0; j < i; j ++)
        if(W.game -> avatar_de_jogadores[i] == W.game -> avatar_de_jogadores[j])
          repetido = true;
    }while(repetido);
    W.game -> vida_de_jogadores[i] = 20;
    W.game -> veneno_de_jogadores[i] = 0;
  }
  restaura_vida();
}

MAIN_LOOP vida(void){
 LOOP_INIT:
  clique = W.new_sound("click.wav");
  if(W.game -> numero_de_jogadores == 0){
    opcoes[0] = W.new_interface(W_INTERFACE_IMAGE,
                                W.width / 6, W.height / 2,
                                W.width / 4, W.height / 2,
                                "2_jogadores.gif");
    opcoes[1] = W.new_interface(W_INTERFACE_IMAGE,
                                W.width / 2, W.height / 2,
                                W.width / 4, W.height / 2,
                                "3_jogadores.gif");
    opcoes[2] = W.new_interface(W_INTERFACE_IMAGE,
                                5 * W.width / 6, W.height / 2,
                                W.width / 4, W.height / 2,
                                "4_jogadores.gif");
    selecao = W.new_interface(W_INTERFACE_PERIMETER,
                              3 * W.width / 4, W.height / 2,
                              W.width / 3 - 2, W.height - 2,
                              1.0, 1.0, 0.0, 1.0);
    selecao -> visible = false;
  }
  else{
    restaura_vida();
  }
 LOOP_BODY:
  if(W.keyboard[W_ESC])
    Wexit_loop();
  else if(W.game -> modo_jogo && W.keyboard[W_SPACEBAR] == 1)
    Wexit_loop();
  if(W.game -> numero_de_jogadores == 0){
    int i;
    selecao -> visible = false;
    for(i = 0; i < 3; i ++){
      if(W.mouse.x > opcoes[i] -> x - opcoes[i] -> width / 2 &&
         W.mouse.x < opcoes[i] -> x + opcoes[i] -> width / 2 &&
         W.mouse.y > opcoes[i] -> y - opcoes[i] -> height / 2 &&
         W.mouse.y < opcoes[i] -> y + opcoes[i] -> height / 2){
        W.move_interface(selecao, opcoes[i] -> x, opcoes[i] -> y);
        selecao -> visible = true;
        if(W.mouse.buttons[W_MOUSE_LEFT] == 1 ||
           W.mouse.buttons[W_MOUSE_LEFT] == -1){
          W.game -> numero_de_jogadores = i + 2;
          W.destroy_interface(selecao);
          W.destroy_interface(opcoes[2]);
          W.destroy_interface(opcoes[1]);
          W.destroy_interface(opcoes[0]);
          inicializa_vida();
          break;
        }
      }
    }
  }
  else{
    int i;
    escolha = -1;
    for(i = 0; i < W.game -> numero_de_jogadores; i ++){
      if(W.mouse.x > fundo[i] -> x - fundo[i] -> width / 2 &&
         W.mouse.x < fundo[i] -> x + fundo[i] -> width / 2 &&
         W.mouse.y > fundo[i] -> y - fundo[i] -> height / 2 &&
         W.mouse.y < fundo[i] -> y + fundo[i] -> height / 2){
        escolha = i;
        if(fundo[i] -> r != 1.0)
          fundo[i] -> r = 0.5;
        if(fundo[i] -> g != 1.0)
          fundo[i] -> g = 0.5;
        if(fundo[i] -> b != 1.0)
          fundo[i] -> b = 0.5;
        if(W.keyboard[W_LEFT] == 1){
          decrementa(i);
        }
        else if(W.keyboard[W_RIGHT] == 1){
          incrementa(i);
        }
      }
      else{
        if(fundo[i] -> r != 1.0)
          fundo[i] -> r = 0.8;
        if(fundo[i] -> g != 1.0)
          fundo[i] -> g = 0.8;
        if(fundo[i] -> b != 1.0)
          fundo[i] -> b = 0.8;
      }
    }
  }
 LOOP_END:
  return;
}

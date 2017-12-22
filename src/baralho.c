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

#include "baralho.h"

static struct interface *slot;
static struct interface *opcoes[9];
static struct interface *opcoes_nome[9];
static struct interface *opcoes_tipo[9];
static struct interface *opcoes_texto[9];
static struct interface *miniaturas[20];
static int offset;
static bool inicializado, loop_terminado;
static int cartas_escolhidas[20], numero_de_cartas, deck_atual;

static void adiciona_carta(int num){
  int i, repetido = 0;
  char nome[64];
  if(numero_de_cartas >= 20)
    return;
  for(i = 0; i < 20; i ++){
    if(cartas_escolhidas[i] == 0)
      break;
    else if(cartas_escolhidas[i] == num)
      repetido ++;
    if(repetido == 2)
      return;
  }
  numero_de_cartas ++;
  cartas_escolhidas[i] = num;
  sprintf(nome, "arquiinimigo/%d_pequeno.gif", num);
  miniaturas[i] = W.new_interface(5,
                                  W.width * ((i % 2)?(0.974):(0.924)),
                                  W.height * (-(i / 2) * 0.0925 + 0.945 -
                                              (i/4) * 0.014),
                                  0.036 * W.width,
                                  0.08 * W.height,
                                  nome);
  miniaturas[i] -> integer = 7;
  if(i){
    sprintf(nome, "deck%dcard%d", deck_atual, i);
    W.write_integer(nome, num);
  }
}

static void novas_cartas(void){
  int i, num;
  if(inicializado){
    for(i = 8; i >= 0; i --){
      W.destroy_interface(opcoes_tipo[i]);
      W.destroy_interface(opcoes_texto[i]);
      W.destroy_interface(opcoes_nome[i]);
      W.destroy_interface(opcoes[i]);
    }
  }
  for(i = 0; i < 9; i ++){
    char nome[64];
    num = (i + offset) % 65 + 1;
    if(num >= 46)
      num += 5;
    sprintf(nome, "arquiinimigo/%d_medio.gif", num);
    opcoes[i] = W.new_interface(6                ,
                                W.width * ((i % 3) * 0.3 + 0.15),
                                W.height * (1.0  - 0.333 * (i / 3) - 0.16),
                                0.25 * W.width, 0.3 * W.height ,
                                nome);
    sprintf(nome, "arquiinimigo/%d_nome.gif", num);
    opcoes_nome[i] = W.new_interface(5,
                                     W.width * ((i % 3) * 0.3 + 0.15),
                                     W.height * (1.0  - 0.333 * (i / 3) - 0.025),
                                     0.14 * W.width, 0.03 * W.height,
                                     nome);
    sprintf(nome, "arquiinimigo/%d_texto.gif", num);
    opcoes_texto[i] = W.new_interface(5,
                                     W.width * ((i % 3) * 0.3 + 0.15),
                                     W.height * (1.0  - 0.333 * (i / 3) - 0.19),
                                     0.24 * W.width, 0.22 * W.height,
                                     nome);
    if(eh_plano_em_andamento(num))
      opcoes_tipo[i] = W.new_interface(5,
                                       W.width * ((i % 3) * 0.3 + 0.15),
                                       W.height * (1.0  - 0.333 * (i / 3) -
                                                   0.065),
                                       0.08 * W.width, 0.025 * W.height,
                                       "arquiinimigo/plano_em_andamento.gif");
    else
      opcoes_tipo[i] = W.new_interface(5,
                                       W.width * ((i % 3) * 0.3 + 0.15),
                                       W.height * (1.0  - 0.333 * (i / 3) -
                                                   0.07),
                                       0.045 * W.width, 0.017 * W.height,
                                       "arquiinimigo/plano.gif");
    opcoes_nome[i] -> integer = 3;
    opcoes_texto[i] -> integer = 3;
    opcoes_tipo[i] -> integer = 3;
    opcoes_texto[i] -> visible = false;
    opcoes_tipo[i] -> visible = false;
    opcoes[i] -> r = (float) num;
  }
}

MAIN_LOOP baralho(void){
 LOOP_INIT:
  inicializado = false;
  loop_terminado = false;
  offset = 0;
  slot = W.new_interface(W_INTERFACE_IMAGE, 19 * W.width / 20, W.height / 2,
                         W.width / 10, W.height,
                         "arquiinimigo/slot.gif");
  novas_cartas();
  {
    int i;
    for(i = 0; i < 20; i ++)
      cartas_escolhidas[i] = 0;
  }
  numero_de_cartas = 0;
  deck_atual = 0;
  {
    int i;
    char nome[16];
    bool ret;
    do{
      sprintf(nome, "deck%dcard%d", deck_atual, 0);
      ret = W.read_integer(nome, &i);
      deck_atual ++;
    }while(ret);
    deck_atual --;
  }
  inicializado = true;
 LOOP_BODY:
  if(W.keyboard[W_ESC])
    Wloop(intro);
  else if(W.keyboard[W_RIGHT] == 1 && W.pending_files == 0){
    offset = (offset + 9) % 65;
    novas_cartas();
  }
  else if(W.keyboard[W_LEFT] == 1 && W.pending_files == 0){
    offset = offset - 9;
    if(offset < 0)
      offset = 65 + offset;
    novas_cartas();
  }
  else if(W.keyboard[W_ENTER] == 1 && numero_de_cartas == 20){
    int i;
    char nome[16];
    for(i = 0; i < 20; i ++){
      W.game -> baralho_arquiinimigo[i] = cartas_escolhidas[i];
    }
    sprintf(nome, "deck%dcard%d", deck_atual, 0);
    W.write_integer(nome, cartas_escolhidas[0]);
    loop_terminado = true;
  }
  if(loop_terminado)
    Wloop(arquiinimigo);
  {
    int i;
    bool click = false;
    if(W.mouse.buttons[W_MOUSE_LEFT] == 1 || W.mouse.buttons[W_MOUSE_LEFT] == -1)
      click = true;
    for(i = 0; i < 9; i ++){
      if(W.mouse.x > opcoes[i] -> x - opcoes[i] -> width / 2 &&
         W.mouse.x < opcoes[i] -> x + opcoes[i] -> width / 2 &&
         W.mouse.y > opcoes[i] -> y - opcoes[i] -> height / 2 &&
         W.mouse.y < opcoes[i] -> y + opcoes[i] -> height / 2){
        opcoes_tipo[i] -> visible = true;
        opcoes_texto[i] -> visible = true;
        if(click)
          adiciona_carta((int) opcoes[i] -> r);
      }
      else{
        opcoes_tipo[i] -> visible = false;
        opcoes_texto[i] -> visible = false;
      }
    }
    if(click){
      for(i = 0; i < 20; i ++)
        if(cartas_escolhidas[i] != 0 &&
           W.mouse.x > miniaturas[i] -> x - miniaturas[i] -> width / 2 &&
           W.mouse.x < miniaturas[i] -> x + miniaturas[i] -> width / 2 &&
           W.mouse.y > miniaturas[i] -> y - miniaturas[i] -> height / 2 &&
           W.mouse.y < miniaturas[i] -> y + miniaturas[i] -> height / 2){
          char nome[16];
          cartas_escolhidas[i] = 0;
          W.destroy_interface(miniaturas[i]);
          numero_de_cartas --;
          if(i){
            sprintf(nome, "deck%dcard%d", deck_atual, i);
            W.delete_integer(nome);
          }
        }
    }
  }
 LOOP_END:
  return;
}

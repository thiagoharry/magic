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

#include "escolhe.h"

#define ALEATORIO 0
#define NOVO      1
//static int escolha;

static struct interface *aleatorio, *novo, *selecao;
static struct interface *salvos[10];
static int numero_de_opcoes, deck_selecionado;
static int baralhos_existentes[10];

static int apagando, apagados;

MAIN_LOOP escolhe(void){
 LOOP_INIT:
  apagando = -1;
  apagados = 0;
  numero_de_opcoes = 0;
  { // Descobre quantos botões são
    bool ret;
    int i;
    for(i = 0; i < 10; i ++){
      salvos[i] = NULL;
      int carta_atual;
      char nome_atual[16];
      snprintf(nome_atual, 16, "deck%dcard0", i);
      ret = W.read_integer(nome_atual, &carta_atual);
      if(ret){
        baralhos_existentes[numero_de_opcoes] = i;
        numero_de_opcoes ++;
      }
    }
    numero_de_opcoes += 2;
  }
  aleatorio = W.new_interface(1, 0.5 * W.width,
                              (1.0 - 1.0/((float) numero_de_opcoes + 1)) *
                               W.height,
                              W.width, W.height / 9,
                              "arquiinimigo/aleatorio.gif");
  { // Criando botão para decks pré-montados
    int i, j;
    for(i = 0; i < numero_de_opcoes - 2; i ++){
      salvos[i] = W.new_interface(5, 0.5 * W.width,
                                  (1.0 - ((float) i + 2)/
                                   ((float) numero_de_opcoes + 1)) *
                                  W.height,
                                  W.width, W.height / 9,
                                  "arquiinimigo/baralho.gif");
      for(j = 0; j < 20; j ++){
        char nome[32];
        int num = 0;
        struct interface *tmp;
        snprintf(nome, 32, "deck%dcard%d", baralhos_existentes[i], j);
        W.read_integer(nome, &num);
        if(num < 1 || num > 70) num = 1;
        snprintf(nome, 32, "arquiinimigo/%d_pequeno.gif", num);
        tmp = W.new_interface(5, W.width * (0.048 * j + 0.025),
                              salvos[i] -> y,
                              0.036 * W.width, 0.08 * W.height,
                              nome);
        tmp -> integer = 2;
      }
    }
  }
  novo = W.new_interface(1, 0.5 * W.width,
                         1.0/((float) numero_de_opcoes + 1) * W.height,
                              W.width, W.height / 9, "arquiinimigo/novo.gif");
  if(numero_de_opcoes > 10)
    novo -> visible = false;
  selecao = W.new_interface(W_INTERFACE_PERIMETER, 0, 0, W.width, W.height / 9,
                            1.0, 1.0, 0.0, 1.0);
  selecao -> visible = false;
 LOOP_BODY:
  deck_selecionado = -1;
  if(W.keyboard[W_ESC])
    Wloop(intro);
  selecao -> visible = false;
  if(W.mouse.y > aleatorio -> y - aleatorio -> height / 2 &&
     W.mouse.y < aleatorio -> y + aleatorio -> height / 2){
    W.move_interface(selecao, aleatorio -> x, aleatorio -> y);
    selecao -> visible = true;
  }
  else if(W.mouse.y > novo -> y - novo -> height / 2 &&
     W.mouse.y < novo -> y + novo -> height / 2){
    W.move_interface(selecao, novo -> x, novo -> y);
    selecao -> visible = true;
  }
  else{
    int i;
    for(i = 0; i < numero_de_opcoes - 2; i ++){//XXX
      if(W.mouse.y > salvos[i] -> y - salvos[i] -> height / 2 &&
         W.mouse.y < salvos[i] -> y + salvos[i] -> height / 2){
        W.move_interface(selecao, salvos[i] -> x, salvos[i] -> y);
        selecao -> visible = true;
        deck_selecionado = i;
      }
    }
  }
  if(W.mouse.buttons[W_MOUSE_LEFT] == 1 || W.mouse.buttons[W_MOUSE_LEFT] == -1){
    if(selecao -> visible){
      if(deck_selecionado >= 0){
        int i;
        char nome[16];
        if(W.mouse.x > 0.96 * W.width){
          apagando = deck_selecionado;
          salvos[deck_selecionado] -> visible = false;
          novo -> visible = false;
          aleatorio -> visible = false;
          apagados = 0;
        }
        else{
          W.game -> baralho_proprio = true;
          for(i = 0; i < 20; i ++){
            snprintf(nome, 16, "deck%dcard%d",
                    baralhos_existentes[deck_selecionado], i);
            W.read_integer(nome, &(W.game -> baralho_arquiinimigo[i]));
          }
          //printf("Selecionado %d\n", deck_selecionado);
          Wloop(arquiinimigo);
        }
      }
      else if(selecao -> y == aleatorio -> y){
        W.game -> baralho_proprio = false;
        Wloop(arquiinimigo); // Aleatório
      }
      else if(selecao -> y == novo -> y){
        W.game -> baralho_proprio = true;
        Wloop(baralho);
      }
    }
  }
  if(apagando >= 0){
    char nome[16];
    snprintf(nome, 16, "deck%dcard%d", baralhos_existentes[apagando], apagados);
    W.delete_integer(nome); // XXX
    apagados ++;
    if(apagados == 20){
      Wloop(escolhe);
    }
  }
 LOOP_END:
  return;
}

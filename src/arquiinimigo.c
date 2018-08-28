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

#include "arquiinimigo.h"

static struct interface *digitos[2];
static struct interface *carta_atual = NULL, *nome_atual, *texto_atual;
static struct interface *plano, *plano_em_andamento, *destaque;
static struct interface *imagens_em_andamento[20][2];
static struct sound *som_compra;
// qubodup (OpengameArt)
static struct sound *clique;


static bool cartas[140];
static int planos_em_andamento;
static int em_andamento[] = {15, 18, 29, 32, 33, 41, 48, 50, 51, 53, 61, 62};

MAIN_LOOP arquiinimigo(void){
 LOOP_INIT:
  {
    int i, j;
    for(i = 0; i < 140; i ++)
      cartas[i] = false;
    for(i = 0; i < 20; i ++)
      for(j = 0; j < 2; j ++)
      imagens_em_andamento[i][j] = NULL;
  }
  if(W.game -> baralho_proprio)
    embaralha_arquiinimigo();
  som_compra = W.new_sound("caos.wav");
  clique = W.new_sound("click.wav");
  planos_em_andamento = 0;
  destaque = NULL;
  plano = W.new_interface(5, W.width / 4, 0.392 * W.height,
                          0.05 * W.width, 0.05 * W.height,
                          "arquiinimigo/plano.gif");
  plano -> integer = 5;
  plano -> visible = false;
  plano_em_andamento = W.new_interface(5, W.width / 4, 0.392 * W.height,
                                       0.15 * W.width, 0.05 * W.height,
                          "arquiinimigo/plano_em_andamento.gif");
  plano_em_andamento -> integer = 5;
  plano_em_andamento -> visible = false;
  digitos[0] = W.new_interface(9, 37.75 * W.width / 40, 19 * W.height / 20,
                               W.width / 20, W.height / 10,
                               "digitos.gif");
  digitos[1] = W.new_interface(9, 39 * W.width / 40, 19 * W.height / 20,
                               W.width / 20, W.height / 10,
                               "digitos.gif");
  digitos[0] -> integer = 4;
  digitos[0] -> r = digitos[0] -> g = digitos[0] -> b =  digitos[0] -> a = 1.0;
  digitos[1] -> integer = 0;
  digitos[1] -> r = digitos[1] -> g = digitos[1] -> b =  digitos[1] -> a = 1.0;
 LOOP_BODY:
  if(W.keyboard[W_ESC])
    Wloop(intro);
  else if(W.keyboard[W_SPACEBAR] == 1)
    Wsubloop(vida);
  if(W.keyboard[W_LEFT] == 1){
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
  else if(W.keyboard[W_RIGHT] == 1){
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
  else if(W.keyboard[W_ENTER] == 1){
    if(carta_atual == NULL){
      W.play_sound(som_compra);
      compra_arquiinimigo(&carta_atual, &nome_atual, &texto_atual);
    }
    else{
      W.destroy_interface(texto_atual);
      W.destroy_interface(nome_atual);
      W.destroy_interface(carta_atual);
      carta_atual = NULL;
      plano_em_andamento -> visible = false;
      plano -> visible = false;
    }
  }
  if(W.mouse.x < 0.9 * W.width && carta_atual == NULL){
    int line, col, position;
    col = 5.5555 * W.mouse.x / W.width;
    line = 4.0 * W.mouse.y / W.height;
    position = 5 * line + col;
    if(imagens_em_andamento[position][0] != NULL)
      imagens_em_andamento[position][1] -> visible = true;
    if(destaque != imagens_em_andamento[position][1]){
      if(destaque != NULL)
        destaque -> visible = false;
      destaque = imagens_em_andamento[position][1];
    }
    if(W.mouse.buttons[W_MOUSE_LEFT] == 1 ||
       W.mouse.buttons[W_MOUSE_LEFT] == -1){
      if(position >= 0 && position < 20 &&
         imagens_em_andamento[position][0] != NULL){
        planos_em_andamento --;
        if(W.game -> baralho_proprio){
          int i;
          for(i = 19; i >= 0; i --)
            if(W.game -> baralho_arquiinimigo[i] != 0)
              break;
          W.game -> baralho_arquiinimigo[i + 1] =
            ((int) (imagens_em_andamento[position][0] -> r)) / 2 + 1;
          printf("Devolveu %d em %d.\n",
                 W.game -> baralho_arquiinimigo[i + 1], i + 1);
        }
        cartas[(int) (imagens_em_andamento[position][0] -> r)] = false;
        W.destroy_interface(imagens_em_andamento[position][1]);
        W.destroy_interface(imagens_em_andamento[position][0]);
        imagens_em_andamento[position][0] = NULL;
        imagens_em_andamento[position][1] = NULL;
        destaque = NULL;
      }
    }
  }
 LOOP_END:
  return;
}

void compra_arquiinimigo(struct interface **carta,
                         struct interface **nome_carta,
                         struct interface **texto){
  int compra, i;
  bool terminou = false;
  char nome[32];
  if(planos_em_andamento == 20 && W.game -> baralho_proprio)
    return;
  while(!terminou){
    if(!W.game -> baralho_proprio)
      do{
        compra = W.random() % 140;
      }while(cartas[compra]);
    else{
      do{
        compra = W.game -> baralho_arquiinimigo[0];
        for(i = 0; i < 19; i ++)
          W.game -> baralho_arquiinimigo[i] =
            W.game -> baralho_arquiinimigo[i+1];
        W.game -> baralho_arquiinimigo[19] = 0;
      }while(compra == 0);
      compra = (compra - 1) * 2;
    }
    if(eh_plano_em_andamento(compra / 2 + 1)){
      if(planos_em_andamento < 20){
        cartas[compra] = true;
        planos_em_andamento ++;
        terminou = true;
        plano_em_andamento -> visible = true;
        for(i = 0; i < 20; i ++){
          if(imagens_em_andamento[i][0] == NULL){
            sprintf(nome, "arquiinimigo/%d_medio.gif", compra / 2 + 1);
            imagens_em_andamento[i][0] =
              W.new_interface(W_INTERFACE_IMAGE,
                              W.width * (0.18 * (i % 5) + 0.09),
                              W.height * (0.25 * (i / 5)  + 0.125),
                              0.18 * W.width, 0.25 * W.height,
                              nome);
            sprintf(nome, "arquiinimigo/%d_texto.gif", compra / 2 + 1);
            imagens_em_andamento[i][1] =
              W.new_interface(5,
                              W.width * (0.18 * (i % 5) + 0.09),
                              W.height * (0.25 * (i / 5)  + 0.125),
                              0.18 * W.width, 0.21 * W.height,
                              nome);
            imagens_em_andamento[i][0] -> integer = 2;
            imagens_em_andamento[i][1] -> integer = 3;
            imagens_em_andamento[i][1] -> visible = false;
            imagens_em_andamento[i][0] -> r = (float) compra;
            break;
          }
        }
        break;
      }
    }
    else{
      terminou = true;
      if(W.game -> baralho_proprio){
        int j;
        for(j = 19; j >= 0; j --)
          if(W.game -> baralho_arquiinimigo[j] != 0)
            break;
        j ++;
        W.game -> baralho_arquiinimigo[j] = compra / 2 + 1;
      }
    }
  }
  if(!plano_em_andamento -> visible)
    plano -> visible = true;
  compra /= 2;
  compra ++;
  sprintf(nome, "arquiinimigo/%d.gif", compra);
  *carta = W.new_interface(1,
                          W.width / 4, W.height / 2,
                          W.width / 2, W.height,
                          nome);
  (*carta) -> integer = 4;

  sprintf(nome, "arquiinimigo/%d_nome.gif", compra);
    *nome_carta = W.new_interface(5, W.width / 4, 39 * W.height / 40,
                                W.width / 3, W.height / 20,
                                nome);
  (*nome_carta) -> integer = 5;

  sprintf(nome, "arquiinimigo/%d_texto.gif", compra);
  *texto = W.new_interface(5, W.width / 4, 8 * W.height / 40,
                           0.95 * W.width / 2, W.height / 3,
                           nome);
                           (*texto) -> integer = 5;
  //(*carta) -> visible = false;
}

bool eh_plano_em_andamento(int num){
  int i;
  for(i = 0; i < 12; i ++)
    if(em_andamento[i] == num)
      return true;
  return false;
}

void embaralha_arquiinimigo(void){
  int i, j;
  int buffer[20];
  for(i = 0; i < 20; i ++){
    int escolha = W.random() % (20 - i);
    buffer[i] = W.game -> baralho_arquiinimigo[escolha];
    for(j = escolha; j < 19-i; j ++)
      W.game -> baralho_arquiinimigo[j] =
        W.game -> baralho_arquiinimigo[j+1];
  }
  for(i = 0; i < 20; i ++)
    W.game -> baralho_arquiinimigo[i] = buffer[i];
}

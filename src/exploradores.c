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

#include "exploradores.h"

static struct interface *tabuleiro;
static struct interface *custo6[4], *custo3[10], *custo1[16];
static struct sound *som_revela, *som_cancela;
static bool escolhe_cor;
static int cor_escolhida;

static void muda_cor(struct interface *i, int cor){
  switch(cor){
  case 1:
    i -> r = 1.0;
    i -> g = 0.0;
    i -> b = 0.0;
    break;
  case 2:
    i -> r = 0.0;
    i -> g = 1.0;
    i -> b = 0.0;
    break;
  case 3:
    i -> r = 0.0;
    i -> g = 0.0;
    i -> b = 1.0;
    break;
  case 4:
    i -> r = 1.0;
    i -> g = 1.0;
    i -> b = 0.0;
    break;
  default:
    i -> r = 1.0;
    i -> g = 1.0;
    i -> b = 1.0;
    break;
  }
}

static void incrementa_cor(struct interface *i){
  if(i -> r == 1.0 && i -> g == 1.0 && i -> b == 1.0){
    i -> r = 1.0;
    i -> g = 0.0;
    i -> b = 0.0;
  }
  else if(i -> r == 1.0 && i -> g == 0.0 && i -> b == 0.0){
    i -> r = 0.0;
    i -> g = 1.0;
    i -> b = 0.0;
  }
  else if(i -> r == 0.0 && i -> g == 1.0 && i -> b == 0.0){
    i -> r = 0.0;
    i -> g = 0.0;
    i -> b = 1.0;
  }
  else if(i -> r == 0.0 && i -> g == 0.0 && i -> b == 1.0){
    i -> r = 1.0;
    i -> g = 1.0;
    i -> b = 0.0;
  }
  else{
    i -> r = 1.0;
    i -> g = 1.0;
    i -> b = 1.0;
  }
}

MAIN_LOOP exploradores(void){
 LOOP_INIT:
  tabuleiro = W.new_interface(W_INTERFACE_IMAGE, W.width / 2, W.height / 2,
                              1.082 * W.height, W.height,
                              "exploradores/tabuleiro.gif");
  som_revela = W.new_sound("caos.wav");
  som_cancela = W.new_sound("fail.wav");
  { // Gerando as cartas de custo 6: 4 de 6 possibilidades
    int cartas_restantes = 6;
    int todas_as_cartas[6] = {1, 2, 3, 4, 5, 6};
    int cartas_finais[4];
    int i, j;
    char nome[32];
    for(i = 0; i < 4; i ++){
      j = W.random() % cartas_restantes;
      cartas_finais[6 - cartas_restantes] = todas_as_cartas[j];
      for(; j < cartas_restantes - 1; j ++)
        todas_as_cartas[j] = todas_as_cartas[j + 1];
      cartas_restantes --;
    }
    // Uma das cartas é Orazca
    cartas_finais[W.random() % 4] = 0;
    sprintf(nome, "exploradores/3-%d.gif", cartas_finais[0]);
    custo6[0] = W.new_interface(5, W.width / 2 - 0.144 * W.height,
                                W.height / 2 - 0.001 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/3-%d.gif", cartas_finais[1]);
    custo6[1] = W.new_interface(5, W.width / 2 + 0.144 * W.height,
                                W.height / 2 + 0.017 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/3-%d.gif", cartas_finais[2]);
    custo6[2] = W.new_interface(5, W.width / 2 - 0.005 * W.height,
                                W.height / 2 + 0.088 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/3-%d.gif", cartas_finais[3]);
    custo6[3] = W.new_interface(5, W.width / 2 + 0.004 * W.height,
                                W.height / 2 - 0.075 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    for( i = 0; i < 4; i ++){
      custo6[i] -> r = 1.0;
      custo6[i] -> g = 1.0;
      custo6[i] -> b = 1.0;
      custo6[i] -> a = 0.0;
      custo6[i] -> integer = 7;
    }
  }
  { // Gerando cartas de custo 3: 10 de 18 possibilidades
    int cartas_restantes = 18;
    int todas_as_cartas[18] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                               11, 12, 13, 14, 15, 16, 17};
    int cartas_finais[10];
    int i, j;
    char nome[32];
    for(i = 0; i < 10; i ++){
      j = W.random() % cartas_restantes;
      cartas_finais[18 - cartas_restantes] = todas_as_cartas[j];
      for(; j < cartas_restantes - 1; j ++)
        todas_as_cartas[j] = todas_as_cartas[j + 1];
      cartas_restantes --;
    }
    sprintf(nome, "exploradores/2-%d.gif", cartas_finais[0]);
    custo3[0] = W.new_interface(5, W.width / 2 - 0.29 * W.height,
                                W.height / 2 + 0.072 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/2-%d.gif", cartas_finais[1]);
    custo3[1] = W.new_interface(5, W.width / 2 - 0.28 * W.height,
                                W.height / 2 - 0.092 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/2-%d.gif", cartas_finais[2]);
    custo3[2] = W.new_interface(5, W.width / 2 + 0.29 * W.height,
                                W.height / 2 - 0.057 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/2-%d.gif", cartas_finais[3]);
    custo3[3] = W.new_interface(5, W.width / 2 + 0.28 * W.height,
                                W.height / 2 + 0.108 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/2-%d.gif", cartas_finais[4]);
    custo3[4] = W.new_interface(5, W.width / 2 + 0.134 * W.height,
                                W.height / 2 + 0.18 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/2-%d.gif", cartas_finais[5]);
    custo3[5] = W.new_interface(5, W.width / 2 + 0.154 * W.height,
                                W.height / 2 - 0.147 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/2-%d.gif", cartas_finais[6]);
    custo3[6] = W.new_interface(5, W.width / 2 - 0.133 * W.height,
                                W.height / 2 - 0.166 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/2-%d.gif", cartas_finais[7]);
    custo3[7] = W.new_interface(5, W.width / 2 - 0.151 * W.height,
                                W.height / 2 + 0.162 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/2-%d.gif", cartas_finais[8]);
    custo3[8] = W.new_interface(5, W.width / 2 - 0.015 * W.height,
                                W.height / 2 + 0.252 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    sprintf(nome, "exploradores/2-%d.gif", cartas_finais[9]);
    custo3[9] = W.new_interface(5, W.width / 2 + 0.015 * W.height,
                                W.height / 2 - 0.24 * W.height,
                                0.1927 * W.height, 0.1719 * W.height,
                                nome);
    for( i = 0; i < 10; i ++){
        custo3[i] -> r = 1.0;
        custo3[i] -> g = 1.0;
        custo3[i] -> b = 1.0;
        custo3[i] -> a = 0.0;
        custo3[i] -> integer = 7;
    }
  }
  { // Gerando cartas de custo 1: 16 de 25 possibilidades
    int cartas_restantes = 25;
    int todas_as_cartas[25] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                               11, 12, 13, 14, 15, 16, 17, 18, 19,
                               20, 21, 22, 23, 24};
    int cartas_finais[16];
    int i, j;
    float offset_x, offset_y;
    char nome[32];
    for(i = 0; i < 16; i ++){
      j = W.random() % cartas_restantes;
      cartas_finais[25 - cartas_restantes] = todas_as_cartas[j];
      for(; j < cartas_restantes - 1; j ++)
        todas_as_cartas[j] = todas_as_cartas[j + 1];
      cartas_restantes --;
    }
    offset_x = 0.148;
    offset_y = -0.073;
    for(i = 0 ; i < 4; i ++){
      sprintf(nome, "exploradores/1-%d.gif", cartas_finais[i]);
      custo1[i] = W.new_interface(5,
                                  W.width / 2 + (- 0.024 + i * offset_x) *
                                  W.height,
                                  W.height / 2 + (0.415 + i * offset_y) *
                                  W.height,
                                  0.1927 * W.height, 0.1719 * W.height,
                                  nome);
      sprintf(nome, "exploradores/1-%d.gif", cartas_finais[i+4]);
      custo1[i+4] = W.new_interface(5,
                                    W.width / 2 + (- 0.416 + i * offset_x) *
                                    W.height,
                                    W.height / 2 + (-0.185 + i * offset_y) *
                                    W.height,
                                    0.1927 * W.height, 0.1719 * W.height,
                                    nome);
    }
    offset_y = 0.09;
    offset_x = 0.136;
    for(i = 0; i < 3; i ++){
      sprintf(nome, "exploradores/1-%d.gif", cartas_finais[i+8]);
      custo1[i+8] = W.new_interface(5,
                                  W.width / 2 + (- 0.435 + i * offset_x) *
                                  W.height,
                                  W.height / 2 + (0.145 + i * offset_y) *
                                  W.height,
                                  0.1927 * W.height, 0.1719 * W.height,
                                  nome);
      sprintf(nome, "exploradores/1-%d.gif", cartas_finais[i+11]);
      custo1[i+11] = W.new_interface(5,
                                     W.width / 2 + (0.166 + i * offset_x) *
                                     W.height,
                                     W.height / 2 + (-0.313 + i * offset_y) *
                                     W.height,
                                     0.1927 * W.height, 0.1719 * W.height,
                                     nome);
    }
    sprintf(nome, "exploradores/1-%d.gif", cartas_finais[14]);
    custo1[14] = W.new_interface(5,
                                 W.width / 2 - 0.428 *  W.height,
                                 W.height / 2 - 0.02 *  W.height,
                                  0.1927 * W.height, 0.1719 * W.height,
                                  nome);
    sprintf(nome, "exploradores/1-%d.gif", cartas_finais[15]);
    custo1[15] = W.new_interface(5,
                                 W.width / 2 + 0.428 *  W.height,
                                 W.height / 2 + 0.03 *  W.height,
                                  0.1927 * W.height, 0.1719 * W.height,
                                  nome);
    for( i = 0; i < 16; i ++){
        custo1[i] -> r = 1.0;
        custo1[i] -> g = 1.0;
        custo1[i] -> b = 1.0;
        custo1[i] -> a = 0.0;
        custo1[i] -> integer = 7;
    }
  }
 LOOP_BODY:
  escolhe_cor = false;
  cor_escolhida = 0;
  if(W.keyboard[W_ESC])
    Wloop(intro);
  else if(W.keyboard[W_SPACEBAR] == 1)
    Wsubloop(vida);
  else if(W.keyboard[W_0] == 1){
    escolhe_cor = true;
    cor_escolhida = 0;
  }
  else if(W.keyboard[W_1] == 1){
    escolhe_cor = true;
    cor_escolhida = 1;
  }
  else if(W.keyboard[W_2] == 1){
    escolhe_cor = true;
    cor_escolhida = 2;
  }
  else if(W.keyboard[W_3] == 1){
    escolhe_cor = true;
    cor_escolhida = 3;
  }
  else if(W.keyboard[W_4] == 1){
    escolhe_cor = true;
    cor_escolhida = 4;
  }
  if(W.mouse.buttons[W_MOUSE_LEFT] == 1 ||
          W.mouse.buttons[W_MOUSE_LEFT] == -1){
    int i;
    float radius = custo6[0] -> width * 0.35;
    for(i = 0; i < 16; i ++){
      if(i < 4 && W.mouse.x > custo6[i] -> x - radius &&
         W.mouse.x < custo6[i] -> x + radius &&
         W.mouse.y > custo6[i] -> y - radius &&
         W.mouse.y < custo6[i] -> y + radius){
        if(custo6[i] -> a == 0.0){
          custo6[i] -> a = 0.2;
          W.play_sound(som_revela);
        }
        else if(custo6[i] -> a != 1.0){
          custo6[i] -> r = 0.0;
          custo6[i] -> g = 0.0;
          custo6[i] -> b = 0.0;
          custo6[i] -> a = 1.0;
        }
        else{
          custo6[i] -> r = 1.0;
          custo6[i] -> g = 1.0;
          custo6[i] -> b = 1.0;
          custo6[i] -> a = 0.0;
          W.play_sound(som_cancela);
        }
        break;
      }
      if(i < 10 && W.mouse.x > custo3[i] -> x - radius &&
         W.mouse.x < custo3[i] -> x + radius &&
         W.mouse.y > custo3[i] -> y - radius &&
         W.mouse.y < custo3[i] -> y + radius){
        if(custo3[i] -> a == 0.0){
          custo3[i] -> a = 0.2;
          W.play_sound(som_revela);
        }
        else if(custo3[i] -> a != 1.0){
          custo3[i] -> r = 0.0;
          custo3[i] -> g = 0.0;
          custo3[i] -> b = 0.0;
          custo3[i] -> a = 1.0;
        }
        else{
          custo3[i] -> r = 1.0;
          custo3[i] -> g = 1.0;
          custo3[i] -> b = 1.0;
          custo3[i] -> a = 0.0;
          W.play_sound(som_cancela);
        }
        break;
      }
      if(W.mouse.x > custo1[i] -> x - radius &&
         W.mouse.x < custo1[i] -> x + radius &&
         W.mouse.y > custo1[i] -> y - radius &&
         W.mouse.y < custo1[i] -> y + radius){
        if(custo1[i] -> a == 0.0){
          custo1[i] -> a = 0.2;
          W.play_sound(som_revela);
        }
        else if(custo1[i] -> a != 1.0){
          custo1[i] -> r = 0.0;
          custo1[i] -> g = 0.0;
          custo1[i] -> b = 0.0;
          custo1[i] -> a = 1.0;
        }
        else{
          custo1[i] -> r = 1.0;
          custo1[i] -> g = 1.0;
          custo1[i] -> b = 1.0;
          custo1[i] -> a = 0.0;
          W.play_sound(som_cancela);
        }
        break;
      }
    }
  }
  else if(escolhe_cor || W.mouse.buttons[W_MOUSE_RIGHT] == 1 ||
          W.mouse.buttons[W_MOUSE_RIGHT] == -1){
    int i;
    float radius = custo6[0] -> width * 0.35;
    for(i = 0; i < 16; i ++){
      if(i < 4 && W.mouse.x > custo6[i] -> x - radius &&
         W.mouse.x < custo6[i] -> x + radius &&
         W.mouse.y > custo6[i] -> y - radius &&
         W.mouse.y < custo6[i] -> y + radius){
        if(custo6[i] -> a != 1.0){
          if(escolhe_cor)
            muda_cor(custo6[i], cor_escolhida);
          else
            incrementa_cor(custo6[i]);
        }
        break;
      }
      if(i < 10 && W.mouse.x > custo3[i] -> x - radius &&
         W.mouse.x < custo3[i] -> x + radius &&
         W.mouse.y > custo3[i] -> y - radius &&
         W.mouse.y < custo3[i] -> y + radius){
        if(custo3[i] -> a != 1.0){
          if(escolhe_cor)
            muda_cor(custo3[i], cor_escolhida);
          else
            incrementa_cor(custo3[i]);
        }
        break;
      }
      if(W.mouse.x > custo1[i] -> x - radius &&
         W.mouse.x < custo1[i] -> x + radius &&
         W.mouse.y > custo1[i] -> y - radius &&
         W.mouse.y < custo1[i] -> y + radius){
        if(custo1[i] -> a != 1.0){
          if(escolhe_cor)
            muda_cor(custo1[i], cor_escolhida);
          else
            incrementa_cor(custo1[i]);
        }
        break;
      }
    }
  }
 LOOP_END:
  return;
}

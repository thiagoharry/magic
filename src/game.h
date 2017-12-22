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

#ifndef _game_h_
#define _game_h_

#include "weaver/weaver.h"
#include "includes.h"

#define N 77

extern const char *nomes[];

struct _game_struct{
  // You can personalize this struct putting your variables here. But
  // don't change it's name. Access it in W.game variable.
  int mapa[7][7];
  bool modo_mapa, pode_mudar;
  int proximo[10];
  int probabilidade_fenomeno;
  bool aether_caotico, fusao_espacial, tunel_interplanar;
  bool baralho_proprio;
  int baralho_arquiinimigo[20];
  int numero_de_jogadores;
  int vida_de_jogadores[4];
  int veneno_de_jogadores[4];
  int avatar_de_jogadores[4];
  bool modo_jogo;
} _game;

void gera_vizinhanca(void);
struct interface *obtem_medio(int, float, float, int);
int gera_carta(void);

MAIN_LOOP main_loop(void);
MAIN_LOOP intro(void);

#endif

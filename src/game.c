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

#include "game.h"

const char *nomes[] = {"bant.gif", "grixis.gif", "naya.gif",
                       "maelstrom.gif", "rios.gif", "piscinas.gif",
                       "tolaria.gif", "vesuva.gif", "krosa.gif",
                       "llanowar.gif", "otaria.gif", "shiv.gif",
                       "nevoa.gif", "turri.gif", "chamine.gif",
                       "skybreen.gif", "minamo.gif", "sokenzan.gif",
                       "profundezas.gif", "tember.gif", "prado.gif",
                       "floresta.gif", "velis.gif", "recife.gif",
                       "mercado.gif", "bacia.gif", "panopticon.gif",
                       "campos.gif", "alimentacao.gif", "quarta.gif",
                       "galhos.gif", "areia.gif", "fornalha.gif",
                       "agyrem.gif", "vapor.gif", "submundo.gif",
                       "hipodromo.gif", "serra.gif", "selvagens.gif",
                       "toca.gif", "baronato.gif", "immersturm.gif",
                       "naar.gif", "murasa.gif", "tazeem.gif",
                       "akoum.gif", "aretopolis.gif", "astral.gif",
                       "bastiao.gif", "belenon.gif", "camada.gif",
                       "gavony.gif", "glen.gif", "ossuario.gif",
                       "bosque.gif", "edros.gif", "jund.gif",
                       "kessig.gif", "campa.gif", "distrito.gif",
                       "lar.gif", "monte.gif", "nephalia.gif",
                       "norn.gif", "onakke.gif", "orochi.gif",
                       "prahv.gif", "mercurio.gif", "jardim.gif",
                       "escadas.gif", "stensia.gif", "takenuma.gif",
                       "portao.gif", "zefiro.gif", "trilha.gif",
                       "selva.gif", "palacio.gif"};

static struct interface *fundo, *mapa, *classico, *selecao, *fundo_sobreposto;
static struct interface *arqui, *explora, *marca_vida, *embaralhador;
static struct interface *caos1, *caos2, *caos3, *caos4;
static int num, carta, carta_anterior, carta_sobreposta;
static struct sound *fail, *success, *som_caos;
static bool usa_escada;

struct interface *obtem_caos(int n){
  char nome[256];
  size_t nome_size = strlen(nomes[n]);
  memcpy(nome, nomes[n], nome_size);
  nome_size -= 4;
  memcpy(&nome[nome_size], "_caos.gif", 10);
  return W.new_interface(8, W.width / 2, W.height / 2,
                         W.width, 40, nome);
}

void apaga_caos(void){
  caos1 -> visible = false;
  if(caos2 != NULL)
    caos2 -> visible = false;
  if(caos3 != NULL)
    caos3 -> visible = false;
  if(caos4 != NULL)
    caos4 -> visible = false;
  if(usa_escada){
    usa_escada = false;
    Wsubloop(escada);
  }
}

void nao_treme(void){
  fundo -> integer = 0;
  if(W.game -> fusao_espacial)
    fundo_sobreposto -> integer = 0;
}

MAIN_LOOP intro(void){ // The game loop
 LOOP_INIT: // Code executed during loop initialization
  embaralhador = W.new_interface(W_INTERFACE_IMAGE, 0.167 * W.width,
                                 0.75 * W.height,
                                 W.width / 4, W.height / 3, "embaralhador.gif");
  marca_vida = W.new_interface(W_INTERFACE_IMAGE, 0.5 * W.width,
                               0.75 * W.height,
                               W.width / 4, W.height / 3, "vida.gif");
  explora = W.new_interface(W_INTERFACE_IMAGE, 0.833 * W.width,
                            0.75 * W.height,
                            W.width / 4, W.height / 3, "exploradores.gif");
  arqui = W.new_interface(W_INTERFACE_IMAGE, W.width / 6, 0.25 * W.height,
                                 W.width / 4, W.height / 3, "arquiinimigo.gif");
  mapa = W.new_interface(W_INTERFACE_IMAGE, 5 * W.width / 6, 0.25 * W.height,
                         W.width / 4, W.height / 3, "mapa.gif");
  classico = W.new_interface(W_INTERFACE_IMAGE, W.width / 2, 0.25 * W.height,
                             W.width / 4, W.height / 3, "classico.gif");
  selecao = W.new_interface(W_INTERFACE_PERIMETER, 3 * W.width / 4, W.height / 2,
                            W.width / 3 - 2, W.height / 2 - 2,
                            1.0, 1.0, 0.0, 1.0);
  selecao -> visible = false;
  usa_escada = false;
  {
    int i;
    for(i = 0; i < 10; i ++)
      W.game -> proximo[i] = -1;
  }
 LOOP_BODY: // Code executed every loop iteration
  W.game -> numero_de_jogadores = 0;
#if W_TARGET == W_ELF
  if(W.keyboard[W_ESC]){
    Wexit_loop();
  }
#endif
  if((W.mouse.buttons[W_MOUSE_LEFT] == 1 ||
           W.mouse.buttons[W_MOUSE_LEFT] == -1) && selecao -> visible){
    if(selecao -> x == arqui -> x && selecao -> y == arqui -> y){
      W.game -> modo_jogo = true;
      Wloop(escolhe); // Arqui-inimigo
    }
    else if(selecao -> x == mapa -> x && selecao -> y == mapa -> y){
      W.game -> modo_jogo = true;
      Wloop(main_loop);
    }
    else if(selecao -> x == classico -> x && selecao -> y == classico -> y){
      W.game -> modo_jogo = true;
      Wloop(main_loop); // Planechase
    }
    else if(selecao -> x == explora -> x && selecao -> y == explora -> y){
      W.game -> modo_jogo = true;
      Wloop(exploradores);
    }
    else if(selecao -> x == marca_vida -> x &&
            selecao -> y == marca_vida -> y){
      W.game -> modo_jogo = false;
      Wsubloop(vida);
    }
    else if(selecao -> x == embaralhador -> x &&
            selecao -> y == embaralhador -> y){
      W.game -> modo_jogo = false;
      Wsubloop(menu_embaralha);
    }
  }
  if(W.mouse.x > classico -> x - classico -> width / 2 &&
     W.mouse.x < classico -> x + classico -> width / 2 &&
     W.mouse.y > classico -> y - classico -> height / 2 &&
     W.mouse.y < classico -> y + classico -> height / 2){
    W.move_interface(selecao, classico -> x, classico -> y);
    W.game -> modo_mapa = false;
    selecao -> visible = true;
  }
  else if(W.mouse.x > mapa -> x - mapa -> width / 2 &&
          W.mouse.x < mapa -> x + mapa -> width / 2 &&
          W.mouse.y > mapa -> y - mapa -> height / 2 &&
          W.mouse.y < mapa -> y + mapa -> height / 2){
    W.move_interface(selecao, mapa -> x, mapa -> y);
    W.game -> modo_mapa = true;
    selecao -> visible = true;
  }
  else if(W.mouse.x > arqui -> x - arqui -> width / 2 &&
          W.mouse.x < arqui -> x + arqui -> width / 2 &&
          W.mouse.y > arqui -> y - arqui -> height / 2 &&
          W.mouse.y < arqui -> y + arqui -> height / 2){
    W.move_interface(selecao, arqui -> x, arqui -> y);
    selecao -> visible = true;
  }
  else if(W.mouse.x > explora -> x - explora -> width / 2 &&
          W.mouse.x < explora -> x + explora -> width / 2 &&
          W.mouse.y > explora -> y - explora -> height / 2 &&
          W.mouse.y < explora -> y + explora -> height / 2){
    W.move_interface(selecao, explora -> x, explora -> y);
    selecao -> visible = true;
  }
  else if(W.mouse.x > marca_vida -> x - marca_vida -> width / 2 &&
          W.mouse.x < marca_vida -> x + marca_vida -> width / 2 &&
          W.mouse.y > marca_vida -> y - marca_vida -> height / 2 &&
          W.mouse.y < marca_vida -> y + marca_vida -> height / 2){
    W.move_interface(selecao, marca_vida -> x, marca_vida -> y);
    selecao -> visible = true;
  }
  else if(W.mouse.x > embaralhador -> x - embaralhador -> width / 2 &&
          W.mouse.x < embaralhador -> x + embaralhador -> width / 2 &&
          W.mouse.y > embaralhador -> y - embaralhador -> height / 2 &&
          W.mouse.y < embaralhador -> y + embaralhador -> height / 2){
    W.move_interface(selecao, embaralhador -> x, embaralhador -> y);
    selecao -> visible = true;
  }
  else{
    selecao -> visible = false;
  }
 LOOP_END: // Code executed at the end of the loop
  return;
}

MAIN_LOOP main_loop(void){ // The game loop
 LOOP_INIT: // Code executed during loop initialization
  fail = W.new_sound("fail.wav");
  success = W.new_sound("success.wav");
  som_caos = W.new_sound("caos.wav");
  W.game -> probabilidade_fenomeno = W.random() % 2000 + 1;
  W.game -> aether_caotico = false;
  W.game -> fusao_espacial = false;
  W.game -> tunel_interplanar = false;
  usa_escada = false;
  carta_anterior = -1;
  carta = W.random() % N;
  caos1 = obtem_caos(carta);
  caos2 = caos3 = caos4 = NULL;
  fundo = W.new_interface(1, W.width / 2, W.height / 2,
                          W.width, W.height,
                         nomes[carta]);
  fundo_sobreposto = NULL;
  apaga_caos();
  W.game -> pode_mudar = false;
  if(W.game -> modo_mapa){
    int i, j;
    for(i = 0; i < 7; i ++)
      for(j = 0; j < 7; j ++)
        W.game -> mapa[i][j] = -1;
    W.game -> mapa[3][3] = carta;
    gera_vizinhanca();
  }
  {
    int i;
    for(i = 0; i < 10; i ++)
      W.game -> proximo[i] = -1;
  }
 LOOP_BODY: // Code executed every loop iteration
  if(W.game -> modo_mapa){
    if(W.game -> mapa[3][3] != carta && fundo_sobreposto == NULL){
      // Voltamos de planiviagem
      carta = W.game -> mapa[3][3];
      caos1 = obtem_caos(carta);
      caos1 -> visible = false;
      if(W.game -> fusao_espacial){
        if(W.game -> proximo[0] != -1){
          carta_sobreposta = W.game -> proximo[0];
          descarta_carta();
        }
        else{
          carta_sobreposta = gera_carta();
        }
        if(carta_sobreposta == 5){
          carta_sobreposta = carta;
          carta = 5;
        }
        caos4 = obtem_caos(carta_sobreposta);
        caos4 -> visible = false;
        W.move_interface(caos4, caos4 -> x, caos4 -> y - caos4 -> height - 1);
        fundo = W.new_interface(1, W.width / 4, W.height / 2,
                                W.width / 2, W.height,
                                nomes[carta]);
        fundo_sobreposto = W.new_interface(1, 3 * W.width / 4, W.height / 2,
                                           W.width / 2, W.height,
                                           nomes[carta_sobreposta]);
      }
      else{
        fundo = W.new_interface(1, W.width / 2, W.height / 2,
                                W.width, W.height,
                                nomes[carta]);
      }
    }
  }
  else if(W.game -> fusao_espacial && fundo_sobreposto == NULL){
    printf("sobreposicao\n");
    //carta = W.game -> mapa[3][3];
    caos1 = obtem_caos(carta);
    caos1 -> visible = false;
    if(W.game -> proximo[0] != -1){
      carta_sobreposta = W.game -> proximo[0];
      descarta_carta();
    }
    else{
      carta_sobreposta = gera_carta();
    }
    if(carta_sobreposta == 5){
      carta_sobreposta = carta;
      carta = 5;
    }
    caos4 = obtem_caos(carta_sobreposta);
    caos4 -> visible = false;
    W.move_interface(caos4, caos4 -> x, caos4 -> y - caos4 -> height - 1);
    W.resize_interface(fundo, W.width / 2, W.height);
    W.move_interface(fundo, W.width / 4, W.height / 2);
    //fundo = W.new_interface(1, W.width / 4, W.height / 2,
    //			    W.width / 2, W.height,
    //			    nomes[carta]);
    fundo_sobreposto = W.new_interface(1, 3 * W.width / 4, W.height / 2,
				       W.width / 2, W.height,
				       nomes[carta_sobreposta]);
    printf("'%s' e '%s'\n", nomes[carta], nomes[carta_sobreposta]);
  }
  else if(W.game -> tunel_interplanar){
    carta = W.game -> mapa[3][3];
    W.destroy_interface(caos1);
    caos1 = obtem_caos(carta);
    caos1 -> visible = false;
    W.destroy_interface(fundo);
    fundo = W.new_interface(1, W.width / 2, W.height / 2,
                            W.width, W.height,
                            nomes[carta]);
    W.game -> tunel_interplanar = false;
  }
  if(W.keyboard[W_ESC]){
    // VOlta ao menu inicial
    Wloop(intro);
  }
  else if(W.keyboard[W_SPACEBAR] == 1)
    Wsubloop(vida);
  else if(W.keyboard[W_UP] && W.game -> modo_mapa){
    // Zoom out
    Wsubloop(planeswalk);
  }
  else if(W.keyboard[W_BACKSPACE] == 1 && carta_anterior != -1 &&
          W.game -> modo_mapa == false && W.game -> fusao_espacial == false){
    // Alterna entre o Plano atual e o último
    int tmp;
    W.destroy_interface(fundo);
    if(caos1 != NULL)
      W.destroy_interface(caos1);
    tmp = carta;
    carta = carta_anterior;
    carta_anterior = tmp;
    caos1 = obtem_caos(carta);
    fundo = W.new_interface(1, W.width / 2, W.height / 2,
                            W.width, W.height,
                            nomes[carta]);
    caos1 -> visible = false;
  }
  else if(W.keyboard[W_C] == 1 || W.mouse.buttons[W_MOUSE_RIGHT] == 1 ||
          W.mouse.buttons[W_MOUSE_RIGHT] == -1){
    // Mostra e oculta o efeito caótico
    if(caos1 -> visible){
      W.cancel(apaga_caos);
      apaga_caos();
    }
    else{
      caos1 -> visible = true;
      if(caos2 != NULL)
        caos2 -> visible = true;
      if(caos3 != NULL)
        caos3 -> visible = true;
      if(caos4 != NULL)
        caos4 -> visible = true;
      W.run_futurelly(apaga_caos, 5.0);
    }
  }
  else if((W.keyboard[W_ENTER] == 1 || W.mouse.buttons[W_MOUSE_LEFT] == 1 ||
           W.mouse.buttons[W_MOUSE_LEFT] == -1) && caos1 -> visible == false &&
          fundo -> integer == 0){
    // Tentativa de planinaltear
    num = W.random() % 6;
    if(num == 0 && W.game -> modo_mapa == false){
      // Tenta planinaltear sem usar mapa
      W.game -> aether_caotico = false;
      if(W.game -> fusao_espacial){
        W.game -> fusao_espacial = false;
        W.destroy_interface(fundo_sobreposto);
        fundo_sobreposto = NULL;
        W.destroy_interface(caos4);
        caos4 = NULL;
      }
      carta_anterior = carta;
      W.destroy_interface(fundo);
      if(caos1 != NULL)
        W.destroy_interface(caos1);
      if(caos2 != NULL){
        W.destroy_interface(caos2);
        caos2 = NULL;
      }
      if(caos3 != NULL){
        W.destroy_interface(caos3);
        caos3 = NULL;
      }
      if(W.game -> proximo[0] != -1){
        carta = W.game -> proximo[0];
        descarta_carta();
      }
      else{
        while(carta == carta_anterior)
          carta = W.random() % N;
      }
      caos1 = obtem_caos(carta);
      fundo = W.new_interface(1, W.width / 2, W.height / 2,
                              W.width, W.height,
                              nomes[carta]);
      if(caos1 != NULL)
        caos1 -> visible = false;
      W.play_sound(success);
      if(checa_fenomeno())
        Wsubloop(fenomeno);
    }
    else if(num == 0 && W.game -> modo_mapa){
      // Planinalteia usando o mapa
      W.destroy_interface(fundo);
      W.destroy_interface(caos1);
      if(caos2 != NULL){
        W.destroy_interface(caos2);
        caos2 = NULL;
      }
      if(caos3 != NULL){
        W.destroy_interface(caos3);
        caos3 = NULL;
      }
      W.game -> aether_caotico = false;
      if(W.game -> fusao_espacial){
        W.game -> fusao_espacial = false;
        W.destroy_interface(fundo_sobreposto);
        fundo_sobreposto = NULL;
        W.destroy_interface(caos4);
        caos4 = NULL;
      }
      W.play_sound(success);
      W.game -> pode_mudar = true;
      Wsubloop(planeswalk);
    }
    else if(num == 1 || W.game -> aether_caotico){
      // Efeito caótico
      if(carta == 69)
        usa_escada = true;
      if(carta == 5){
        // Efeito caótico das Piscinas da Formação
        int n1, n2, n3;
        W.destroy_interface(caos1);
        if(caos2 != NULL){
          W.destroy_interface(caos2);
          caos2 = NULL;
        }
        if(caos3 != NULL){
          W.destroy_interface(caos3);
          caos3 = NULL;
        }
        n1 = W.random() % N;
        while(n1 == 5) n1 = W.random() % N;
        n2 = W.random() % N;
        while(n2 == 5 || n2 == n1) n2  = W.random() % N;
        n3 = W.random() % N;
        while(n3 == 5 || n3 == n1 || n3 == n2)
          n3 = W.random() % N;
        if(n1 == 69 || n2 == 69 || n3 == 69)
          usa_escada = true;
        caos1 = obtem_caos(n1);
        caos2 = obtem_caos(n2);
        caos3 = obtem_caos(n3);
        W.move_interface(caos2, W.width / 2, W.height / 3);
        W.move_interface(caos3, W.width / 2, 2 * W.height / 3);
        caos1 -> visible = true;
        caos2 -> visible = true;
        caos3 -> visible = true;
      }
      else{
        if(caos1 != NULL)
          caos1 -> visible = true;
      }
      if(caos4 != NULL)
        caos4 -> visible = true;
      W.play_sound(som_caos);
      W.run_futurelly(apaga_caos, 5.0);
    }
    else{
      fundo -> integer = 5;
      if(W.game -> fusao_espacial && fundo_sobreposto != NULL)
        fundo_sobreposto -> integer = 5;
      W.run_futurelly(nao_treme, 0.5);
      W.play_sound(fail);
    }
  }
 LOOP_END: // Code executed at the end of the loop
  return;
}

int main(void){
  Winit(); // Initializes Weaver
  Wloop(intro); // Enter a new game loop
  return 0;
}


void gera_vizinhanca(void){
  int k, nova_carta = -1;
  const int coord[] = {3, 3, 3, 2, 2, 3, 4, 3, 3, 4};
  for(k = 0; k < 10; k += 2){
    if(W.game -> mapa[coord[k]][coord[k + 1]] == -1){
      if(W.game -> proximo[0] != -1){
        nova_carta = W.game -> proximo[0];
        descarta_carta();
      }
      else
        nova_carta = gera_carta();
      W.game -> mapa[coord[k]][coord[k + 1]] = nova_carta;
    }
  }
}

int gera_carta(void){
  int i, j;
  while(1){
    int card = W.random() % N;
    bool repetida = false;
    for(i = 0; i < 7; i ++)
      for(j = 0; j < 7; j ++)
        if(W.game -> mapa[i][j] == card)
          repetida = true;
    for(i = 0; i < 10; i ++)
      if(W.game -> proximo[i] == card)
        repetida = true;
    if(!repetida)
      return card;
  }
}

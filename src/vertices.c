#include "vertices.h"
#include "globals.h"
#include "transformacoes.h"
#include <stdio.h>
#include <stdlib.h>
programa *inicializa_lista() {

  programa *temp = (programa *)malloc(sizeof(programa));

  temp->baricentroX = 0;
  temp->baricentroY = 0;
  temp->numPontos = 0;
  temp->janelaAltura = 0;
  temp->janelaLargura = 0;
  temp->inicio = NULL;
  temp->ultimo = NULL;
  temp->opcaoTransformacao = 0;
  temp->opcaoCurva = 0;
  for (int i = 0; i < 3; i++) {
    temp->rgbPonto[i] = 0;
    temp->rgbLinha[i] = 0;
  }

  temp->selectSupEsq = (cantosPoligono){0, 0, 0};
  temp->selectSupDir = (cantosPoligono){0, 0, 0};
  temp->selectInfEsq = (cantosPoligono){0, 0, 0};
  temp->selectInfDir = (cantosPoligono){0, 0, 0};

  return temp;
}

void novo_ponto(int x, int y, programa *poligono) {
  ponto *novo_ponto = (ponto *)malloc(sizeof(ponto));
  novo_ponto->x = x;
  novo_ponto->y = y;
  novo_ponto->z = 0;
  novo_ponto->anguloCentro = 0;
  novo_ponto->proximo = NULL;
  novo_ponto->anterior = NULL;

  if (poligono->numPontos == 0) {
    poligono->inicio = novo_ponto;
  } else {
    poligono->ultimo->proximo = novo_ponto;
    novo_ponto->anterior = poligono->ultimo;
  }

  poligono->ultimo = novo_ponto;
  poligono->numPontos++;

  if(poligono->numPontos >= 3){
      setAngulos(poligono);

      int trocou = 1;
      while(trocou){
          trocou = 0;
          for(ponto *atual = poligono->inicio; atual != NULL && atual->proximo; atual = atual->proximo){
              if(atual->anguloCentro > atual->proximo->anguloCentro){
                  int tx = atual->x;
                  atual->x = atual->proximo->x;
                  atual->proximo->x = tx;

                  int ty = atual->y;
                            atual->y = atual->proximo->y;
                            atual->proximo->y = ty;

                double ta = atual->anguloCentro;
                atual->anguloCentro = atual->proximo->anguloCentro;
                atual->proximo->anguloCentro = ta;

                double tr = atual->raioCentro;
                atual->raioCentro = atual->proximo->raioCentro;
                atual->proximo->raioCentro = tr;

                  trocou = 1;

              }
          }
      }



  }

}

void apaga_ponto(programa *poligono) {

  ponto *atual = poligono->inicio;

  if (poligono->inicio == poligono->ultimo) {
    poligono->inicio = NULL;
    poligono->ultimo = NULL;
    free(atual);

  } else {
      poligono->inicio = atual->proximo;
      if (poligono->inicio != NULL) {
          poligono->inicio->anterior = NULL;
      }
      free(atual);
  }

  if (poligono->numPontos != 0) {

    poligono->numPontos--;
  }
}

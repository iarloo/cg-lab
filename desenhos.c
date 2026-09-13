#include "desenhos.h"
#include "vertices.h"
#include <GL/gl.h>
#include <math.h>
void desenha_ponto(programa *poligono) {

  glColor3f(poligono->rgbPonto[0], poligono->rgbPonto[1],
            poligono->rgbPonto[2]);
  glPointSize(6);

  glBegin(GL_POINTS);

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    glVertex2f(atual->x, atual->y);
  }
  glEnd();
}

void desenha_plano_cartesiano(programa *poligono) {

  glColor3f(1.0, 0.0, 0.0);

  glLineWidth(2);

  glBegin(GL_LINE_STRIP);
  glVertex2f(-poligono->janelaLargura, 0);
  glVertex2f(poligono->janelaLargura, 0);
  glEnd();

  glBegin(GL_LINE_STRIP);
  glVertex2f(0, poligono->janelaAltura);
  glVertex2f(0, -poligono->janelaAltura);
  glEnd();
}

void desenha_poligono(programa *poligono) {

  glColor3f(poligono->rgbLinha[0], poligono->rgbLinha[1],
            poligono->rgbLinha[2]);
  glLineWidth(3);
  glBegin(GL_LINE_LOOP);
  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    glVertex2f(atual->x, atual->y);
  }
  glEnd();
}

void getCantosSelect(programa *poligono) {
  if (poligono->inicio == NULL && poligono->numPontos < 3) {
    return;
  }
  ponto *maiorx = poligono->inicio;
  ponto *maiory = poligono->inicio;

  ponto *menorx = maiorx;
  ponto *menory = maiory;

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {

    if (maiorx->x < atual->x) {
      maiorx = atual;
    }

    if (maiory->y < atual->y) {
      maiory = atual;
    }
    if (menorx->x > atual->x) {
      menorx = atual;
    }

    if (menory->y > atual->y) {
      menory = atual;
    }
  }

  poligono->selectSupEsq.x = menorx->x;
  poligono->selectSupEsq.y = maiory->y; // superior-esquerdo

  poligono->selectSupDir.x = maiorx->x;
  poligono->selectSupDir.y = maiory->y; // superior-direito

  poligono->selectInfDir.x = maiorx->x,
  poligono->selectInfDir.y = menory->y; // inferior-direito

  poligono->selectInfEsq.x = menorx->x,
  poligono->selectInfEsq.y = menory->y; // inferior-esquerdo
}

void desenha_selecao_poligono(programa *poligono, double multiplicador,
                              int ancoraX, int ancoraY, int ponto) {

  int supEsqX = ancoraX + (int)round((poligono->selectSupEsq.x - ancoraX) *
                                     multiplicador);
  int supEsqY = ancoraY + (int)round((poligono->selectSupEsq.y - ancoraY) *
                                     multiplicador);
  int supDirX = ancoraX + (int)round((poligono->selectSupDir.x - ancoraX) *
                                     multiplicador);
  int supDirY = ancoraY + (int)round((poligono->selectSupDir.y - ancoraY) *
                                     multiplicador);
  int infDirX = ancoraX + (int)round((poligono->selectInfDir.x - ancoraX) *
                                     multiplicador);
  int infDirY = ancoraY + (int)round((poligono->selectInfDir.y - ancoraY) *
                                     multiplicador);
  int infEsqX = ancoraX + (int)round((poligono->selectInfEsq.x - ancoraX) *
                                     multiplicador);
  int infEsqY = ancoraY + (int)round((poligono->selectInfEsq.y - ancoraY) *
                                     multiplicador);

  glColor3f(0, 0, 1);
  glLineWidth(1);
  glBegin(GL_LINE_LOOP);
  glVertex2f(supEsqX, supEsqY);
  glVertex2f(supDirX, supDirY);
  glVertex2f(infDirX, infDirY);
  glVertex2f(infEsqX, infEsqY);
  glEnd();

  if (ponto == 1) {
    glColor3f(0, 0, 0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(supEsqX, supEsqY);
    glVertex2f(supDirX, supDirY);
    glVertex2f(infDirX, infDirY);
    glVertex2f(infEsqX, infEsqY);
    glEnd();
  }
}

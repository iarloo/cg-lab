#include "transformacoes.h"
#include "vertices.h"
#include <math.h>
#include <stdlib.h>

#include <math.h>
extern int a, b;
double distancia(double x1, double y1, double x2, double y2) {
  double dx = x2 - x1;
  double dy = y2 - y1;
  return sqrt(dx * dx + dy * dy);
}

void fazerTranslacao(int x, int y, programa *poligono) {

  // troca a cor do poligono.
  poligono->rgbLinha[0] = 0;
  poligono->rgbLinha[1] = 0.8;
  poligono->rgbLinha[2] = 0.2;

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    atual->x += x;
    atual->y += y;
  }
}

double areaPoligono(programa *poligono) {
  double somatorio = 0;
  long x0;
  long y0;
  long x1;
  long y1;

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    x0 = atual->x;
    y0 = atual->y;

    if (atual->proximo == NULL) {
      x1 = poligono->inicio->x;
      y1 = poligono->inicio->y;
    } else {
      x1 = atual->proximo->x;
      y1 = atual->proximo->y;
    }

    somatorio += ((x0 * y1)) - ((y0 * x1));
  }

  return somatorio / 2.0;
}

void baricentroPoligono(programa *poligono) {

  double Xc = 0, Yc = 0;
  long x0, y0, x1, y1;
  double area = areaPoligono(poligono);

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    x0 = atual->x;
    y0 = atual->y;

    if (atual->proximo == NULL) {
      x1 = poligono->inicio->x;
      y1 = poligono->inicio->y;
    } else {
      x1 = atual->proximo->x;
      y1 = atual->proximo->y;
    }

    Xc += (x1 + x0) * ((x0 * y1) - (y0 * x1));
    Yc += (y1 + y0) * ((x0 * y1) - (y0 * x1));
  }

  if (area == 0) {

    poligono->baricentroX = 0;
    poligono->baricentroY = 0;

  } else {
    Xc /= 6 * area;

    Yc /= 6 * area;
    poligono->baricentroX = Xc;
    poligono->baricentroY = Yc;
  }
}

void setAngulos(programa *poligono) {

  baricentroPoligono(poligono);

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    float Dx = atual->x - poligono->baricentroX;
    float Dy = atual->y - poligono->baricentroY;
    atual->anguloCentro = atan2(Dy, Dx);
    atual->raioCentro = hypotf(Dy, Dx);
  }
}

void fazerRotacao(programa *poligono, double angulo) {
  double Cx = poligono->baricentroX;
  double Cy = poligono->baricentroY;

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    double angulo_novo = atual->anguloCentro + angulo;

    // R * Sin/Cos(theta + beta) calcula o a posição nova do angulo MAS. é
    // preciso adicionar o baricentroPoligono para o desenho ficar certo na
    // tela.
    atual->x = Cx + atual->raioCentro * cos(angulo_novo);
    atual->y = Cy + atual->raioCentro * sin(angulo_novo);

    atual->anguloCentro = angulo_novo;
  }
}

void fazerEscala(programa *poligono, double multiplicador, int ancoraX,
                 int ancoraY) {

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    // sendo P a origem arbitraria.
    // 1 Passo: Desloca tudo para o sistema de coordenadas baseado em P fazendo
    // a subtração de P com Vertice. 2 Passo: Fazemos a operação. 3 Passo:
    // Devolvemos o valor P a coordenada para voltarmos ao sistema de referencia
    // original.
    atual->x = ancoraX + ((atual->x - ancoraX) * multiplicador);
    atual->y = ancoraY + ((atual->y - ancoraY) * multiplicador);
  }
}

void fazerReflexaoEixoY(programa *poligono, int ancora) {
  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    atual->x = ancora - (atual->x - ancora);
  }
}
void fazerEspelhoX(programa *poligono) {

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    atual->y = -atual->y;
  }
}
void fazerEspelhoY(programa *poligono) {
  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    atual->x = -atual->x;
  }
}
void fazerEspelhoOrig(programa *poligono) {
  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    atual->x = -atual->x;
    atual->y = -atual->y;
  }
}

void fazerCisalhamentoHorizontal(programa *poligono, double multiplicador) {

  int ancoraY;
  double sinal;

  if (a == 2 && b == 3) {
    // fundo foi agarrado — âncora é o topo
    ancoraY = poligono->selectSupEsq.y;
    sinal = -1.0;
  } else {
    // topo foi agarrado (a==0,b==1) — âncora é o fundo
    ancoraY = poligono->selectInfEsq.y;
    sinal = 1.0;
  }

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    atual->x = atual->x + (sinal * multiplicador * (atual->y - ancoraY));
  }
}

void fazerCisalhamentoVertical(programa *poligono, double multiplicador) {

  int ancoraX;
  double sinal;

  if (a == 1 && b == 3) {
    // direita foi agarrada — âncora é a esquerda
    ancoraX = poligono->selectSupEsq.x;
    sinal = 1.0;
  } else {
    // esquerda foi agarrada (a==0,b==2) — âncora é a direita
    ancoraX = poligono->selectSupDir.x;
    sinal = -1.0;
  }

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    atual->y = atual->y + (sinal * multiplicador * (atual->x - ancoraX));
  }
}

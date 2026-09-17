#include "curvas.h"
#include "constantes.h"
#include <math.h>
#include <stddef.h>

static const double M_HERMITE[4][4] = {
    {2, -2, 1, 1}, {-3, 3, -2, -1}, {0, 0, 1, 0}, {1, 0, 0, 0}};

static const double M_BEZIER[4][4] = {
  {-1, 3, -3, 1}, {3, -6, 3, 0}, {-3, 3, 0, 0}, {1, 0, 0, 0}};
     

double static avaliaHermiteEscalar(double t, double p0, double p1, double t0,
                                   double t1) {
  double base[4] = {t * t * t, t * t, t, 1.0};
  double geo[4] = {p0, p1, t0, t1};
  double resultado = 0.0;

  for (int i = 0; i < 4; i++) {
    double coef = 0.0;
    for (int j = 0; j < 4; j++) {
      coef += M_HERMITE[i][j] * geo[j];
    }
    resultado += base[i] * coef;
  }

  return resultado;
}

int calculaHermite(programa *poligono, pontoCurva *saida, int capacidade) {
  double p0x, p0y, p1x, p1y;
  if (capacidade == 1) {
    return 0;
  }

  int i = 0;

  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    p0x = atual->x;
    p0y = atual->y;

    if (atual->proximo == NULL) {

      p1x = poligono->inicio->x;
      p1y = poligono->inicio->y;

    } else {

      p1x = atual->proximo->x;

      p1y = atual->proximo->y;
    }
    for (int j = 0; j < capacidade / poligono->numPontos; j++) {
      double t = j / (double)(capacidade / poligono->numPontos - 1);

      saida[i].x = avaliaHermiteEscalar(t, p0x, p1x, 100, 10);
      saida[i].y = avaliaHermiteEscalar(t, p0y, p1y, 90, 30);
      i++;
    }
  }

  return capacidade;
}

int calculaBezier(programa *poligono, pontoCurva *saida, int capacidade) {
  //
  return 0;
}

int calculaBSpline(programa *poligono, pontoCurva *saida, int capacidade) {
  // TODO
  return 0;
}

int calculaCatmullRom(programa *poligono, pontoCurva *saida, int capacidade) {
  int n = poligono->numPontos;
  double xs[n], ys[n];

  int k = 0;
  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    xs[k] = atual->x;
    ys[k] = atual->y;
    k++;
  }

  int pontosPorSegmento = capacidade / n;
  int pos = 0;

  for (int seg = 0; seg < n; seg++) {
    int i0 = seg;
    int i1 = (seg + 1) % n;
    int iAntesI0 = (seg - 1 + n) % n;
    int iDepoisI1 = (seg + 2) % n;

    double t0x = (xs[i1] - xs[iAntesI0]) / 2.0;
    double t0y = (ys[i1] - ys[iAntesI0]) / 2.0;
    double t1x = (xs[iDepoisI1] - xs[i0]) / 2.0;
    double t1y = (ys[iDepoisI1] - ys[i0]) / 2.0;

    for (int j = 0; j < pontosPorSegmento; j++) {
      double t = j / (double)(pontosPorSegmento - 1);

      saida[pos].x = avaliaHermiteEscalar(t, xs[i0], xs[i1], t0x, t1x);
      saida[pos].y = avaliaHermiteEscalar(t, ys[i0], ys[i1], t0y, t1y);
      pos++;
    }
  }

  return pos;
}

int calculaCurva(programa *poligono, pontoCurva *saida, int capacidade) {
  switch (poligono->opcaoCurva) {
  case HERMITE:
    return calculaHermite(poligono, saida, capacidade);
  case BEZIER:
    return calculaBezier(poligono, saida, capacidade);
  case BSPLINE:
    return calculaBSpline(poligono, saida, capacidade);
  case CATMULLR:
    return calculaCatmullRom(poligono, saida, capacidade);
  default:
    return 0;
  }
}

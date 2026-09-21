#include "curvas.h"
#include "constantes.h"
#include <math.h>
#include <stddef.h>

static const double M_HERMITE[4][4] = {
    {2, -2, 1, 1}, {-3, 3, -2, -1}, {0, 0, 1, 0}, {1, 0, 0, 0}};

static const double M_BEZIER[4][4] = {
  {-1, 3, -3, 1}, {3, -6, 3, 0}, {-3, 3, 0, 0}, {1, 0, 0, 0}};

static const double M_BSPLINE[4][4] = {
    {-1.0 / 6.0, 3.0 / 6.0, -3.0 / 6.0, 1.0 / 6.0},
    { 3.0 / 6.0,-6.0 / 6.0,  3.0 / 6.0, 0.0       },
    {-3.0 / 6.0, 0.0,        3.0 / 6.0, 0.0       },
    { 1.0 / 6.0, 4.0 / 6.0,  1.0 / 6.0, 0.0       }};

static double avaliaMatriz(double t, const double matriz[4][4],
                              double p0, double p1, double p2, double p3) {
  double base[4] = {t * t * t, t * t, t, 1.0};
  double geo[4] = {p0, p1, p2, p3};
  double resultado = 0.0;

  for (int i = 0; i < 4; i++) {
    double coef = 0.0;
    for (int j = 0; j < 4; j++) {
      coef += matriz[i][j] * geo[j];
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

      saida[i].x = avaliaMatriz(t,M_HERMITE, p0x, p1x, 100, 10);
      saida[i].y = avaliaMatriz(t,M_HERMITE, p0y, p1y, 90, 30);
      i++;
    }
  }

  return capacidade;
}

int calculaBezier(programa *poligono, pontoCurva *saida, int capacidade) {
  int n = poligono->numPontos;
  if (n < 2 || capacidade < 2) return 0;

  double xs[n], ys[n];
  int k = 0;
  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    xs[k] = atual->x;
    ys[k] = atual->y;
    k++;
  }

  int pontosPorSegmento = capacidade / n;
  if (pontosPorSegmento < 2) pontosPorSegmento = 2;

  int pos = 0;
  for (int seg = 0; seg < n; seg++) {
    int i0     = seg;
    int i1     = (seg + 1) % n;
    int iAntes = (seg - 1 + n) % n;
    int iDepois= (seg + 2) % n;

    // Tangentes estilo Catmull-Rom
    double t0x = (xs[i1]     - xs[iAntes])  / 2.0;
    double t0y = (ys[i1]     - ys[iAntes])  / 2.0;
    double t1x = (xs[iDepois] - xs[i0])     / 2.0;
    double t1y = (ys[iDepois] - ys[i0])     / 2.0;

    // Converte para pontos de controle Bézier:
    // P0 = ponto atual
    // P1 = P0 + t0/3
    // P2 = P1 - t1/3
    // P3 = próximo ponto
    double b0x = xs[i0],           b0y = ys[i0];
    double b1x = xs[i0] + t0x/3.0, b1y = ys[i0] + t0y/3.0;
    double b2x = xs[i1] - t1x/3.0, b2y = ys[i1] - t1y/3.0;
    double b3x = xs[i1],           b3y = ys[i1];

    for (int j = 0; j < pontosPorSegmento && pos < capacidade; j++) {
      double t = j / (double)(pontosPorSegmento - 1);
      saida[pos].x = avaliaMatriz(t, M_BEZIER, b0x, b1x, b2x, b3x);
      saida[pos].y = avaliaMatriz(t, M_BEZIER, b0y, b1y, b2y, b3y);
      pos++;
    }
  }

  return pos;
}

int calculaBSpline(programa *poligono, pontoCurva *saida, int capacidade) {
  int n = poligono->numPontos;
  if (n < 4 || capacidade < 2) {
    return 0;
  }

  double xs[n], ys[n];
  int k = 0;
  for (ponto *atual = poligono->inicio; atual != NULL; atual = atual->proximo) {
    xs[k] = atual->x;
    ys[k] = atual->y;
    k++;
  }

  int pontosPorSegmento = capacidade / n;
  if (pontosPorSegmento < 2) {
    pontosPorSegmento = 2;
  }

  int pos = 0;
  for (int seg = 0; seg < n; seg++) {
    int i0 = (seg - 1 + n) % n;
    int i1 = seg % n;
    int i2 = (seg + 1) % n;
    int i3 = (seg + 2) % n;

    for (int j = 0; j < pontosPorSegmento && pos < capacidade; j++) {
      double t = j / (double)(pontosPorSegmento - 1);
      saida[pos].x = avaliaMatriz(t, M_BSPLINE, xs[i0], xs[i1], xs[i2], xs[i3]);
      saida[pos].y = avaliaMatriz(t, M_BSPLINE, ys[i0], ys[i1], ys[i2], ys[i3]);
      pos++;
    }
  }

  return pos;
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

      saida[pos].x = avaliaMatriz(t,M_HERMITE, xs[i0], xs[i1], t0x, t1x);
      saida[pos].y = avaliaMatriz(t,M_HERMITE, ys[i0], ys[i1], t0y, t1y);
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

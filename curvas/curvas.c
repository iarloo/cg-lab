#include "curvas.h"
#include "constantes.h"
#include <math.h>
#include <stddef.h>

static const double M_HERMITE[4][4] = {
    {2, -2, 1, 1}, {-3, 3, -2, -1}, {0, 0, 1, 0}, {1, 0, 0, 0}};

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

  double p0x = poligono->inicio->x;
  double p0y = poligono->inicio->y;

  double p1x = poligono->ultimo->x;
  double p1y = poligono->ultimo->y;

  if (capacidade == 1) {
    return 0;
  }

  for (int i = 0; i < capacidade; i++) {
    double t = i / (double)(capacidade - 1);

    saida[i].x = avaliaHermiteEscalar(t, p0x, p1x, 100, 10);
    saida[i].y = avaliaHermiteEscalar(t, p0y, p1y, 90, 30);
  }

  return capacidade;
}

int calculaBezier(programa *poligono, pontoCurva *saida, int capacidade) {
  // TODO
  return 0;
}

int calculaBSpline(programa *poligono, pontoCurva *saida, int capacidade) {
  // TODO
  return 0;
}

int calculaCatmullRom(programa *poligono, pontoCurva *saida, int capacidade) {
  // TODO
  return 0;
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

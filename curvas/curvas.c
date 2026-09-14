#include "curvas.h"
#include "constantes.h"
#include <math.h>
#include <stddef.h>

int calculaHermite(programa *poligono, pontoCurva *saida, int capacidade) {
  // TODO
  return 0;
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

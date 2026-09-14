#ifndef CURVAS_H
#define CURVAS_H

#include "vertices.h"

// Quantos pontos amostrados gerar por segmento da curva.
// Mais alto = curva mais suave, mais pontos pra desenhar.
#define RESOLUCAO_CURVA 500

typedef struct pontoCurva {
  double x;
  double y;
} pontoCurva;

// Cada função recebe os pontos de controle (poligono->inicio) e preenche
// o array `saida` (capacidade máxima `capacidade`), devolvendo quantos
// pontos foram efetivamente escritos.
int calculaHermite(programa *poligono, pontoCurva *saida, int capacidade);
int calculaBezier(programa *poligono, pontoCurva *saida, int capacidade);
int calculaBSpline(programa *poligono, pontoCurva *saida, int capacidade);
int calculaCatmullRom(programa *poligono, pontoCurva *saida, int capacidade);

// Dispatcher: olha poligono->opcaoCurva e chama a função certa.
int calculaCurva(programa *poligono, pontoCurva *saida, int capacidade);

#endif

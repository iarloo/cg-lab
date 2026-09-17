#ifndef vertices
#define vertices

typedef struct ponto {

  int x;
  int y;
  int z;
  double anguloCentro;
  double raioCentro;
  struct ponto *proximo;
  struct ponto *anterior;
} ponto;

typedef struct cantosPoligono {
  int x;
  int y;
  int z;
} cantosPoligono;

typedef struct programa {

  double baricentroX;
  double baricentroY;
  int numPontos;
  ponto *inicio;
  ponto *ultimo;
  int janelaLargura;
  int janelaAltura;
  int opcaoTransformacao;
  int opcaoCurva;
  float rgbPonto[3];
  float rgbLinha[3];

  cantosPoligono selectSupEsq;
  cantosPoligono selectSupDir;
  cantosPoligono selectInfEsq;
  cantosPoligono selectInfDir;

} programa;

programa *inicializa_lista();

void novo_ponto(int x, int y, programa *poligono);

void apaga_ponto(programa *poligono);
#endif

#include "vertices.h"
#include <math.h>
void fazerTranslacao(int x, int y, programa *poligono);
double areaPoligono(programa *poligono);
void baricentroPoligono(programa *poligono);
void setAngulos(programa *poligono);
void fazerRotacao(programa *poligono, double angulo);
double distancia(double x1, double y1, double x2, double y2);
void fazerEscala(programa *poligono, double multiplicador, int ancoraX,
                 int ancoraY);
void fazerEspelhoX(programa *poligono);
void fazerEspelhoY(programa *poligono);
void fazerEspelhoOrig(programa *poligono);
void fazerCisalhamentoHorizontal(programa *poligono, double multiplicador);
void fazerCisalhamentoVertical(programa *poligono, double multiplicador);

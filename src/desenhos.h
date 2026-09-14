
#include "vertices.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void desenha_ponto(programa *poligono);
void desenha_plano_cartesiano(programa *poligono);
void desenha_poligono(programa *poligono);

void desenha_selecao_poligono(programa *poligono, double multiplicador,
                              int ancoraX, int ancoraY, int ponto);

void getCantosSelect(programa *poligono);
void desenha_curva(programa *poligono);

#include "janela.h"
#include "constantes.h"
#include "desenhos.h"
#include "globals.h"
#include "vertices.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void redimensionar(int largura, int altura) {

  poligono->janelaLargura = largura / 2;
  poligono->janelaAltura = altura / 2;

  glViewport(0, 0, largura, altura);

  // Como vamos configurar a área de projeção precisamos colocar o modo da
  // matrix em projeção.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Configura a área visivel da janela, coloca as cordenadas do retangulo.
  gluOrtho2D(-poligono->janelaLargura, poligono->janelaLargura,
             -poligono->janelaAltura, poligono->janelaAltura);

  // Volta para o modo de visualização de objetos, deixando pronto para
  // desenhar e transformar.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void espacoDeDesenho() {

  glClearColor(1, 1, 1, 1);

  // Limpando o buffer de cor do
  glClear(GL_COLOR_BUFFER_BIT);

  desenha_plano_cartesiano(poligono);
  desenha_ponto(poligono);
  desenha_poligono(poligono);

  if (poligono->opcaoTransformacao == ESCALA) {

    double multiplicadorPreview;

    if (arrastando && distNoClick > 0.001) {
      multiplicadorPreview = distNoRelease / distNoClick;
    } else {
      multiplicadorPreview = 1.0;
    }
    desenha_selecao_poligono(poligono, multiplicadorPreview, ancorax, ancoray,
                             1);
  } else if (poligono->opcaoTransformacao == CISALHA) {
    double multiplicadorPreview;
    if (arrastando && distNoClick > 0.001) {
      multiplicadorPreview = 1;
    } else {
      multiplicadorPreview = 1.0;
    }
    getCantosSelect(poligono);
    desenha_selecao_poligono(poligono, multiplicadorPreview,
                             poligono->selectInfEsq.x, poligono->selectInfEsq.y,
                             0);
  }

  glFlush();
}

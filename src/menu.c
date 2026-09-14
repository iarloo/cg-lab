#include "menu.h"
#include "constantes.h"
#include "desenhos.h"
#include "globals.h"
#include "transformacoes.h"
#include "vertices.h"
#include <GL/freeglut_std.h>
#include <GL/glut.h>
#include <stdlib.h>
void menuPrincipal(int escolha) {

  switch (escolha) {

  case 3:
    while (poligono->numPontos != 0) {

      apaga_ponto(poligono);
    }
    limpou = 1;
    break;
  case 4:
    exit(1);
  }

  glutPostRedisplay();
}
void menuCurvas(int escolha) {

  switch (escolha) {
  case HERMITE:
    poligono->opcaoCurva = HERMITE;
    glutPostRedisplay();
    break;

  case BEZIER:
    poligono->opcaoCurva = BEZIER;
    glutPostRedisplay();
    break;

  case BSPLINE:

    poligono->opcaoCurva = BSPLINE;
    glutPostRedisplay();
    break;

  case CATMULLR:
    poligono->opcaoCurva = CATMULLR;
    glutPostRedisplay();
    break;
  }
}
void menuTransformacao(int escolha) {

  switch (escolha) {
  case TRANSLACAO:
    poligono->opcaoTransformacao = TRANSLACAO;
    glutPostRedisplay();
    break;

  case ROTACAO:
    poligono->opcaoTransformacao = ROTACAO;
    glutPostRedisplay();
    break;

  case ESCALA:
    poligono->opcaoTransformacao = ESCALA;
    glutPostRedisplay();
    break;

  case ESPELHOX:
    fazerEspelhoX(poligono);
    glutPostRedisplay();
    poligono->opcaoTransformacao = 0;
    break;
  case ESPELHOY:
    fazerEspelhoY(poligono);
    glutPostRedisplay();
    poligono->opcaoTransformacao = 0;
    break;
  case ESPELHOORIGEM:
    fazerEspelhoOrig(poligono);
    glutPostRedisplay();
    poligono->opcaoTransformacao = 0;
    break;

  case CISALHA:
    poligono->opcaoTransformacao = CISALHA;
    glutPostRedisplay();
    break;

  case 8:
    poligono->opcaoTransformacao = 0;
    poligono->rgbLinha[0] = 0;
    poligono->rgbLinha[1] = 0;
    poligono->rgbLinha[2] = 0;
    glutPostRedisplay();
    break;
  }
}
void configuraMenus() {

  int submenu1 = glutCreateMenu(menuTransformacao);
  glutAddMenuEntry("Translacao", TRANSLACAO);
  glutAddMenuEntry("Rotacao", ROTACAO);
  glutAddMenuEntry("Escala", ESCALA);
  glutAddMenuEntry("Espelho em X", ESPELHOX);
  glutAddMenuEntry("Espelho em Y", ESPELHOY);
  glutAddMenuEntry("Espelho na Origem", ESPELHOORIGEM);
  glutAddMenuEntry("Cisalha", CISALHA);
  glutAddMenuEntry("Sair do modo Transformacao", 8);

  int submenu2 = glutCreateMenu(menuCurvas);
  glutAddMenuEntry("Hermite", HERMITE);
  glutAddMenuEntry("Bezier", BEZIER);
  glutAddMenuEntry("Bspline", BSPLINE);
  glutAddMenuEntry("Catmullar", CATMULLR);

  glutCreateMenu(menuPrincipal);
  glutAddSubMenu("Transformacoes", submenu1);
  glutAddSubMenu("Curvas", submenu2);
  glutAddMenuEntry("Limpar", 3);
  glutAddMenuEntry("Fechar Programa", 4);

  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

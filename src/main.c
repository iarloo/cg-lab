#include "constantes.h"
#include "desenhos.h"
#include "globals.h"
#include "janela.h"
#include "menu.h"
#include "mouse.h"
#include "transformacoes.h"
#include "vertices.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

programa *poligono;
int origemX;
int origemY;
double multiplicador = 1.0;
double distNoClick;
double distNoRelease;
int arrastando = 0;
int limpou = 0;
int ancorax = 0;
int ancoray = 0;
int a, b;
double deslocX, deslocY;

int main(int argcp, char **argv) {

  poligono = inicializa_lista();

  glutInit(&argcp, argv);

  // GLUT_SINGLE e GLUT_RGBA é para dizer quais buffers eu vou querer.
  glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
  glutInitWindowPosition(POSISAO_JANELA_X, POSISAO_JANELA_Y);
  glutInitWindowSize(TAMANHO_JANELA_LARGURA, TAMANHO_JANELA_ALTURA);

  glutCreateWindow("Janela do Trabalho_1");

  // callback para mostrar a tela.
  glutDisplayFunc(espacoDeDesenho);

  // Callback para configurar a projeção na criação e redimensionamento.
  glutReshapeFunc(redimensionar);

  // Tava testando
  glutMouseFunc(mouse);

  glutMotionFunc(posicaoMouse);
  configuraMenus();

  glutMainLoop();

  return 0;
}

#include "desenhos.h"
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

void mouse(int button, int state, int x, int y) {

  // Guardando as coordenadas de onde o clique do mouse foi feito.
  int clickX = x - poligono->janelaLargura;
  int clickY = poligono->janelaAltura - y;

  // Qual opção está ativa ?
  switch (poligono->opcaoTransformacao) {

  case TRANSLACAO:
    // se a translação foi escolhida e o botão no mouse foi segurado
    if (state == GLUT_DOWN) {

      // guarda o valor do clique em uma variavel global
      //  para que seja possivel comparar o valor do mouse de agora com o valor
      //  de origem na callback de motion
      origemX = clickX;
      origemY = clickY;
      arrastando = 1;
    } else {
      arrastando = 0;
    }

    break;

  case ROTACAO:
    // se a translação foi escolhida e o botão no mouse foi segurado
    if (state == GLUT_DOWN) {

      // guarda o valor do clique em uma variavel global
      //  para que seja possivel comparar o valor do mouse de agora com o valor
      //  de origem na callback de motion
      origemX = clickX;
      origemY = clickY;
      arrastando = 1;
    } else {
      arrastando = 0;
    }

    break;

  case ESCALA:
    if (state == GLUT_DOWN) {

      // guarda o valor do clique em uma variavel global
      //  para que seja possivel comparar o valor do mouse de agora com o valor
      //  de origem na callback de motion
      origemX = clickX;
      origemY = clickY;
      getCantosSelect(poligono);

      // Calcula a distancia do clique do mouse de um dos cantinhos de seleção
      double d[4];
      d[0] = distancia(clickX, clickY, poligono->selectSupEsq.x,
                       poligono->selectSupEsq.y);
      d[1] = distancia(clickX, clickY, poligono->selectSupDir.x,
                       poligono->selectSupDir.y);
      d[2] = distancia(clickX, clickY, poligono->selectInfEsq.x,
                       poligono->selectInfEsq.y);
      d[3] = distancia(clickX, clickY, poligono->selectInfDir.x,
                       poligono->selectInfDir.y);

      // Computamos qual distancia entre o mouse e o canto foi menor.
      int menor = 0;
      for (int i = 0; i < 4; i++) {
        if (d[i] < d[menor]) {
          menor = i;
        }
      }

      // Se foi perto o suficiente logo definimos nossa ancora.
      if (d[menor] < 10) {
        // âncora = canto oposto ao agarrado
        if (menor == 0) {
          ancorax = poligono->selectInfDir.x;
          ancoray = poligono->selectInfDir.y;
        } else if (menor == 1) {
          ancorax = poligono->selectInfEsq.x;
          ancoray = poligono->selectInfEsq.y;
        } else if (menor == 2) {
          ancorax = poligono->selectSupDir.x;
          ancoray = poligono->selectSupDir.y;
        } else {
          ancorax = poligono->selectSupEsq.x;
          ancoray = poligono->selectSupEsq.y;
        }

        // Calculamos a distancia/modulo de onde clicamos e do ponto de
        // ancoragem
        distNoClick = distancia(clickX, clickY, ancorax, ancoray);

        // Certificar que se a pessoa clicar no canto mas não mexer o mouse ela
        // n vai fazer uma multiplicação por zero
        distNoRelease = distNoClick;

        // ligando a flag que diz que estamos arrastando o mouse
        arrastando = 1;
      }

    } else {
      // Se estamos dentro desse else significa que o botão foi solto.
      // Logo verificamos se estavamos previamente arrastando.
      if (arrastando == 1) {
        // Evitando divisão por 0
        if (distNoClick > 0.001) {

          // Multiplicador que guarda quando o mouse viajou para multiplicar as
          // coordenadas dos pontos
          multiplicador = distNoRelease / distNoClick;
          fazerEscala(poligono, multiplicador, ancorax, ancoray);
          // Calculamos novamente os cantos de seleção desse poligono.
          getCantosSelect(poligono);
        }
        // Chamamos espacoDeDesenho de novo.
        glutPostRedisplay();
      }
      arrastando = 0;
    }
    break;
  case CISALHA:
    if (state == GLUT_DOWN) {

      // Calcula a distancia do clique do mouse de um dos cantinhos de seleção

      //  de origem na callback de motion
      origemX = clickX;
      origemY = clickY;
      getCantosSelect(poligono);

      double dc[4];
      dc[0] = distancia(clickX, clickY, poligono->selectSupEsq.x,
                        poligono->selectSupEsq.y);
      dc[1] = distancia(clickX, clickY, poligono->selectSupDir.x,
                        poligono->selectSupDir.y);
      dc[2] = distancia(clickX, clickY, poligono->selectInfEsq.x,
                        poligono->selectInfEsq.y);
      dc[3] = distancia(clickX, clickY, poligono->selectInfDir.x,
                        poligono->selectInfDir.y);
      int menor = 0;
      int segundoMenor = 1;

      if (dc[segundoMenor] < dc[menor]) {
        int temp = menor;
        menor = segundoMenor;
        segundoMenor = temp;
      }

      for (int i = 2; i < 4; i++) {
        if (dc[i] < dc[menor]) {
          segundoMenor = menor;
          menor = i;
        } else if (dc[i] < dc[segundoMenor]) {
          segundoMenor = i;
        }
      }

      if (dc[menor] < 1000) {

        if (menor < segundoMenor) {
          a = menor;
          b = segundoMenor;
        } else {
          a = segundoMenor;
          b = menor;
        }
        distNoClick = distancia(clickX, clickY, poligono->selectInfEsq.x,
                                poligono->selectInfEsq.y);
        distNoRelease = distNoClick;
        arrastando = 1;
      }

    } else {
      if (arrastando) {

        if (a == 0 && b == 1) {
          double altura = poligono->selectSupEsq.y - poligono->selectInfEsq.y;
          if (altura > 0.001) {
            fazerCisalhamentoHorizontal(poligono, deslocX / altura);
          }
        } else if (a == 2 && b == 3) {
          double altura = poligono->selectSupEsq.y - poligono->selectInfEsq.y;
          if (altura > 0.001) {
            fazerCisalhamentoHorizontal(poligono, deslocX / altura);
          }
        } else if (a == 0 && b == 2) {
          double largura = poligono->selectSupDir.x - poligono->selectSupEsq.x;
          if (largura > 0.001) {
            fazerCisalhamentoVertical(poligono, deslocY / largura);
          }
        } else if (a == 1 && b == 3) {
          double largura = poligono->selectSupDir.x - poligono->selectSupEsq.x;
          if (largura > 0.001) {
            fazerCisalhamentoVertical(poligono, deslocY / largura);
          }
        }

        getCantosSelect(poligono);
        glutPostRedisplay();
      }
      arrastando = 0;
    }
    break;

  default:
    if (limpou != 0) {
      limpou = 0;
      break;
    }
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) {

      break;
    }
    if (poligono->numPontos < 6) {
      poligono->rgbPonto[0] = 1;
      poligono->rgbPonto[1] = 0;
      poligono->rgbPonto[2] = 0;
      novo_ponto(clickX, clickY, poligono);
      glutPostRedisplay();
    }
    break;
  }
}

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
void menuCurvas(int escolha) {}
void menuTransformacao(int escolha) {

  switch (escolha) {
  case TRANSLACAO:
    poligono->opcaoTransformacao = TRANSLACAO;
    break;

  case ROTACAO:
    poligono->opcaoTransformacao = ROTACAO;
    break;

  case ESCALA:
    poligono->opcaoTransformacao = ESCALA;
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

void posicaoMouse(int x, int y) {

  switch (poligono->opcaoTransformacao) {
  case TRANSLACAO:
    if (arrastando) {
      int posicaoAgoraX = x - poligono->janelaLargura;
      int posicaoAgoraY = poligono->janelaAltura - y;

      fazerTranslacao(posicaoAgoraX - origemX, posicaoAgoraY - origemY,
                      poligono);

      baricentroPoligono(poligono);
      // faz o reancoramento da posicao do mouse para centralizar de novo.
      origemX = posicaoAgoraX;
      origemY = posicaoAgoraY;

      glutPostRedisplay();
    }
    break;
  case ROTACAO:
    if (arrastando) {
      int posicaoAgoraX = x - poligono->janelaLargura;
      int posicaoAgoraY = poligono->janelaAltura - y;

      double anguloAntes = atan2(origemY - poligono->baricentroY,
                                 origemX - poligono->baricentroX);
      double anguloAgora = atan2(posicaoAgoraY - poligono->baricentroY,
                                 posicaoAgoraX - poligono->baricentroX);
      float delta = anguloAgora - anguloAntes;

      fazerRotacao(poligono, delta);

      origemX = posicaoAgoraX;
      origemY = posicaoAgoraY;

      glutPostRedisplay();
    }
    break;

  case ESCALA:

    if (arrastando == 1) {
      // Pega a posição atual do mouse para comparar
      int posicaoAgoraX = x - poligono->janelaLargura;
      int posicaoAgoraY = poligono->janelaAltura - y;

      // guarda o valor da distancia entre o mouse e a ancora quando o botão
      // foi solto.
      distNoRelease = distancia(posicaoAgoraX, posicaoAgoraY, ancorax, ancoray);

      glutPostRedisplay();
    }
    break;

  case CISALHA:
    if (arrastando == 1) {
      int posicaoAgoraX = x - poligono->janelaLargura;
      int posicaoAgoraY = poligono->janelaAltura - y;

      deslocX = posicaoAgoraX - origemX;
      deslocY = posicaoAgoraY - origemY;

      glutPostRedisplay();
    }
    break;
  }
}

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

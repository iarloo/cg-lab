#include "mouse.h"
#include "../transformacoes/transformacoes.h"
#include "constantes.h"
#include "desenhos.h"
#include "globals.h"
#include "vertices.h"
#include <GL/glut.h>
#include <math.h>
void mouseTranslacao(int state, int clickX, int clickY) {
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
}

void mouseRotacao(int state, int clickX, int clickY) {
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
}

void mouseEscala(int state, int clickX, int clickY) {
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

        setAngulos(poligono);
      }
      // Chamamos espacoDeDesenho de novo.
      glutPostRedisplay();
    }
    arrastando = 0;
  }
}

void mouseCisalha(int state, int clickX, int clickY) {
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
}

void mouseDefault(int button, int state, int clickX, int clickY) {
  if (limpou != 0) {
    limpou = 0;
    return;
  }
  if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
    return;

  if (poligono->numPontos < MAX_VERTICES) {
    poligono->rgbPonto[0] = 1;
    poligono->rgbPonto[1] = 0;
    poligono->rgbPonto[2] = 0;
    novo_ponto(clickX, clickY, poligono);

    if (poligono->numPontos >= 3) {
      setAngulos(poligono);
    }
    getCantosSelect(poligono);

    glutPostRedisplay();
  }
}

void mouse(int button, int state, int x, int y) {

  // Guardando as coordenadas de onde o clique do mouse foi feito.
  int clickX = x - poligono->janelaLargura;
  int clickY = poligono->janelaAltura - y;

  // Qual opção está ativa ?
  switch (poligono->opcaoTransformacao) {

  case TRANSLACAO:
    mouseTranslacao(state, clickX, clickY);
    break;

  case ROTACAO:
    mouseRotacao(state, clickX, clickY);
    break;

  case ESCALA:
    mouseEscala(state, clickX, clickY);
    break;

  case CISALHA:
    mouseCisalha(state, clickX, clickY);
    break;

  default:
    mouseDefault(button, state, clickX, clickY);
    break;
  }
}

void motionTranslacao(int x, int y) {
  if (arrastando) {
    int posicaoAgoraX = x - poligono->janelaLargura;
    int posicaoAgoraY = poligono->janelaAltura - y;

    fazerTranslacao(posicaoAgoraX - origemX, posicaoAgoraY - origemY, poligono);

    baricentroPoligono(poligono);
    // faz o reancoramento da posicao do mouse para centralizar de novo.
    origemX = posicaoAgoraX;
    origemY = posicaoAgoraY;

    glutPostRedisplay();
  }
}

void motionRotacao(int x, int y) {
  if (arrastando) {
    int posicaoAgoraX = x - poligono->janelaLargura;
    int posicaoAgoraY = poligono->janelaAltura - y;

    double anguloAntes =
        atan2(origemY - poligono->baricentroY, origemX - poligono->baricentroX);
    double anguloAgora = atan2(posicaoAgoraY - poligono->baricentroY,
                               posicaoAgoraX - poligono->baricentroX);
    float delta = anguloAgora - anguloAntes;

    fazerRotacao(poligono, delta);

    origemX = posicaoAgoraX;
    origemY = posicaoAgoraY;

    glutPostRedisplay();
  }
}

void motionEscala(int x, int y) {
  if (arrastando == 1) {
    // Pega a posição atual do mouse para comparar
    int posicaoAgoraX = x - poligono->janelaLargura;
    int posicaoAgoraY = poligono->janelaAltura - y;

    // guarda o valor da distancia entre o mouse e a ancora quando o botão
    // foi solto.
    distNoRelease = distancia(posicaoAgoraX, posicaoAgoraY, ancorax, ancoray);

    glutPostRedisplay();
  }
}

void motionCisalha(int x, int y) {
  if (arrastando == 1) {
    int posicaoAgoraX = x - poligono->janelaLargura;
    int posicaoAgoraY = poligono->janelaAltura - y;

    deslocX = posicaoAgoraX - origemX;
    deslocY = posicaoAgoraY - origemY;

    glutPostRedisplay();
  }
}

void posicaoMouse(int x, int y) {

  switch (poligono->opcaoTransformacao) {
  case TRANSLACAO:
    motionTranslacao(x, y);
    break;
  case ROTACAO:
    motionRotacao(x, y);
    break;
  case ESCALA:
    motionEscala(x, y);
    break;
  case CISALHA:
    motionCisalha(x, y);
    break;
  }
}

cmake_minimum_required(VERSION 3.16)

project(Trabalho_1 C)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(
  programa
  main.c
  mouse.c
  menu.c
  janela.c
  desenhos.c
  transformacoes.c
  vertices.c
  globals.h
  mouse.h
  menu.h
  janela.h
  desenhos.h
  transformacoes.h
  vertices.h)
add_executable(teste basicGlutGlCurvaFechadaTransformaTrab2026.c)

target_link_libraries(programa PRIVATE GLUT::GLUT OpenGL::GLU OpenGL::GL m)

target_link_libraries(teste PRIVATE GLUT::GLUT OpenGL::GLU OpenGL::GL m)

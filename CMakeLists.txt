cmake_minimum_required(VERSION 3.16)

project(Trabalho_1 C)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(
  programa
  constantes.c
  main.c
  vertices.c
  vertices.h
  desenhos.h
  desenhos.c
  transformacoes.c
  transformacoes.h)
add_executable(teste basicGlutGlCurvaFechadaTransformaTrab2026.c)

target_link_libraries(programa PRIVATE GLUT::GLUT OpenGL::GLU OpenGL::GL m)

target_link_libraries(teste PRIVATE GLUT::GLUT OpenGL::GLU OpenGL::GL m)

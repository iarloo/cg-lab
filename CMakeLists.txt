cmake_minimum_required(VERSION 3.10)
project(cg-lab C)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(
  cg-lab
  src/main.c
  src/mouse.c
  src/menu.c
  src/janela.c
  src/desenhos.c
  src/vertices.c
  transformacoes/transformacoes.c)

target_include_directories(
  cg-lab PRIVATE src transformacoes
                 # cores animacao
)

target_link_libraries(cg-lab OpenGL::GL OpenGL::GLU GLUT::GLUT m)

cmake_minimum_required(VERSION 3.10)
project(cg-lab C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
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
  transformacoes/transformacoes.c
  curvas/curvas.c)

target_include_directories(
  cg-lab PRIVATE src transformacoes curvas
                 # cores animacao
)

target_link_libraries(cg-lab OpenGL::GL OpenGL::GLU GLUT::GLUT m)

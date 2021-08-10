cmake_minimum_required(VERSION 3.19)
project(trabalhopratico C)

set(CMAKE_C_STANDARD 99)

add_executable(trabalhopratico main.c insereDados.c menu1.c mostraDados.c verificaDados.c jogo.h utils.h utils.c estruturas.c estruturas.h fich.c)
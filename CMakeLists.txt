cmake_minimum_required(VERSION 3.29)
project(projetoMaromo C)

set(CMAKE_C_STANDARD 11)

add_executable(projetoMaromo main.c
        tratamentoentrada.h
        tratamentoentrada.c
        cadastrarDoador.h
)

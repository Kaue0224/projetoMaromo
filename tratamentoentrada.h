#ifndef TRATAMENTOENTRADA_H
#define TRATAMENTOENTRADA_H

#include "cadastrarDoador.h"

void limparTela();

void apagarfila();

void verificarfilastdin(char *entrada);

int verificarEmail(char email[]);

int verificarTelefone(char telefone[]);

int validardata(char data[]);

void listarTopDoadores();

int encontrarDoadorPorEmail(const char *emailBusca, Doador *doadorEncontrado);

#endif

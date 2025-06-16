
#ifndef CADASTRARDOADOR_H
#define CADASTRARDOADOR_H

typedef struct {
  char nome[100];
  char email[100];
  char telefone[11];
  double valor_doacao;
  char data_ultima_doacao[11];
} Doador;

void cadastrarDoador(Doador);

int processarCadastro(char *linha, Doador *doador);

#endif //CADASTRARDOADOR_H

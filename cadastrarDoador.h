// Arquivo: cadastrarDoador.h (ou doador.h)

#ifndef CADASTRARDOADOR_H
#define CADASTRARDOADOR_H

#define MAX_DOADORES 500

// 1. A DEFINIÇÃO DA STRUCT
typedef struct {
    char nome[100];
    char email[100];
    char telefone[20];
    double valor_doacao;
    char data_ultima_doacao[11];
} Doador;

// 2. APENAS OS PROTÓTIPOS DAS FUNÇÕES
void cadastrarUser();

void pesquisarUser();

void removerUser();

void atualizarInformacoes();

void listarTopDoadores();

#endif //CADASTRARDOADOR_H

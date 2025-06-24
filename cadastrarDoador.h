#include <stdio.h>
#include <string.h>
#include "tratamentoentrada.h"


typedef struct {
  char nome[100];
  char email[100];
  char telefone[11];
  double valor_doacao;
  char data_ultima_doacao[11];
} Doador;

void removerBarraNcsv(Doador *doador) {

    doador->nome[strcspn(doador->nome, "\n")] = '\0';
    doador->email[strcspn(doador->email, "\n")] = '\0';
    doador->telefone[strcspn(doador->telefone, "\n")] = '\0';
    doador->data_ultima_doacao[strcspn(doador->data_ultima_doacao, "\n")] = '\0';


}


void cadastrarUser(){

    Doador doador;

    printf("\ndigite o nome do doador: ");
    fgets(doador.nome, sizeof(doador.nome), stdin);
    verificarfilastdin(doador.nome);

    printf("\ndigite o email do doador: ");
    fgets(doador.email, sizeof(doador.email), stdin);
    verificarfilastdin(doador.email);

    printf("\ndigite o telefone do doador: ");
    fgets(doador.telefone, sizeof(doador.telefone), stdin);
    verificarfilastdin(doador.telefone);

    printf("\ndigite o valor da doacao: ");
    scanf("%lf", &doador.valor_doacao);
    apagarfila();

    printf("\ndigite a data da ultima doacao: ");
    fgets(doador.data_ultima_doacao, sizeof(doador.data_ultima_doacao), stdin);
    verificarfilastdin(doador.data_ultima_doacao);

    FILE *fptr;

    fptr = fopen("C:/Users/kaued/CLionProjects/projetoMaromo/doadores.csv", "a");
    if(fptr == NULL) {
        printf("erro ao abrir");
        return;
    }

    removerBarraNcsv(&doador);

    fprintf(fptr, "\"%s\",%s,%s,%0.5lf,%s\n",
        doador.nome,
        doador.email,
        doador.telefone,
        doador.valor_doacao,
        doador.data_ultima_doacao

    );

    fclose(fptr);
    printf("Doador cadastrado com sucesso!\n");
}



void editarUser(Doador doador){}


void pesquisarUser() {
    char emailBusca[100];

    printf("\n=== PESQUISA DE DOADOR POR EMAIL ===\n");
    printf("Digite o email para pesquisa: ");
    fgets(emailBusca, sizeof(emailBusca), stdin);
    verificarfilastdin(emailBusca);
    emailBusca[strcspn(emailBusca, "\n")] = '\0';

    FILE *fptr = fopen("C:/Users/kaued/CLionProjects/projetoMaromo/doadores.csv", "r");
    if (fptr == NULL) {
        perror("Erro ao abrir doadores.csv");
        return;
    }

    char linha[512];
    int encontrou = 0;
    int linhaAtual = 0;

    while (fgets(linha, sizeof(linha), fptr)) {
        linhaAtual++;

        if (linhaAtual == 1) continue; // pula o cabeçalho

        // quebra a linha
        char *nome = strtok(linha, ",");
        char *email = strtok(NULL, ",");
        char *telefone = strtok(NULL, ",");
        char *valor = strtok(NULL, ",");
        char *data = strtok(NULL, "\n");

        // remove aspas iniciais e finais do nome
        if (nome && nome[0] == '"') {
            nome++; // pula aspas inicial
            char *aspasFinal = strrchr(nome, '"');
            if (aspasFinal) *aspasFinal = '\0'; // remove aspas final
        }

        if (email != NULL && strcmp(emailBusca, email) == 0) {
            printf("\n--- DOADOR ENCONTRADO ---\n");
            printf("Nome: %s\n", nome);
            printf("Email: %s\n", email);
            printf("Telefone: %s\n", telefone);
            printf("Valor da doacao: %s\n", valor);
            printf("Data da ultima doacao: %s\n", data);
            encontrou = 1;
            break;
        }
    }

    if (!encontrou) {
        printf("\nNenhum doador com esse email foi encontrado.\n");
    }

    fclose(fptr);
}


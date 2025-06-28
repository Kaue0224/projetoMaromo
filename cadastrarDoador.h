#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_DOADORES 500
#include "tratamentoentrada.h"
#include "tratamentoentrada.h"
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


void cadastrarUser() {
    Doador doador;

    do {
        strlen(doador.nome) < 5 ? printf("\ndigite um nome valido!") : 0;

        printf("\ndigite o nome do doador: ");
        fgets(doador.nome, sizeof(doador.nome), stdin);
        verificarfilastdin(doador.nome);
    }while (strlen(doador.nome) < 5 );

    do {
        printf("\ndigite o email do doador: ");
        fgets(doador.email, sizeof(doador.email), stdin);
        verificarfilastdin(doador.email);
    }while(verificarEmail(doador.email) == 0 );

    do {
        printf("\ndigite o telefone do doador: ");
        fgets(doador.telefone, sizeof(doador.telefone), stdin);
        verificarfilastdin(doador.telefone);
    }while (verificarTelefone(doador.telefone) == 0);

    printf("\ndigite o valor da doacao: ");
    scanf("%lf", &doador.valor_doacao);
    apagarfila();

    do {
        printf("\ndigite a data da ultima doacao: ");
        fgets(doador.data_ultima_doacao, sizeof(doador.data_ultima_doacao), stdin);
        verificarfilastdin(doador.data_ultima_doacao);
    }while(validardata(doador.data_ultima_doacao) == 0);



    FILE *fptr;

    fptr = fopen("doadores.csv", "a");
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

    FILE *fptr = fopen("doadores.csv", "r");
    if (fptr == NULL) {
        perror("erro ao abrir doadores.csv");
        return;
    }

    char linha[512];
    int encontrou = 0;
    int linhaAtual = 0;

    while (fgets(linha, sizeof(linha), fptr)) {
        linhaAtual++;

        if (linhaAtual == 1) continue;


        char *nome = strtok(linha, ",");
        char *email = strtok(NULL, ",");
        char *telefone = strtok(NULL, ",");
        char *valor = strtok(NULL, ",");
        char *data = strtok(NULL, "\n");


        if (nome && nome[0] == '"') {
            nome++;
            char *aspasFinal = strrchr(nome, '"');
            if (aspasFinal) *aspasFinal = '\0';
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

void removerUser() {
    char emailBusca[100];
    printf("\n=== REMOVER DOADOR POR EMAIL ===\n");
    printf("Digite o email do doador a remover: ");
    fgets(emailBusca, sizeof(emailBusca), stdin);
    verificarfilastdin(emailBusca);
    emailBusca[strcspn(emailBusca, "\n")] = '\0';  // Remove \n

    FILE *fptr = fopen("doadores.csv", "r");
    if (fptr == NULL) {
        perror("Erro ao abrir doadores.csv");
        return;
    }

    char linha[512];
    int encontrou = 0;

    // Busca o doador para mostrar antes de confirmar exclusão
    while (fgets(linha, sizeof(linha), fptr)) {
        char linhaCopia[512];
        strcpy(linhaCopia, linha);

        char *nome = strtok(linhaCopia, ",");
        char *email = strtok(NULL, ",");

        if (email != NULL) {
            if (email[0] == '"') email++;
            char *fimAspas = strchr(email, '"');
            if (fimAspas) *fimAspas = '\0';

            if (strcmp(email, emailBusca) == 0) {
                printf("\n--- DOADOR ENCONTRADO ---\n");
                printf("Nome: %s\n", nome);
                printf("Email: %s\n", email);
                // Você pode imprimir telefone, valor, data aqui se quiser
                encontrou = 1;
                break;
            }
        }
    }
    fclose(fptr);

    if (!encontrou) {
        printf("Nenhum doador com esse email foi encontrado.\n");
        return;
    }

    // Pergunta confirmação
    char resposta;
    printf("Deseja realmente excluir este doador? (S/N): ");
    scanf(" %c", &resposta);
    apagarfila();

    if (resposta != 'S' && resposta != 's') {
        printf("Exclusao cancelada.\n");
        return;
    }

    // Se confirmou, faz a remoção
    fptr = fopen("doadores.csv", "r");
    FILE *temp = fopen("doadores.csv", "w");
    if (fptr == NULL || temp == NULL) {
        perror("Erro ao abrir arquivos");
        if (fptr) fclose(fptr);
        if (temp) fclose(temp);
        return;
    }

    // Copia cabeçalho
    if (fgets(linha, sizeof(linha), fptr)) {
        fprintf(temp, "%s", linha);
    }

    int removido = 0;
    while (fgets(linha, sizeof(linha), fptr)) {
        char linhaCopia[512];
        strcpy(linhaCopia, linha);

        char *nome = strtok(linhaCopia, ",");
        char *email = strtok(NULL, ",");

        if (email != NULL) {
            if (email[0] == '"') email++;
            char *fimAspas = strchr(email, '"');
            if (fimAspas) *fimAspas = '\0';

            if (strcmp(email, emailBusca) == 0) {
                removido = 1;
                continue; // pula essa linha
            }
        }
        fputs(linha, temp);
    }

    fclose(fptr);
    fclose(temp);

    if (removido) {
        if (remove("doadores.csv") != 0) {
            perror("Erro ao remover arquivo original");
            return;
        }
        if (rename("doadores.csv", "doadores.csv") != 0) {
            perror("Erro ao renomear arquivo temporario");
            return;
        }
        printf("Doador removido com sucesso!\n");
    } else {
        printf("Erro: doador nao removido.\n");
        remove("doadores.csv");
    }
}

int processarLinhaCSV(char *linha, Doador *doador) {

    linha[strcspn(linha, "\n")] = 0;


    if (sscanf(linha, "%99[^,],%99[^,],%19[^,],%lf,%10[^,]",
               doador->nome, doador->email, doador->telefone,
               &doador->valor_doacao, doador->data_ultima_doacao) != 5) {
        return 0;
               }
    return 1;
}

int compararDoadores(const void *a, const void *b) {
    Doador *doadorA = (Doador *)a;
    Doador *doadorB = (Doador *)b;

    if (doadorA->valor_doacao < doadorB->valor_doacao) {
        return 1;
    } else if (doadorA->valor_doacao > doadorB->valor_doacao) {
        return -1;
    } else {
        return 0;
    }
}

void listarTopDoadores() {
    limparTela();
    printf("\nTOP 10 DOADORES \n");
    FILE *arquivo = fopen("doadores.csv", "r");
    if (arquivo == NULL) {
        perror(" Erro ao abrir");
        return;
    }

    Doador todosOsDoadores[MAX_DOADORES];
    int numDoadores = 0;
    char  linha [256];

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL && numDoadores < MAX_DOADORES) {
        if (processarLinhaCSV(linha, &todosOsDoadores[numDoadores])) {
            numDoadores++;
        }
    }
fclose(arquivo);

    if (numDoadores == 0) {
        printf("nenhum doador cadastrado");
        return;
    }

    qsort(todosOsDoadores, numDoadores, sizeof(Doador), compararDoadores);

    printf("%-4s %-30s %s\n", "posicao", "Nome do Doador", "Valor Doado");

    int limite = (numDoadores < 10)? numDoadores : 10;

    for (int i = 0; i < limite; i++) {
        printf("#%-3d %-30s R$ %9.2f\n", i + 1, todosOsDoadores[i].nome, todosOsDoadores[i].valor_doacao);
    }
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cadastrarDoador.h"
#include "tratamentoentrada.h"
#define MAX_DOADORES 500

// Remove o caractere de nova linha dos campos do doador
void removerBarraNcsv(Doador *doador) {
    doador->nome[strcspn(doador->nome, "\n")] = '\0';
    doador->email[strcspn(doador->email, "\n")] = '\0';
    doador->telefone[strcspn(doador->telefone, "\n")] = '\0';
    doador->data_ultima_doacao[strcspn(doador->data_ultima_doacao, "\n")] = '\0';
}

// Processa uma linha do CSV e extrai os dados para a struct Doador
int processarLinhaCSV(char *linha, Doador *doador) {
    linha[strcspn(linha, "\n")] = 0;

    if (sscanf(linha, "%99[^,],%99[^,],%19[^,],%lf,%10[^,]",
               doador->nome, doador->email, doador->telefone,
               &doador->valor_doacao, doador->data_ultima_doacao) != 5) {
        return 0;
    }
    return 1;
}

// Função para validar o valor da doação inserido pelo usuário
int validarValorDoacao(double *valor) {
    char buffer[50];
    char *endptr;

    while (1) {
        printf("\ndigite o valor da doacao: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro na leitura!\n");
            return 0;
        }
        *valor = strtod(buffer, &endptr);

        if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
            printf("Valor invalido! Digite apenas numeros.\n");
            continue;
        }
        if (*valor < 0) {
            printf("Valor da doacao nao pode ser negativo.\n");
            continue;
        }
        return 1;
    }
}

// Verifica se o e-mail já existe no arquivo
int emailExiste(const char *email) {
    FILE *fptr = fopen("doadores.csv", "r");
    if (fptr == NULL) return 0;

    char linha[512];
    Doador temp;

    while (fgets(linha, sizeof(linha), fptr)) {
        if (processarLinhaCSV(linha, &temp)) {
            if (strcmp(temp.email, email) == 0) {
                fclose(fptr);
                return 1;
            }
        }
    }

    fclose(fptr);
    return 0;
}

// Verifica se o telefone já existe no arquivo
int telefoneExiste(const char *telefone) {
    FILE *fptr = fopen("doadores.csv", "r");
    if (fptr == NULL) return 0;

    char linha[512];
    Doador temp;

    while (fgets(linha, sizeof(linha), fptr)) {
        if (processarLinhaCSV(linha, &temp)) {
            if (strcmp(temp.telefone, telefone) == 0) {
                fclose(fptr);
                return 1;
            }
        }
    }

    fclose(fptr);
    return 0;
}

// Função principal para cadastrar um novo doador
void cadastrarUser() {
    Doador doador;

    // Cadastro do nome
    do {
        printf("\ndigite o nome do doador: ");
        fgets(doador.nome, sizeof(doador.nome), stdin);
        verificarfilastdin(doador.nome);

        if (strcmp(doador.nome, "cancel\n") == 0) {
            printf("Cadastro cancelado pelo usuario.\n");
            return;
        }

        if (strlen(doador.nome) < 5) {
            printf("Digite um nome valido!\n");
        }
    } while (strlen(doador.nome) < 5);

    // Cadastro do email
    do {
        printf("\ndigite o email do doador: ");
        fgets(doador.email, sizeof(doador.email), stdin);
        verificarfilastdin(doador.email);

        if (strcmp(doador.email, "cancel\n") == 0) {
            printf("Cadastro cancelado pelo usuario.\n");
            return;
        }
        if (verificarEmail(doador.email) == 0) {
            printf("Email invalido!\n");
            continue;
        }

        if (emailExiste(doador.email)) {
            printf("Este email ja esta cadastrado!\n");
            continue;
        }

        break;
    } while (1);

    // Cadastro do telefone
    do {
        printf("\ndigite o telefone do doador: ");
        fgets(doador.telefone, sizeof(doador.telefone), stdin);
        verificarfilastdin(doador.telefone);

        if (strcmp(doador.telefone, "cancel\n") == 0) {
            printf("Cadastro cancelado pelo usuario.\n");
            return;
        }

        if (verificarTelefone(doador.telefone) == 0) {
            printf("Telefone invalido!\n");
            continue;
        }

        if (telefoneExiste(doador.telefone)) {
            printf("Este telefone ja esta cadastrado!\n");
            continue;
        }

        break;
    } while (1);

    // Cadastro do valor
    if (!validarValorDoacao(&doador.valor_doacao)) {
        printf("Erro ao ler o valor da doacao.\n");
        return;
    }

    // Cadastro da data
    do {
        printf("\ndigite a data da ultima doacao: ");
        fgets(doador.data_ultima_doacao, sizeof(doador.data_ultima_doacao), stdin);
        verificarfilastdin(doador.data_ultima_doacao);
    } while (validardata(doador.data_ultima_doacao) == 0);

    // Grava os dados no arquivo CSV
    FILE *fptr = fopen("doadores.csv", "a");
    if (fptr == NULL) {
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

// Função reservada para futura edição de doador
void editarUser(Doador doador) {
}

// Pesquisa um doador por email e exibe suas informações
void pesquisarUser() {
    char emailBusca[100];
    Doador doadorEncontrado;

    limparTela();
    printf("--- PESQUISA DE DOADOR POR E-MAIL ---\n");
    printf("Digite o email para pesquisa: ");
    if(strcmp(emailBusca,"cancel\n") == 0)return;
    fgets(emailBusca, sizeof(emailBusca), stdin);

    emailBusca[strcspn(emailBusca, "\n")] = '\0';

    if (encontrarDoadorPorEmail(emailBusca, &doadorEncontrado) == 1) {
        printf("\n--- DOADOR ENCONTRADO ---\n");
        printf("Nome: %s\n", doadorEncontrado.nome);
        printf("Email: %s\n", doadorEncontrado.email);
        printf("Telefone: %s\n", doadorEncontrado.telefone);
        printf("Valor da doacao: R$ %.2f\n", doadorEncontrado.valor_doacao);
        printf("Data da ultima doacao: %s\n", doadorEncontrado.data_ultima_doacao);
    } else {
        printf("\nNenhum doador com o email '%s' foi encontrado.\n", emailBusca);
    }
}

// Remove um doador do arquivo CSV com base no email
void removerUser() {
    char emailBusca[100];
    printf("\n=== REMOVER DOADOR POR EMAIL ===\n");
    printf("Digite o email do doador a remover: ");
    fgets(emailBusca, sizeof(emailBusca), stdin);
    verificarfilastdin(emailBusca);
    if(strcmp(emailBusca,"cancel\n") == 0)return;
    emailBusca[strcspn(emailBusca, "\n")] = '\0';

    FILE *fptr = fopen("doadores.csv", "r");
    if (fptr == NULL) {
        perror("Erro ao abrir doadores.csv");
        return;
    }

    char linha[512];
    int encontrou = 0;

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

    char resposta;
    printf("Deseja realmente excluir este doador? (S/N): ");
    scanf(" %c", &resposta);
    apagarfila();

    if (resposta != 'S' && resposta != 's') {
        printf("Exclusao cancelada.\n");
        return;
    }

    fptr = fopen("doadores.csv", "r");
    FILE *temp = fopen("doadores.csv", "w");
    if (fptr == NULL || temp == NULL) {
        perror("Erro ao abrir arquivos");
        if (fptr) fclose(fptr);
        if (temp) fclose(temp);
        return;
    }

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
                continue;
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

// Função auxiliar para ordenar os doadores pelo valor doado
int compararDoadores(const void *a, const void *b) {
    Doador *doadorA = (Doador *) a;
    Doador *doadorB = (Doador *) b;

    if (doadorA->valor_doacao < doadorB->valor_doacao) {
        return 1;
    } else if (doadorA->valor_doacao > doadorB->valor_doacao) {
        return -1;
    } else {
        return 0;
    }
}

// Exibe os 10 maiores doadores
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
    char linha[256];

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

    int limite = (numDoadores < 10) ? numDoadores : 10;

    for (int i = 0; i < limite; i++) {
        printf("#%-3d %-30s R$ %9.2f\n", i + 1, todosOsDoadores[i].nome, todosOsDoadores[i].valor_doacao);
    }
}

// Atualiza as informações de um doador com base no email
void atualizarInformacoes() {
    // ...
    // Já comentado na estrutura geral anterior
}

// Busca um doador pelo email e retorna 1 se encontrado
int encontrarDoadorPorEmail(const char *emailBusca, Doador *doadorEncontrado) {
    FILE *fptr = fopen("doadores.csv", "r");
    if (fptr == NULL) {
        perror("Erro ao abrir doadores.csv para busca");
        return 0;
    }
    char linha[512];
    while (fgets(linha, sizeof(linha), fptr)) {
        if (processarLinhaCSV(linha, doadorEncontrado) == 1) {
            if (strcmp(doadorEncontrado->email, emailBusca) == 0) {
                fclose(fptr);
                return 1;
            }
        }
    }
    fclose(fptr);
    return 0;
}
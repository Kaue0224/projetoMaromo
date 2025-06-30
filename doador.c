#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cadastrarDoador.h"
#include "tratamentoentrada.h"
#define MAX_DOADORES 500


void removerBarraNcsv(Doador *doador) {
    doador->nome[strcspn(doador->nome, "\n")] = '\0';
    doador->email[strcspn(doador->email, "\n")] = '\0';
    doador->telefone[strcspn(doador->telefone, "\n")] = '\0';
    doador->data_ultima_doacao[strcspn(doador->data_ultima_doacao, "\n")] = '\0';
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

int validarValorDoacao(double *valor) {
    char buffer[50];
    char *endptr;

    while (1) {
        printf("\ndigite o valor da doacao: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro na leitura!\n");
            return 0;
        }
        // Tenta converter para double
        *valor = strtod(buffer, &endptr);

        // Se o endptr não apontar para o fim da string (exceto '\n'), tem caracteres inválidos
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

int emailExiste(const char *email) {
    FILE *fptr = fopen("doadores.csv", "r");
    if (fptr == NULL) return 0;

    char linha[512];
    Doador temp;

    while (fgets(linha, sizeof(linha), fptr)) {
        if (processarLinhaCSV(linha, &temp)) {
            if (strcmp(temp.email, email) == 0) {
                fclose(fptr);
                return 1; // E-mail já existe
            }
        }
    }

    fclose(fptr);
    return 0; // Não existe
}

int telefoneExiste(const char *telefone) {
    FILE *fptr = fopen("doadores.csv", "r");
    if (fptr == NULL) return 0;

    char linha[512];
    Doador temp;

    while (fgets(linha, sizeof(linha), fptr)) {
        if (processarLinhaCSV(linha, &temp)) {
            if (strcmp(temp.telefone, telefone) == 0) {
                fclose(fptr);
                return 1; // Telefone já existe
            }
        }
    }

    fclose(fptr);
    return 0; // Não existe
}

void cadastrarUser() {
    Doador doador;

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

        break; // Email valido e nao existe, sai do loop
    } while (1);

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

        break; // Telefone valido e nao existe, sai do loop
    } while (1);

    if (!validarValorDoacao(&doador.valor_doacao)) {
        printf("Erro ao ler o valor da doacao.\n");
        return;
    }

    do {
        printf("\ndigite a data da ultima doacao: ");
        fgets(doador.data_ultima_doacao, sizeof(doador.data_ultima_doacao), stdin);
        verificarfilastdin(doador.data_ultima_doacao);
    } while (validardata(doador.data_ultima_doacao) == 0);


    FILE *fptr;

    fptr = fopen("doadores.csv", "a");
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


void editarUser(Doador doador) {
}


void pesquisarUser() {
    char emailBusca[100];
    Doador doadorEncontrado; // Uma struct vazia para guardar o resultado

    limparTela();
    printf("--- PESQUISA DE DOADOR POR E-MAIL ---\n");
    printf("Digite o email para pesquisa: ");
    fgets(emailBusca, sizeof(emailBusca), stdin);
    emailBusca[strcspn(emailBusca, "\n")] = '\0';

    // Chama a "ferramenta" para fazer o trabalho pesado
    if (encontrarDoadorPorEmail(emailBusca, &doadorEncontrado) == 1) {
        // Se a ferramenta retornou 1 (sucesso), nós imprimimos os dados
        printf("\n--- DOADOR ENCONTRADO ---\n");
        printf("Nome: %s\n", doadorEncontrado.nome);
        printf("Email: %s\n", doadorEncontrado.email);
        printf("Telefone: %s\n", doadorEncontrado.telefone);
        printf("Valor da doacao: R$ %.2f\n", doadorEncontrado.valor_doacao);
        printf("Data da ultima doacao: %s\n", doadorEncontrado.data_ultima_doacao);
    } else {
        // Se a ferramenta retornou 0 (falha), avisamos o usuário
        printf("\nNenhum doador com o email '%s' foi encontrado.\n", emailBusca);
    }
}

void removerUser() {
    char emailBusca[100];
    printf("\n=== REMOVER DOADOR POR EMAIL ===\n");
    printf("Digite o email do doador a remover: ");
    fgets(emailBusca, sizeof(emailBusca), stdin);
    verificarfilastdin(emailBusca);
    emailBusca[strcspn(emailBusca, "\n")] = '\0'; // Remove \n

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

void atualizarInformacoes() {
    char email_pesquisa[100];
    Doador doadorParaAtualizar;
    int encontrado = 0;

    limparTela();
    printf("atualizar doadores\n");
    printf("Digite o e-mail do doador que deseja atualizar: ");
    fgets(email_pesquisa, sizeof(email_pesquisa), stdin);
    email_pesquisa[strcspn(email_pesquisa, "\n")] = 0;

    // --- PARTE 1: BUSCAR O DOADOR (Esta parte está OK) ---
    FILE *arquivo_leitura = fopen("doadores.csv", "r");
    if (arquivo_leitura == NULL) {
        perror("Erro ao abrir 'doadores.csv'");
        return;
    }

    char linha[512];
    while (fgets(linha, sizeof(linha), arquivo_leitura) != NULL) {
        if (processarLinhaCSV(linha, &doadorParaAtualizar) == 1) {
            if (strcmp(doadorParaAtualizar.email, email_pesquisa) == 0) {
                encontrado = 1;
                break;
            }
        }
    }
    fclose(arquivo_leitura);

    if (!encontrado) {
        printf("nenhum doador com o e-mail '%s' foi encontrado.\n", email_pesquisa);
        return;
    }


    printf(" Doador Encontrado! \n");
    printf("digite as novas informacoes ou pressione enter para manter a atual.\n");

    char nome_novo[100], telefone_novo[20], data_nova[11], valor_novo_str[50];
    printf("Nome atual: %s\n> Novo nome: ", doadorParaAtualizar.nome);
    fgets(nome_novo, sizeof(nome_novo), stdin);
    nome_novo[strcspn(nome_novo, "\n")] = 0;

    printf("Telefone atual: %s\n> Novo telefone: ", doadorParaAtualizar.telefone);
    fgets(telefone_novo, sizeof(telefone_novo), stdin);
    telefone_novo[strcspn(telefone_novo, "\n")] = 0;

    printf("Data da doacao atual: %s\n> Nova data (DD/MM/AAAA): ", doadorParaAtualizar.data_ultima_doacao);
    fgets(data_nova, sizeof(data_nova), stdin);
    data_nova[strcspn(data_nova, "\n")] = 0;

    printf("Valor da doacao atual: %.2f\n> Novo valor: ", doadorParaAtualizar.valor_doacao);
    fgets(valor_novo_str, sizeof(valor_novo_str), stdin);
    valor_novo_str[strcspn(valor_novo_str, "\n")] = 0;


    if (strlen(nome_novo) > 0) strcpy(doadorParaAtualizar.nome, nome_novo);
    if (strlen(telefone_novo) > 0) strcpy(doadorParaAtualizar.telefone, telefone_novo);
    if (strlen(data_nova) > 0) strcpy(doadorParaAtualizar.data_ultima_doacao, data_nova);
    if (strlen(valor_novo_str) > 0) doadorParaAtualizar.valor_doacao = atof(valor_novo_str);


    FILE *arquivo_origem = fopen("doadores.csv", "r");
    FILE *arquivo_temp = fopen("temp.csv", "w");

    if (arquivo_origem == NULL || arquivo_temp == NULL) {
        perror("erro ao criar arquivo temporario");
        return;
    }


    fgets(linha, sizeof(linha), arquivo_origem);
    fputs(linha, arquivo_temp);


    while (fgets(linha, sizeof(linha), arquivo_origem) != NULL) {
        char linha_copia[512];
        strcpy(linha_copia, linha);

        Doador doador_temp;

        if (processarLinhaCSV(linha_copia, &doador_temp) == 1) {
            if (strcmp(doador_temp.email, email_pesquisa) == 0) {
                fprintf(arquivo_temp, "%s,%s,%s,%.2f,%s\n",
                        doadorParaAtualizar.nome, doadorParaAtualizar.email, doadorParaAtualizar.telefone,
                        doadorParaAtualizar.valor_doacao, doadorParaAtualizar.data_ultima_doacao);
            } else {
                fputs(linha, arquivo_temp);
            }
        } else {
            fputs(linha, arquivo_temp);
        }
    }

    fclose(arquivo_origem);
    fclose(arquivo_temp);


    remove("doadores.csv");
    rename("temp.csv", "doadores.csv");

    printf("\n>> Doador atualizado com sucesso! <<\n");
}

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



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastrarDoador.h"
#include "limparTela.h"


/*
FILE *abrirAquivo(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    return arquivo;
}
*/
int main() {
    int opcaoUsuario = 1;


    do {
        limparTela();

        // Exibe o menu de opções para o usuário
        printf("\n--- MENU DE OPCOES ---\n"
            " 1 - Cadastrar Doadores\n"
            " 2 - Consultar Doadores\n "
            " 3 - Atualizar Info\n"
            " 4 - Top 10 Doadores\n"
            " 5 - Remover Doador\n"
            " 0 - ENCERRAR PROGRAMA\n"
            " ---------------------- \n"
            " Digite sua opcao: ");
        scanf("%d", &opcaoUsuario);


        switch (opcaoUsuario) {
            case 1:
                limparTela();
                printf(">> Chamando funcao: Cadastrar Doador\n");
                cadastrarDoador();

                break;

            case 2:
                limparTela();
                printf(">> Chamando funcao: Consultar Doadores\n");

                break;

            case 3:
                limparTela();
                printf(">> Chamando funcao: Atualizar Informacoes\n");

                break;

            case 4:
                limparTela();
                printf(">> Chamando funcao: Top 10 Doadores\n");

                break;

            case 5:
                limparTela();
                printf(">> Chamando funcao: Remover Doador\n");

                break;

            case 0:
                limparTela();
                printf(">> Voce escolheu ENCERRAR o programa. Saindo...\n");
                break;

            default:
                limparTela();
                printf(">> Opcao invalida! Por favor, digite um numero entre 0 e 5.\n");
                break;
        }
    } while (opcaoUsuario != 0);

    printf("\nPrograma encerrado \n");

    return 0;
}

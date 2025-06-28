#include <string.h>
#include <stdio.h>
#include "cadastrarDoador.h"
#include "tratamentoentrada.h"


int main() {
    char opcaoUsuario[10];

    do {

        printf("\n--- MENU DE OPCOES ---\n"
            " 1 - Cadastrar Doadores\n"
            " 2 - Consultar Doadores\n "
            "3 - Atualizar Info\n"
            " 4 - Top 10 Doadores\n"
            " 5 - Remover Doador\n"
            " 0 - ENCERRAR PROGRAMA\n"
            " ---------------------- \n"
            " Digite sua opcao: ");
        fgets(opcaoUsuario,sizeof(opcaoUsuario), stdin);
        verificarfilastdin(opcaoUsuario);


        switch (opcaoUsuario[0]) {

            case '1': printf(">> Chamando funcao: Cadastrar Doador\n");cadastrarUser();break;;
            case '2': printf(">> Chamando funcao: Consultar Doadores\n");pesquisarUser();break;
            case '3': printf(">> Chamando funcao: Atualizar Informacoes\n");break;
            case '4': printf(">> Chamando funcao: Top 10 Doadores\n");listarTopDoadores();break;
            case '5': printf(">> Chamando funcao: Remover Doador\n");removerUser();break;
            case '0': printf(">> Voce escolheu ENCERRAR o programa. Saindo...\n");break;
            default: printf(">> Opcao invalida! Por favor, digite um numero entre 0 e 5.\n");break;

        }
    } while (opcaoUsuario[0] != 0);


    return 0;
}

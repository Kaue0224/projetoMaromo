// =============================================================================
// INCLUDES (BIBLIOTECAS E CABEÇALHOS)
// =============================================================================

// Inclui a biblioteca padrão de Entrada e Saída (Input/Output),
// necessária para funções como printf() e fgets().
#include <stdio.h>

// Inclui a biblioteca de manipulação de strings,
// necessária para funções como strcmp(), strcpy(), etc. (embora não usadas diretamente aqui).
#include <string.h>

// Inclui o "cardápio" de funções relacionadas aos doadores.
// Isso permite que o 'main' saiba que funções como cadastrarUser() e pesquisarUser() existem.
#include "cadastrarDoador.h" 

// Inclui o "cardápio" de funções utilitárias, como as de validação e limpeza de tela.
#include "tratamentoentrada.h" 

// =============================================================================
// FUNÇÃO PRINCIPAL (main)
// =============================================================================
// A função main é o ponto de entrada de qualquer programa em C.
// A execução sempre começa aqui.
int main() {
    // Declara um array de caracteres (uma string) para armazenar a opção
    // que o usuário digitará no menu.
    char opcaoUsuario[10];

    /*
     * Inicia um loop 'do-while'.
     * A principal característica do 'do-while' é que ele executa o bloco de código
     * PELO MENOS UMA VEZ antes de verificar a condição de parada.
     * Isso é perfeito para menus, pois garante que o menu seja exibido na primeira vez.
     */
    do {
        // Imprime o menu de opções formatado para o usuário na tela.
        printf("\n--- MENU DE OPCOES ---\n"
            " 1 - Cadastrar Doadores\n"
            " 2 - Consultar Doadores\n"
            " 3 - Atualizar Info\n"
            " 4 - Top 10 Doadores\n"
            " 5 - Remover Doador\n"
            " 0 - ENCERRAR PROGRAMA\n"
            " ---------------------- \n"
            " Digite sua opcao: ");

        // Lê a entrada do teclado de forma segura usando fgets.
        // Ele lê a linha inteira, incluindo o 'Enter' (\n), até o limite do array.
        fgets(opcaoUsuario, sizeof(opcaoUsuario), stdin);
        
        // Chama uma função do seu arquivo de tratamento para limpar o buffer do teclado
        // caso o usuário tenha digitado mais caracteres do que o array suporta.
        // Também é provável que esta função remova o '\n' do final da string.
        verificarfilastdin(opcaoUsuario);


        /*
         * A estrutura 'switch' é usada para tomar uma decisão com base no valor
         * de uma variável. É uma alternativa mais limpa a múltiplos 'if-else if'.
         * Aqui, estamos olhando apenas para o PRIMEIRO caractere digitado pelo usuário (opcaoUsuario[0]).
         */
        switch (opcaoUsuario[0]) {

            case '1': // Se o primeiro caractere for '1'
                printf(">> Chamando funcao: Cadastrar Doador\n");
                cadastrarUser(); // Chama a função que realiza o cadastro
                break; // 'break' é essencial para sair do switch e não "cair" no próximo case.

            case '2': // Se o primeiro caractere for '2'
                printf(">> Chamando funcao: Consultar Doadores\n");
                pesquisarUser(); // Chama a função que realiza a pesquisa
                break;

            case '3': // Se o primeiro caractere for '3'
                printf(">> Chamando funcao: Atualizar Informacoes\n");
                atualizarInformacoes(); // Chama a função que realiza a atualização
                break;

            case '4': // Se o primeiro caractere for '4'
                printf(">> Chamando funcao: Top 10 Doadores\n");
                listarTopDoadores(); // Chama a função que gera o ranking
                break;

            case '5': // Se o primeiro caractere for '5'
                printf(">> Chamando funcao: Remover Doador\n");
                removerUser(); // Chama a função que realiza a remoção
                break;

            case '0': // Se o primeiro caractere for '0'
                printf(">> Voce escolheu ENCERRAR o programa. Saindo...\n");
                // Não usamos 'return 0' aqui para permitir que o loop termine pela condição.
                break;

            default: // Se o caractere não for nenhum dos anteriores
                printf(">> Opcao invalida! Por favor, digite um numero entre 0 e 5.\n");
                break;
        }

    // Esta é a condição de parada do loop.
    // "Enquanto o primeiro caractere da opção do usuário for DIFERENTE do caractere '0'..."
    // "...continue repetindo o loop."
    // Quando o usuário digita '0', a condição se torna falsa e o programa sai do loop.
    } while (opcaoUsuario[0] != '0');

    // Esta linha só será executada depois que o loop terminar.
    printf("\nPrograma encerrado.\n");

    // Retorna 0 para o sistema operacional, indicando que o programa
    // terminou sua execução com sucesso.
    return 0;
}
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

    char opcaoUsuario[10];

    do {

        printf("\n--- MENU ---\n"
                     " 1 - pesquisar por id\n"
                     " 2 - pesquisar por email\n"
        );
        fgets(opcaoUsuario,sizeof(opcaoUsuario), stdin);
        verificarfilastdin(opcaoUsuario);


        switch (opcaoUsuario[0]) {
            case '1': printf("pesquisar por id"); break;
            case '2': printf("pesquisar por email: "); break;
            default: printf(">> Opcao invalida! Por favor, digite um numero entre 0 e 5.\n");break;

        }
    } while (opcaoUsuario != 0);



}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastrarDoador.h"




int processarCadastro(char *linha, Doador *doador) {
    linha[strcspn(linha, "\n")] = 0;
    if (sscanf(linha, "%99[^;];%99[^;];%19[^;];%lf;%10[^;]", doador->nome, doador->email, doador->telefone,
               &doador->valor_doacao, doador->data_ultima_doacao) != 5) {
        printf("a linha de cadastro deu erro. \n");
        return 0;
    }



    printf("deu bom %s \n", doador->nome);
    return 1;
}

#include <stdio.h>
#include <string.h>
#include "tratamentoentrada.h"

void limparTela() {
    for (int i = 0; i < 100; i++) {
        printf("\n");
    }
}

void apagarfila() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void verificarfilastdin(char *entrada) {
    if (strchr(entrada, '\n') == NULL) {
        apagarfila();
    }
}

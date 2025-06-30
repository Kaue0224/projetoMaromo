#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

int verificarTelefone(char str[]) {
    int len = strlen(str);

    // Remove o \n se estiver no final
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }

    if (len < 9) {
        printf("O número deve ter pelo menos 9 dígitos!\n");
        return 0;
    }

    for (int i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            printf("O número não pode conter letras ou símbolos!\n");
            return 0;
        }
    }

    return 1; // Somente números e comprimento suficiente
}

int verificarEmail(char email[]) {
    int tam = strlen(email);

    // Remove o \n no final, se existir
    if (email[tam - 1] == '\n') {
        email[tam - 1] = '\0';
        tam--;
    }

    // Verifica se contém '@' e '.'
    char *arroba = strchr(email, '@');
    char *ponto = strrchr(email, '.');

    // Validações básicas
    if (!arroba || !ponto) {
        printf("Email invalido: falta '@' ou '.'\n");
        return 0;
    }

    // '@' não pode ser o primeiro caractere
    if (arroba == email) {
        printf("Email invalido: '@' na posicao errada\n");
        return 0;
    }

    // '.' deve vir depois de '@'
    if (ponto < arroba) {
        printf("Email invalido: '.' vem antes do '@'\n");
        return 0;
    }

    // Deve haver algo após o último ponto (ex: .com)
    if (strlen(ponto + 1) < 2) {
        printf("Email invalido: dominio muito curto\n");
        return 0;
    }

    return 1; // Email válido
}

int bissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

// Função principal: valida uma data no formato dd/mm/aaaa
int validardata(char data[]) {
    // Verifica se a string tem exatamente 10 caracteres e os separadores corretos
    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') {
        printf("Data invalida: formato incorreto. Use dd/mm/aaaa\n");
        return 0;
    }

    // Extrai partes da data como strings
    char diaStr[3], mesStr[3], anoStr[5];
    strncpy(diaStr, data, 2);
    diaStr[2] = '\0';

    strncpy(mesStr, data + 3, 2);
    mesStr[2] = '\0';

    strncpy(anoStr, data + 6, 4);
    anoStr[4] = '\0';

    // Converte para inteiros
    int dia = atoi(diaStr);
    int mes = atoi(mesStr);
    int ano = atoi(anoStr);

    // Verifica se os valores estão em intervalos válidos
    if (dia < 1 || mes < 1 || mes > 12 || ano < 1) {
        printf("Data invalida: valores fora do intervalo\n");
        return 0;
    }

    // Dias máximos por mês
    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajusta fevereiro se for bissexto
    if (bissexto(ano)) {
        dias_mes[1] = 29;
    }

    // Verifica se o dia é válido para o mês
    if (dia > dias_mes[mes - 1]) {
        printf("Data inválida: esse mes nao tem %d dias\n", dia);
        return 0;
    }

    return 1; // Data válida
}

#include <stdlib.h> // A função system() está aqui

void limparTela() {
#ifdef _WIN32
    // Se estiver compilando para Windows
    system("cls");
#else
    // Para outros sistemas (Linux, macOS)
    system("clear");
#endif
}
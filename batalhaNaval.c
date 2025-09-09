#include <stdio.h>
#include <string.h>

#define TAM 10   // tamanho do tabuleiro
#define HAB 5    // tamanho das matrizes de habilidade (5x5)

// Função para inicializar o tabuleiro com água (0)
void inicializar_tabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para imprimir o tabuleiro
void imprimir_tabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ ");  // água
            else if (tabuleiro[i][j] == 3)
                printf("N ");  // navio
            else if (tabuleiro[i][j] == 5)
                printf("* ");  // área de habilidade
        }
        printf("\n");
    }
}

// Criar matriz cone 5x5
void criar_cone(int cone[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            // cone expandindo de cima para baixo
            if (j >= (HAB/2 - i) && j <= (HAB/2 + i) && i <= HAB/2)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Criar matriz cruz 5x5
void criar_cruz(int cruz[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (i == HAB/2 || j == HAB/2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Criar matriz octaedro 5x5 (losango)
void criar_octaedro(int octa[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (abs(i - HAB/2) + abs(j - HAB/2) <= HAB/2)
                octa[i][j] = 1;
            else
                octa[i][j] = 0;
        }
    }
}

// Aplicar matriz de habilidade no tabuleiro
void aplicar_habilidade(int tabuleiro[TAM][TAM], int habilidade[HAB][HAB], int origem_x, int origem_y) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (habilidade[i][j] == 1) {
                int x = origem_x + (i - HAB/2);
                int y = origem_y + (j - HAB/2);

                // Verificar se está dentro do tabuleiro
                if (x >= 0 && x < TAM && y >= 0 && y < TAM) {
                    if (tabuleiro[x][y] == 0)  // não sobrescreve navio
                        tabuleiro[x][y] = 5;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializar_tabuleiro(tabuleiro);

    // Colocar alguns navios (valor 3)
    tabuleiro[2][2] = 3;
    tabuleiro[5][5] = 3;
    tabuleiro[7][3] = 3;

    // Criar habilidades
    int cone[HAB][HAB], cruz[HAB][HAB], octa[HAB][HAB];
    criar_cone(cone);
    criar_cruz(cruz);
    criar_octaedro(octa);

    // Aplicar habilidades no tabuleiro
    aplicar_habilidade(tabuleiro, cone, 2, 7);   // cone em (2,7)
    aplicar_habilidade(tabuleiro, cruz, 5, 5);  // cruz em (5,5)
    aplicar_habilidade(tabuleiro, octa, 7, 7);  // octaedro em (7,7)

    // Mostrar tabuleiro
    printf("\n=== TABULEIRO COM HABILIDADES ===\n\n");
    imprimir_tabuleiro(tabuleiro);

    return 0;
}

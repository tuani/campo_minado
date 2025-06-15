#include <stdio.h>        // Importa funções padrão de entrada e saída
#include <stdlib.h>       // Importa funções como malloc, free e rand
#include <time.h>         // Importa time() para gerar aleatoriedade com srand

// Define a struct Celula — representa cada espaço no campo minado
typedef struct {
    char valor;           // 'X' = bomba, 'O' = seguro
    int revelado;         // 1 = revelado, 0 = escondido
} Celula;

// Função que recebe linha, coluna e número de colunas, e retorna índice no vetor
int get_index(int linha, int coluna, int colunas) {
    return linha * colunas + coluna; // Converte coordenada 2D em índice 1D
}

// Mostra as posições das bombas (apenas para testes e apresentação)
void mostrar_bombas(Celula *campo, int linhas, int colunas) {
    printf("\n💣 Mapa das Bombas (apenas para testes):\n");
    for (int l = 0; l < linhas; l++) {
        for (int c = 0; c < colunas; c++) {
            int i = get_index(l, c, colunas);
            if (campo[i].valor == 'X')
                printf(" X ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

// Função que cria e retorna o campo de jogo (recebe linhas, colunas e bombas)
Celula* criar_campo(int linhas, int colunas, int bombas) {
    int total = linhas * colunas;
    Celula *campo = malloc(total * sizeof(Celula));

    // Inicializa todas as células como seguras e não reveladas
    for (int i = 0; i < total; i++) {
        campo[i].valor = 'O';
        campo[i].revelado = 0;
    }

    // Posiciona bombas aleatoriamente
    int colocadas = 0;
    while (colocadas < bombas) {
        int pos = rand() % total;
        if (campo[pos].valor != 'X') {
            campo[pos].valor = 'X';
            colocadas++;
        }
    }

    return campo;
}

// Função que apenas exibe o campo (recebe, mas não retorna)
void exibir_campo(Celula *campo, int linhas, int colunas) {
    printf("\n   ");
    for (int i = 0; i < colunas; i++)
        printf("%2d ", i);
    printf("\n");

    for (int l = 0; l < linhas; l++) {
        printf("%2d ", l);
        for (int c = 0; c < colunas; c++) {
            int i = get_index(l, c, colunas);
            if (campo[i].revelado)
                printf(" %c ", campo[i].valor);
            else
                printf(" . ");
        }
        printf("\n");
    }
}

// Função que retorna a escolha da pausa
int menu_pausa() {
    int op;
    printf("\n=== PAUSA ===\n1. Voltar\n2. Sair\nEscolha: ");
    scanf("%d", &op);
    return op;
}

// Função principal do jogo
void jogar_partida(int nivel, int *pontuacao) {
    int linhas, colunas, bombas;

    if (nivel == 1) { linhas = 4; colunas = 4; bombas = 2; }
    else if (nivel == 2) { linhas = 5; colunas = 5; bombas = 3; }
    else if (nivel == 3) { linhas = 6; colunas = 6; bombas = 4; }
    else {
        printf("Nível inválido!\n");
        return;
    }

    Celula *campo = criar_campo(linhas, colunas, bombas);
    mostrar_bombas(campo, linhas, colunas);
    int total = linhas * colunas;

    int jogadas_seguras = 0;
    int perdeu = 0;
    int sair = 0;

    printf("\nJogo iniciado! (-1 para pausar)\n");

    while (!perdeu && jogadas_seguras < (total - bombas) && !sair) {
        exibir_campo(campo, linhas, colunas);

        int l, c;
        printf("Linha (-1 pausa): ");
        scanf("%d", &l);

        if (l == -1) {
            if (menu_pausa() == 2) {
                sair = 1;
                break;
            } else {
                continue;
            }
        }

        printf("Coluna: ");
        scanf("%d", &c);

        if (l < 0 || l >= linhas || c < 0 || c >= colunas)
            continue;

        int i = get_index(l, c, colunas);

        if (campo[i].revelado)
            continue;

        campo[i].revelado = 1;

        if (campo[i].valor == 'X') {
            printf("\n💥 BUM! Você perdeu.\n");
            perdeu = 1;
        } else {
            printf("✅ Seguro!\n");
            jogadas_seguras++;
        }
    }

    exibir_campo(campo, linhas, colunas);

    if (sair)
        printf("\n👋 Você saiu do jogo.\n");
    else if (perdeu)
        printf("😢 Fim de jogo!\n");
    else {
        printf("\n🎉 Parabéns, você venceu!\n");
        (*pontuacao)++;
    }

    printf("Pontuação: %d\n", *pontuacao);

    free(campo);
}

// Função que retorna a escolha do nível
int menu_niveis() {
    int nivel;
    printf("\nEscolha o nível de dificuldade:\n");
    printf("1 - Fácil (4x4, 2 bombas)\n");
    printf("2 - Médio (5x5, 3 bombas)\n");
    printf("3 - Difícil (6x6, 4 bombas)\n");
    printf("Escolha: ");
    scanf("%d", &nivel);
    return nivel;
}

// Função que exibe o menu principal do jogo
void menu_principal() {
    int opcao;
    int pontuacao = 0;

    do {
        printf("\n===== CAMPO MINADO =====\n");
        printf("1 - Jogar\n");
        printf("2 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int nivel = menu_niveis();
            jogar_partida(nivel, &pontuacao);
        } else if (opcao != 2) {
            printf("Opção inválida!\n");
        }

    } while (opcao != 2);

    printf("\nPontuação final: %d\n", pontuacao);
    printf("Até a próxima!\n");
}

// Função principal
int main() {
    srand(time(NULL));
    menu_principal();
    return 0;
}

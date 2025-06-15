#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Cada célula pode conter uma bomba ('X') ou estar segura ('O')
typedef struct {
    char valor;     // 'X' = bomba, 'O' = seguro
    int revelado;   // 1 = revelado, 0 = escondido
} Celula;

// Converte coordenadas 2D para índice no vetor 1D
int get_index(int linha, int coluna, int colunas) {
    return linha * colunas + coluna;
}

// Mostra onde estão as bombas (usado para testes e depuração)
void mostrar_bombas(Celula *campo, int linhas, int colunas) {
    printf("\n💣 Mapa das Bombas (apenas para testes):\n");
    for (int l = 0; l < linhas; l++) {
        for (int c = 0; c < colunas; c++) {
            int i = get_index(l, c, colunas);
            printf(" %c ", campo[i].valor == 'X' ? 'X' : '.');
        }
        printf("\n");
    }
}

// Cria o campo e posiciona as bombas aleatoriamente
Celula* criar_campo(int linhas, int colunas, int bombas) {
    int total = linhas * colunas;
    Celula *campo = malloc(total * sizeof(Celula));

    for (int i = 0; i < total; i++) {
        campo[i].valor = 'O';
        campo[i].revelado = 0;
    }

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

// Exibe o campo com as células reveladas ou ocultas
void exibir_campo(Celula *campo, int linhas, int colunas) {
    printf("\n   ");
    for (int i = 0; i < colunas; i++)
        printf("%2d ", i);
    printf("\n");

    for (int l = 0; l < linhas; l++) {
        printf("%2d ", l);
        for (int c = 0; c < colunas; c++) {
            int i = get_index(l, c, colunas);
            printf(" %c ", campo[i].revelado ? campo[i].valor : '.');
        }
        printf("\n");
    }
}

// Exibe o menu de pausa durante o jogo
int menu_pausa() {
    int op;
    printf("\n=== PAUSA ===\n1. Voltar\n2. Sair\nEscolha: ");
    scanf("%d", &op);
    return op;
}

// Executa uma partida com base no nível escolhido
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
    mostrar_bombas(campo, linhas, colunas); // Remover se quiser ocultar as bombas
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
            } else continue;
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

// Menu para seleção de nível de dificuldade
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

// Menu principal do jogo
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

int main() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios
    menu_principal();
    return 0;
}

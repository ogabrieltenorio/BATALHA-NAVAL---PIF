#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"
#include "board.h"
#include "fleet.h"
#include "rnd.h"
#include "io.h" 

// validacao do game

int is_place_navio(Board *board, int tamanho, int linha, int coluna, int orient) {
    // 1. vendo se o navio cabe no board
    if (orient == ORIENT_H) { // horizontal
        if (coluna < 0 || coluna + tamanho > board->colunas) return 0;
    } else { // vertical
        if (linha < 0 || linha + tamanho > board->linhas) return 0;
    }

    for (int i = 0; i < tamanho; i++) {
        // calcula posicao (r, c) de cada celula do navio
        int l = linha + (orient == ORIENT_V ? i : 0);
        int c = coluna + (orient == ORIENT_H ? i : 0);
        
        Cell *cell = get_cell(board, l, c);
        // add checagem de null p n explodir
        if (cell == NULL || cell->state != CELL_agua) return 0;
    }
    return 1; // deu bom, valido
}

int place_auto_navio(Board *board, Fleet *fleet) {
    const int MAX_TENTATIVAS = 5000; // aumentei o limite de tentativas p garantir
    
    for (int i = 0; i < fleet->count; i++) {
        Navio *navio = &fleet->navios[i];
        int colocado = 0;
        int tentativas = 0;
        while (!colocado && tentativas < MAX_TENTATIVAS) {
            // gera coords e orientacao aleatorias
            int linha = random_number(board->linhas);
            int coluna = random_number(board->colunas);
            int orient = random_orientation(); 
            
            // 1. tenta validar a colocacao
            if (is_place_navio(board, navio->tamanho, linha, coluna, orient)) {
                
                // set_ship_on_board n existia, fiz la no board.c
                set_ship_on_board(board, navio, linha, coluna, orient, i);
                
                colocado = 1; 
            }
            tentativas++;
        }
        
        if (!colocado) {
            printf("ERRO: Nao foi possivel posicionar o navio %s.\n", navio->nome);
            return 0; 
        }
    }
    return 1; 
}

int place_manual_navio(Board *board, Fleet *fleet) {
   
    for (int i = 0; i < fleet->count; i++) {
        Navio *navio = &fleet->navios[i];
        int colocado = 0;
        int r, c, orient; 
        
        while (!colocado) {
            printf("\n--- Posicionando: %s (Tamanho: %d) ---\n", navio->nome, navio->tamanho);
            io_display_board(board, 1); 

            // substitui a chamada ficticia read_input pelas funcs reais do io.c
            io_read_coordenada(&r, &c);
            orient = io_read_orietation();
            
            if (is_place_navio(board, navio->tamanho, r, c, orient)) {
                
                // 3. se for valido, joga o navio no board
                set_ship_on_board(board, navio, r, c, orient, i);
                
                colocado = 1;
            } else {
                printf("Posicao invalida! O navio nao cabe ou ja existe algo la. Tente novamente.\n");
            }
        }
    }
    return 1; 
}

// processa o tiro
// mudei retorno p int p main saber o q rolou
int process_tiro(Player *atacante, Player *defensor) {
    int r, c;
    printf("\n%s, sua vez de atirar. ", atacante->nickname);
   
    // tava read_coordinate, mas o nome certo eh io_read_coordenada
    io_read_coordenada(&r, &c); 
   
    // 2. acessar celula do defensor
    Cell *cell = get_cell(&defensor->board, r, c);

    if (cell == NULL) return 0;
    
    // ve se ja atirou antes p n contar duplicado
    if (cell->state == CELL_dano || cell->state == CELL_erro) {
        printf("Ja atirou nesta posicao ou posicao invalida! Tente novamente.\n");
        return 2; // codigo p 'repetir jogada'
    }

    atacante->total_tiros++; // conta o tiro p stat

    if (cell->state == CELL_navio) {
        printf("ACERTOU! Fogo a bordo!\n");
        cell->state = CELL_dano;
        
        // logica p atualizar dano no navio
        if(cell->navio_id >= 0) {
            defensor->fleet.navios[cell->navio_id].dano++;
             if (defensor->fleet.navios[cell->navio_id].dano >= defensor->fleet.navios[cell->navio_id].tamanho) {
                 printf("AFUNDOU O NAVIO!\n");
            }
        }

        atacante->score++; 
        return 1;

    } else if (cell->state == CELL_agua) {
        printf("Agua!\n");
        cell->state = CELL_erro;
        return 0;
    }
    
    return 0;
}

// func aux p configurar o player
// att pra receber as dimensoes do config
void setup_player(Player *p, int player_num, int linhas, int colunas) {
    printf("\n--- CONFIGURACAO JOGADOR %d ---\n", player_num);
    printf("Nome: ");
    scanf("%s", p->nickname);
    
    // tem q inicializar a memoria antes
    inicialize_fleet(&p->fleet);
    // usa as vars do menu, chega de hardcode 10x10
    inicialize_board(&p->board, linhas, colunas);
    p->score = 0;
    p->total_tiros = 0; // reseta stats

    printf("Como deseja posicionar sua frota?\n");
    printf("(A)utomatico ou (M)anual? ");
    char resp[10];
    scanf("%s", resp);

    if (toupper(resp[0]) == 'M') {
        place_manual_navio(&p->board, &p->fleet);
    } else {
        printf("Posicionando sua frota aleatoriamente...\n");
        place_auto_navio(&p->board, &p->fleet);
    }
}

// mudei game_over_alt p game_over p bater c o header
int game_over(Fleet *fleet) {
    for (int i = 0; i < fleet->count; i++) {
        // usei a struct certa (dano vs tamanho) em vez de vida_restante
        if (fleet->navios[i].dano < fleet->navios[i].tamanho) {
            return 0; // achou navio vivo
        }
    }
    return 1; // tudo afundado
}
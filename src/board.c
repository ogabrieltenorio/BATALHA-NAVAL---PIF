#include<stdio.h>
#include<stdlib.h>
#include "board.h" 
// tive que incluir fleet.h aqui pra ele saber o que é ORIENT_H, senao da ruim
#include "fleet.h" 

void inicialize_board(Board *board , int linhas , int colunas){
      // Validar linhas e colunas [6,26]
    // o if original tava bugado (coluna < 26 OU coluna > 6 é sempre vdd kkk). arrumei pra logica bater:
    if((linhas < 6 || linhas > 26) || (colunas < 6 || colunas > 26)){
         printf("Dimensões Invalidas") ; 
         // forcei um padrao aqui pra nao crashar o programa todo se o user digitar errado
         board->linhas = 10;
         board->colunas = 10;
         return ;
    }
    board -> linhas = linhas ;
    board -> colunas = colunas ;

    int total_cells = linhas * colunas ; 

    board ->cells = malloc(total_cells * sizeof(Cell));
    
    if(board ->cells == NULL){
        printf("Falha ao alocar memoria");
        return ;
    }

    for (int i = 0 ; i < total_cells ; i++){
        board->cells[i].state = CELL_agua ;
        board->cells[i].navio_id = -1 ;
    }
}

void free_board(Board *board){
    if(board->cells != NULL){
        free(board->cells);
    }
}

int board_get_cell(Board *board , int l , int c , Cell **result_cells){
    if(l < 0 || l >= board-> linhas || c < 0 || c >= board-> colunas){
        *result_cells = NULL; 
         return 0;
    } 

    int indice = l * board-> colunas + c;

    *result_cells = &board->cells[indice];
    
    return 1 ;
}

// criei essa func pq o game.c usa ela direto e nao tinha implementacao. eh tipo um atalho
Cell *get_cell(Board *board, int row, int col) {
    if(row < 0 || row >= board->linhas || col < 0 || col >= board->colunas) {
        return NULL;
    }
    return &board->cells[row * board->colunas + col];
}

// implementei essa pra "pintar" o navio no grid, pq o game.c chamava mas n tinha nada aqui
void set_ship_on_board(Board *board, void *navio_generico, int linha, int coluna, int orient, int id) {
    Navio *navio = (Navio*)navio_generico;
    for(int i = 0; i < navio->tamanho; i++) {
        int l = linha + (orient == ORIENT_V ? i : 0);
        int c = coluna + (orient == ORIENT_H ? i : 0);
        Cell *cell = get_cell(board, l, c);
        if(cell) {
            cell->state = CELL_navio;
            cell->navio_id = id; 
        }
    }
}

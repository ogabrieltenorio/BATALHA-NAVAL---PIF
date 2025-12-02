#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "board.h"
#include "game.h"
#include "io.h" 

// Funções exibir (TABULEIRO E FROTA)
void io_display_board(Board *board , int mostra_navios){
    printf("  ") ;
    for(int c = 0 ; c < board -> colunas ; c++){
        printf("%c ", 'A' + c) ; // dei espaco extra pra alinhar
    }
    printf("\n");

    for(int l = 0 ; l < board -> linhas ; l++){
        printf("%2d ", l + 1);

        for (int c = 0; c < board->colunas; c++) {
            Cell *cell = get_cell(board , l , c); 
            
            // se der null, imprime algo generico pra nao crashar
            if (!cell) { printf("? "); continue; }

            char simbolo;
            switch (cell->state) {
                case CELL_agua: simbolo = '~'; break; 
                case CELL_dano:   simbolo = 'X'; break; // mudei pra X maiusculo pra ver melhor
                case CELL_erro:  simbolo = '*'; break; 
                case CELL_navio: 
                    // Operador ternário: Se show_ships != 0, mostra 'N', senão, mostra '~'
                    simbolo = (mostra_navios) ? 'N' : '~';
                    break; 
                default:         simbolo = '?'; break;
            }
            printf("%c ", simbolo); // espaco extra aqui tbm
        }
        printf("\n");
    }
}

void io_display_fleet_status(Fleet *fleet){
    printf("\n--- Status da Frota ---\n");
    for (int i = 0; i < fleet->count; i++) {
        Navio *navios= &fleet->navios[i];
        printf("%-15s: %d/%d acertos. %s\n", 
               navios ->nome, 
               navios ->dano, 
               navios ->tamanho, 
               (navios->dano >= navios -> tamanho ? "**AFUNDADO**" : "Flutuando"));
    }
}

// Funções de Entrada 
void io_read_coordenada(int *linha , int *coluna){
    char entrada[10] ;
    // loop pra nao deixar o cara sair sem digitar algo certo
    while(1) {
        printf("Digite Coordenada ex: A5 ") ;
        scanf("%s", entrada); 
        char letra = toupper(entrada[0]); 
        if (letra >= 'A' && letra <= 'Z') {
            *coluna = letra - 'A'; 
            int numero = atoi(&entrada[1]);
            *linha = numero - 1; 
            break;
        }
        printf("Coordenada errada, tenta de novo bro.\n");
    }
} 

int io_read_orietation(){
    char entrada[10];
    while(1){
        printf("Orientacao (H = Horizontal, V = Vertical): ");
        scanf("%s", entrada);
        char c = toupper(entrada[0]);
        
        if(c == 'H'){
            return ORIENT_H ; 
        }
        else if (c == 'V'){
            return ORIENT_V ; 
        }
        printf("Opcao invalida! Tente H ou V.\n");
    }
}

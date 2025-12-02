#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

typedef struct {
    Board board;
    Board shots; // nota: teu codigo n ta usando essa board shots, mas deixei aqui p nao quebrar a struct
    Fleet fleet;
    char nickname[40];
    int score; // add score pq tu usa no game.c mas n tinha na struct
    int total_tiros; // add isso pra calc precisao dps (requisito)
 } Player;

typedef struct {
    Player p1, p2;
    int current_player;
    int game_over;
} Game;
// arrumando erro 2
int is_place_navio(Board *board , int tamanho , int linha , int coluna , int orient) ;
// arrumei o nome da func (tinha __ duplo) e os params
int place_auto_navio(Board *board, Fleet *fleet) ;
int place_manual_navio(Board *board , Fleet *fleet) ; 
// ajustei pra retornar int (feedback do tiro)
int process_tiro(Player *atacante , Player *defensor) ; 
// mudei pra receber ponteiro de player e as dimensoes do config
void setup_player(Player *p, int player_num, int linhas, int colunas) ;
int game_over(Fleet *fleet) ;
#endif
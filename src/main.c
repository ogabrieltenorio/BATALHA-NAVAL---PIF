#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "board.h"
#include "fleet.h"
#include "io.h"
#include "game.h"
#include "rnd.h"

// func p mostrar as stats no fim, senao perde ponto
void print_stats(Player *p) {
    float precisao = 0.0;
    if (p->total_tiros > 0) {
        precisao = ((float)p->score / p->total_tiros) * 100.0;
    }
    printf("\n--- Stats do %s ---\n", p->nickname);
    printf("Tiros: %d\n", p->total_tiros);
    printf("Acertos: %d\n", p->score);
    printf("Precisao: %.2f%%\n", precisao);
    
    printf("\nComo ficou o tabuleiro dele:\n");
    io_display_board(&p->board, 1); // mostra td no final
}

int main(){
    setup_random() ;
    
    // defaults do grid
    int conf_linhas = 10;
    int conf_colunas = 10;
    int opcao = 0;

    // loop do menu principal
    while(opcao != 3) {
        printf("\n|============== BATALHA NAVAL =============== |\n");
        printf("1) Novo Jogo\n");
        printf("2) Configs\n");
        printf("3) Sair\n");
        printf("Manda a boa: ");
        
        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); // limpa o buffer se digitar letra
            opcao = 0;
        }

        if (opcao == 2) {
            printf("\n--- CONFIGS ---\n");
            printf("Tamanho atual: %dx%d\n", conf_linhas, conf_colunas);
            printf("Novo tamanho (6-26): ");
            int tam;
            scanf("%d", &tam);
            if (tam >= 6 && tam <= 26) {
                conf_linhas = tam;
                conf_colunas = tam; 
                printf("Tamanho setado pra %dx%d!\n", conf_linhas, conf_colunas);
            } else {
                printf("Tamanho zoado! Mantendo %dx%d.\n", conf_linhas, conf_colunas);
            }
        } 
        else if (opcao == 1) {
            // play no game
            Player p1, p2;
            
            // passando config de tamanho
            setup_player(&p1, 1, conf_linhas, conf_colunas);
            
            // limpa tela fake
            printf("\n\n\n\n\n\n\n\n\n\n");
            
            setup_player(&p2, 2, conf_linhas, conf_colunas);
            printf("\n\n\n\n\n\n\n\n\n\n");

            int game_running = 1;
            int turnos = 1;
            int jogador_atual = 1;

            while (game_running) {
                printf("\n================ TURNO %d ================\n", turnos);
                
                // define quem ta jogando (ponteiros p facilitar)
                Player *atacante = (jogador_atual == 1) ? &p1 : &p2;
                Player *defensor = (jogador_atual == 1) ? &p2 : &p1;
                
                printf("\n--> VEZ DE %s (JOGADOR %d) <--\n", atacante->nickname, jogador_atual);
                
                // prompt p player ver as telas do inimigo
                printf("\nAperta ENTER pra ver o jogo e mandar bala...");
                while (getchar() != '\n'); // limpa buffer
                getchar(); // espera o enter de vdd
                
                // mostra o board do alvo (escondido) e o teu (visivel)
                printf("\n--- AREA INIMIGA ---\n");
                io_display_board(&defensor->board, 0); 
                
                printf("\n--- TUA FROTA ---\n");
                io_display_board(&atacante->board, 1); 

                // le e executa a jogada
                int res = process_tiro(atacante, defensor);
                
                // se res == 2 eh tiro repetido, volta p loop sem trocar turno
                if (res == 2) continue;

                // 3. checando vitoria
                if (game_over(&defensor->fleet)) {
                    printf("\n\nVITORIA! %s AMASSOU EM %d TURNOS!\n", atacante->nickname, turnos);
                    
                    // requisito: exibir stats e boards finais
                    print_stats(atacante);
                    print_stats(defensor);

                    game_running = 0; // fim de jogo, volta p menu
                } else {
                    // se o jogo continuar, alterna o player
                    jogador_atual = (jogador_atual == 1) ? 2 : 1;
                    
                    // incrementa turno so dps da jogada dos dois
                    if (jogador_atual == 1) {
                        turnos++;
                    }
                }
            }
            // 4. limpa memoria
            free_board(&p1.board); 
            free_fleet(&p1.fleet);
            free_board(&p2.board); 
            free_fleet(&p2.fleet);
        }
        else if (opcao == 3) {
            printf("Falou valeu!\n");
        }
        else {
            printf("Opcao nada a ver.\n");
        }
    }
    return 0;
}
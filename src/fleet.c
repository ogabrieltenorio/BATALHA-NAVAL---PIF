#include<stdio.h>
#include<stdlib.h>
#include<string.h> // coloquei pq tava faltando pro strcpy funcionar
#include "fleet.h" 

int inicialize_fleet(Fleet *fleet){
     fleet -> count = 6 ; 

     fleet -> navios = malloc( 6 * sizeof(Navio)) ; 
     
     if (fleet->navios == NULL) {
        return -1; 
     }
    
    strcpy(fleet->navios[0].nome, "Porta-Avioes");
    fleet->navios[0].tamanho = 5;  
    fleet->navios[0].dano = 0;   
    fleet->navios[0].posicao = 0;  
    
   
    strcpy(fleet->navios[1].nome, "Encouracado");
    fleet->navios[1].tamanho = 4;  
    fleet->navios[1].dano = 0;   
    fleet->navios[1].posicao = 0; 
    

    strcpy(fleet->navios[2].nome, "Cruzador");
    fleet->navios[2].tamanho = 3;  
    fleet->navios[2].dano = 0;   
    fleet->navios[2].posicao = 0 ; 

    strcpy(fleet->navios[3].nome, "Cruzador");
    fleet->navios[3].tamanho = 3;  
    fleet->navios[3].dano = 0;   
    fleet->navios[3].posicao = 0;  

    strcpy(fleet->navios[4].nome, "Destroyer");
    fleet->navios[4].tamanho = 2;  
    fleet->navios[4].dano = 0;   
    fleet->navios[4].posicao = 0; 
    
    strcpy(fleet->navios[5].nome, "Destroyer");
    fleet->navios[5].tamanho = 2;  
    fleet->navios[5].dano = 0;   
    fleet->navios[5].posicao = 0;  

     return 0 ;
} 

// CORRIGIDO ERRO 1
void free_fleet(Fleet *fleet){
    if(fleet -> navios != NULL){
        free(fleet -> navios);
    }
}

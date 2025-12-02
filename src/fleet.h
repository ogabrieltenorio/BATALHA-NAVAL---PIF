#ifndef FLEET_H
#define FLEET_H 

typedef enum {ORIENT_H , ORIENT_V} Orientation ; 

typedef struct {
    char nome[20]; // NOME
    int tamanho; // TAMANHO
    int dano; // ACERTO
    int posicao; // POSICAO
    Orientation orienta ;
} Navio ;

typedef struct{
    Navio *navios ; 
    int count ; 
} Fleet ;

int inicialize_fleet(Fleet *fleet); 
void free_fleet(Fleet *fleet) ; 

#endif
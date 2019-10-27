#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

void estadoActual(tPartida p);

int main()
{
    tPartida part;
    char p1[50];
    char p2[50];
    int game_mode = 0;
    int empieza = 0;
    int fila = 0;
    int columna = 0;

    printf("Ingrese el nombre del jugador 1 (máx 50 caracteres): \n");
    scanf("%s", p1);
    printf("Ingrese el nombre del jugador 2 (máx 50 caracteres: \n");
    scanf("%s", p2);
    //p1[0] = 'a';
    //p2[0] = 'b';
    printf("Ingrese el modo de juego: \n\t0: USUARIO VS. USUARIO\n\t1: USUARIO VS. AGENTE IA\n\t2: AGENTE IA VS. AGENTE IA\n");
    scanf("%id", &game_mode);
    game_mode = game_mode + 103;
    printf("Ingrese qué jugador debe comenzar la partida:\n\t0: PLAYER 1\n\t1: PLAYER 2\n\t2: AL AZAR\n");
    scanf("%id", &empieza);
    empieza = empieza + 100;

    //La ejecución no pasa de esta línea, andá a saber por qué

    printf("------COMIENZA LA PARTIDA-------");
    nueva_partida(&part, game_mode, empieza, p1, p2);

    while(part->estado == PART_EN_JUEGO){
        estadoActual(part);
        printf("Juega PLAYER %i\n", (part->turno_de - 99) );
        printf("   Ingrese fila y columna: ");
        scanf("%id %id", &fila, &columna);
        nuevo_movimiento(part, fila, columna);
    }
    if(part->estado == PART_GANA_JUGADOR_1){
        printf("PLAYER 1 GANA!");
    }else if(part->estado == PART_GANA_JUGADOR_2){
        printf("PLAYER 2 GANA!");
    }else{
        printf("ES UN EMPATE!");
    }

    return 0;
}

void estadoActual(tPartida p){
    int elem = 0;
    char impr = ' ';

    for(int i=0; i<3; i++){
        printf("|");
        for(int j=0; j<3; j++){
            elem = p->tablero->grilla[i][j];
            if(elem == PART_SIN_MOVIMIENTO){
                impr = ' ';
            }else if(elem == PART_JUGADOR_1){
                impr = 'X';
            }else if(elem == PART_JUGADOR_2){
                impr = 'O';
            }

            printf(" %c |", impr);
        }
        printf("\n");
    }
}

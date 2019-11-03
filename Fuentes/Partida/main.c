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
    int x = 0;
    int y = 0;
    int error_movimiento = PART_MOVIMIENTO_ERROR;
    //p1[0] = 'a';
    //p2[0] = 'b';

    printf("Ingrese el nombre del jugador 1 (máx 50 caracteres): \n");
    scanf("%s", p1);
    printf("Ingrese el nombre del jugador 2 (máx 50 caracteres: \n");
    scanf("%s", p2);
    printf("Ingrese el modo de juego: \n\t0: USUARIO VS. USUARIO\n\t1: USUARIO VS. AGENTE IA\n\t2: AGENTE IA VS. AGENTE IA\n");
    scanf("%i", &game_mode);
    game_mode = game_mode + PART_MODO_USUARIO_VS_USUARIO;
    printf("Ingrese qué jugador debe comenzar la partida:\n\t0: PLAYER 1\n\t1: PLAYER 2\n\t2: AL AZAR\n");
    scanf("%i", &empieza);
    empieza = empieza + PART_JUGADOR_1;

    printf("\n------COMIENZA LA PARTIDA-------\n");

    nueva_partida(&part, game_mode, empieza, p1, p2);

    while(part->estado == PART_EN_JUEGO){
        estadoActual(part);

        printf("\nJuega PLAYER %i", (part->turno_de - (PART_JUGADOR_1 - 1)) );
        do{
            printf("\nIngrese x: ");
            scanf("%id", &x);
            printf("Ingrese y: ");
            scanf("%id", &y);
            printf("\n");
        }while((x>3 || x<1) || (y>3 || y<1));
        error_movimiento = nuevo_movimiento(part, (y-1), (x-1));
        if(error_movimiento == PART_MOVIMIENTO_ERROR){
            printf("ERROR! Intente jugar de nuevo.\n");;
        }
    }
    printf("\n");
    estadoActual(part);
    printf("\n");
    if(part->estado == PART_GANA_JUGADOR_1){
        printf("PLAYER 1 GANA! Felicidades %s!", part->nombre_jugador_1);
        finalizar_partida(&part);
    }else if(part->estado == PART_GANA_JUGADOR_2){
        printf("PLAYER 2 GANA! Felicidades %s!", part->nombre_jugador_2);
        finalizar_partida(&part);
        }else{
            printf("ES UN EMPATE!");
            finalizar_partida(&part);
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

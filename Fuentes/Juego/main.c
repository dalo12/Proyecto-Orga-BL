#include <stdio.h>
#include <stdlib.h>
#include "partida.h"
#include "ia.h"

void estadoActual(tPartida p);
void userVsUser(int empieza, char *p1, char *p2);
void userVsIA(int empieza, char *p1, char *p2);
void IAvsIA(int empieza, char *p1, char *p2);

int main()
{
    char p1[50];
    char p2[50];
    int game_mode = 0;
    int empieza = 0;

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

    if(game_mode == PART_MODO_USUARIO_VS_USUARIO){
        userVsUser(empieza, p1, p2);
    }else if(game_mode == PART_MODO_USUARIO_VS_AGENTE_IA){
        userVsIA(empieza, p1, p2);
    }else{
        IAvsIA(empieza, p1, p2);
    }

    return 0;
}

/**
Ejecuta una partida de jugador vs jugador
@param empieza El jugador que empieza la partida (PART_JUGADOR_1, PART_JUGADOR_2 ó PART_JUGADOR_RANDOM)
@param p1 Nombre del primer jugador
@param p2 Nombre del segundo jugador
**/
void userVsUser(int empieza, char *p1, char *p2){
    tPartida part;
    int x = 0;
    int y = 0;
    int error_movimiento = PART_MOVIMIENTO_ERROR;

    printf("\n------COMIENZA LA PARTIDA-------\nJUGADOR VS. JUGADOR\n\n");
    nueva_partida(&part, PART_MODO_USUARIO_VS_USUARIO, empieza, p1, p2);

    while(part->estado == PART_EN_JUEGO){
        estadoActual(part);

        printf("\nJuega JUGADOR %i", (part->turno_de - (PART_JUGADOR_1 - 1)) );
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
        printf("JUGADOR 1 GANA! Felicidades %s!", part->nombre_jugador_1);
    }else if(part->estado == PART_GANA_JUGADOR_2){
        printf("JUGADOR 2 GANA! Felicidades %s!", part->nombre_jugador_2);
    }else{
        printf("ES UN EMPATE!");
    }
    finalizar_partida(&part);
}

/**
Ejecuta una partida de jugador vs IA
@param empieza El jugador que empieza la partida (PART_JUGADOR_1, PART_JUGADOR_2 ó PART_JUGADOR_RANDOM)
@param p1 Nombre del primer jugador
@param p2 Nombre de la IA
**/
void userVsIA(int empieza, char *p1, char *p2){
    tPartida part;
    int x = 0;
    int y = 0;
    int x_ia = 0;
    int y_ia = 0;
    int error_movimiento = PART_MOVIMIENTO_ERROR;
    tBusquedaAdversaria ba;

    printf("\n------COMIENZA LA PARTIDA-------\nJUGADOR VS. IA\n\n");
    nueva_partida(&part, PART_MODO_USUARIO_VS_AGENTE_IA, empieza, p1, p2);

    while(part->estado == PART_EN_JUEGO){
        estadoActual(part);

        if(part->turno_de == PART_JUGADOR_1){
            printf("\nJuega JUGADOR");
            do{
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
            }while(error_movimiento == PART_MOVIMIENTO_ERROR);
        }else{
            printf("\nJuega IA \n");

            crear_busqueda_adversaria(&ba, part); //genera la búsqueda del mejor movimiento
           proximo_movimiento(ba, &x_ia, &y_ia); //encuentra el mejor movimiento
           nuevo_movimiento(part, x_ia, y_ia); //mueve hacia el mejor movimiento
            destruir_busqueda_adversaria(&ba); //destruye la búsqueda
        }

    }
    printf("\n");
    estadoActual(part);
    printf("\n");
    if(part->estado == PART_GANA_JUGADOR_1){
        printf("JUGADOR GANA! Felicidades %s!", part->nombre_jugador_1);
    }else if(part->estado == PART_GANA_JUGADOR_2){
        printf("IA GANA! Felicidades %s!", part->nombre_jugador_2);
    }else{
        printf("ES UN EMPATE!");
    }
    finalizar_partida(&part);
}

/**
Ejecuta una partida de jugador vs IA
@param empieza El jugador que empieza la partida (PART_JUGADOR_1, PART_JUGADOR_2 ó PART_JUGADOR_RANDOM)
@param p1 Nombre del primer jugador
@param p2 Nombre de la IA
**/
void IAvsIA(int empieza, char *p1, char *p2){
    tPartida part;
    int x_ia1 = 0;
    int y_ia1 = 0;
    int x_ia2 = 0;
    int y_ia2 = 0;
    tBusquedaAdversaria ba1;
    tBusquedaAdversaria ba2;

    //TODO Borrar
        int contador_de_ciclo = 0;
    printf("\n------COMIENZA LA PARTIDA-------\nIA VS. IA\n\n");
    nueva_partida(&part, PART_MODO_AGENTE_IA_VS_AGENTE_IA, empieza, p1, p2);
    crear_busqueda_adversaria(&ba1, part);
    while(part->estado == PART_EN_JUEGO){
        estadoActual(part);
        printf("%i\n", contador_de_ciclo);

        crear_busqueda_adversaria(&ba1, part);
        if(part->turno_de == PART_JUGADOR_1){
            printf("\nJuega IA 1 \n");

            crear_busqueda_adversaria(&ba1, part); //genera la búsqueda del mejor movimiento
            proximo_movimiento(ba1, &x_ia1, &y_ia1); //encuentra el mejor movimiento
            nuevo_movimiento(part, x_ia1, y_ia1); //mueve hacia el mejor movimiento
            destruir_busqueda_adversaria(&ba1); //destruye la búsqueda
        }else{
            printf("\nJuega IA 2 \n");

            crear_busqueda_adversaria(&ba2, part); //genera la búsqueda del mejor movimiento
            proximo_movimiento(ba2, &x_ia2, &y_ia2); //encuentra el mejor movimiento
            nuevo_movimiento(part, x_ia2, y_ia2); //mueve hacia el mejor movimiento
            destruir_busqueda_adversaria(&ba2); //destruye la búsqueda
        }

    }
    printf("\n");
    estadoActual(part);
    printf("\n");
    if(part->estado == PART_GANA_JUGADOR_1){
        printf("IA 1 GANA! Felicidades %s!", part->nombre_jugador_1);
    }else if(part->estado == PART_GANA_JUGADOR_2){
        printf("IA 2 GANA! Felicidades %s!", part->nombre_jugador_2);
    }else{
        printf("ES UN EMPATE!");
    }
    finalizar_partida(&part);
}

/**
Imprime el estado actual de la partida
@param p Partida a mostrar el estado actual
**/
void estadoActual(tPartida p){
    int elem = 0;
    char impr = ' ';

    printf("     1   2   3\n");
    for(int i=0; i<3; i++){
        printf("%i: |", (i+1));
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

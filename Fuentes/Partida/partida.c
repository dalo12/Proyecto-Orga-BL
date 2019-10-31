#include "partida.h"

#include <time.h>
#include <stdlib.h>

/**
Comprueba si algún jugador ganó, comprobando las filas del tablero
@param t Tablero a verificar
@return El número almacenado en al grilla que está alineado en una fila
**/
static int comprobarFilas(tTablero t){
    int a_retornar = PART_SIN_MOVIMIENTO;
    int victoria = 0;
    int i = 0;

    while(i<3 && !victoria){
        if((t->grilla[i][0] != PART_SIN_MOVIMIENTO)){
            if((t->grilla[i][0] == t->grilla[i][1]) && (t->grilla[i][1] == t->grilla[i][2])){
                a_retornar = t->grilla[i][0];
                victoria = 1;
            }
        }
        i++;
    }

    return a_retornar;
}

/**
Comprueba si algún jugador ganó, comprobando las columnas del tablero
@param t Tablero a verificar
@return El número almacenado en al grilla que está alineado en una fila
**/
static int comprobarColumnas(tTablero t){
    int a_retornar = PART_SIN_MOVIMIENTO;
    int victoria = 0;
    int j = 0;

    while(j<3 && !victoria){
        if((t->grilla[0][j] != PART_SIN_MOVIMIENTO)){
            if((t->grilla[0][j] == t->grilla[1][j]) && (t->grilla[1][j] == t->grilla[2][j])){
                a_retornar = t->grilla[0][j];
                victoria = 1;
            }
        }
        j++;
    }

    return a_retornar;
}

/**
Comprueba si algún jugador ganó, comprobando las diagonales del tablero
@param t Tablero a verificar
@return El número almacenado en al grilla que está alineado en una fila
**/
static int comprobarDiagonales(tTablero t){
    int a_retornar = PART_SIN_MOVIMIENTO;

    if(t->grilla[0][0] != PART_SIN_MOVIMIENTO){
        if((t->grilla[0][0] == t->grilla[1][1]) && (t->grilla[1][1] == t->grilla[2][2])){
            a_retornar = t->grilla[0][0];
        }
    }
    if(t->grilla[0][2] != PART_SIN_MOVIMIENTO){
        if((t->grilla[0][2] == t->grilla[1][1]) && (t->grilla[1][1] == t->grilla[2][0])){
            a_retornar = t->grilla[0][2];
        }
    }

    return a_retornar;
}

/**
Cuenta la cantidad de lugares vacíos que quedan en el tablero
@param t Tablero a verificar
@return El número de casilleros vacíos
**/
static int contarVacios(tTablero t){
    int cont = 0;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(t->grilla[i][j] == PART_SIN_MOVIMIENTO){
                cont++;
            }
        }
    }

    return cont;
}

/**
Inicializa una nueva partida, indicando:
 - Modo de partida (Usuario vs. Usuario o Usuario vs. Agente IA).
 - Jugador que comienza la partida (Jugador 1, Jugador 2, o elección al azar).
 - Nombre que representa al Jugador 1.
 - Nombre que representa al Jugador 2.
**/
extern void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre){
    int eol1 = 0;
    int eol2 = 0;
    int i = 0;
    srand(time(NULL)); // Initialization, should only be called once.
    int r = rand(); // Returns a pseudo-random integer between 0 and RAND_MAX.

    *p=(tPartida)malloc(sizeof(struct partida));
    if(*p != NULL){
        (*p)->tablero = (tTablero) malloc(sizeof(struct tablero));
        if((*p)->tablero != NULL){
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    (*p)->tablero->grilla[i][j] = PART_SIN_MOVIMIENTO;
                }
            }

            (*p)->modo_partida=modo_partida;
            //Genero un turno random, en caso de ser requerido
            if(comienza == PART_JUGADOR_RANDOM){
                if(r % 2){
                    (*p)->turno_de = PART_JUGADOR_1;
                }else{
                    (*p)->turno_de = PART_JUGADOR_2;
                }
            }else{
                (*p)->turno_de = comienza;
            }

            (*p)->estado = PART_EN_JUEGO;
            //Preguntar nombres
            while(i<50 && (!eol1 || !eol2)){
                if(!eol1){
                    (*p)->nombre_jugador_1[i] = j1_nombre[i];
                    eol1 = (j1_nombre[i] == '\0');
                }
                if(!eol2){
                    (*p)->nombre_jugador_2[i] = j2_nombre[i];
                    eol2 = (j2_nombre[i] == '\0');
                }
            }
            /*(*p)->nombre_jugador_1= *j1_nombre;
            (*p)->nombre_jugador_2= *j2_nombre;*/
        }else{
            exit(PART_ERROR_MEMORIA);
        }
    }else{
        exit(PART_ERROR_MEMORIA);
    }

}

/**
Actualiza, si corresponde, el estado de la partida considerando que el jugador al que le corresponde jugar, decide hacerlo en la posición indicada (X,Y).
En caso de que el movimiento a dicha posición sea posible, retorna PART_MOVIMIENTO_OK; en caso contrario, retorna PART_MOVIMIENTO_ERROR.
Las posiciones (X,Y) deben corresponderse al rango [0-2]; X representa el número de fila, mientras Y el número de columna.
**/
extern int nuevo_movimiento(tPartida p, int mov_x, int mov_y){
    int a_retornar = PART_MOVIMIENTO_ERROR;
    int estado_filas = 0;
    int estado_columnas = 0;
    int estado_diagonales = 0;

    if(mov_x > 2 || mov_x < 0 || mov_y > 2 || mov_y < 0){
        a_retornar = PART_MOVIMIENTO_ERROR;
    }else{ //significa que la coordenada (mov_x, mov_y) corresponde a un valor válido del tablero
        if(p->tablero->grilla[mov_x][mov_y] != PART_SIN_MOVIMIENTO){
            a_retornar = PART_MOVIMIENTO_ERROR;
        }else{ //significa que la coordenada (mov_x, mov_y) está disponible
            p->tablero->grilla[mov_x][mov_y] = p->turno_de;
            a_retornar = PART_MOVIMIENTO_OK;
        }
    }

    //Actualiza el turno de la partida
    if(p->turno_de == PART_JUGADOR_1){
        p->turno_de = PART_JUGADOR_2;
    }else{
        p->turno_de = PART_JUGADOR_1;
    }

    //Actualiza el estado de la partida
    estado_filas = comprobarFilas(p->tablero);
    estado_columnas = comprobarColumnas(p->tablero);
    estado_diagonales = comprobarDiagonales(p->tablero);

    if(estado_filas == PART_JUGADOR_1){
        p->estado = PART_GANA_JUGADOR_1;
    }else if(estado_filas == PART_JUGADOR_2){
        p->estado = PART_GANA_JUGADOR_2;
    }else if(estado_columnas == PART_JUGADOR_1){
        p->estado = PART_GANA_JUGADOR_1;
    }else if(estado_columnas == PART_JUGADOR_2){
        p->estado = PART_GANA_JUGADOR_2;
    }else if(estado_diagonales == PART_JUGADOR_1){
        p->estado = PART_GANA_JUGADOR_1;
    }else if(estado_diagonales == PART_JUGADOR_2){
        p->estado = PART_GANA_JUGADOR_2;
    }else if(contarVacios(p->tablero) == 0){
        p->estado = PART_EMPATE;
    }

    return a_retornar;
}

/**
Finaliza la partida referenciada por P, liberando toda la memoria utilizada.
**/
extern void finalizar_partida(tPartida * p){
    (*p)->estado = 0;
    (*p)->modo_partida = 0;
    /*for(int i=0; i<50; i++){
        (*p)->nombre_jugador_1[i] = NULL;
        (*p)->nombre_jugador_2[i] = NULL;
    } */ //Necesario? Me genera warnings
    (*p)->nombre_jugador_1[0] = '\0';
    (*p)->nombre_jugador_2[0] = '\0';
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            (*p)->tablero->grilla[i][j] = 0;
        }
    }
    (*p)->turno_de = 0;
    free(*p);
}

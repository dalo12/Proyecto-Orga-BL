/**
Inicializa una nueva partida, indicando:
 - Modo de partida (Usuario vs. Usuario o Usuario vs. Agente IA).
 - Jugador que comienza la partida (Jugador 1, Jugador 2, o elección al azar).
 - Nombre que representa al Jugador 1.
 - Nombre que representa al Jugador 2.
**/
extern void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre){
    *p=(tPartida)malloc(sizeof(struct partida));
    if(*p != NULL){
        (*p)->tablero = (tTablero) malloc(sizeof(struct tablero));
        if(*p->tablero != NULL){
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    *p->tablero->grilla[i][j] = PART_SIN_MOVIMIENTO;
                }
            }

            (*p)->modo_partida=modo_partida;
            (*p)->comienza=comienza;
            (*p)->estado = PART_EN_JUEGO;
            //Preguntar nombres
            (*p)->nombre_jugador_1=j1_nombre;
            (*p)->nombre_jugador_2=j2_nombre;
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

    if(mov_x > 2 || mov_x < 0 || mov_y > 2 || mov_y < 0){
        a_retornar = PART_MOVIMIENTO_ERROR;
    }else{ //significa que la coordenada (mov_x, mov_y) corresponde a un valor válido del tablero
        if(p->tablero->grilla[mov_x][mov_y] != 0){
            a_retornar = PART_MOVIMIENTO_ERROR;
        }else{ //significa que la coordenada (mov_x, mov_y) está disponible
            p->tablero->grilla[mov_x][mov_y] = p->turno_de;
            a_retornar = PART_MOVIMIENTO_OK;
        }
    }

    return a_retornar;
}

/**
Finaliza la partida referenciada por P, liberando toda la memoria utilizada.
**/
extern void finalizar_partida(tPartida * p){
    *p->estado = NULL;
    *p->modo_partida = NULL;
    *p->nombre_jugador_1 = NULL;
    *p->nombre_jugador_2 = NULL; //así borro los nombres?
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            *p->tablero->grilla[i][j] = NULL;
        }
    }
    //*p->
    //Completar



}

#endif // PARTIDA_H_INCLUDED

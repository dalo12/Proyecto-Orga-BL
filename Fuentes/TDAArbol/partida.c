

/**
Inicializa una nueva partida, indicando:
 - Modo de partida (Usuario vs. Usuario o Usuario vs. Agente IA).
 - Jugador que comienza la partida (Jugador 1, Jugador 2, o elección al azar).
 - Nombre que representa al Jugador 1.
 - Nombre que representa al Jugador 2.
**/
extern void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre){
    *p=(tPartida)malloc(sizeof(struct partida));
    (*p)->modo_partida=modo_partida;
    (*p)->comienza=comienza;
    //Preguntar nombres
    (*p)->nombre_jugador_1=j1_nombre;
    (*p)->nombre_jugador_2=j2_nombre;

}

/**
Actualiza, si corresponde, el estado de la partida considerando que el jugador al que le corresponde jugar, decide hacerlo en la posición indicada (X,Y).
En caso de que el movimiento a dicha posición sea posible, retorna PART_MOVIMIENTO_OK; en caso contrario, retorna PART_MOVIMIENTO_ERROR.
Las posiciones (X,Y) deben corresponderse al rango [0-2]; X representa el número de fila, mientras Y el número de columna.
**/
extern int nuevo_movimiento(tPartida p, int mov_x, int mov_y){



}

/**
Finaliza la partida referenciada por P, liberando toda la memoria utilizada.
**/
extern void finalizar_partida(tPartida * p){



}

#endif // PARTIDA_H_INCLUDED

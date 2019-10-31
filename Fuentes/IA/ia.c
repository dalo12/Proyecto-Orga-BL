#include <stdlib.h>

#include "lista.h"
#include "arbol.h"
#include "ia.h"

// Prototipos de funciones auxiliares.
static void ejecutar_min_max(tBusquedaAdversaria b);
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
static int valor_utilidad(tEstado e, int jugador_max);
static tLista estados_sucesores(tEstado e, int ficha_jugador);
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
static tEstado clonar_estado(tEstado e);

//------ Inicio funciones auxiliares creadas por la comisión

/**
Comprueba si algún jugador ganó, comprobando las filas del tablero
@param e Estado del tablero a verificar
@return El número almacenado en al grilla que está alineado en una fila
**/
static int comprobarFilas(tEstado e){
    int a_retornar = PART_SIN_MOVIMIENTO;
    int victoria = 0;
    int i = 0;

    while(i<3 && !victoria){
        if((e->grilla[i][0] != PART_SIN_MOVIMIENTO)){
            if((e->grilla[i][0] == e->grilla[i][1]) && (e->grilla[i][1] == e->grilla[i][2])){
                a_retornar = e->grilla[i][0];
                victoria = 1;
            }
        }
        i++;
    }

    return a_retornar;
}

/**
Comprueba si algún jugador ganó, comprobando las columnas del tablero
@param e Estado del tablero a verificar
@return El número almacenado en al grilla que está alineado en una columna
**/
static int comprobarColumnas(tEstado e){
    int a_retornar = PART_SIN_MOVIMIENTO;
    int victoria = 0;
    int j = 0;

    while(j<3 && !victoria){
        if((e->grilla[0][j] != PART_SIN_MOVIMIENTO)){
            if((e->grilla[0][j] == e->grilla[1][j]) && (e->grilla[1][j] == e->grilla[2][j])){
                a_retornar = e->grilla[0][j];
                victoria = 1;
            }
        }
        j++;
    }

    return a_retornar;
}

/**
Comprueba si algún jugador ganó, comprobando las diagonales del tablero
@param e Estado actual del tablero a verificar
@return El número almacenado en al grilla que está alineado en alguna diagonal
**/
static int comprobarDiagonales(tEstado e){
    int a_retornar = PART_SIN_MOVIMIENTO;

    if(e->grilla[0][0] != PART_SIN_MOVIMIENTO){
        if((e->grilla[0][0] == e->grilla[1][1]) && (e->grilla[1][1] == e->grilla[2][2])){
            a_retornar = e->grilla[0][0];
        }
    }
    if(e->grilla[0][2] != PART_SIN_MOVIMIENTO){
        if((e->grilla[0][2] == e->grilla[1][1]) && (e->grilla[1][1] == e->grilla[2][0])){
            a_retornar = e->grilla[0][2];
        }
    }

    return a_retornar;
}

/**
Cuenta la cantidad de lugares vacíos que quedan en el tablero
@param e Estado del tablero a verificar
@return El número de casilleros vacíos
**/
static int contarVacios(tEstado e){
    int cont = 0;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(e->grilla[i][j] == PART_SIN_MOVIMIENTO){
                cont++;
            }
        }
    }

    return cont;
}

/**
Hace un nuevo movimiento en el tablero de E a partir de (X,Y)
@param e Estado actual del tablero
@param valor Valor a asignar a la hora de mover
@param x Referencia a la posición en el eje x del tablero donde se hizo el último movimiento
@param y Referencia a la posición en el eje y del tablero donde se hizo el último movimiento
**/
static void moverCercano(tEstado e, int valor, int *x, int *y){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(!(i<=(*x) && j<=(*y))){
                if(e->grilla[i][j] == PART_SIN_MOVIMIENTO){
                    e->grilla[i][j] = valor;
                    *x = i;
                    *y = j;
                    break;
                }
            }
        }
    }
}
//------ Fin funciones auxiliares creadas por la comisión

void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p){
    int i, j;
    tEstado estado;

    (*b) = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));
    if ((*b) == NULL) exit(IA_ERROR_MEMORIA);

    estado = (tEstado) malloc(sizeof(struct estado));
    if (estado == NULL) exit(IA_ERROR_MEMORIA);

    // Se clona el estado del tablero de la partida, al estado inicial de la búsqueda adversaria.
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            estado->grilla[i][j] = p->tablero->grilla[i][j];
        }
    }

	// Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
	// inicialmente es IA_NO_TERMINO
    estado->utilidad = IA_NO_TERMINO;

    // Inicializa los valores que representarán a los jugadores MAX y MIN respectivamente.
    (*b)->jugador_max = p->turno_de;
    (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    // Inicializa un árbol para la búsqueda adversaria inicialmente vacío.
    crear_arbol(&((*b)->arbol_busqueda));

    // Inicializa la raíz del árbol de búsqueda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);

    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
*/
void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y){


}

/**
>>>>>  A IMPLEMENTAR   <<<<<
**/
void destruir_busqueda_adversaria(tBusquedaAdversaria * b){



}

// ===============================================================================================================
// FUNCIONES Y PROCEDEMIENTOS AUXILIARES
// ===============================================================================================================

/**
Ordena la ejecución del algoritmo Min-Max para la generación del árbol de búsqueda adversaria, considerando como
estado inicial el estado de la partida almacenado en el árbol almacenado en B.
**/
static void ejecutar_min_max(tBusquedaAdversaria b){
    tArbol a = b->arbol_busqueda;
    tNodo r = a_raiz(a);
    int jugador_max = b->jugador_max;
    int jugador_min = b->jugador_min;

    crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
- A referencia al árbol de búsqueda adversaria.
- N referencia al nodo a partir del cual se construye el subárbol de búsqueda adversaria.
- ES_MAX indica si N representa un nodo MAX en el árbol de búsqueda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el árbol de búsqueda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min){}

/**
>>>>>  A IMPLEMENTAR   <<<<< -> implementado 30/10/2019
Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX ganó la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empató la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdió la partida.
- IA_NO_TERMINO en caso contrario.
**/
static int valor_utilidad(tEstado e, int jugador_max){
    int resultado = IA_NO_TERMINO;
    int estado_filas = comprobarFilas(e);
    int estado_columnas = comprobarColumnas(e);
    int estado_diagonales = comprobarDiagonales(e);

    if((estado_filas == jugador_max) || (estado_columnas == jugador_max) || (estado_diagonales == jugador_max) ){
        resultado = IA_GANA_MAX;
    }else if(contarVacios(e) == 0){
        resultado = IA_EMPATA_MAX;
    }else if((estado_filas != PART_SIN_MOVIMIENTO) || (estado_columnas != PART_SIN_MOVIMIENTO) || (estado_diagonales != PART_SIN_MOVIMIENTO)){
        //si en las filas o en las columnas o en las diagonales hay un resultado que no es vacío, entonces perdió max
        resultado = IA_PIERDE_MAX;
    }else{
        resultado = IA_NO_TERMINO;
    }

    return resultado;
}

/**
>>>>>  A IMPLEMENTAR   <<<<< -> implementado 30/10/2019
Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
Un estado sucesor corresponde a la clonación del estado E, junto con la incorporación de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posición que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocación de la función
estados_sucesores(estado, ficha) retornaría dos listas L1 y L2 tal que:
- L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
- El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
**/
static tLista estados_sucesores(tEstado e, int ficha_jugador){
    tLista lista_sucesores;
    crear_lista(&lista_sucesores);
    int x = 0;
    int y = 0;
    int cant_sucesores = contarVacios(e);

    for(int i=0; i<cant_sucesores; i++){
        tEstado sucesor = clonar_estado(e);
        moverCercano(sucesor, ficha_jugador, &x, &y);
    }

    return lista_sucesores;
}

/**
>>>>>  A IMPLEMENTAR   <<<<< -> implementado 30/10/2019
Inicializa y retorna un nuevo estado que resulta de la clonación del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e){
    tEstado a_retornar = (tEstado) malloc(sizeof(struct estado));
    if(a_retornar == NULL){
        exit(IA_ERROR_MEMORIA);
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            a_retornar->grilla[i][j] = e->grilla[i][j];
        }
    }
    a_retornar->utilidad = e->utilidad;

    return a_retornar;
}

/**
Computa la diferencia existente entre dos estados.
Se asume que entre ambos existe sólo una posición en el que la ficha del estado anterior y nuevo difiere.
La posición en la que los estados difiere, es retornada en los parámetros *X e *Y.
**/
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y){
    int i,j, hallado = 0;
    for(i=0; i<3 && !hallado; i++){
        for(j=0; j<3 && !hallado; j++){
            if (anterior->grilla[i][j] != nuevo->grilla[i][j]){
                *x = i;
                *y = j;
                hallado = 1;
            }
        }
    }
}

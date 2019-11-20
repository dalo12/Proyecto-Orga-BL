#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "arbol.h"
#include <time.h>
#include "ia.h"

// Prototipos de funciones auxiliares.
static void ejecutar_min_max(tBusquedaAdversaria b);
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
static int valor_utilidad(tEstado e, int jugador_max);
static tLista estados_sucesores(tEstado e, int ficha_jugador);
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
static tEstado clonar_estado(tEstado e);

//Funciones auxiliares agregadas
int lleno(tEstado estado);
void fEliminar(tElemento e);
int MAX(tArbol a, tNodo n, int alpha, int beta, int jugador_max, int jugador_min);
int MIN(tArbol a, tNodo n, int alpha, int beta, int jugador_max, int jugador_min);

//Esta funcion permite no eliminar el elemto a la ora de destruir
void fNoElimina(tElemento elemento) {}

void eliminarEstado(tElemento estado) {
    if (estado != NULL) {
        tEstado aux = (tEstado) estado;
        free(aux);
    }
}
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
/*static void moverCercano(tEstado e, int valor, int *x, int *y){
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
*/
//------ Fin funciones auxiliares creadas por la comisión

void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p){
    int i, j;
    tEstado estado;

    (*b) = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));
    if ((*b) == NULL) exit(IA_ERROR_MEMORIA);

    estado = (tEstado) malloc(sizeof(struct estado));
    if (estado == NULL) exit(IA_ERROR_MEMORIA);

    // Se clona el estado del tablero de la partida, al estado inicial de la b�squeda adversaria.
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            estado->grilla[i][j] = p->tablero->grilla[i][j];
        }
    }

	// Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
	// inicialmente es IA_NO_TERMINO
    estado->utilidad = IA_NO_TERMINO;

    // Inicializa los valores que representar�n a los jugadores MAX y MIN respectivamente.
    (*b)->jugador_max = p->turno_de;
    (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    // Inicializa un �rbol para la b�squeda adversaria inicialmente vac�o.
    crear_arbol(&((*b)->arbol_busqueda));

    // Inicializa la ra�z del �rbol de b�squeda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);

    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
*/
void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y) {
    //Atributos
    tArbol arbol = b->arbol_busqueda;
    tEstado mejor_estado, estado_inicial;
    tPosicion pos_actual, fin;
    int val, actualUtilidad;

    tLista lista_hijos=arbol->raiz->hijos;
    pos_actual = l_primera(lista_hijos);
    fin = l_fin(lista_hijos);
    estado_inicial = a_recuperar(arbol, arbol->raiz);
    mejor_estado = NULL;
    val = IA_INFINITO_NEG;

    while (pos_actual != fin && val != IA_GANA_MAX) {
        actualUtilidad = ((tEstado)a_recuperar(arbol, l_recuperar(lista_hijos, pos_actual)))->utilidad;

        if (actualUtilidad > val && actualUtilidad != IA_NO_TERMINO) {
            mejor_estado = ((tEstado)a_recuperar(arbol, l_recuperar(lista_hijos, pos_actual)));
            val = actualUtilidad;
        }

        pos_actual = l_siguiente(lista_hijos, pos_actual);
    }

    if (mejor_estado == NULL)
        mejor_estado = ((tEstado)a_recuperar(arbol, l_recuperar(lista_hijos, l_ultima(lista_hijos))));

    diferencia_estados(estado_inicial, mejor_estado, x, y);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
**/
void destruir_busqueda_adversaria(tBusquedaAdversaria * b){
        tArbol a=(*b)->arbol_busqueda;
        a_destruir(&a, &fEliminar);
        free(*b);
        *b=NULL;
}
void fEliminar(tElemento e){
    if(e!=NULL){
        tEstado n = (tEstado) e;
        free(n);
    }
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
- A referencia al �rbol de b�squeda adversaria.
- N referencia al nodo a partir del cual se construye el sub�rbol de b�squeda adversaria.
- ES_MAX indica si N representa un nodo MAX en el �rbol de b�squeda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el �rbol de b�squeda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min) {
    if (es_max)
        MAX(a, n, alpha, beta, jugador_max, jugador_min);
    else
        MIN(a, n, alpha, beta, jugador_max, jugador_min);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX gan� la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empate la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdi la partida.
- IA_NO_TERMINO en caso contrario.
**/
static int valor_utilidad(tEstado e, int jugador_max) {
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

static tLista estados_sucesores(tEstado e, int ficha_jugador) {

    tEstado toCreate;
    tLista list;
    tPosicion actual, fin;
    crear_lista(&list);
    int pos, size;
    srand(time(NULL));
    int j;
    int i;

    size = 0;
    for ( i = 0; i < 3; i++) {
        for ( j = 0; j < 3; j++) {
            if (e->grilla[i][j] == PART_SIN_MOVIMIENTO) {
                    size++;
                    toCreate = clonar_estado(e);
                    toCreate->grilla[i][j] = ficha_jugador;
                    pos = rand() % size;
                    actual = l_primera(list);
                    fin = l_fin(list);

                    while(pos != 0 && actual != fin) {
                        actual = l_siguiente(list, actual);
                        pos--;
                    }

                    l_insertar(list, actual, toCreate);
                }
        }
    }

    return list;
}


/**
>>>>>  A IMPLEMENTAR   <<<<< -> implementado 30/10/2019
Inicializa y retorna un nuevo estado que resulta de la clonación del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e){
    tEstado toReturn = (tEstado) malloc(sizeof(struct estado));
    toReturn->utilidad = e->utilidad;
    int i;
    int j;

    for ( i = 0; i < 3; i++) {
        for ( j = 0; j < 3; j++)
            toReturn->grilla[i][j] = e->grilla[i][j];
    }

    return toReturn;
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


int MAX(tArbol a, tNodo n, int alpha, int beta, int jugador_max, int jugador_min) {

    int utilidad, utilidadTemp;
    tNodo insertado;
    tLista sucesores;
    tPosicion actual, fin;
    tEstado estado = a_recuperar(a, n);
    tEstado temp;
    int termino;

    utilidad = valor_utilidad(estado, jugador_max);
    estado->utilidad = utilidad;

    if (utilidad == IA_NO_TERMINO && contarVacios(estado)>0) {
        sucesores = estados_sucesores(estado, jugador_max);
        actual = l_primera(sucesores);
        fin = l_fin(sucesores);
        termino = 0;

        while (actual != fin && !termino) {
            if (estado->utilidad == IA_NO_TERMINO)
                estado->utilidad = -9999;

            if (alpha == IA_INFINITO_NEG)
                alpha = -9999;

            if (beta == IA_INFINITO_POS)
                beta = 9999;

            temp = l_recuperar(sucesores, actual);
            insertado = a_insertar(a, n, NULL, temp);
            l_eliminar(sucesores, actual, &fNoElimina);

            utilidadTemp = MIN(a, insertado, alpha, beta, jugador_max, jugador_min);

            if (utilidadTemp > estado->utilidad && utilidadTemp != IA_NO_TERMINO)
                estado->utilidad = utilidadTemp;

            if (utilidadTemp >= beta && utilidadTemp != IA_NO_TERMINO)
                termino = 1;

            if (utilidadTemp > alpha && utilidadTemp != IA_NO_TERMINO)
                alpha = utilidadTemp;

            if (actual->siguiente == NULL)
                fin = l_fin(sucesores);

        }

        l_destruir(&sucesores, &eliminarEstado);
    }

    return estado->utilidad;
}

int MIN(tArbol a, tNodo n, int alpha, int beta, int jugador_max, int jugador_min) {

    int utilidad, utilidadTemp;
    tNodo insertado;
    tLista sucesores;
    tPosicion actual, fin;
    tEstado estado = a_recuperar(a, n);
    tEstado temp;
    int termino;

    utilidad = valor_utilidad(estado, jugador_max);
    estado->utilidad = utilidad;

    if (utilidad == IA_NO_TERMINO && contarVacios(estado)>0) {

        sucesores = estados_sucesores(estado, jugador_min);
        actual = l_primera(sucesores);
        fin = l_fin(sucesores);
        termino = 0;

        while (actual != fin && !termino) {
            if (estado->utilidad == IA_NO_TERMINO)
                estado->utilidad = 9999;

            if (alpha == IA_INFINITO_NEG)
                alpha = -9999;

            if (beta == IA_INFINITO_POS)
                beta = 9999;

            temp = l_recuperar(sucesores, actual);
            insertado = a_insertar(a, n, NULL, temp);
            l_eliminar(sucesores, actual, &fNoElimina);

            utilidadTemp = MAX(a, insertado, alpha, beta, jugador_max, jugador_min);

            if (utilidadTemp < estado->utilidad && utilidadTemp != IA_NO_TERMINO)
                estado->utilidad = utilidadTemp;

            if (utilidadTemp <= alpha && utilidadTemp != IA_NO_TERMINO)
                termino = 1;

            if (utilidadTemp < beta && utilidadTemp != IA_NO_TERMINO)
                beta = utilidadTemp;


            if (actual->siguiente == NULL)
                fin = l_fin(sucesores);
        }

        l_destruir(&sucesores, &eliminarEstado);
    }

    return estado->utilidad;
}


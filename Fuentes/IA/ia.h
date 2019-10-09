#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#include "arbol.h"
#include "partida.h"

// Importante: IA_PIERDE_MAX < IA_EMPATA_MAX < IA_GANA_MAX

#define IA_PIERDE_MAX       1000
#define IA_EMPATA_MAX       1001
#define IA_GANA_MAX         1002
#define IA_NO_TERMINO       1003
#define IA_ERROR_MEMORIA    1004

struct busqueda_adversaria{
    tArbol arbol_busqueda;
    int jugador_max;
    int jugador_min;
};

struct estado{
    int tablero [3][3];
    int utilidad;
};

typedef struct busqueda_adversaria * tBusquedaAdversaria;
typedef struct estado * tEstado;

/**
 Inicializa la estructura correspondiente a una búsqueda adversaria, a partir del estado actual de la partida parametrizada.
 Se asume la partida parametrizada con estado PART_EN_JUEGO.
 Los datos del tablero de la partida parametrizada son clonados, por lo que P no se ve modificada.
**/
extern void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p);

/**
 Computa y retorna el próximo movimiento a realizar por el jugador MAX, a la espera de obtener un RESULTADO_ESPERADO.
 En caso no poder concretar el RESULTADO_ESPERADO a partir del estado actual de B, intenta concretar un estado según el siguiente detalle:
 - Si estado esperado es IA_GANA_MAX y no se puede obtener, se busca un estado IA_EMPATA_MAX; de no existir, se retorna un estado IA_PIERDE_MAX.
 - Si estado esperado es IA_EMPATA_MAX y no se puede obtener, se busca un estado IA_GANA_MAX; de no existir, se retorna un estado IA_GANA_MAX.
 - Si estado esperado es IA_PIERDE_MAX y no se puede obtener, se busca un estado IA_EMPATA_MAX; de no existir, se retorna un estado IA_GANA_MAX.
**/
extern void proximo_movimiento(tBusquedaAdversaria b, int resultado_esperado, int * x, int * y);

/**
 Libera el espacio asociado a la estructura correspondiente para la búsqueda adversaria.
**/
extern void destruir_busqueda_adversaria(tBusquedaAdversaria * b);


#endif // IA_H_INCLUDED

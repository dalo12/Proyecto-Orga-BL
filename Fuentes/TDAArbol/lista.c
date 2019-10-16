#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


/**
 Inicializa una lista vacía.
 Una referencia a la lista creada es referenciada en *L.
**/
extern void crear_lista(tLista *l){//Crea la lista vacia con un celda dammi vacio al inicio;
    *l=(tLista)malloc(sizeof(struct celda));
    (*l)->siguiente = NULL;//Setea el apuntador al celda siguiente en nulo
    (*l)->elemento = NULL;//Setea el elemento en nulo
}

/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D
**/
extern void l_insertar(tLista l, tPosicion p, tElemento e){//Agrega una celda en la pos pasada por parametro
    tPosicion aux;
    aux=(tPosicion)malloc(sizeof(struct celda));//Asigno memoria para la nueva celda
    aux->elemento=e;//Guardo el elemento
    aux->siguiente=p->siguiente;
    p->siguiente=aux;

}

/**
 Elimina el nodo que se encuentra en la posición P de L.
 El elemento almacenado en la posición P es eliminado mediante la función fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/

//Cont tPos t tLista no tendira 2 punteros a la celda? tengo que eliminar los 2? en necesario el extern?

extern void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){//Elimina la celda siguiente a la pos pasada
    tPosicion aux;
    if(p->siguiente==NULL)
        exit(LST_POSICION_INVALIDA);
    aux=p->siguiente;//Asigna aux a al nodo siguiente al de la pos pasada
    p->siguiente=aux->siguiente;//P ahora apunta al siguiente de aux es decir se saltea aux
    fEliminar(p->elemento);
    //aux->siguiente = NULL;
    free(aux);//Libero el espacio de aux(lo elimino)
}

/**
 Destruye la lista L, elimininando cada una de sus posiciones.
 Los elementos almacenados en las posiciones son eliminados mediante la función fEliminar parametrizada.
**/
extern void l_destruir(tLista * l, void (*fEliminar)(tElemento)){
    tLista aux=(*l)->siguiente;//Lista auxiliar
    tLista aEliminar;
    while(aux!=NULL){//Si la lista no es vacia la recorro y elimino
        aEliminar=aux;
        aux=aux->siguiente;
        (*l)->siguiente=aux;
        (*fEliminar)(aEliminar->elemento);//Elimino el elemento dentro de la celda
        free(aEliminar);//Elimino la celda
    }
}

 /**
 Recupera y retorna el elemento en la posición P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
extern tElemento l_recuperar(tLista l, tPosicion p){
    if(p->siguiente==NULL || p==NULL)
        exit(LST_POSICION_INVALIDA);
    return p->siguiente->elemento;//Retorno el elemento
}

/**
 Recupera y retorna la primera posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_primera(tLista l){
    return l;//Devuelve el nodo dami ??????


}

/**
 Recupera y retorna la posición siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
extern tPosicion l_siguiente(tLista l, tPosicion p){
    if(p->siguiente==NULL || p==NULL)
        exit(LST_NO_EXISTE_SIGUIENTE);
    return p->siguiente;


}

/**
 Recupera y retorna la posición anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
extern tPosicion l_anterior(tLista l, tPosicion p){
    tLista aux=l;
    if(l==p || p==NULL)//Si la lista es vacia devuelvo el error
        exit(LST_NO_EXISTE_ANTERIOR);
    else{
        while(aux->siguiente!=p){//Si la lista no es vacio la recorro hasta encontrar la pos anterior de p
            aux=aux->siguiente;
        }
    }
    return aux;

}

 /**
 Recupera y retorna la última posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_ultima(tLista l){
    tPosicion aux;
    tPosicion anterior = l;
    if(anterior->siguiente != NULL){
        aux = anterior->siguiente;
        while(aux->siguiente!=NULL){//Si la lista no es vacio la recorro hasta encontrar la ultima celda
            anterior = aux;
            aux=aux->siguiente;
        }
    }
    return anterior;
}

 /**
 Recupera y retorna la posición fin de L
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_fin(tLista l){
    tLista aux=l;
    while(aux->siguiente != NULL){//Si la lista no es vacio la recorro hasta encontrar la pos final
       aux=aux->siguiente;
    }
    return aux;
}


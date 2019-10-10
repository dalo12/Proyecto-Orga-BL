#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void estadoActual(tArbol a);
void preorden(tNodo n, int nivel);

int main(){
    tArbol arbol;
    crear_arbol(&arbol);

    //estadoActual(arbol);
    return 0;
}

void estadoActual(tArbol a){
    preorden(a->raiz, 0); //0 indica el nivel
}

void preorden(tNodo n, int nivel){
    tLista hijos_n = n->hijos; //Lista de nodos
    tPosicion p = l_primera(hijos_n); //Posición que almacena un nodo

    for(int i=0; i<nivel; i++){
        printf("\t");
    }
    printf("L %p\n", n->elemento);

    while(p != l_ultima(hijos_n)){
        preorden(p->elemento, nivel+1);
        p = l_siguiente(hijos_n, p);
    }

}

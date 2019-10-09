#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void estadoActual(tArbol a);
void preorden(tNodo n, int nivel);

int main(){
    tArbol ar;
    crear_arbol(&ar);
    crear_raiz(ar, (int *) 15);

    estadoActual(ar);
    return 0;
}

void estadoActual(tArbol a){
    if(a->raiz != NULL){
        preorden(a->raiz, 0); //0 indica el nivel
    }
}

void preorden(tNodo n, int nivel){
    if(n != NULL){
        tLista hijos_n = n->hijos; //Lista de nodos
        tPosicion p = l_primera(hijos_n); //Posición que almacena un nodo

        for(int i=0; i<nivel; i++){
            printf("\t");
        }
        printf("L %d\n", n->elemento);

        while(p != l_ultima(hijos_n)){
            preorden(p->elemento, nivel+1);
            p = l_siguiente(hijos_n, p);
        }
    }
}

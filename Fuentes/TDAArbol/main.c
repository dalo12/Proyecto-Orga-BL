#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void estadoActual(tArbol a);
void preorden(tNodo n, int nivel);
void fEliminar(int *n);

int main(){
    tArbol ar;
    crear_arbol(&ar);
    crear_raiz(ar, (int *) 15);
    //tNodo raiz=a_raiz(ar);
    //tLista hijos=a_hijos(ar,raiz);
    //tNodo n=(tNodo)l_recuperar(hijos,l_siguiente(hijos,hijos));
    //int aInsertar=40;
   // a_insertar(ar,a_raiz(ar),n,(tElemento)aInsertar);
    //estadoActual(arbol);
   // estadoActual(ar);
    tNodo h = NULL;
    for(int i=0; i<20; i++){
        h = a_insertar(ar, ar->raiz, NULL, (int *) i);
    }
    estadoActual(ar);

    a_destruir(&ar, fEliminar);
    //estadoActual(ar);
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
            printf("   ");
        }
        printf("L %d\n", n->elemento);

        while(p != l_fin(hijos_n)){//l_fin(hijos_n)){
            preorden(p->elemento, nivel+1);
            p = l_siguiente(hijos_n, p);
        }
        preorden(p->elemento, nivel+1);
    }
}

void fEliminar(int* n){
    free(n);
}

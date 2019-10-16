#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void estadoActual(tArbol a);
void preorden(tNodo n, int nivel);
void fEliminar(tElemento e);

int main(){
    tArbol ar;
    crear_arbol(&ar);
    crear_raiz(ar, 15);
    //tNodo raiz=a_raiz(ar);
    //tLista hijos=a_hijos(ar,raiz);
    //tNodo n=(tNodo)l_recuperar(hijos,l_siguiente(hijos,hijos));
    //int aInsertar=40;
   // a_insertar(ar,a_raiz(ar),n,(tElemento)aInsertar);
    //estadoActual(arbol);
   // estadoActual(ar);
    tNodo h = NULL;
    tNodo h_medio = NULL;
    for(int i=0; i<20; i++){
        if(i==13){
            h_medio = a_insertar(ar, ar->raiz, NULL, i);
        }else{
            h = a_insertar(ar, ar->raiz, NULL, i);
        }
    }
    a_insertar(ar, ar->raiz, h, 45);
    tNodo h1 = a_insertar(ar, h, NULL, 77);
    a_insertar(ar, h1, NULL, 32);

    tNodo h2 = a_insertar(ar, h_medio, NULL, 133);
    a_insertar(ar, h_medio, h2, 132);
    a_insertar(ar, h2, NULL, 134);

    estadoActual(ar);

    printf("\n---DESTRUIR---\n\n");
    a_destruir(&ar, &fEliminar);
    estadoActual(ar);
    return 0;
}

void estadoActual(tArbol a){
    if(a->raiz != NULL && a->raiz->hijos != NULL){
        preorden(a->raiz, 0); //0 indica el nivel
    }else{
        printf("El árbol no tiene raíz.\n");
    }
}

void preorden(tNodo n, int nivel){
    if(n != NULL && n->hijos != NULL){
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

void fEliminar(tElemento e){
    int n = (int) e;
    n = 0;
    //free(n);//solamente es valido si lo que quiero liberar(osea e)fue asignado dinamicamente(malloc)
}

#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void estadoActual(tArbol a);
void imprimir_preorden(tNodo n, int nivel);
void fEliminar(tElemento e);

int main(){
    tArbol ar;
    crear_arbol(&ar);
    crear_raiz(ar, 15);

    //crear_raiz(ar, 16); //Tira error, porque debe hacerlo
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

    //a_insertar(ar, ar->raiz, h2, 145); //Tira error, porque debe hacerlo

    estadoActual(ar);

// ---- a_eliminar() INICIO PRUEBA
    /*a_eliminar(ar, h_medio, &fEliminar);
    printf("\n\nElimino el nodo %d\n", h_medio->elemento);
    estadoActual(ar);
    /*
    //debería saltar error. Lo hace
    a_eliminar(ar, ar->raiz, &fEliminar);
    estadoActual(ar);
    */
    /*
    //creo un arbol con una raiz con dos hijos.
    //debería saltar error. Lo hace
    tArbol ar2;
    crear_arbol(&ar2);
    crear_raiz(ar2, 234);
    tNodo ar2_h1 = a_insertar(ar2, ar2->raiz, NULL, 345);
    a_insertar(ar2, ar2->raiz, NULL, 456);

    estadoActual(ar2);
    a_eliminar(ar2, ar2->raiz, &fEliminar);
    estadoActual(ar2);
    */

// ---- a_eliminar() FIN PRUEBA

// ---- a_sub_arbol() INICIO PRUEBA
    printf("\n---SUBARBOL---\n");
    tArbol na;
    a_sub_arbol(ar, h_medio, &na);
    printf("\nEstado actual de ar:\n");
    estadoActual(ar);
    printf("\nEstado actual de na:\n");
    estadoActual(na);
// ---- a_sub_arbol() FIN PRUEBA

// ---- a_sub_arbol() INICIO PRUEBA
    printf("\n---DESTRUIR---\n\n");
    a_destruir(&na, &fEliminar);
    estadoActual(na);
// ---- a_destruir() FIN PRUEBA

    return 0;
}

void estadoActual(tArbol a){
    if(a->raiz != NULL && a->raiz->hijos != NULL){
        imprimir_preorden(a->raiz, 0); //0 indica el nivel
    }else{
        printf("El árbol no tiene raíz.\n");
    }
}

void imprimir_preorden(tNodo n, int nivel){
    if(n != NULL && n->hijos != NULL){
        tLista hijos_n = n->hijos; //Lista de nodos
        tPosicion p = l_primera(hijos_n); //Posición que almacena un nodo

        for(int i=0; i<nivel; i++){
            printf("   ");
        }
        /*
        if(n->padre != NULL){
            printf("L %d (%d)\n", n->elemento, n->padre->elemento);
        }else{
            printf("L %d (NULL)\n", n->elemento);
        }
        */
        printf("L %d\n", n->elemento);
        while(p != l_fin(hijos_n)){//l_fin(hijos_n)){
            imprimir_preorden(p->elemento, nivel+1);
            p = l_siguiente(hijos_n, p);
        }
        imprimir_preorden(p->elemento, nivel+1);
    }
}

void fEliminar(tElemento e){
    int n = (int) e;
    n = -1;
    //free(n);//solamente es valido si lo que quiero liberar(osea e)fue asignado dinamicamente(malloc)
}

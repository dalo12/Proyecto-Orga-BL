#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

/**
Función privada. Se utiliza por a_destruir() para recorrer y eliminar el arbol con un
recorrido en preorden.
@param n Nodo en el que estoy parado actualmente
@param fEliminar Función que se utiliza para eliminar el elemento del nodo
**/
static void aux_destruir(tNodo n, void(*fEliminar)(tElemento)){
    tLista l = n->hijos;
    if(l != NULL){
        tPosicion p = l_primera(l);
        tNodo h;

        /*Este while actúa igual que un foreach para la lista de hijos de n*/
        while(p != l_fin(l)){ // o NULL ? No, l_fin(l) retorna la última componente de la lista, que es visitada en el ciclo anterior en el l_recuperar().
            h = l_recuperar(l, p); //suponiendo que la lista l es una lista de tNodo
            aux_destruir(h, fEliminar);
            p = l_siguiente(l, p);
        }

        n->hijos = NULL;
        n->padre = NULL;
        (fEliminar)(n->elemento);
        free(n);
    }
}

/**
Función creada para eliminar un nodo de la lista de hijos, pero no el nodo en sí mismo.
@param e Elemento a eliminar
**/
static void noElimino(void* e){
    //No hago nada
}

/**
Busca y elimina un nodo hijo de la lista de hijos de su nodo padre
@param a Árbol a recorrer (es necesario?)
@param h Nodo actual en el que estoy parado
@param n Nodo buscado
**/
static void buscar_y_borrar_hijo(tArbol a, tNodo h, tNodo n){
    tLista l = h->hijos;
    tPosicion p = l_primera(l);
    tNodo s;
    int encontrado = 0;

    //Me fijo si el nodo n buscado es el nodo h pasado por parámetro
    if(n == h){
        // dos nodos son lo mismo si tienen el mismo elemento, el mismo padre y los mismos hijos
        encontrado = 1;
    }

    //Me fijo si el nodo n buscado está en la lista de hijos del nodo h pasado por parámetro y de ser así, lo elimino
    if(!encontrado){
        while(!encontrado && p != l_fin(l)){
            s = l_recuperar(l, p);
            if(s == n){
                encontrado = 1;
                l_eliminar(l, p, noElimino);
            }
            p = l_siguiente(l, p);
        }
    }

    //Me fijo si el nodo n buscado está en algún descendiente del nodo h
    if(!encontrado){
        l = h->hijos;
        p = l_primera(l);

        while(l_fin(l)){
            s = l_recuperar(l, p);
            buscar_y_borrar_hijo(a, s, n);
            p = l_siguiente(l, p);
        }
    }
}

/**
Inicializa un árbol vacío.
Una referencia al árbol creado es referenciado en *A.
**/

extern void crear_arbol(tArbol * a){
    *a = (tArbol) malloc(sizeof(struct arbol));//Asigno memoria a la estructura arbol
    (*a)->raiz = NULL;//Raiz es nulo
}

/**
Crea la raíz de A.
Si A no es vacío, finaliza indicando ARB_OPERACION_INVALIDA.
**/

extern void crear_raiz(tArbol a, tElemento e){//TENGO QUE CREAR ESPACIO PARA EL NODO O ESO PASA CUANDO HAGO EL MALLOC DE tArbol?
    tLista l;
    tNodo root = (tNodo) malloc(sizeof(struct nodo));

    crear_lista(&l);//crear el nodo
    if(a->raiz != NULL)
        exit(ARB_OPERACION_INVALIDA);

    root->elemento = e;
    root->padre=NULL;
    root->hijos=l;
    a->raiz = root;
    //a->raiz->elemento=e;
    //a->raiz->padre=NULL;
    //a->raiz->hijos=l;


}

/**
 Inserta y retorna un nuevo nodo en A.
 El nuevo nodo se agrega en A como hijo de NP, hermano izquierdo de NH, y cuyo rótulo es E.
 Si NH es NULL, el nuevo nodo se agrega como último hijo de NP.
 Si NH no corresponde a un nodo hijo de NP, finaliza indicando ARB_POSICION_INVALIDA.
 NP direcciona al nodo padre, mientras NH al nodo hermano derecho del nuevo nodo a insertar.
**/

extern tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
    tLista listaHijos=np->hijos;
    tLista aux=l_primera(listaHijos);
    tLista insert;//Pos anterior
    tNodo aInsertar=(tNodo)malloc(sizeof(struct nodo));
    aInsertar->padre=np;
    aInsertar->elemento=e;
    tLista hijos_de_a_insertar;
    crear_lista(&hijos_de_a_insertar);
    aInsertar->hijos = hijos_de_a_insertar;

    if(nh==NULL)//Si el hermano es nulo inserto al final
        l_insertar(listaHijos,l_fin(listaHijos),aInsertar);
    else{//Si no es nulo recorro la lista de hijos hasta encontrar
        while(aux!=NULL && nh!=aux->elemento){
            insert=aux;//A pos anterior le asigno aux
            aux=l_siguiente(listaHijos,aux);
        }
         if(nh==aux->elemento)//Si encuentro al hermano inserto en la lista
            l_insertar(listaHijos,insert,aInsertar);
        else
            exit(ARB_POSICION_INVALIDA);//Si no error
    }
    return aInsertar;
}


/**
 Elimina el nodo N de A.
 El elemento almacenado en el árbol es eliminado mediante la función fEliminar parametrizada.
 Si N es la raíz de A, y tiene un sólo hijo, este pasa a ser la nueva raíz del árbol.
 Si N es la raíz de A, y a su vez tiene más de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la raíz de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posición que ocupa N en la lista de hijos de su padre.
**/

extern void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    tLista listaHijo;
    tPosicion posLista;
    tPosicion posListaPadre;
    tLista listaPadre;
    int cont=0;
    if(a->raiz==n){//Si raiz es n
        listaHijo=n->hijos;
        posLista=l_primera(listaHijo);
        while(posLista!=NULL && cont<2){
            if(l_siguiente(listaHijo,posLista)!=NULL){
                cont++;
                posLista=l_siguiente(listaHijo,posLista);
            }
        }
        if(cont>=2){
            exit(ARB_OPERACION_INVALIDA);
        }
        else
            if(cont==1){
                free(a->raiz->elemento);
                a->raiz->hijos=NULL;
                n->padre=NULL;
                a->raiz=n;
            }
    }
    else{//Preguntar
        listaHijo=n->hijos;
        listaPadre=n->padre->hijos;
        tNodo padre=n->padre;
        posListaPadre=l_primera(listaPadre);
        posLista=l_primera(listaHijo);
        int cont=0;
        while(posListaPadre!=NULL && cont!=1){
            if(l_recuperar(listaPadre,posListaPadre)==padre){
                cont=1;
            }
            else{
                posListaPadre=l_siguiente(listaPadre,posListaPadre);

            }



        }
        while(posLista!=NULL){
            tNodo aInsertar=l_recuperar(listaHijo,posLista);
            l_insertar(listaPadre,posListaPadre,aInsertar);
            posLista=l_siguiente(listaHijo,posLista);
            posListaPadre=l_siguiente(listaPadre,posListaPadre);

        }




    }



}

/**
 Destruye el árbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el árbol son eliminados mediante la función fEliminar parametrizada.
**/
extern void a_destruir(tArbol * a, void (*fEliminar)(tElemento)){
    tNodo n = (*a)->raiz;

    if(n != NULL){
        aux_destruir(n, fEliminar);
    }
}

/**
Recupera y retorna el elemento del nodo N.
*/

extern tElemento a_recuperar(tArbol a, tNodo n){
    return n->elemento;
}


/**
Recupera y retorna el nodo correspondiente a la raíz de A.
**/
extern tNodo a_raiz(tArbol a){
    return a->raiz;
}

/**
 Obtiene y retorna una lista con los nodos hijos de N en A.
**/
extern tLista a_hijos(tArbol a, tNodo n){
    return n->hijos;
}

/**
 Inicializa un nuevo árbol en *SA.
 El nuevo árbol en *SA se compone de los nodos del subárbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/
extern void a_sub_arbol(tArbol a, tNodo n, tArbol * sa){
    /*tNodo aux = (tNodo)malloc(sizeof(struct nodo));
    aux->elemento = n->elemento;
    aux->hijos = n->hijos;
    aux->padre = n->padre;*/
    (*sa)->raiz = n;
    n->padre = NULL;
    tNodo h = a->raiz;

    buscar_y_borrar_hijo(a, h, n);
}


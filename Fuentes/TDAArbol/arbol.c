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
        fEliminar(n->elemento);
        free(n);
    }
}

/**
Función creada para eliminar un nodo de la lista de hijos, pero no el nodo en sí mismo.
@param e Elemento a eliminar
**/
static void noElimino(tElemento e){
    //No hago nada
}

/**
Función creada para eliminar un nodo, pero sin eliminar a sus hijos (aunque sí a la lista de sus hijos)
@param n Nodo a liminar
@param fEliminar Función que elimina el elemento que contiene el nodo n
**/
static void eliminarNodo(tElemento e){
    tNodo n = (tNodo) e;
    tLista hijos = n->hijos;
    l_destruir(&hijos, &noElimino); //mato al nodo, pero no a sus hijos
    n->padre = NULL;
    n = NULL;
}

/**
Busca y elimina un nodo hijo de la lista de hijos de su nodo padre
@param a Árbol a recorrer (es necesario?)
@param actual Nodo actual en el que estoy parado
@param buscado Nodo buscado
**/
static void buscar_y_borrar_hijo(tArbol a, tNodo actual, tNodo buscado){
    tLista lista_hijos_actual = actual->hijos;
    tPosicion pos_hijo_actual = l_primera(lista_hijos_actual);
    tNodo hijo_actual;
    int encontrado = 0;

    //Me fijo si el nodo buscado es el nodo actual pasado por parámetro
    if(buscado == actual){
        encontrado = 1;
    }

    //Me fijo si el nodo n buscado está en la lista de hijos del nodo h pasado por parámetro y de ser así, lo elimino
    if(!encontrado){
        while(!encontrado && pos_hijo_actual != l_fin(lista_hijos_actual)){
            hijo_actual = l_recuperar(lista_hijos_actual, pos_hijo_actual);
            if(hijo_actual == buscado){
                encontrado = 1;
                l_eliminar(lista_hijos_actual, pos_hijo_actual, &noElimino);
            }
            pos_hijo_actual = l_siguiente(lista_hijos_actual, pos_hijo_actual);
        }
    }

    //Me fijo si el nodo n buscado está en algún descendiente del nodo h
    if(!encontrado){
        lista_hijos_actual = actual->hijos;
        pos_hijo_actual = l_primera(lista_hijos_actual);

        while(pos_hijo_actual != l_fin(lista_hijos_actual)){
            hijo_actual = l_recuperar(lista_hijos_actual, pos_hijo_actual);
            buscar_y_borrar_hijo(a, hijo_actual, buscado);
            pos_hijo_actual = l_siguiente(lista_hijos_actual, pos_hijo_actual);
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

extern void crear_raiz(tArbol a, tElemento e){
    tLista l;
    tNodo root = (tNodo) malloc(sizeof(struct nodo)); //crea el nodo

    crear_lista(&l);//crear la lista de hijos del nodo
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
    tLista lista_hijos_padre = np->hijos;
    tPosicion pos_nh = l_primera(lista_hijos_padre);
    //tPosicion pos_anterior;//Pos anterior
    tNodo aInsertar = (tNodo)malloc(sizeof(struct nodo));
    int encontrado = 0;

    aInsertar->padre = np;
    aInsertar->elemento=e;
    tLista hijos_de_a_insertar;
    crear_lista(&hijos_de_a_insertar);
    aInsertar->hijos = hijos_de_a_insertar;

    if(nh == NULL){//Si el hermano es nulo inserto al final
        l_insertar(lista_hijos_padre,l_fin(lista_hijos_padre), aInsertar);
    }else{//Si no es nulo recorro la lista de hijos hasta encontrar
        //tNodo posible_nh = l_recuperar(lista_hijos_padre, pos_nh);
        while(pos_nh != l_fin(lista_hijos_padre) && !encontrado){
            if(l_recuperar(lista_hijos_padre, pos_nh) == nh){
                encontrado = 1;
            }else{
                pos_nh = l_siguiente(lista_hijos_padre, pos_nh);
            }
            /*
            //pos_anterior = pos_hijo_padre;//A pos anterior le asigno la posición anterior de hijo padre
            posible_nh = l_recuperar(lista_hijos_padre, pos_nh);
            pos_nh = l_siguiente(lista_hijos_padre,pos_nh);
            */
        }
        if(encontrado){//Si encuentro al hermano inserto en la lista
            l_insertar(lista_hijos_padre, pos_nh, aInsertar);
        }else{
            exit(ARB_POSICION_INVALIDA);//Si no error
        }
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
    tPosicion pos_hijo = l_primera(n->hijos);

    if(n == a->raiz){
    // ---- CASO 2 ----
        //Cuento los hijos que tiene la raíz
        int cant_hijos = 0;
        while(pos_hijo != l_fin(n->hijos) && cant_hijos < 2){
            cant_hijos++;
            pos_hijo = l_siguiente(n->hijos, pos_hijo);
        }

        //Si la raíz tiene más de un hijo, caigo en error
        if(cant_hijos > 1){
            exit(ARB_OPERACION_INVALIDA);
        }else{
    // ---- CASO 1 ----

            //Sino, la reemplazo por su hijo

            tPosicion pos_hijo_unico = l_primera(a->raiz->hijos);
            tNodo hijo_raiz = l_recuperar(a->raiz->hijos, pos_hijo_unico);

            fEliminar(n->elemento);
            eliminarNodo(n); //elimino al nodo con mi función especial

            a->raiz = hijo_raiz;
            hijo_raiz->padre = NULL;
        }
    }else{
    // ---- CASO 3 ----

        tNodo padre_n = n->padre;
        tLista lista_hermanos_n = padre_n->hijos;

        //busco la posición de n en la lista de hijos de su padre
        tPosicion pos_hermano_n = l_primera(lista_hermanos_n);
        tNodo hermano_n;
        tPosicion pos_n = NULL;
        int encontrado = 0;

        while(pos_hermano_n != l_fin(lista_hermanos_n) && !encontrado){
            hermano_n = l_recuperar(lista_hermanos_n, pos_hermano_n);
            if(hermano_n == n){ //encontré la pos de n
                pos_n = pos_hermano_n;
                encontrado = 1;
            }
            pos_hermano_n = l_siguiente(lista_hermanos_n, pos_hermano_n);
        }

        //agrego los hijos de n a la lista de hijos del padre de n
        tLista lista_hijos_n = n->hijos;
        tPosicion pos_hijo_n = l_primera(lista_hijos_n);
        tNodo hijo_n;
        if(pos_n != NULL){ //estará de más esta verificación? Por las dudas ...

            while(pos_hijo_n != l_fin(lista_hijos_n)){
                hijo_n = l_recuperar(lista_hijos_n, pos_hijo_n);
                hijo_n->padre = padre_n;
                l_insertar(lista_hermanos_n, pos_n, hijo_n);
                pos_n = l_siguiente(lista_hermanos_n, pos_n); //el l_insertar hace que la pos_n cambie (se atrase 1)
                pos_hijo_n = l_siguiente(lista_hijos_n, pos_hijo_n);
            }
        }
        //elimino a n de la lista de hijos del padre
        fEliminar(n->elemento);
        l_eliminar(lista_hermanos_n, pos_n, &eliminarNodo);
        l_destruir(&lista_hijos_n, &noElimino);
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
    *sa = (tArbol) malloc(sizeof(struct arbol));
    (*sa)->raiz = n;
    n->padre = NULL;

    if(n == a->raiz){
        a->raiz = NULL;
    }else{
        tNodo h = a->raiz; //porque empiezo a buscar el padre de n buscando desde la raíz
        buscar_y_borrar_hijo(a, h, n);
    }
}


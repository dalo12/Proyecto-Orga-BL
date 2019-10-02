







/**
Inicializa un árbol vacío.
Una referencia al árbol creado es referenciado en *A.
**/
extern void crear_arbol(tArbol * a){
    (a*)=(tArbol)malloc(sizeof(struct arbol));//Asigno memoria a la estructura arbol
    (a*)->raiz=NULL;//Raiz es nulo
}

/**
Crea la raíz de A.
Si A no es vacío, finaliza indicando ARB_OPERACION_INVALIDA.
**/
extern void crear_raiz(tArbol a, tElemento e){//TENGO QUE CREAR ESPACIO PARA EL NODO O ESO PASA CUANDO HAGO EL MALLOC DE tArbol?
    tLista l;
    crear_lista(&l)//crear el nodo
    if(a->raiz==NULL)
        exit(ARB_OPERACION_INVALIDA);
    a->raiz->elemento=e;
    a->raiz->padre=NULL;
    a->raiz->hijos=l;


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
    aInsertar->

    if(nh==NULL)//Si el hermano es nulo inserto al final
        l_insertar(listaHijos,l_fin(listaHijos),aInsertar);
    else{//Si no es nulo recorro la lista de hijos hasta encontrar
        while(l_siguiente(listaHijos)!=NULL && nh!=aux){
            insert=aux;//A pos anterior le asigno aux
            aux->siguiente=aux->siguiente;
        }
         if(nh==aux)//Si encuentro al hermano inserto en la lista
            l_insertar(listaHijos,insert,aInsertar);
        else
            exit(ARB_POSICION_INVALIDA);//Si no error
    }
}

/**
 Elimina el nodo N de A.
 El elemento almacenado en el árbol es eliminado mediante la función fEliminar parametrizada.
 Si N es la raíz de A, y tiene un sólo hijo, este pasa a ser la nueva raíz del árbol.
 Si N es la raíz de A, y a su vez tiene más de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la raíz de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posición que ocupa N en la lista de hijos de su padre.
**/
extern void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    if(a->raiz==n){//Si raiz es n


    }
    else{




    }



}

/**
 Destruye el árbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el árbol son eliminados mediante la función fEliminar parametrizada.
**/
extern void a_destruir(tArbol * a, void (*fEliminar)(tElemento));

/**
Recupera y retorna el elemento del nodo N.
*/
extern tElemento a_recuperar(tArbol a, tNodo n){

}

/**
Recupera y retorna el nodo correspondiente a la raíz de A.
**/
extern tNodo a_raiz(tArbol a);

/**
 Obtiene y retorna una lista con los nodos hijos de N en A.
**/
extern tLista a_hijos(tArbol a, tNodo n);

/**
 Inicializa un nuevo árbol en *SA.
 El nuevo árbol en *SA se compone de los nodos del subárbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/
extern void a_sub_arbol(tArbol a, tNodo n, tArbol * sa);


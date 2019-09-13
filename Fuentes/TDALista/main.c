#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
void elimanarElemento(int* e);
void insertar(tLista l);
void imprimir(tLista l);
int main()
{
    //int e=5;
    tLista l;
    (crear_lista(&l));
    //l_insertar(l,l,&e);
   // printf("Hello world!  %d \n",e);
    insertar(l);
   //imprimir(l);
    //l_destruir(l,elimanarElemento);
   //imprimir(l);


    return 0;
}
void imprimir(tLista l){
    tLista aux;
        aux=l_primera(l);
        //int *ele=(int*)l_recuperar(l,aux);
        //printf(" Numero %d \n",*ele);
        while(aux!=2){
            //int *ele=(int*)l_recuperar(l,aux);
           // printf(" %d \n",l_recuperar(l,aux));
           // printf(" Numero %d \n",*ele);
            aux=l_siguiente(l,aux);
    }
}
void insertar(tLista l){
    int e;
    for(int i=0;i<20;i++){
        e=i+5;//Elemento a insertar
        l_insertar(l,l,&e);//inserto el elemento en la lista
    }

}

void elimanarElemento(int* e){
   free(*e);
}

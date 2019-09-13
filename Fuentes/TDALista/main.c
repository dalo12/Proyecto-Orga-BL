#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void eliminarElemento(int* e);
void insertar(tLista l);
void imprimir(tLista l);
tLista l;

int main()
{
    int res = 0;
    int e;

    printf("----BIENVENIDO AL SIMULADOR DE LISTA----");
    do{
        printf("\nSeleccione una opción:\n\t1: Crear lista de enteros.\n\t2: Insertar entero.\n\t3: Imprimir lista por pantalla.\n\t4: Salir.\n\n");
        scanf("%d", &res);

        switch(res){
            case 1: {
                crear_lista(&l);
                printf("Lista creada con éxito!\n");
                break;
            }
            case 2: {
                printf("Ingrese el entero a insertar: \n");
                scanf("%i", &e);
                l_insertar(l, l_ultima(l), e);
                break;
            }
            case 3: {
                imprimir(l);
                break;
            }
            case 4: {
                l_destruir(l, eliminarElemento);
                printf("Lista destruida con éxito.\nSaliendo...");
                break;
            }
        }
    }while((res > 0) && (res < 5));

/* No sé que onda esto
    //int e=5;
    tLista l;
    (crear_lista(&l));
    //l_insertar(l,l,&e);
   // printf("Hello world!  %d \n",e);
    insertar(l);
   //imprimir(l);
    //l_destruir(l,elimanarElemento);
   //imprimir(l);

*/
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

void eliminarElemento(int* e){
   free(*e);
}

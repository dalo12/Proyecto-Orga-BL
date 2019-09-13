#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void eliminarElemento(int* e);
void insertar(tLista l);
void imprimir(tLista l);

int main()
{
    int res = 0;
    //int *e=(int *)malloc(sizeof(int));
    tLista l;


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
                int *e=(int *)malloc(sizeof(int));
                scanf("%d", e);

               //*aux=e;
               //l_insertar(l, l, e);
                insertar(l);
                break;
            }
            case 3: {
                imprimir(l);
                break;
            }
            /*case 4: {
                l_destruir(&l, eliminarElemento);
                printf("Lista destruida con éxito.\nSaliendo...");
                break;
            }*/
        }
    }while((res > 0) && (res < 5));

    return 0;
}

void imprimir(tLista l){
    tLista aux;

        aux=l_primera(l);
        while(aux!=l_fin(l)){
            int *ele=(int*)l_recuperar(l,aux);
            printf(" Numero11 %d \n",*ele);
            aux=l_siguiente(l,aux);
        }
        int *ele=(int*)l_fin(l)->elemento;
        printf(" Numero sali %d \n",*ele);
}
void insertar(tLista l){
    int *e;
    for(int i=0;i<20;i++){
        e=(int *)malloc(sizeof(int));
        *e=i+8;//Elemento a insertar
        l_insertar(l,l,e);//inserto el elemento en la lista
    }

}

void eliminarElemento(int* e){
   free((int *)e);
}

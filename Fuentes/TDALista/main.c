#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void eliminarElemento(int* e);
void insertar(tLista l);
void imprimir(tLista l);
void recorrerParaAtras(tLista l);

int main()
{
    int res = 0;
    int cont=0;
    tLista l;


    printf("----BIENVENIDO AL SIMULADOR DE LISTA----");
    do{
        do{
            printf("\nSeleccione una opción:\n\t1: Crear lista de enteros.\n\t2: Insertar entero.\n\t3: Imprimir lista por pantalla.\n\t4: Eliminar Lista.\n\t5: Salir.\n\n");
            scanf("%d", &res);
        }while(res<1 || res>5);

        switch(res){
            case 1: {
                if(cont==0){
                    crear_lista(&l);
                    printf("Lista creada con éxito!\n");
                    cont = 1;
                }
                else{
                    printf("Ya hay una lista creada\n");
                }
                break;
            }
            case 2: {
                if(cont==1){
                    printf("Ingrese el entero a insertar: \n");
                    int *e=(int *)malloc(sizeof(int));
                    scanf("%i", e);
                    l_insertar(l, l_fin(l), e);
                    /*while(cont!=-1){
                        int *e=(int *)malloc(sizeof(int));
                        *e=cont;
                        if(cont!=-1){
                            l_insertar(l, l_fin(l), e);
                            scanf("%i ", &cont);
                        }
                //insertar(l);
                }*/
                //system("clear");
                //cont=1;
                }
                else
                    printf("Debe crear la lista antes de insertar un elemento\n");
                break;
            }
            case 3: {
                if(cont==1){
                    imprimir(l);
                    //printf("\n hacia atras \n");
                    //recorrerParaAtras(l);
                }
                else
                    printf("Debe crear la lista antes de imprimirla\n");
                break;
            }
            case 4: {
            if(cont==1){
                l_destruir(&l, (void *)eliminarElemento);
                printf("Lista destruida con éxito.\n");
                cont = 0;
            }
            else{
                printf("Debe crear la lista para poder eliminarla\n");
                }
            break;
            }
        }
    }while(res != 5);

    return 0;
}

void imprimir(tLista l){
    tLista aux;
        aux=l;
        printf("[ ");
        while(aux!=l_fin(l)){
            int *ele=(int*)l_recuperar(l,aux);
            printf("%d , ",*ele);
            aux=l_siguiente(l,aux);
        }
        printf("] ");
        if(l->siguiente==NULL)
            printf("La lista esta vacia \n");
}
void insertar(tLista l){
    int *e;
    for(int i=1;i<=20;i++){
        e=(int *)malloc(sizeof(int));
        *e=i;//Elemento a insertar
        l_insertar(l,l_fin(l),e);//inserto el elemento en la lista
    }

}

void eliminarElemento(int* e){
   free((int *)e);
}

void recorrerParaAtras(tLista l){
    tLista aux;
    aux=l_ultima(l);
    printf("[ ");
        while(aux!=l){
            int *ele=(int*)l_recuperar(l,aux);
            printf("%i , ",*ele);
            aux=l_anterior(l,aux);
        }
        int *ele=(int*)l_recuperar(l,aux);
        printf("%i",*ele);
        printf("] ");
        if(l->siguiente==NULL)
            printf("La lista esta vacia \n");
}



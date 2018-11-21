/*
 * HILOS
 * 
 * CAST --> (char*) variable
 * 
 */

#include <pthread.h> // AÑADIMOS ESTA LIBRERÍA
#include <stdio.h>
#include <stdlib.h>

void* imprimi(void* parameter)
{
   
    while(1){
         printf("%s", (char*) parameter);
    }

    return NULL;
}


 int main()
 {

    char* array[] = {"Hola", "Pepe"};

    // CREAMOS LAS VARIABLES ID DEL HILO
    pthread_t hilo1;
    pthread_t hilo2;

    // CREAMOS EL HILOS
    pthread_create(&hilo1, NULL, &imprimi, (void*) array[0]);
    pthread_create(&hilo2, NULL, &imprimi, (void*) array[1]);
    
    // COMPRUEBA QUE HA DEVUELTO EL VALOR ESPERADO
    pthread_join(hilo1, NULL); 
    pthread_join(hilo1, NULL);

    return EXIT_SUCCESS;

 }
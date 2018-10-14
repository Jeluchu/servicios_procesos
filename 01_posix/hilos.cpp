#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// LIBRERÍAS PARA HILOS
#include <pthread.h>

/*
 *
 * POSIX (Portable Operating System Interface)
 * En nuestro programa deberemos incluir alguna librería 
 * además de que a la hora de compilar será necesario
 * linkar el programa con alguna de las librerías
 * 
 */


void *hola(void *arg) 
{
    char const *msg = "Hola";
    int i;

    for(i = 0; i < strlen(msg); i++) 
    {
        printf("%c", msg[i]);
        fflush(stdout);
        usleep(1000000);
    }
    return NULL;
}

void *mundo(void *arg ) 
{
    char const *msg = " mundo ";
    int i;

    for(i = 0; i < strlen(msg); i++) 
    {
        printf("%c", msg[i]);
        fflush(stdout);
        usleep(1000000);
    }
    return NULL;
}

int main(int  argc, char *argv[]) 
{
    // CREAMOS LOS HILOS
    pthread_t  h1;
    pthread_t  h2;

    // FUNCIÓNQUE NOS PERMITE CREAR UN NUEVO HILO DE EJECUCIÓN
    pthread_create(&h1, NULL , hola , NULL);
    pthread_create(&h2, NULL , mundo , NULL);

    printf ("Fin\n");
}
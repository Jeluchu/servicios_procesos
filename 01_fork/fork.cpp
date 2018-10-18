/*
 *
 * pid_t --> Tipo de dato (semejanza con int)
 *           Tipo de dato que representa a una ID de un proceso
 * 
 * fork --> Devuelve siempre una ID de proceso
 *          Divide el programa en 2 procesos (padre e hijo)
 *          Devuelve el ID del proceso hijo
 * 
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid_hijo; // pid_hijo = ID --> NULL 

    printf("El ID del proceso principal del programa es: %d\n", (int) getpid());
    
    pid_hijo = fork(); // pid_hijo --> Toma valores
    
    // EMPIEZA EL PROCESO HIJO

    /* 
     * SE EJECUTAN 2 PROCESOS EN PARALELO (AL MISMO TIEMPO)
     * 
     * En el PADRE, existe pid_hijo, que contiene el ID del HIJO cogido en el fork
     * diferente a NULL, ejecuta el 'if'
     * 
     * En el hijo, no existe pid_hijo, con lo cuál el valor del mismo es NULL, y 
     * ejecuta el 'else', como está puesto 'getpid', podemos ver como está ejecutándolo
     * en otro proceso diferente al padre
     * 
    */

    if(pid_hijo !=0)
    {
        printf("Este es el proceso PADRE, con ID: %d\n", (int) getpid());
        printf("Este es el proceso HIJO, con ID: %d\n", (int) pid_hijo);
    } else
    {
        printf("Este es el proceso HIJO, con ID: %d\n", (int) getpid());
        printf("Este sería el pid_hijo del proceso HIJO, no existente: %d\n", (int) pid_hijo);
    }

}
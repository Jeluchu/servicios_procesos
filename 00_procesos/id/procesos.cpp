/* 
 *
 * CADA PROGRAMA ES 1 PROCESO (PERO DENTRO DEL PROGRAMA PUEDE HABER VARIOS PROCESOS)
 *
 * UN PROGRAMA PUEDE TENER VARIOS HILOS, SINO, SERÍA UN ÚNICO PROCESO
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    // IMPRIMIR EL ID DEL PROCESO DEL PROGRAMA (CAMBIA CADA VEZ)
    printf("El ID del proceso es: %d\n", (int) getpid());

    // IMPRIME DONDE SE EJECUTA, ES DECIR LA TERMINAL DONDE SE ESTÁ EJECUTANDO
    printf("El ID padre es: %d\n", (int) getppid());

    /*
     *
     * getpid --> ID DEL PROCESO DEL PROGRAMA
     * getppid --> ID DE LA TERMINAL
     * 
     */

}
#include <stdio.h>
#include <stdlib.h>

// LIBRERÍAS PARA USAR "pid_t"
#include <sys/types.h>
#include <unistd.h>

/*
 *
 * Para conocer el PID y el PPID de un proceso se pueden emplear
 * las funciones getpid y getppid. Estas funciones están efinidas 
 * en la librería unistd.h
 *
 * Se declaran de la siguiente forma: 
 * pid_t  getpid  (void);
 * pid_t  getppid  (void);
 * 
 * 
 */
    
int  main(int  argc , char *argv []) {
    
    pid_t pid; // CREAMOS EL PROCESO

    pid = fork ();

    if(pid == -1) {
        printf ("Fallo en fork\n");
        return  -1;
    }else
    {

        if (! pid) {

            // ESTE PROCESO TENDRÁ UN VALOR POR DEBAJO AL PROCESO PADRE
            printf ("Proceso  hijo: PID  %d\n", getpid ());
        
        } else {

            // ESTE PROCESO TENDRÁ UN VALOR POR ENCIMA AL PROCESO HIJO
            printf ("Proceso  padre: PID  %d\n", getpid ()); 

        }

    }

    return  EXIT_SUCCESS;
}
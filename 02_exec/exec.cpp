#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(char* programa, char** arg_list)
{
    pid_t pid_hijo;

    pid_hijo = fork();

    if (pid_hijo !=0)
    {
        return pid_hijo;
    }
    else 
    {
        /*
         * Ejecuta el programa citado con la lista de argumentos  
         * hasta que se encuentre con un NULL
         */
        execvp(programa, arg_list);
        // SI DA ERROR, TE MUESTRA POR LA TUBERÍA DE ERRORES LO SIGUIENTE
        fprintf(stderr, "Ha ocurrido un error en execvp\n");
        abort();
    }
}

int main()
{
    char* arg_list[] = 
    {
        "firefox",
        "-v",     
         NULL      
    };

    spawn("firefox", arg_list); 

    printf("HECHO CON EL PROGRAMA PRINCIPAL\n");

    return EXIT_SUCCESS;
}
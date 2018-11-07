#include <stdlib.h>

int main ()
{
    int return_value;
    return_value = system("echo Estoy ejecutando la función system");

    return return_value;
}
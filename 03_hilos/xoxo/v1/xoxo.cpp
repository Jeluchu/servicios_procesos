#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 1000

void *imprime(void *x)
{
  for (int i = 0; i < MAX; i++)
      fputc(*((char *) x), stderr); // NO TIENE BUFFER, ES DIRECTO DE AHÍ EL STDERR

  return NULL;
}


int main (int argc, char *argv[])
{

  char x = 'x';
  char o = 'o';

  pthread_t mi_hilo[2];
  
  pthread_create(&mi_hilo[0], NULL, &imprime, (void *) &x);
  pthread_create(&mi_hilo[1], NULL, &imprime, (void *) &o);

  pthread_join(mi_hilo[0], NULL);
  pthread_join(mi_hilo[1], NULL);

  fputc('\n', stderr);

  return EXIT_SUCCESS;

}

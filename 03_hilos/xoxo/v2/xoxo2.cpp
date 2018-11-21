#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 1000
#define N 2

void *imprime(void *x)
{
  for (int i = 0; i < MAX; i++)
      fputc(*((char *) x), stderr); // NO TIENE BUFFER, ES DIRECTO DE AHÍ EL STDERR

  return NULL;
}


intmain (int argc, char *argv[])
{

  char param[N] = {'x' , 'o'};

  pthread_t mi_hilo[N];

  for(int i = 0; i < N; i++)
      pthread_create(&mi_hilo[i], NULL, &imprime, (void *) &param[i]);

  for(int i = 0; i < N; i++)
        pthread_join(mi_hilo[i], NULL);

  fputc('\n', stderr);

  return EXIT_SUCCESS;

}

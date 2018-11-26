#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio_ext.h>

// DEFINIMOS CONSTANTES Y PUERTO
#define GRANDE 255
#define PUERTO 1998
#define N 100

int main(int argc, char *argv[])
{
  int fd;
  char palabra[N];
  char buffer[GRANDE];

  // RELLENAMOS EL BUFFER DE '\0'
  memset(buffer, '\0', sizeof(buffer));

  // CREAMOS LA ESTUCTURA DEL SOCKET
  struct sockaddr_in sas;

  // CREAMOS EL SOCKET
  fd = socket(AF_INET, SOCK_STREAM, 0);

  sas.sin_family = AF_INET; // IPv4
  sas.sin_addr.s_addr = inet_addr("127.0.0.1"); // LOCALHOST
  sas.sin_port = htons(PUERTO);

  socklen_t len = sizeof(sas);

  int resultado;

  // REALIZAMOS LA CONEXIÓN DEL SOCKET
  resultado = connect(fd, (struct sockaddr *) &sas, len);

  // TRATAMOS EL ERROR
  if(resultado == -1)
  {
    perror("Ha ocurrido un error en Matrix");
    exit(1);
  }

  bool valor = false;

  do
  {
    int tamano = 0;
    __fpurge(stdin);

    printf("Introduce una palabra: ");
    fgets(palabra, N, stdin);

    // CALCULAMOS LA LONGITUD
    tamano = strlen(palabra);

    // COMPARAMOS LAS CADENAS
    if(strcmp(palabra, "salir\n")==0)
    {
      valor = true;
    }
    else
    {
      // UNE LA CADENA Y SOBREESCRIBE EL CARARCTER '\0'
      strncat(buffer, palabra, tamano);
    }
  }while(valor == false);

  // ENVIAMOS LA LISTA RECIBIDA AL SERVER
  send(fd, buffer, strlen(buffer), 0);

  // RECIBIMOS LA LISTA Y SE IMPRIME
  recv(fd, buffer, strlen(buffer), 0);
  printf("%s", buffer);

  // CERRAMOS
  close(fd);
}

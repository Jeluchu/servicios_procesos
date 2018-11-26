#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>
#include <sys/wait.h>

// DECLARAMOS LAS CONSTANTES
#define GRANDE 255

// CONSTANTE DE LECTURA/ESCRITURA
#define R 0
#define W 1

#define M 2

// CREAMOS UNA SEÑAL QUE NO VARÍA
sig_atomic_t hijo_actual;

void handler_senal(int senal)
{
   int actual;

   // ESPERA AL PROCESO Y DEVUELVE SU ESTADO
   wait(&actual);

   // IGUALAMOS LA SEÑAL ATÓMICA CON EL ESTADO DEL PROCESO
   hijo_actual = actual;
}

void handler_cliente(int fd_client)
{
  int fd[M][M];

  // CREAMOS LA TUBERÍA
  pipe(fd[0]);
  pipe(fd[1]);

  // CREAMOS EL PROCESO HIJO
  pid_t hijo_pid;
  hijo_pid = fork();

  if(hijo_pid)
  {
    // PROCESO PADRE
    // CERRAMOS LAS TUBERÍAS TANTO EN ESCRITURA COMO EN LECTURA
    close(fd[0][0]);
    close(fd[1][1]);

    // IGUALAMOS EL TAMAÑO EN LISTA_PALABRAS
    char *lista_palabras = (char *)malloc(255);

    // RECIBIR MENSAJES DESDE EL CLIENTE
    int byte = recv(fd_client, lista_palabras,255,0);
    lista_palabras[byte] = '\0';

    // ESCRIBIMOS LA LISTA DE PALABRAS
    write(fd[R][W], lista_palabras, sizeof(char)*byte);
    close(fd[0][1]);

    // LEEMOS LA LISTA DE PALABRAS
    read(fd[W][R], lista_palabras, sizeof(char)*byte);

    // ENVIAMOS LA LISTA AL CLIENTE
    send(fd_client, lista_palabras, byte, 0);

    // LIBERAMOS EL ESPACIO DE LA MEMORIA
    free(lista_palabras);

    close(fd[1][0]);
  }
  else
  {
    // PROCESO HIJO
    // CERRANIS EL CLIENTE
    close(fd_client);
    close(fd[0][1]);
    close(fd[1][0]);

    dup2(fd[R][R], STDIN_FILENO);
    dup2(fd[W][W], STDOUT_FILENO);

    execlp("sort", "sort", NULL);
    fprintf(stderr, "Ha ocurrido un error\n");
    close(fd[R][R]);
    close(fd[W][W]);

    abort();
  }
}


int main(int argc, char *argv[])
{
  int puerto = 1998;
  int opcion;
  int cambiador = 0;
  int actuador = 1;

  // CREAMOS LA ESTRUCTURA DEL SOCKET
  struct sockaddr_in sas;
  int fd_socket_server;

  // CREAMOS EL SOCKET
  fd_socket_server = socket(AF_INET, SOCK_STREAM, 0);

  const char *const atajos = "lp: ";
  const struct option caminatas[] =
  {
    {"cambiador", 0, NULL, 'l'},
    {"puerto", 1, NULL, 'p'},
    {NULL, 0, NULL, 0}
  };

  do
  {
   opcion = getopt_long(argc, argv, atajos, caminatas, NULL);

   switch(opcion)
   {
    case 'l':
       cambiador = 1;
       break;
    case 'p': // PUERTO
       sscanf(optarg, "%i", &puerto);
       break;
    case -1:
       break;
   }
  } while(opcion != -1);

  sas.sin_family = AF_INET; // IPv4
  sas.sin_port = htons(puerto);

  if(cambiador == 0)
     sas.sin_addr.s_addr = htonl(INADDR_ANY);
   else
     sas.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

   // SE ACTIVA EL SOCKET
   setsockopt(fd_socket_server, SOL_SOCKET, SO_REUSEADDR, &actuador, sizeof(actuador));

   // REALIZAMOS EL BIND
   if(bind(fd_socket_server, (struct sockaddr *)&sas, sizeof(sas))!=0)
   {
     perror("Se ha producido un error en el bind");
     return 1;
   }

  if(listen(fd_socket_server, 5)!=0)
  {
    perror("No se ha podido escuchar conexiones");
    return  1;
  }

  do
  {
    socklen_t tamano = sizeof(sas);

    // SE ACEPTAN LAS CONEXIONES ENTRANTES
    int fd_client = accept(fd_socket_server, (struct sockaddr *)&sas,&tamano);

    pid_t pid_hijo;
    pid_hijo = fork();

    if(pid_hijo)
    {
      close(fd_client);
    }
    else
    {
      close(STDIN_FILENO);
      close(STDOUT_FILENO);
      close(fd_socket_server);

      handler_cliente(fd_client);
      close(fd_client);
      return 0;
    }
  }while(1);
  close(fd_socket_server);
  return EXIT_SUCCESS;
 }

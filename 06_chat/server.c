#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#define PORT 4444
#define BUF_SIZE 2000
#define CLADDR_LEN 100

void * recibirMensaje(void * socket)
{
   int sockfd, ret;
   char buffer[BUF_SIZE];
   sockfd = (int) socket;
   memset(buffer, 0, BUF_SIZE);
   for (;;)
   {
      ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
      if (ret < 0)
      {
       printf("Internal Server Error: No se reciben los datos\n");
      }
      else
      {
       printf("Cliente: ");
       fputs(buffer, stdout);
      }
   }
}

void main()
{
   struct sockaddr_in addr, cl_addr;
   int sockfd, len, ret, newsockfd;
   char buffer[BUF_SIZE];
   pid_t childpid;
   char clientAddr[CLADDR_LEN];
   pthread_t rThread;

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
    printf("¡Error al crear el socket!\n");
    exit(1);
   }
   printf("Socket creado correctamente...\n");

   memset(&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = INADDR_ANY;
   addr.sin_port = PORT;

   ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
   if (ret < 0) {
    printf("Error uniendo conexiones\n");
    exit(1);
   }
   printf("Unión realizada...\n");

   printf("Esperano una conexión...\n");
   listen(sockfd, 5);


   len = sizeof(cl_addr);
   newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);
   if (newsockfd < 0) {
    printf("Error aceptando la conexión\n");
    exit(1);
   }

   inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
   printf("Conexión aceptada de %s...\n", clientAddr);

   memset(buffer, 0, BUF_SIZE);
   printf("Escribe tu mensaje y pulsa ¡Enter!\n");

   //creating a new thread for receiving messages from the client
   ret = pthread_create(&rThread, NULL, recibirMensaje, (void *) newsockfd);
   if (ret) {
    printf("ERROR: El código devuelto del pthread_create() es %d\n", ret);
    exit(1);
   }

   while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
    ret = sendto(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, len);
    if (ret < 0) {
     printf("¡Error enviando datos!\n");
     exit(1);
    }
   }

   close(newsockfd);
   close(sockfd);

   pthread_exit(NULL);
   return;
}

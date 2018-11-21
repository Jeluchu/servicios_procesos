#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  int socket_fd;

  socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);

  if (socket_fd == -1)
  {
    perror("El socket ha muerto");
    exit(1);
  }
  else
  {
   perror("¡El socket vive!");
  }

  close(socket_fd);
  return 0;
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <linux/if_packet.h>

// THE L2 PROTOCOLS
#include <net/ethernet.h>

/*
 * BROADCAST
 *  Cualquiera puedes escuchar nuestro mensaje
 *
 * MULTICAST
 *  Solamente ciertas personas o ciertos
 *  equipos podrásn escuchar nuestro mensaje
 *
 * UNICAST
 *  Se refiere a que solamente puede ser escuchado
 *  entre el transmisor y el receptor
 *
*/

int main()
{
  int packet_socket;

  // CREACIÓN DEL SOCKET
  packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

  if(packet_socket == -1)
  {
    // NO SE PUDO ABRIR EL SOCKET
    perror("El socket está muerto");
    exit(1);
  }
  else
  {
    // EL SOCKET SE HA ABIERTO
    perror("El socket está vivito y coleando");
  }
  close(packet_socket);

}

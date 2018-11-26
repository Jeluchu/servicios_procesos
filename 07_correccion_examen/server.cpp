#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define GRANDE 255
#define N 5

void sort(char[], int);

int main(int argc, char* argv[])
{
	int socket_desc, client_socket, c, read_size;
	struct sockaddr_in server, client;
	char buffer[GRANDE], i;

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1) {
		printf("No se ha podido crear el socket");
	}
	puts("Socket creado correctamente");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8880);

	if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {

		perror("¡Error! El bind ha fallado");
		return 1;
	}
	puts("¡Bind hecho!");

	listen(socket_desc, 3);

	puts("Esperando a que lleguen conexiones...");
	c = sizeof(struct sockaddr_in);

	client_socket = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c);

	if (client_socket < 0) {
		perror("Fallo al aceptar");
		return 1;
	}

	puts("¡Conexión aceptada!");

   /*
       recvfrom y recvmsg se emplean para recibir mensajes  desde
       un socket, y pueden utilizarse para recibir datos
   */
	while ((read_size = recv(client_socket, &buffer, N * sizeof(char), 0)) > 0) {

		sort(buffer, N);

		write(client_socket, &buffer, N * sizeof(char));
	}

	if (read_size == 0) {
		puts("Cliente desconectado");
	}
	else if (read_size == -1) {
		perror("Fallo al realizar la función: recv");
	}

	return 0;
}

void sort(char lista[], int n)
{
	int c, d, t;

	for (c = 0; c < (n - 1); c++) {
		for (d = 0; d < n - c - 1; d++) {
			if (lista[d] > lista[d + 1]) {

				t = lista[d];
				lista[d] = lista[d + 1];
				lista[d + 1] = t;
			}
		}
	}
}

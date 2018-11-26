#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define GRANDE 255
#define N 5
int main(int argc, char* argv[])
{
	int sock, i, temp;
	struct sockaddr_in server;
	char server_reply[GRANDE];
	char buffer[GRANDE];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("No se puede crear el socket");
	}
	puts("Socket creado correctamente");

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8880);

	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
		perror("¡Error! La conexión ha fallado");
		return 1;
	}

	puts("¡Conectado!\n");

	if (send(sock, &buffer, N * sizeof(char), 0) < 0) {
		puts("¡Envío Fallido!");
		return 1;
	}

	if (recv(sock, &server_reply, N * sizeof(char), 0) < 0) {
		puts("recv failed");
		return 0;
	}

  for (i = 0; i < N; i++) {
		printf("Introduce una palabra: ");
    scanf("%s", buffer);
	}

	puts("Respuesta del servidor :\n");
	for (i = 0; i < N; i++) {
		printf("%d\n", server_reply[i]);
	}

	close(sock);
	return 0;
}

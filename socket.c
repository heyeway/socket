#include "socket.h"

#define		SUCCESS		(0)
#define		FAILURE		(-1)

#define		RHOST		("127.0.0.1")
#define		RPORT		(1234)

static struct sockaddr_in server_address;
static int sockfd;

static int init_server(char *s_addr, uint16_t s_port);

int main(int argc, char **argv)
{
	init_server(argv[1], 0);

	accept(sockfd, NULL, NULL);

	shutdown(sockfd, SHUT_RDWR);

	return 0;
}

int init_server(char *s_addr, uint16_t s_port)
{
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(RPORT);

	inet_pton(AF_INET, s_addr, &(server_address.sin_addr.s_addr));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd > 0) {
		if(bind(sockfd, (struct sockaddr *)(&server_address), sizeof(struct sockaddr)) == SUCCESS) {
			if(listen(sockfd, 10) == SUCCESS) {
				return SUCCESS;
			}
		}
		shutdown(sockfd, SHUT_RDWR);
	}
	return FAILURE;
}

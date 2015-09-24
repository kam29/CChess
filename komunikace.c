#ifndef komunikace
#define komunikace

//#include "global.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define DATA_LENGTH		100
#define DEFAULT_SOCKET_NUMBER	5000

#define ERROR_SOCKET		1
#define ERROR_BIND		2
#define ERROR_IP		3
#define ERROR_CONNECT		4
#define ERROR_ACCEPTING		5
#define ERROR_SEND		6
#define ERROR_RECV		7
#define ERROR_CLOSE		8

#define SECURE_BYTE		'8'

#define SIGNALS signal(SIGTERM, signal_handler); signal(SIGINT, signal_handler);

int stop = 0;

typedef struct client {

   int client_socket;
   struct sockaddr_in server_addr;
   struct hostent sserver;

   char in_buffer[DATA_LENGTH];
   char out_buffer[DATA_LENGTH];

} client;

typedef struct server {

   int server_socket;
   int client_socket;
   struct sockaddr_in server_addr;  
   struct sockaddr_in client_addr;
   socklen_t clien;

   char in_buffer[DATA_LENGTH];
   char out_buffer[DATA_LENGTH];

} server;

void signal_handler(int signal)
{

   printf("Signal %d received\n", signal);

   if (signal == SIGTERM || signal == SIGINT) {
      stop = 1;
   }
   
   return;
}



int create_server(server * serv, unsigned int port) {

   serv->server_socket = socket(AF_INET, SOCK_STREAM, 0);
   if(serv->server_socket < 0) {
      perror("Socket create");
      return ERROR_SOCKET;
   }

   bzero((char *) &serv->server_addr, sizeof(serv->server_addr));

   serv->server_addr.sin_family = AF_INET;
   serv->server_addr.sin_addr.s_addr = INADDR_ANY;
   serv->server_addr.sin_port = htons(port);

   if(bind(serv->server_socket, (struct sockaddr *) &serv->server_addr, sizeof(serv->server_addr)) < 0) {
      perror("Binding socket");
      return ERROR_BIND;
   }

   unsigned short int socket_number = getsocketname(serv->server_socket, (struct sockaddr *) &serv->server_addr, sizeof(serv->server_addr));   
   printf("I'm listening on port: %hu", socket_number);

   return EXIT_SUCCESS;
}



int create_client(client * cli, unsigned int port, char * ip) {

   cli->client_socket = socket(AF_INET, SOCK_STREAM, 0);
   if(cli->client_socket < 0) {
      perror("Socket create");
      return ERROR_SOCKET;
   }

   cli->sserver = gethostbyname(ip);
   if(cli->sserver == NULL) {
      perror("Incorrect IP address");
      return ERROR_IP;
   }
   
   bzero((char *) &cli->server_addr, sizeof(cli->server_addr));

   cli->server_addr.sin_family = AF_INET;
   bcopy((char *)cli->sserver->h_addr_list[0],
         (char *)&cli->sserver_addr.sin_addr.s_addr,
         cli->sserver->h_length);
   cli->server_addr.sin_port = htons(port);

   printf("Client ready to connecting\n");

   return EXIT_SUCCESS;
}



int server_accept(server * serv) {

   serv->client_socket = accept(serv->server_socket, (struct sockaddr *) &serv->server_addr, sizeof(serv->server_addr));

   if(serv->client_socket < 0) {
      perror("Accepting client");
      return ERROR_ACCEPTING;
   }

   return EXIT_SUCCESS;
}



int client_connect(client * cli) {

   if (connect(cli->client_socket,(struct sockaddr *) &cli->server_addr,sizeof(cli->server_addr)) < 0) {
      error("Connecting to server");
      return ERROR_CONNECT;
   }

   return EXIT_SUCCESS;
}



int send_message(int * sock, char * buffer) {

   int count = write(*sock, buffer, strlen(buffer));

   bzero(buffer, DATA_LENGTH);

   if(count < 0) {
      perror("Sending message");
      return ERROR_SEND;
   }

   return EXIT_SUCCESS;
}



int recv_message(int *sock, char * buffer) {

   bzero(buffer, DATA_LENGTH);

   int count = read(*sock, buffer, DATA_LENGTH);

   if(count < 0) {
      perror("Receiving message");
      return ERROR_RECV;
   }

   return EXIT_SUCCESS;
}



int cancel_connection(int *sock) {

   if(shutdown(*sock, SHUT_RDWR) < 0) {
      perror("Closing connection");
      return ERROR_CLOSE;
   }

   return EXIT_SUCCESS;
}



#endif

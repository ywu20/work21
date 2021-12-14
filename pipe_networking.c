#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int from_client = 0;
  mkfifo("well_known", 0644);
  int well_known = open("well_known",O_RDONLY);
  printf("Open well known pipe\n");
  from_client = well_known;
  char secret_name[10];
  read(well_known, secret_name,10);
  remove("well_known");
  int secret = open(secret_name,O_WRONLY,10);
  to_client = &secret;
  printf("Open well secret pipe\n");
  printf("secret_name:%s\n",secret_name);
  int w = 0;
  int a = write(*to_client, &w, sizeof (int));
  //printf("server wrote %d bytes to client\n",a);
  printf("server wrote %d to client\n",w);

  int response;
  read(well_known, &response,sizeof(int));
  printf("server got %d from client\n", response);

  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server = 0;
  char secret_name [10] = "secret";//strcat("secret", getpid());//itoa(getpid());
  mkfifo(secret_name, 0644);
  int well_known = open("well_known", O_WRONLY);
  to_server = &well_known;
  printf("Open well known pipe\n");
  write(*to_server, secret_name, sizeof(secret_name));
  int secret = open(secret_name, O_RDONLY);
  printf("Open well secret pipe\n");
  from_server = secret;

  int response;
  int a = read(from_server, &response, sizeof(int));
  //printf("client received %d bytes from server\n", a);
  printf("client received %d from server\n", response);
  remove(secret_name);
  response ++;
  write(*to_server, &response, sizeof(int));
  printf("client wrote %d to server\n", response);

  return from_server;
}

#include "pipe_networking.h"


int main() {
  //int * to_client_address = malloc(sizeof(int));
  int to_client;
  int from_client;
  char inputs[50];
while(1){
  from_client = server_handshake(&to_client);

  while (read(from_client, inputs, 50)){

  printf("Server got: %s \n", inputs);
  char response[50];
  int i;
  for(i=0;i<50;i++){
    response[i] = toupper(inputs[i]);
  }
  write(to_client, response, 50);
 }
}
return 0;
}

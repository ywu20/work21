#include "pipe_networking.h"


int main() {
  int to_server;

  int from_server;

  from_server = client_handshake(&to_server);
    char inputs[50];


   while(1){
   printf("Enter the word: \n");
   fgets(inputs,50,stdin);
   inputs[strlen(inputs)-1] = '\0';
   printf("You inputed: %s\n",inputs);
   int a = write(to_server, inputs, 50);
   char result [50];
   read(from_server,result,50);
   printf("Response from server: %s\n", result);
 }

}

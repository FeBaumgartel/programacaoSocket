#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int socket_desc;
    struct sockaddr_in server;
    char message[2000], server_reply[2000];

    /* AF_INET - IPv4, SOCK_STREAM - tcp, 0 - IP */
     socket_desc = socket(AF_INET, SOCK_STREAM, 0); 
    
    if (socket_desc == -1){
        printf("Não foi possível criou socket\n");
        return 1;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    
    if(connect(socket_desc, (struct sockaddr *) &server, sizeof(server))<0){
        printf("Erro ao conectar\n");
        return 1;
    }

    printf("Conectado\n");
    

    do{
         bzero(message, sizeof(message));
        
        /* envia dados */
        printf("Digite uma mensagem: ");

        int ch, n = 0;
        /* lê a entrada de dados do usuário via getchar */
        while ((ch = getchar()) != '\n' && n < 2000) {
            message[n] = ch;
            ++n;
        }

        if(send(socket_desc, message, strlen(message), 0)<0){
            printf("Não criou socket\n");
            return 1;
        }

        printf("Dados Enviados\n");

        if(recv(socket_desc, server_reply, 2000, 0)<0){
            printf("Falha no recv\n");
            return 1;
        }

        printf("Resposta recebida\n");
        printf("%s",server_reply);
        
        bzero(server_reply, sizeof(server_reply));
    }while(strcmp(message,"exit")!=0);
    
    close(socket_desc);

    return 0;
}
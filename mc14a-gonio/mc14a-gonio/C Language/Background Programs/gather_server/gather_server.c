#include <gplib.h>   // Global Gp Shared memory pointer

#include "../../Include/pp_proj.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int send_all(int sock, const char *data, unsigned int len) {
    unsigned int sent = 0;
    int n;
    
    while(sent < len) {
        n = send(sock, data+sent, len-sent, 0);
        if(n == -1)
            break;
        sent += n;
    }
    
    return n == -1 ? -1 : 0;
}

int main(void) 
{
    int sockfd, newfd;
    struct sockaddr_in serv_addr;
    GATHER *gather;
    int line_length;
    unsigned int samples;  

	InitLibrary();
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(1717);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    listen(sockfd, 1);
    
    while(1) {
        newfd = accept(sockfd, NULL, NULL);
        
        gather = &pshm->Gather;
	    samples = gather->Samples;
	    line_length = gather->LineLength << 2;
	
        send_all(newfd, (char*)&gather->Items, sizeof(unsigned char));
        send_all(newfd, (char*)gather->Type, gather->Items*sizeof(unsigned short));
        send_all(newfd, (char*)&line_length, sizeof(unsigned int));
        send_all(newfd, (char*)&samples, sizeof(unsigned int));
        send_all(newfd, (char*)gather->Buffer, (line_length*samples));
        close(newfd);
    }
    close(sockfd);
	
	CloseLibrary();	
	return 0;
}
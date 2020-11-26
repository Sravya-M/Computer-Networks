// MT2019114
//Client side implementation
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() { 
	int sock;
	struct sockaddr_in saddr; 
  
    // Creating socket file descriptor 
	if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
	        printf("socket creation failed"); 
	        exit(0); 
	}

    // Filling server information 
	saddr.sin_family = AF_INET; 
   	saddr.sin_port = htons(8500); 
   	saddr.sin_addr.s_addr = INADDR_ANY; 
      
    int n, len,x=5;
	int a[x];
	// reading integers from console
	for(int i=0;i<x;i++)
		scanf("%d",&a[i]);

// sending data to server for sorting
	sendto(sock,&a,x*sizeof(int),0,(const struct sockaddr *)&saddr,sizeof(saddr));

// receiving increasing order from server
	n = recvfrom(sock,&a,x*sizeof(int),MSG_WAITALL,(struct sockaddr*)&saddr,&len);
	
	for(int i=0;i<x;i++)
		printf("%d ",a[i]);

	printf("\n");
	
// receiving decreasing order from server
	for(int i=0;i<x;i++)
	{
		recvfrom(sock,&a[i],sizeof(int),MSG_WAITALL,(struct sockaddr*)&saddr,&len);
		printf("%d ",a[i]);
	}

	close(sock); 
	return 0; 
}
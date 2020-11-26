/* MT2019114
TCP client program
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
	int sock = socket(AF_INET,SOCK_STREAM,0);

// initialize the socket structure
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_port=htons(8500);
	address.sin_addr.s_addr=INADDR_ANY;

	if(connect(sock,(struct sockaddr *)&address,sizeof(address))<0){
		printf("connection failure\n");
		return -1;
	}

	int n=5;
	char c[n];
	for(int i=0;i<n;i++)
		scanf("%c",&c[i]);

	send(sock,&c,n*sizeof(char),0);
	recv(sock,&c,n*sizeof(char),0);

	for(int i=0;i<n;i++)
		printf("%c ",c[i]);

	printf("\n");
	for(int i=0;i<n;i++)
	{
		recv(sock,&c[i],sizeof(char),0);
		printf("%c ",c[i]);
	}
	
	printf("\n");
	close(sock);
	return 0;
}

// MT2019114
// server side implementation
// Server is receiving integers from client and sorting them to ascending and descending order
// resending the sorted numbers to client
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

// bubble sort function
void sort(int a[],int n)
{
	int i,j,swap,temp;
   	for (i = n-1; i >=0; i--)      
    	{
        	swap=0;
        	for(j=0;j<i;j++)
        	{
        	    if(a[j]>a[j+1])
        	    {
        	        temp=a[j];
        	        a[j]=a[j+1];
        	        a[j+1]=temp;
        	        swap=1;
        	    }
        	}
        if(swap==0)
            break;
    	}
	return ;
}

int main() { 

   	int sock=socket(AF_INET, SOCK_DGRAM, 0);
   	struct sockaddr_in saddr={0}, caddr={0}; 
      
   	if (sock < 0 ) {
		printf("socket creation failed");
        	exit(0);
    	}
      
    // Filling server information
    	saddr.sin_family    = AF_INET; // IPv4 
    	saddr.sin_addr.s_addr = INADDR_ANY; 
    	saddr.sin_port = htons(8500); 
      
    // Bind the socket with the server address
	if ( bind(sock, (const struct sockaddr *)&saddr,sizeof(saddr)) < 0 ) 
	{
		printf("bind failed\n");
		exit(0);
	}
      
    int len, n,x=5;
	int a[x];
// receiving integers from clients and sorting them and sending back
	n=recvfrom(sock,&a,x*sizeof(int),MSG_WAITALL,(struct sockaddr*)&caddr,&len); 

	sort(a,x);

	sendto(sock,&a,x*sizeof(int),MSG_CONFIRM,(struct sockaddr*)&caddr,len);

	for(int i=x-1;i>=0;i--)
		sendto(sock,&a[i],sizeof(int),MSG_CONFIRM,(struct sockaddr*)&caddr,len);
      
    	return 0; 
}

/* MT2019114
TCP server program
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

// bubble sort
void sort(char a[],int n)
{
	int i,j;
	char swap,temp;
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

int main()
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_port=htons(8500);
	address.sin_addr.s_addr=INADDR_ANY;

	if(bind(sock,(struct sockaddr *)&address,sizeof(address))<0){
		printf("Did not bind to a ip address and port\n");
		return -1;
	}

	listen(sock,4);

	int c_socket=accept(sock,NULL,NULL);

	int n=5;
	char c[n];

	recv(c_socket,&c,n*sizeof(char),0);
	sort(c,n);

	send(c_socket,&c,n*sizeof(char),0);
	
	int i;
	for(i=n-1;i>=0;i--)
		send(c_socket,&c[i],sizeof(char),0);

	close(sock);
	return 0;
}

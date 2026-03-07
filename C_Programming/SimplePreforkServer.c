#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define WORKERS 4
#define PORT 8080

int main()
{
    int listenfd, connfd;
    struct sockaddr_in addr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(listenfd, 10);

    /* Prefork workers */
    for(int i=0;i<WORKERS;i++)
    {
        if(fork()==0)
        {
            while(1)
            {
                connfd = accept(listenfd,NULL,NULL);
                printf("Worker %d handled connection\n", getpid());
                close(connfd);
            }
        }
    }

    while(1) pause();   // master just waits
}

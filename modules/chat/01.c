#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdarg.h>

#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE (1 << 10)
#define SA struct sockaddr

void err_quit( const char * format, ... )
{
    char buf[1024];
    va_list vlist;
    va_start(vlist, format);
    vsprintf(buf, format, vlist);
    va_end(vlist);
    fprintf(stderr, "%s\n", buf);
    exit( EXIT_FAILURE );
}

void err_sys( const char * format, ... )
{
    char buf[1024];
    va_list vlist;
    va_start(vlist, format);
    vsprintf(buf, format, vlist);
    va_end(vlist);
    perror(buf);
}

int main(int argc, char ** argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in serv_addr;
    
    if ( argc != 2 )
        err_quit("usage: a.out <IPaddress>");
    
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
        err_sys("socket_error");
    
    memset( &serv_addr, 0, sizeof(serv_addr) );
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(13); //сервер времени и даты
    
    if ( inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0 )
        err_quit("inet_pton error for %s", argv[1]);
    
    if ( connect( sockfd, (const SA *) &serv_addr, sizeof(serv_addr) ) < 0 )
        err_sys("connect error");
    
    while ( (n = read(sockfd, recvline, MAXLINE) ) > 0 )
    {
        recvline[n] = 0;
        if ( fputs(recvline, stdout) == EOF )
            err_sys("fputs error");
    }
    
    if ( n < 0 )
        err_sys("read error");
    
    exit( EXIT_SUCCESS );
}

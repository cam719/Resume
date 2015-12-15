#include "awget.h"
#include "packet.h"
#include "serialize.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("ERROR: NO URL GIVEN\n");
        return 1;
    }
    struct sockaddr_in server;
    char URL[100]; 
    strcpy(URL, argv[1]);
    printf("URL LENGTH = %d", strlen(URL));
    struct packet p;
    struct packet p2;
    char data[500];
    char buf[500];
    int size = 0;
    int sock = socket(AF_INET , SOCK_STREAM , 0);
    int ret = initialize_struct(&p, strlen(URL), URL);
    if(ret == -1)
    {
        return -1;
    }

    printPacket(&p);
   
    int pos = randomInt(p.size);
    char current[100];
    strcpy(current, p.ss_list[pos]);
    char *pch;
    char port[20], ip[20];
    deletePos(&p, pos);
    serialize(&p, data);
    deserialize(data,&p2);

   
    //Split line up into ip and port variables
    pch = strtok (current," ");
    strcpy(ip, pch);
    pch = strtok (NULL," ");
    strcpy(port, pch);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(atoi(port));

    printf("Connecting to server...\n");
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
    }

    send(sock , data , sizeof(data) , 0);


    //char *URL = "http://www.host.com/r/web/www/pic01.jpg";
    char *file_name;
    file_name = strrchr( URL, '/' ) + 1;
    printf("URL = %s\n", URL);
    printf("FILE NAME = %s\n", file_name);
    char command[120];
    sprintf(command, "%s %s", "rm", file_name);
    memset(buf, 0, sizeof(buf));
    recv(sock, buf, sizeof(buf), 0);
    memcpy(&size, buf, sizeof(int));
    printf("SIZE = %d", size);
    int read_size = 0;
    FILE *fd = fopen(file_name, "wb");
    int length = 0;
    while(length < size)
    {
        memset(buf, 0, sizeof(buf));
        read_size = recv(sock , buf, sizeof(buf), 0);
        length += read_size;
        fwrite(&buf,1,read_size,fd);
        printf("LENGTH: %d\n", length);
    
    	read_size = 0;

    }  

    send(sock, buf , sizeof(buf) , 0);
    close(sock);
    fclose(fd);
    free_struct(&p);
    free_struct(&p2);
}

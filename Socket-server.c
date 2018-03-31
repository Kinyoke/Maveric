#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
 
int listenfd = 0,connfd = 0, n = 0;
  
typedef enum{false , true}boolean;

boolean state = true;

struct sockaddr_in serv_addr;
 
char sendBuff[1025],recvBuff[1024];  

int numrv;

static int client_no = 1;  

int send_int(int fd, int num);

int receive_int(int fd, int *num);

int main(void)
{
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("socket retrieve success\n");
  
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));
      
  serv_addr.sin_family = AF_INET;    
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  serv_addr.sin_port = htons(5000);    
 
  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
  
  if(listen(listenfd, 10) == -1){
      printf("Failed to listen\n");
      return -1;
  }     
  
  while(1)
    {      
      connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
      while((n = read(connfd, recvBuff, sizeof(recvBuff)-1)) > 0)
       {
        recvBuff[n] = 0;
        if (strcmp(recvBuff,"help") == 0)
        {
          strcpy(sendBuff, "Welcom to maven server\n");
          write(connfd, sendBuff, strlen(sendBuff));
        }
        if (strcmp(recvBuff,"exit") == 0)
        {
          close(connfd);    
        }
       }
       printf("%d\n", client_no);
       ++client_no;
       sleep(1);
    } 
 
  return 0;
}


int send_int(int fd, int num)
{
    int32_t conv = htonl(num);
    char *data = (char*)&conv;
    int left = sizeof(conv);
    int rc;
    do {
        rc = write(fd, data, left);
        if (rc < 0) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                // use select() or epoll() to wait for the socket to be writable again
            }
            else if (errno != EINTR) {
                return -1;
            }
        }
        else {
            data += rc;
            left -= rc;
        }
    }
    while (left > 0);
    return 0;
}

int receive_int(int fd, int *num)
{
    int32_t ret;
    char *data = (char*)&ret;
    int left = sizeof(ret);
    int rc;
    do {
        rc = read(fd, data, left);
        if (rc <= 0) { /* instead of ret */
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                // use select() or epoll() to wait for the socket to be readable again
            }
            else if (errno != EINTR) {
                return -1;
            }
        }
        else {
            data += rc;
            left -= rc;
        }
    }
    while (left > 0);
    *num = ntohl(ret);
    return 0;
}
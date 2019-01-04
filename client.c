
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <time.h>

int main(void)
{
    int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[256];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;

    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); // port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    /* Create file where data will be stored */
    FILE *fp;
    fp = fopen("file.txt", "ab"); 
    char name[50];
    int card;
    int i, x;
    char password[50];
    char text[100];

    printf("\nName: ");
    scanf("%s", &name);
    printf("\nMatric Card: ");
    scanf("%i", &card);
    printf("\nPlease enter a text: ");
    scanf("%s", &text);
    printf("\nPlease choose following options to:");
    printf("\n\n1 - Encrypt the text");
    printf("\n2 - Decrypt the text");
    printf("\n\nChoosen : ");
    scanf("%d",&x );

   switch(x)
   {
   case 1:
      for(i = 0; (i < 100 && text[i] != '\0'); i++)
        text[i] = text[i] + 10;

      printf("\nEncrypted text: %s\n", text);
      printf("\n");
      break;

   case 2:
      for(i = 0; (i < 100 && text[i] != '\0'); i++)
        text[i] = text[i] - 10;

      printf("\nDecrypted text: %s\n", text);
      printf("\n");
      break;

   default:
      printf("\nError\n");
   }

    time_t t= time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fp, "Date & time: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);


    fprintf(fp, "Name: %s\nMatric Card: %d\nText: %s\n\n", name, card, text);
    fclose(fp);
    if(NULL == fp)
    {
        printf("Error opening file");
        return 1;
    }


    return 0;
}

// Command arguments: ipAddress port message
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
void errExit(const char szFmt[], ... ); // prototype
int main(int argc, char *argv[]){
    int       iSd;                 // socket descriptor
    struct    sockaddr_in host;    // remote host to connect to
    int       irc;                 // return code (error if < 0)
    ssize_t   iBytesSent;
    ssize_t   iBytesReceived;
    char      *pszRequest;
    char      szResponse[2048]; 
    if(argc != 4)
        errExit("usage: %s ipAddress port message", argv[0]);
    // create the socket with the appropriate properties
    iSd = socket(AF_INET, SOCK_STREAM, 0);
    if (iSd == -1)
          errExit("Failed to create socket: %s", strerror(errno));
    
    // set up sockaddr
    host.sin_family = AF_INET;
    host.sin_port = htons(atoi(argv[2])); 
    inet_pton(AF_INET, argv[1], &(host.sin_addr.s_addr));
     
    // Connect to remote server
    irc = connect(iSd, (struct sockaddr *) &host, 
            sizeof(host));
    if (irc < 0)
        errExit("Failed to connect: %s", strerror(errno));   
    printf("Connection Established!\n");
    
    // send the message
    pszRequest = argv[3];
    iBytesSent = send(iSd, pszRequest, strlen(pszRequest) + 1, 0);
    if(iBytesSent != strlen(pszRequest) + 1)
        errExit("Failed to send request: %s", strerror(errno));     
    printf("Request Sent!\n");

    // read reply
    iBytesReceived = recv(iSd, szResponse, sizeof(szResponse), 0);
    if(iBytesReceived < 0)
        errExit("Failed to receive response: %s", strerror(errno));   
    printf("Response:\n%s\n", szResponse);
    
    close(iSd);
    return 0;
}



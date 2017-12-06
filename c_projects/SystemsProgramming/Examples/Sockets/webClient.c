#include <stdio.h>
#include <sys/socket.h>    // domain, socket type
#include <netinet/in.h>    // sockaddr structs
#include <arpa/inet.h>     // for IP address conversions
#include <string.h>        // strerror
#include <unistd.h>        // close
#include <errno.h>         // errno
void errExit(const char szFmt[], ... ); // prototype
#define REMOTE_HOST "129.115.28.4" // cs.utsa.edu
int main()
{
    int     iSd;              // socket descriptor
    struct  sockaddr_in host; // remote host address
    int     irc;              // return code (error if < 0)
    ssize_t iBytesSent;
    ssize_t iBytesReceived;
    char    *pszRequest;
    char    szResponse[2048];
    // create the socket with the appropriate properties
    iSd = socket(AF_INET, SOCK_STREAM, 0);
    if (iSd == -1)
          errExit("Failed to create socket: %s", strerror(errno));
    // set up sockaddr
    host.sin_family = AF_INET;
    host.sin_port = htons(80); // http
    inet_pton(AF_INET, REMOTE_HOST, &(host.sin_addr.s_addr));
    // Connect to remote server
    irc = connect(iSd, (struct sockaddr *) &host, 
            sizeof(host));
    if (irc < 0)
        errExit("Failed to connect");     
    printf("Connection Established!\n");
    // make the request
    pszRequest = "GET / HTTP/1.0/\r\n\r\n";
    iBytesSent = send(iSd, pszRequest, strlen(pszRequest) + 1, 0);
    if(iBytesSent != strlen(pszRequest) + 1)
        errExit("Failed to send pszRequest");     
    printf("Request Sent!\n");
    // read reply
    iBytesReceived = recv(iSd, szResponse, sizeof(szResponse), 0);
    if(iBytesReceived < 0)
        errExit("Failed to receive szResponse");     
    printf("Response:\n%s\n", szResponse);
    close(iSd);
    return 0;
}

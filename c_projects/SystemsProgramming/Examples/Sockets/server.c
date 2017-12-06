#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#define TRUE 1
void errExit(const char szFmt[], ... ); // prototype
int main()
{
    int       iSd;                 // socket descriptor
    int       iCommSd;             // communication socket descriptor
    struct    sockaddr_in local;   // local host
    struct    sockaddr_in client;  // remote client
    socklen_t iClientSockAddrLen;  // client sockaddr length
    char      *pszMessage;         // message for client
    char      szRequest[1024];     // message from client
    int       iRequestLen;         // size of message from client
    int       irc;                 // return code (error if < 0)

    // create the socket with the appropriate properties
    iSd = socket(AF_INET, SOCK_STREAM, 0);
    if (iSd == -1)
        errExit("Failed to create socket%s", strerror(errno));

    // set up sockaddr.  The client must use the same family and port
    local.sin_family = AF_INET;
    local.sin_port = htons(8088);       // arbitrary port 
    local.sin_addr.s_addr = INADDR_ANY; // all available interfaces

    // bind the address
    irc = bind(iSd, (struct sockaddr *) &local, sizeof(local));
    if (irc < 0)
        errExit("Failed to bind socket: %s", strerror(errno));  

    printf("Socket Bound!\n");

    // set socket to listen mode
    irc = listen(iSd, 5);
    if (irc < 0)
        errExit("Failed to listen: %s", strerror(errno)); 
    printf("Listening for connection requests...\n");

    // We will keep doing accept calls until the program
    // has an error or is terminated.   After accepting
    // the connection from the client, this code receives
    // only one request from that client and responds.
        
    while(TRUE)
    {
        // This len is set to avoid overwriting memory
        iClientSockAddrLen = sizeof(struct sockaddr_in);
        iCommSd = accept(iSd, (struct sockaddr *) &client
                        , &iClientSockAddrLen);
        if (iCommSd == -1) 
            errExit("Failed to create communication socket: %s"
                   , strerror(errno));
        printf("Connection Established!\n");

        // read message from client
        iRequestLen = recv(iCommSd, szRequest, 1024, 0);
        if(iRequestLen > 0)
            pszMessage = "Your message was received!";
        else if (iRequestLen == 0)
            pszMessage = "No message from client.";
        else
            errExit("recv failure: %s"
                   , strerror(errno));
        printf("Message from client: \n\t%s\n", szRequest);
        // send a message
        write(iCommSd, pszMessage, strlen(pszMessage) + 1);
        //send(iCommSd, pszMessage, strlen(message) + 1, 0);
        // prior to the next accept, iCommSd must be closed
        close(iCommSd);
    }
    close(iSd);
    return 0;
}


#include <EthernetInterface.h>
#include <string>
#include "ServerCommunicator.h"

ServerCommunicator::ServerCommunicator() : server("192.168.70.28", 4445)
{
    printf("conecting \n");

    ethernet.connect();

    const char *ip = ethernet.get_ip_address();

    printf("IP address is: %s\n", ip ? ip : "No IP");

    udp.open( &ethernet);
}

void ServerCommunicator::requestMessage()
{
    printf("sending empty packet to '%d' at '%s'\n",
        server.get_port(),
        server.get_ip_address()
    );

    nsapi_size_or_error_t r = udp.sendto( server, buffer, sizeof(buffer));
    printf("sent %d bytes\n",r);
}

string ServerCommunicator::getMessage()
{
    //Request a message from the server.
    requestMessage();

    printf("recieveing...\n");

    //[messageLength] How many characters the message consists of.
    int messageLength = udp.recvfrom( &source, buffer, sizeof(buffer));
    //Add a terminating character to the end of the message.
    buffer[messageLength]='\0';

    //Development only.
    printf("message from %s/%d \n",
        source.get_ip_address(),
        source.get_port()
    );

    return buffer;
}

#include <mbed.h>
#include <EthernetInterface.h>
#include <rtos.h>
#include "communications.h"


int main()
{
    DigitalIn sw(SW2);

    ServerCommunicator serverCommunicator;

    while(1)
    {
        //Wait until the user presses the button.
        printf("press sw2\n");
        while(sw.read());

        //Retrieve a message from the server and print it out to the console.
        char* message = (char*) serverCommunicator.getMessage().c_str();
        printf("data %s\n", message);
        printf("----\n");
    }
}

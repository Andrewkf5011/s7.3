#include <mbed.h>
#include <EthernetInterface.h>
#include <rtos.h>
#include "components.h"
#include "communications.h"


int main()
{
    AssignmentBoard board;

    Button btn(board.K64F_SW2, true);

    ServerCommunicator serverCommunicator("192.168.70.15",4445);

    while(1)
    {
        //Wait until the switch has been pressed.
        printf("press sw2\n");
        while(!(btn.isPressed()));

        //Send a request to the server.
        serverCommunicator.requestMessage();

        char* msg = (char*)serverCommunicator.getMessage().c_str();
        printf("data: %s\n", msg);
        printf("----\n");
    }
}

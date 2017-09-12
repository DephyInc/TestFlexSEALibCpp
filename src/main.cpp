#include <iostream>
#include "Windows.h"
#include <stdio.h>
#include <unistd.h>

#include "flexsea_system.h"
#include "flexsea_config.h"
#include "flexsea_interface.h"
#include "serial.h"

using namespace std;

void genAndSendFlexSEAPacket(uint8_t arrLen)
{
	static uint8_t packetIndex = 0;
	packetIndex++;
	uint16_t nb = 0;
	uint8_t commStr[100];

	//Prepare and send command:
	tx_cmd_tools_comm_test_w(TX_N_DEFAULT, 1, arrLen, packetIndex, 0);
	pack(P_AND_S_DEFAULT, FLEXSEA_MANAGE_1, NULL, &nb, commStr);
	flexsea_serial_transmit(nb, commStr, 0);
}

int main()
{
	cout << "Demo code - C++ project with FlexSEA-Stack DLL" << endl;

	//Prepare FlexSEA stack:
	initFlexSEAStack_minimalist(FLEXSEA_PLAN_1);

	//Serial driver test:
	flexsea_serial_open(1,0);

	//Send data for 5s, 100Hz:
	for(int i = 0; i < 500; i++)
	{
		printf("Sending FlexSEA packet #%i...\n", i);
		genAndSendFlexSEAPacket(10);
		Sleep(10);
	}

	flexsea_serial_close();

	return 0;
}

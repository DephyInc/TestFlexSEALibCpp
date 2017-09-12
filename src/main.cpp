#include <iostream>
#include "flexsea_global_structs.h"
#include "flexsea_system.h"
#include "flexsea_board.h"
#include "flexsea_config.h"
#include "flexsea_interface.h"
#include "Windows.h"
#include <stdio.h>
#include "serial.h"
//#include <time.h>
#include <unistd.h>

using namespace std;

void genMasterCommTestPacket(uint8_t arrLen)
{
	uint8_t info[2] = {PORT_RS485_2, PORT_RS485_2};
	static uint8_t packetIndex = 0;
	packetIndex++;
	//uint8_t tmpBoardID = setBoardID(FLEXSEA_PLAN_1);

	//Prepare and send command:
	tx_cmd_tools_comm_test_w(TX_N_DEFAULT, 1, arrLen, packetIndex, 0);
	packAndSend(P_AND_S_DEFAULT, FLEXSEA_MANAGE_1, info, SEND_TO_SLAVE);

	//Restore board_id:
	//setBoardID(tmpBoardID);
}

int main()
{
	cout << "Demo code - C++ project with FlexSEA-Stack DLL" << endl;

	//Prepare FlexSEA stack:
	initFlexSEAStack(FLEXSEA_PLAN_1, flexsea_send_serial_slave, \
			flexsea_send_serial_master);

	//Serial driver test:
	flexsea_serial_open(1,0);

	//Send data for 5s, 100Hz:
	for(int i = 0; i < 500; i++)
	{
		printf("Sending FlexSEA packet #%i...\n", i);
		genMasterCommTestPacket(10);
		Sleep(10);
	}
	flexsea_serial_close();

	return 0;
}

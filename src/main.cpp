#include <iostream>
#include "flexsea_global_structs.h"
#include "flexsea_system.h"
#include "flexsea_board.h"
#include "flexsea_config.h"
#include "flexsea_interface.h"

using namespace std;

int main()
{
	cout << "Demo code - C++ project with FlexSEA-Stack & SerialDriver DLL" << endl;

	//Prepare FlexSEA stack:
	initFlexSEAStack(FLEXSEA_MANAGE_1, flexsea_send_serial_slave, \
			flexsea_send_serial_master);

	//Do a simple interaction with the stack to show that it works:
	uint8_t newId = FLEXSEA_PLAN_1;
	uint8_t test = setBoardID(newId);
	cout << "New ID is " << newId + 0x26 << ", old one was " << test + 0x26;

	return 0;
}

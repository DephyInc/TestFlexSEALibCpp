#include <iostream>
#include "Windows.h"
#include <stdio.h>
#include <unistd.h>
#include "flexsea_system.h"
#include "flexsea_config.h"
#include "flexsea_interface.h"
#include "cmd-ActPack.h"
#include "flexsea_user_structs.h"
#include <serialInterface.h>


using namespace std;

uint8_t packetIndex = 0;
uint16_t nb = 0;
uint8_t commStr[100];

//ActPack variables:
uint8_t controller = CTRL_NONE;
int32_t setpoint = 0;
uint8_t setGains = KEEP;
int16_t g0 = 0;
int16_t g1 = 0;
int16_t g2 = 0;
int16_t g3 = 0;
uint8_t syst = 0;

void requestReadActPack(uint8_t offset)
{
	ptx_cmd_actpack_rw(FLEXSEA_MANAGE_1, &nb, commStr, offset, controller, setpoint, setGains, g0, g1, g2, g3, syst);
	flexsea_serial_transmit(nb, commStr, 0);
}

int main()
{
	cout << "Demo code - C++ project with FlexSEA-Stack DLL" << endl;
	enumerate_ports();

	//Prepare FlexSEA stack:
	initFlexSEAStack_minimalist(FLEXSEA_PLAN_1);

	//Serial driver test:
	flexsea_serial_open(1, 0);

	//Send data for Xs, 100Hz:
	for(int i = 0; i < 10; i++)
	{
		printf("Sending FlexSEA packet #%i...\n", i);
		requestReadActPack(0);
		Sleep(10);
	}

	flexsea_serial_close();

	return 0;
}

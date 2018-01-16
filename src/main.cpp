#include <iostream>
#include "Windows.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "flexsea_system.h"
#include "flexsea_config.h"
#include "flexsea_interface.h"
#include "cmd-ActPack.h"
#include "cmd-Rigid.h"
#include "flexsea_user_structs.h"
#include <serialInterface.h>
#include <signal.h>
#include <cppFlexSEA.h>

using namespace std;

int main()
{
	cout << "Demo code - C++ project with FlexSEA-Stack DLL" << endl;

	//Prepare FlexSEA stack:
	initFlexSEAStack_minimalist(FLEXSEA_PLAN_1);

	//Display ports available
	enumerate_ports();

	//Open port (hardcoded):
	flexsea_serial_open(1, 0);

	sleep(1);

	//Infinite loop - break w/ Ctrl+c
	while(1)
	{
		readActPack(0,0,10);
		Sleep(5);
	}

	cout << "Closing port then exiting..." << endl;
	flexsea_serial_close();

	return 0;
}

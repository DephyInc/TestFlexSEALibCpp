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

uint8_t activeDemo = 0;

void printMenu(void)
{
	cout << "What demo would you like to try?" << endl << endl;
	cout << "[1] Read-Only: no actuator, sensors only." << endl;
	cout << "[2] Open-Speed: PWM will ramp up, then down, then up..." << endl;
	cout << "[3] Position-1: Motor will hold its current position." << endl;
	cout << "[4] Position-2: Motor will toggle between two positions." << endl;
	cout << "[q] Quit program." << endl << endl;
	//ToDo: expand that list
}

char userSelection(void)
{
	char c = 0;
	cout << "Please enter your selection: ";
	cin >> c;

	if(c >= '1' && c <= '4')
	{
		//Valid demo:
		activeDemo = (int)(c - '0');
	}
	else if(c == 'q')
	{
		activeDemo = 0;
	}
	else
	{
		cout << "Invalid selection, please try again." << endl;
		userSelection();
	}

	return activeDemo;
}

int main()
{
	cout << "Demo code - C++ project with FlexSEA-Stack DLL" << endl;

	//Prepare FlexSEA stack:
	initFlexSEAStack_minimalist(FLEXSEA_PLAN_1);

	//Display ports available
	enumerate_ports();

	//Open port (hardcoded):
	flexsea_serial_open(1, 0);

	printMenu();
	userSelection();

	sleep(1);

	//Infinite loop - break w/ Ctrl+c
	while(activeDemo != 0)
	{
		switch(activeDemo)
		{
			case 1:
				readActPack(0,0,10);
				break;
			case 2:
				cout << "Not programmed!" << endl;
				break;
			default:
				cout << "Not programmed!" << endl;
				break;
		}

		Sleep(5);
	}

	cout << "Closing port then exiting..." << endl;
	flexsea_serial_close();

	return 0;
}

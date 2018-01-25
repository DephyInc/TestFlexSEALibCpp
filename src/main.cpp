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

// prototypes
void openSpeedDemo(void);
void holdPositionDemo(void);

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
				openSpeedDemo();
				readActPack(0,0,10);
				break;
			case 3:
				holdPositionDemo();
				readActPack(0,0,10);
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

// open speed demo
void openSpeedDemo()
{
	static int state = 0; // motor states: initialize, stop, speed up, constant speed, slow down 
	static int stateTimeCounter = 0; // 
	static int stateTime = 200; // max time in miliseconds to spend in each state
	static int gain = 15; // motor voltage gain
	static int deadBand = 350; // motor voltage deadband in miliVolts. Motor won't turn below this

	stateTimeCounter++;
	switch(state) 
	{
		case 0: // state 0: initialize everything
			cout<< "setting controller to Open ...\n";
			setControlMode(CTRL_OPEN);
			setMotorVoltage(0);

			state = 1; // move to hold state
			break;
		
		case 1: // state 1: hold position
			// set motor voltage to zero. No motion
			setMotorVoltage(0);

			if (stateTimeCounter > stateTime)
			{
				state = 2; // move to ramp up state
				stateTimeCounter = 0; // reset state time counter
			}
			break;
		
		case 2: // state 2: ramp up motor velocity
			// gradually increase motor voltage linearly based on gain and time spent in this state
			setMotorVoltage(deadBand + gain*stateTimeCounter);
			
			if (stateTimeCounter > stateTime){
				state = 3; // move to constant velocity state
				stateTimeCounter = 0;
			}
			break;

		case 3: // state 3: constant velocity
			// hold motor voltage at constant, which matches the voltage ramped up to in state 2 
			setMotorVoltage(deadBand + gain*stateTime);

			if (stateTimeCounter > stateTime)
			{
				state = 4; // move to ramp down state
				stateTimeCounter = 0;
			}
			break;

		case 4: // state 4: ramp down motor velocity	
			// gradually decrease motor voltage linearly based on gain and time spent in this state
			setMotorVoltage(deadBand + gain*stateTime - gain*stateTimeCounter);

			if (stateTimeCounter > stateTime)
			{
				state = 1; // move to hold state 
				stateTimeCounter = 0;
			}
			break;

		default: // error state should never get here
			//	shut things down as a precaution
			setMotorVoltage(0);
			cout<<"error invald state\n";
	}

}

// hold starting postion demo
void holdPositionDemo()
{
	static int initialized = 0;
	static uint32_t startingPosition;
	// current gains
	int I_KP = 100;
	int I_KI = 1;

	// position controller gains
	int pos_KP = 20;
	int pos_KI = 6;


	if (!initialized)
	{
		cout << "Setting controller to Open...\n";
		setControlMode(CTRL_POSITION);
		setZGains(pos_KP, pos_KI, I_KP, I_KI);
		startingPosition = rigid1.ex.enc_ang[0];
		initialized = 1;
	}

	setMotorPosition(startingPosition);

}

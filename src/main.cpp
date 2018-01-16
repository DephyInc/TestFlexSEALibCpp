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

using namespace std;

uint8_t packetIndex = 0;
uint16_t nb = 0;
uint8_t commStr[100], test[100];
uint8_t pp = 0;

//ActPack variables:
uint8_t controller = CTRL_NONE;
int32_t setpoint = 0;
uint8_t setGains = KEEP;
int16_t g0 = 0;
int16_t g1 = 0;
int16_t g2 = 0;
int16_t g3 = 0;
uint8_t syst = 0;

//Returns the next communication offset
uint8_t offs(uint8_t min, uint8_t max)
{
	static uint8_t riOffs = 0;
	riOffs++;
	if(riOffs > max){riOffs = min;}
	return riOffs;
}

void requestReadActPack(uint8_t offset)
{
	ptx_cmd_actpack_rw(FLEXSEA_MANAGE_1, &nb, commStr, offset, controller, setpoint, setGains, g0, g1, g2, g3, syst);
	flexsea_serial_transmit(nb, commStr, 0);
}

void printRigid(void)
{
	system("cls"); //Clear terminal (Win)

	cout << "Gyro X: " << rigid1.mn.gyro.x << endl;
	cout << "Gyro Y: " << rigid1.mn.gyro.y << endl;
	cout << "Gyro Z: " << rigid1.mn.gyro.z << endl;
	cout << "Accel X: " << rigid1.mn.accel.x << endl;
	cout << "Accel Y: " << rigid1.mn.accel.y << endl;
	cout << "Accel Z: " << rigid1.mn.accel.z << endl;
	cout << "Motor angle: " << rigid1.ex.enc_ang[0] << endl;
	cout << "Motor velocity: " << rigid1.ex.enc_ang_vel[0] << endl;
	cout << "Motor current: " << rigid1.ex.mot_current << endl;
	cout << "Joint angle: " << rigid1.ex.joint_ang[0] << endl;
	cout << "Joint velocity: " << rigid1.ex.joint_ang_vel[0] << endl;
	cout << "Joint Ang-Mot: " << rigid1.ex.joint_ang_from_mot[0] << endl;
	cout << "+VB: " << rigid1.re.vb << endl;
	cout << "Battery current: " << rigid1.re.current << endl;
	cout << "Temperature: " << rigid1.re.temp << endl;
	cout << "6-ch strain #0: " << rigid1.mn.genVar[0] << endl;
	cout << "..." << endl;
}

void readActPack(uint8_t minOffs, uint8_t maxOffs, uint8_t printDiv)
{
	static uint8_t pDiv = 0;

	//Send a FlexSEA packet:
	requestReadActPack(offs(minOffs, maxOffs));
	//Get return value, and feed it to the stack
	flexsea_serial_read(test, 0, &pp);
	if(pp)
	{
		//We parsed a packet:
		pDiv++;
		pDiv %= printDiv;
		if(!pDiv)
		{
			printRigid();
		}
	}
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

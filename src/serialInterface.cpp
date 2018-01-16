//****************************************************************************
//Simple interface for wjwwood/serial/
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include <Windows.h>
#include <iostream>
#include <serialInterface.h>
#include <stdint.h>
#include <stdio.h>
#include "serial.h"

using namespace std;

//****************************************************************************
// Local variable(s)
//****************************************************************************

serial::Serial my_serial;
string portUsed = "COM5";

//****************************************************************************
// External variable(s)
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

int flexsea_serial_open(unsigned int tries, unsigned int delay)
{
	cout << "Opening " << portUsed << ". ";
	my_serial.setPort(portUsed);
	//my_serial.setTimeout(simpleTimeout(1000));
	my_serial.open();

	return isPortOpen();
}

//Closes the SPI port
void flexsea_serial_close(void)
{
	cout << "Closing " << portUsed << ". ";
	my_serial.close();
	isPortOpen();
}

void flexsea_serial_transmit(char bytes_to_send, unsigned char *serial_tx_data, unsigned char verbal)
{
	my_serial.write(serial_tx_data, bytes_to_send);
}

int flexsea_serial_read(uint8_t *buffer)
{

//
	return 0;
}

void enumerate_ports(void)
{
	vector<serial::PortInfo> devices_found = serial::list_ports();

	vector<serial::PortInfo>::iterator iter = devices_found.begin();

	while( iter != devices_found.end() )
	{
		serial::PortInfo device = *iter++;

		printf( "(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(),
		device.hardware_id.c_str() );
	}
}

int isPortOpen(void)
{
	cout << "Is the serial port open?";
	if(my_serial.isOpen())
	{
		cout << " Yes." << endl;
		return 1;
	}
	else
	{
		cout << " No." << endl;
		return 0;
	}
}

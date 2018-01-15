//****************************************************************************
//Simple C serial port driver - Windows
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include <Windows.h>
#include "serial.h"
#include <stdint.h>
#include <stdio.h>

//****************************************************************************
// Local variable(s)
//****************************************************************************

HANDLE hComm;

//****************************************************************************
// External variable(s)
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

//Opens the Serial port specified in device[]
//will try "tries" times with a delay of "delay" us between each try
//From http://stackoverflow.com/questions/18108932/linux-c-serial-port-reading-writing
int flexsea_serial_open(unsigned int tries, unsigned int delay)
{
	hComm = CreateFile("\\\\.\\COM5",            //port name
						GENERIC_READ | GENERIC_WRITE, //Read/Write
						0,            // No Sharing
						NULL,         // No Security
						OPEN_EXISTING,// Open existing port only
						0,            // Non Overlapped I/O
						NULL);        // Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE)
		printf("Error in opening Serial port");
	else
		printf("\nOpening serial port successful\n");

	return 1;
}
	
//Serial port test: sends a single char
void flexsea_serial_putc(char *bytes_to_write)
{

}

//Closes the SPI port
void flexsea_serial_close(void)
{
	CloseHandle(hComm);//Closing the Serial Port
}

void flexsea_serial_transmit(char bytes_to_send, unsigned char *serial_tx_data, unsigned char verbal)
{
	BOOL Status;

	char   lpBuffer[100] = "A";		       // lpBuffer should be  char or byte array, otherwise write will fail
	memcpy(lpBuffer, serial_tx_data, bytes_to_send);

	DWORD  dNoOFBytestoWrite;              // No of bytes to write into the port
	DWORD  dNoOfBytesWritten = 0;          // No of bytes written to the port

	dNoOFBytestoWrite = sizeof(lpBuffer); // Calculating the no of bytes to write into the port

	Status = WriteFile(hComm,               // Handle to the Serialport
						lpBuffer,            // Data to be written to the port
					   dNoOFBytestoWrite,   // No of bytes to write into the port
					   &dNoOfBytesWritten,  // No of bytes written to the port
					   NULL);

	if (Status != TRUE)
		printf("\n\n   Error %d in Writing to Serial Port", (int)GetLastError());
}

#define TRIES 	8
#define DELAY	1
//From http://stackoverflow.com/questions/18108932/linux-c-serial-port-reading-writing
int flexsea_serial_read(uint8_t *buffer)
{
//	int n = 0, spot = 0, i = 0;
//	unsigned char buf = '\0';
//	char bytesavailable = 0;
//	int ret = 0;
//
//	//Wait for n bytes
//	do{
//		ioctl(fd, FIONREAD, &bytesavailable);
//		if(bytesavailable > 0)
//		{
//			for(i = 0; i < bytesavailable; i++)
//			{
//			   read( fd, &buf, 1 );
//			   update_rx_buf_byte_usb(buf);
//			}
//
//			ret = 0;
//		}
//		else
//		{
//			usleep(10);
//			n++;
//			if(n > 500)
//			{
//				ret = 1;
//				break;
//			}
//		}
//	}while(bytesavailable > 0);
//
//	return ret; //1 = failed, 0 = read at least one byte
	return 0;
}

#ifdef __cplusplus
}
#endif

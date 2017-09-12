/****************************************************************************
	[Project] FlexSEA: Flexible & Scalable Electronics Architecture
	[Sub-project] 'flexsea-manage' Mid-level computing, and networking
	Copyright (C) 2017 Dephy, Inc. <http://dephy.com/>
*****************************************************************************
	[Lead developper] Jean-Francois (JF) Duval, jfduval at dephy dot com.
	[Origin] Based on Jean-Francois Duval's work at the MIT Media Lab
	Biomechatronics research group <http://biomech.media.mit.edu/>
	[Contributors]
*****************************************************************************
	[This file] flexsea_board: configuration and functions for this
	particular board
*****************************************************************************
	[Change log] (Convention: YYYY-MM-DD | author | comment)
	* 2016-09-23 | jfduval | Initial GPL-3.0 release
	*
****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include <string.h>
#include "flexsea_board.h"
#include "flexsea_system.h"
#include <flexsea_comm.h>
#include <flexsea_payload.h>
#include "serial.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//<FlexSEA User>
//==============
//Board architecture. Has to be changed in all the flexsea_board files!

/*
uint8_t board_id = FLEXSEA_MANAGE_1;		//This board
uint8_t board_up_id = FLEXSEA_PLAN_1;		//This board's master

//Slave bus #1 (RS-485 #1):
//=========================
uint8_t board_sub1_id[SLAVE_BUS_1_CNT] = {FLEXSEA_EXECUTE_2, FLEXSEA_EXECUTE_4};

//Slave bus #2 (RS-485 #2):
//=========================
uint8_t board_sub2_id[SLAVE_BUS_2_CNT] = {FLEXSEA_EXECUTE_1, FLEXSEA_EXECUTE_3};

uint8_t board_sub3_id[SLAVE_BUS_3_CNT] = {FLEXSEA_MANAGE_1};

//(make sure to update SLAVE_BUS_x_CNT in flexsea_board.h!)

 */

//===============
//</FlexSEA User>

//Test PC:
uint32_t downstreamBufferPos = 0;
uint32_t upstreamBufferPos = 0;
PacketWrapper downstreamPackets[DOWNSTREAM_BUFFER_LEN];
PacketWrapper upstreamPackets[UPSTREAM_BUFFER_LEN];
PacketWrapper lastDownstreamPacket, lastUpstreamPacket;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

//Wrapper for the specific serial functions. Useful to keep flexsea_network
//platform independent (for example, we don't need need puts_rs485() for Plan)
void flexsea_send_serial_slave(PacketWrapper* p)
{
	uint8_t port = p->destinationPort;
	uint8_t* str = p->packed;
	uint16_t length = COMM_STR_BUF_LEN;

	//If it's a valid slave port, send message...
	if(port == PORT_RS485_1)
	{
		//puts_rs485_1(str, length);

		//We store the packets in this buffer
		downstreamPackets[downstreamBufferPos] = *p;
		downstreamPackets[downstreamBufferPos].numb = length;
		//For convenience, here's the last packet received:
		lastDownstreamPacket = downstreamPackets[downstreamBufferPos];
		downstreamBufferPos++;
		downstreamBufferPos %= DOWNSTREAM_BUFFER_LEN;
	}
	else if(port == PORT_RS485_2)
	{
		//puts_uart_ex(str, length);

		//Test:
		flexsea_serial_transmit(length, str, 0);

	}
	else
	{
		//Unknown port, call flexsea_error()
		flexsea_error(SE_INVALID_SLAVE);
		return;
	}

	//...then take care of the transceiver state to allow reception (if needed)
	if(IS_CMD_RW(p->cmd))
	{
		commPeriph[port].transState = TS_TRANSMIT_THEN_RECEIVE;
	}
	else
	{
		commPeriph[port].transState = TS_TRANSMIT;
	}
}

void flexsea_send_serial_master(PacketWrapper* p)
{
	Port port = p->destinationPort;
	uint8_t *str = p->packed;
	uint16_t length = COMM_STR_BUF_LEN;
	//uint8_t retVal = 0;

	if(port == PORT_SPI)
	{
		commPeriph[PORT_SPI].tx.packetReady = 1;
		//This will be sent during the next SPI transaction
		memcpy(comm_str_spi, str, length);
	}
	else if(port == PORT_USB)
	{
		//retVal = CDC_Transmit_FS(str, length);
		//if(retVal != USBD_OK)
		{
			//(Handle errors here)
		}

		//We store the packets in this buffer
		upstreamPackets[upstreamBufferPos] = *p;
		upstreamPackets[upstreamBufferPos].numb = length;
		//For convenience, here's the last packet sent:
		lastUpstreamPacket = upstreamPackets[upstreamBufferPos];
		upstreamBufferPos++;
		upstreamBufferPos %= UPSTREAM_BUFFER_LEN;
	}
	else if(port == PORT_WIRELESS)
	{
		//puts_expUart(str, length);
	}
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

#ifdef __cplusplus
}
#endif

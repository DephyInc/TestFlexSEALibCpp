//****************************************************************************
//Simple interface for wjwwood/serial/
//****************************************************************************

#ifndef INC_SIMPLE_SERIAL_H
#define INC_SIMPLE_SERIAL_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>

//****************************************************************************
// Prototype(s):
//****************************************************************************

int flexsea_serial_open(unsigned int tries, unsigned int delay);
void flexsea_serial_close(void);
void flexsea_serial_transmit(char bytes_to_send, unsigned char *serial_tx_data, unsigned char verbal);
void flexsea_serial_putc(char *bytes_to_write);
int flexsea_serial_read(uint8_t *buffer, unsigned char verbal, uint8_t *pp);
void enumerate_ports(void);
int isPortOpen(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

#endif


//****************************************************************************
//Simple C serial port driver
//****************************************************************************

#ifndef INC_SIMPLE_SERIAL_H
#define INC_SIMPLE_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

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
int flexsea_serial_read(uint8_t *buffer);

//****************************************************************************
// Definition(s):
//****************************************************************************

#ifdef __cplusplus
}
#endif

#endif


#ifndef SERIALDRIVER1_H
#define SERIALDRIVER1_H

#include "serialdriver1_global.h"
#include <QString>
#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QTimer>

//Timer:
#define CLOCK_TIMER_PERIOD		500	//ms
#define CLOCK_TIMER_MAX_COUNT	30	//30*500ms = 15s

class SERIALDRIVER1SHARED_EXPORT SerialDriver1 : public QObject
{
	 Q_OBJECT

public:
	SerialDriver1();

	void open(QString name, int tries, int delay, bool* success);
	void close(void);
	int write(uint8_t bytes_to_send, uint8_t *serial_tx_data);

private:

	QSerialPort USBSerialPort;
	bool comPortOpen;
	QTimer* clockTimer;
	uint16_t timerCount;

	void timerEvent(void);
};

#endif // SERIALDRIVER1_H

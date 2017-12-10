#include <stdio.h>
#include "Altino.h"

#define irsensor1 178
#define irsensor2 165
#define irsensor3 166

void go(int speed);
SensorData left(int speed, SensorData sdata);
SensorData straight(int speed, SensorData sdata);
SensorData right(int speed, SensorData sdata);
void Gobacksound();

int main(void) {
	SensorData sdata;

	int speed = 300;

	Open(szPort);
	
	delay(500);

	while (1) {
		sdata = Sensor(1);

		printf("%d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[1], sdata.IRSensor[2]);
		if (sdata.IRSensor[0] < irsensor1 && sdata.IRSensor[0] > irsensor2) {
			sdata = straight(speed, sdata);
		}
		else if (sdata.IRSensor[0] >= irsensor1) {
			sdata = right(speed, sdata);
		}
		else if (sdata.IRSensor[0] <= irsensor3) {
			sdata = left(speed, sdata);
		}
	}

	go(0);
	Steering(2);
	Led(0x0000);
	
	Close(szPort);

	return 0;
}

void go(int speed) {
	Go(speed, speed);
}

SensorData left(int speed, SensorData sdata) {
	Steering(1);
	Led(0x0020);
	go(speed);

	while (sdata.IRSensor[0] <= irsensor2 || sdata.IRSensor[2] <= 0) {
		sdata = Sensor(1);
		printf("%d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[1], sdata.IRSensor[2]);
	}

	Led(0x0000);

	return sdata;
}

SensorData straight(int speed, SensorData sdata) {
	Steering(2);
	go(speed);

	while (sdata.IRSensor[0] < irsensor1 && sdata.IRSensor[0] > irsensor2) {
		sdata = Sensor(1);
		printf("%d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[1], sdata.IRSensor[2]);
	}

	Led(0x0000);

	return sdata;
}

SensorData right(int speed, SensorData sdata) {
	Steering(3);
	Led(0x0010);
	go(speed);

	while (sdata.IRSensor[0] >= irsensor1 || sdata.IRSensor[0] <= 0) {
		sdata = Sensor(1);
		printf("%d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[1], sdata.IRSensor[2]);
	}

	Led(0x0000);

	return sdata;
}

void CDS(int speed, SensorData sdata)
{
	if (sdata.CDSSensor <= 100)
	{
		go(0, 0);
		delay(3000);
		go(speed);
	}
}

void Gobacksound()
{
	Sound(44);
	delay(500);
	Sound(0);
	delay(100);
	Sound(44);
	delay(500);
	Sound(0);
	delay(100);
	Sound(46);
	delay(500);
	Sound(0);
	delay(100);
	Sound(46);
	delay(500);
	Sound(0);
	delay(100);
	Sound(44);
	delay(500);
	Sound(0);
	delay(100);
	Sound(44);
	delay(500);
	Sound(0);
	delay(100);
	Sound(41);
	delay(500);
	Sound(0);
	delay(100);
}
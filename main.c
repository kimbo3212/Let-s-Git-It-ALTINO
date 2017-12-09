#include <stdio.h>
#include "Altino.h"

void go(int speed);
SensorData left(int speed, SensorData sdata);
SensorData straight(int speed, SensorData sdata);
SensorData right(int speed, SensorData sdata);

int main(void) {
	SensorData sdata;

	int speed = 300;

	Open(szPort);
	
	delay(500);

	while (1) {
		sdata = Sensor(1);

		printf("%d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[1], sdata.IRSensor[2]);
		if (sdata.IRSensor[0] < 167 && sdata.IRSensor[2] < 158) {
			sdata = straight(speed, sdata);
		}
		else if (sdata.IRSensor[0] >= 167) {
			sdata = right(speed, sdata);
		}
		else if (sdata.IRSensor[2] >= 158) {
			sdata = left(speed, sdata);
		}
		else if (sdata.CDSSensor <= 100)
		{
			g0(0);
			delay(3000);
			go(300);
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

	while (sdata.IRSensor[2] >= 158) {
		sdata = Sensor(1);
		printf("%d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[1], sdata.IRSensor[2]);
	}

	Led(0x0000);

	return sdata;
}

SensorData straight(int speed, SensorData sdata) {
	Steering(2);
	go(speed);

	while (sdata.IRSensor[0] < 167 && sdata.IRSensor[2] < 158) {
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

	while (sdata.IRSensor[0] >= 167) {
		sdata = Sensor(1);
		printf("%d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[1], sdata.IRSensor[2]);
	}

	Led(0x0000);

	return sdata;
}
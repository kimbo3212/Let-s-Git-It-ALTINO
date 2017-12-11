#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Altino.h"

#define irsensor1 10          // default
#define irsensor2 30          // default + 13
#define irsensor3 100          // default + 30
#define irsensor4 80          // collect
#define irsensor5 160
#define irsensor6 230
#define row 1000
#define col 1000

void go(int speed);
SensorData left(int speed, SensorData sdata);
SensorData straight(int speed, SensorData sdata);
SensorData right(int speed, SensorData sdata);
void CDS(int speed, SensorData sdata);
SensorData Back(int speed, SensorData sdata);
void Gobacksound();
void Startsound();
double Func(double x, double y);
double Integral(double start, double end, double y, double(*func)(double a, double b));

typedef struct MAP {
	int x;
	int y;
}Map;

static int NumIntervals = 100;

int main(void) {
	SensorData sdata;

	int speed = 320;

	Open(szPort);

	delay(500);

	while (1) {
		sdata = Sensor(1);

		printf("%d %d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[4], sdata.IRSensor[2], sdata.CDSSensor);
		if (sdata.IRSensor[0] > irsensor3 || sdata.IRSensor[4] > irsensor6) {
			sdata = Back(speed, sdata);
		}
		else if ((sdata.IRSensor[0] > irsensor1 && sdata.IRSensor[0] <= irsensor2) || (sdata.IRSensor[4] <= irsensor5 && sdata.IRSensor[4] > irsensor4)) {

			sdata = straight(speed, sdata);
		}
		else if ((sdata.IRSensor[0] > irsensor2 && sdata.IRSensor[0] <= irsensor3) || (sdata.IRSensor[4] <= irsensor6 && sdata.IRSensor[4] > irsensor5)) {
			sdata = right(speed, sdata);
		}
		else if (sdata.IRSensor[0] <= irsensor1 || sdata.IRSensor[4] <= irsensor4) {
			sdata = left(speed, sdata);
		}
	}

	return 0;
}

void go(int speed) {
	Go(speed, speed);
}

SensorData left(int speed, SensorData sdata) {
	Steering(1);
	Led(0x0020);
	go(speed);

	while (sdata.IRSensor[0] <= irsensor1 || sdata.IRSensor[4] <= irsensor4) {
		sdata = Sensor(1);
		printf("%d %d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[4], sdata.IRSensor[2], sdata.CDSSensor);
		CDS(speed, sdata);
	}

	Led(0x0000);

	return sdata;
}

SensorData straight(int speed, SensorData sdata) {
	Steering(2);
	go(speed);

	while ((sdata.IRSensor[0] > irsensor1 && sdata.IRSensor[0] <= irsensor2) || (sdata.IRSensor[4] <= irsensor5 && sdata.IRSensor[4] > irsensor4)) {
		sdata = Sensor(1);
		printf("%d %d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[4], sdata.IRSensor[2], sdata.CDSSensor);
		CDS(speed, sdata);
	}

	Led(0x0000);

	return sdata;
}

SensorData right(int speed, SensorData sdata) {
	int count = 0;

	Steering(3);
	Led(0x0010);
	go(speed);

	while ((sdata.IRSensor[0] > irsensor2 && sdata.IRSensor[0] <= irsensor3) || (sdata.IRSensor[4] <= irsensor6 && sdata.IRSensor[4] > irsensor5)) {
		sdata = Sensor(1);
		printf("%d %d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[4], sdata.IRSensor[2], sdata.CDSSensor);
		CDS(speed, sdata);
	}

	Led(0x0000);

	return sdata;
}

void CDS(int speed, SensorData sdata)
{
	if (sdata.CDSSensor <= 100)
	{
		go(0);
		Led(0x0000);
		Steering(2);

		Close(szPort);

		exit(0);
	}
}

SensorData Back(int speed, SensorData sdata) {
	Steering(1);
	speed *= -1;
	go(speed);

	while (sdata.IRSensor[0] > irsensor3 || sdata.IRSensor[4] > irsensor6) {
		sdata = Sensor(1);
		printf("%d %d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[4], sdata.IRSensor[2], sdata.CDSSensor);
		CDS(-speed, sdata);
	}

	return sdata;
}


void Gobacksound() {

	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(46);
	delay(100);
	Sound(0);
	delay(100);
	Sound(46);
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(41);

	delay(200);
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
	delay(1000);
	Sound(0);
	delay(100);

	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(41);
	delay(100);
	Sound(0);
	delay(100);
	Sound(41);
	delay(100);
	Sound(0);
	delay(100);
	Sound(39);

	delay(400);
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
	Sound(41);

	delay(500);
	Sound(0);
	delay(100);
	Sound(39);
	delay(2000);
	Sound(0);
	delay(100);

	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(46);
	delay(100);
	Sound(0);
	delay(100);
	Sound(46);
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(41);

	delay(200);
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
	delay(1000);
	Sound(0);
	delay(100);

	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(41);
	delay(100);
	Sound(0);
	delay(100);
	Sound(39);
	delay(100);
	Sound(0);
	delay(100);
	Sound(41);
	delay(100);
	Sound(0);
	delay(100);
	Sound(37);

	delay(300);

	delay(500);
	Sound(0);
	delay(100);
	Sound(41);
	delay(500);
	Sound(0);
	delay(100);
	Sound(39);
	delay(500);
	Sound(0);
	delay(100);
	Sound(41);
	delay(500);
	Sound(0);
	delay(100);
	Sound(37);
	delay(1500);
	Sound(0);
	delay(100);

	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(46);
	delay(100);
	Sound(0);
	delay(100);
	Sound(46);
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);
	delay(100);
	Sound(0);
	delay(100);
	Sound(41);
	delay(100);
	Sound(0);
	delay(100);
}

void Startsound() {

	Sound(41);
	delay(200);
	Sound(0);
	delay(50);
	Sound(41);
	delay(200);
	Sound(0);
	delay(50);
	Sound(41);
	delay(400);
	Sound(0);
	delay(50);

	Sound(41);
	delay(200);
	Sound(0);
	delay(50);
	Sound(41);
	delay(200);
	Sound(0);
	delay(50);
	Sound(41);
	delay(400);
	Sound(0);
	delay(50);

	Sound(41);
	delay(200);
	Sound(0);
	delay(50);
	Sound(44);
	delay(200);
	Sound(0);
	delay(50);
	Sound(37);
	delay(200);
	Sound(0);
	delay(50);
	Sound(39);
	delay(200);
	Sound(0);
	delay(50);
	Sound(41);
	delay(800);
	Sound(0);
	delay(50);

}

double Func(double x, double y) {
	return 1.0 / (1.0 - pow(x, y));
}

double Integral(double start, double end, double y, double(*func)(double a, double b)) {
	double ans = 0.0;
	double dx = ((end - start) / (NumIntervals + 1));
	int i;

	for (int i = 0; i < NumIntervals; i++) {
		ans += func(start + i * dx, y);
	}
	ans *= dx;

	return ans;
}
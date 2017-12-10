#include <stdio.h>
#include "Altino.h"

#define irsensor1 170          // �⺻�� + 13
#define irsensor2 165          // �⺻��
#define irsensor3 190          // �⺻�� + 30
#define irsensor4 600          // �����
#define irsensor5 400

void go(int speed);
SensorData left(int speed, SensorData sdata);
SensorData straight(int speed, SensorData sdata);
SensorData right(int speed, SensorData sdata);
void CDS(int speed, SensorData sdata);
SensorData Back(int speed, SensorData sdata);
void Gobacksound();
SensorData GoBack(int backSpeed, SensorData sdata);

int main(void) {
	SensorData sdata;

	int speed = 300;

	Open(szPort);

	delay(500);

	while (1) {
		sdata = Sensor(1);

		printf("%d %d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[4], sdata.IRSensor[2], sdata.CDSSensor);
		if (sdata.IRSensor[0] > irsensor3 || sdata.IRSensor[0] <= 0 || sdata.IRSensor[4] > irsensor4) {
			sdata = Back(speed, sdata);
		}
		else if (sdata.IRSensor[0] < irsensor1 && sdata.IRSensor[0] > irsensor2 && sdata.IRSensor[4] <= irsensor5) {

			sdata = straight(speed, sdata);
		}
		else if ((sdata.IRSensor[0] >= irsensor1 && sdata.IRSensor[0] <= irsensor3) || sdata.IRSensor[0] <= 0 || (sdata.IRSensor[4] > irsensor5 && sdata.IRSensor[4] <= irsensor4)) {
			sdata = right(speed, sdata);
		}
		else if (sdata.IRSensor[0] <= irsensor2 && sdata.IRSensor[4] <= irsensor5) {
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

	while (sdata.IRSensor[0] <= irsensor2 && sdata.IRSensor[4] <= irsensor5) {
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

	while (sdata.IRSensor[0] < irsensor1 && sdata.IRSensor[0] > irsensor2 && sdata.IRSensor[4] <= irsensor5) {
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

	while ((sdata.IRSensor[0] >= irsensor1 && sdata.IRSensor[0] <= irsensor3) || sdata.IRSensor[0] <= 0 || (sdata.IRSensor[4] > irsensor5 && sdata.IRSensor[4] <= irsensor4)) {
		sdata = Sensor(1);
		if (sdata.IRSensor[0] <= irsensor2 - 6) {           // �⺻��
			count++;
		}
		if (count >= 5) {
			go(speed);
			delay(200);
			Steering(1);
			delay(1000);
		}
		printf("%d %d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[4], sdata.IRSensor[2], sdata.CDSSensor);
		printf("count : %d\n", count);
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
		delay(3000);
		go(400);
		delay(1000);
		go(speed);
	}
}
SensorData Back(int speed, SensorData sdata) {
	Steering(2);
	speed += 50;
	speed *= -1;
	go(speed);

	while (sdata.IRSensor[0] > irsensor3 || sdata.IRSensor[4] > irsensor4) {
		sdata = Sensor(1);
		printf("%d %d %d %d\n", sdata.IRSensor[0], sdata.IRSensor[4], sdata.IRSensor[2], sdata.CDSSensor);
	}

	return sdata;
void Gobacksound()
{
	Sound(44);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(46);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(46);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(41);//��
	delay(200);
	delay(500);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(46);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(46);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(41);//��
	delay(1000);
	Sound(0);
	delay(100);

	Sound(44);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(100);
	Sound(0);
	delay(100); 
	Sound(41);//��
	delay(100);
	Sound(0);
	delay(100); 
	Sound(41);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(39);//��
	delay(400);
	delay(500);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(500);
	Sound(0);
	delay(100); 
	Sound(41);//��
	delay(500);
	Sound(0);
	delay(100); 
	Sound(41);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(39);//��
	delay(2000);
	Sound(0);
	delay(100);
	
	Sound(44);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(46);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(46);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(41);//��
	delay(200);
	delay(500);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(46);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(46);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(44);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(41);//��
	delay(1000);
	Sound(0);
	delay(100);

	Sound(44);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(41);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(39);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(41);//��
	delay(100);
	Sound(0);
	delay(100);
	Sound(37);//��
	delay(300);
  
	delay(500);
	Sound(0);
	delay(100);
	Sound(41);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(39);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(41);//��
	delay(500);
	Sound(0);
	delay(100);
	Sound(37);//��
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
}
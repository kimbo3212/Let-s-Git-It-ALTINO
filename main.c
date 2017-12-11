#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Altino.h"

#define irsensor1 10          // 기본값
#define irsensor2 30          // 기본값 + 13
#define irsensor3 100          // 기본값 + 30
#define irsensor4 80          // 측정값
#define irsensor5 120
#define irsensor6 180

#define msensor1 -1830
#define msensor2 1220

typedef struct {
	int x;
	int y;
}x_y;

void go(int speed);
void left(int speed, SensorData sdata[]);
void straight(int speed, SensorData sdata[]);
void right(int speed, SensorData sdata[]);
void CDS(int speed, SensorData sdata[]);
void Back(int speed, SensorData sdata[]);
void Gobacksound();
void Startsound();


int map[100][100] = { 0 };
int a, b, x = 50, y = 50;
int count, index = 7;
int x_go = -1, y_go = 0;
int start, end;
int steer;
FILE *q, *w, *e, *r;

x_y xy[8] = { { -1, 1 },{ 0, 1 },{ 1, 1 },{ 1, 0 },{ 1, -1 },{ 0, -1 },{ -1, -1 },{ -1, 0 } };

int main(void) {
	SensorData sdata[2];

	int speed = 320;
	steer = 0;

	map[x][y] = 1;
	q = fopen("mapX.txt", "w+");
	w = fopen("mapY.txt", "w+");
	e = fopen("time.txt", "w+");
	r = fopen("steer.txt", "w+");

	Open(szPort);

	delay(500);

	sdata[0] = Sensor(1);
	start = clock();
	sdata[1] = Sensor(2);
	end = clock();
	fprintf(q, "%d\n", sdata[1].MSensor[0]);
	fprintf(w, "%d\n", sdata[1].MSensor[1]);
	fprintf(e, "%d\n", end - start);
	fprintf(r, "%d\n", steer);

	while (1) {
		count = 0;
		if (a - sdata[1].MSensor[0] <= 5 && a - sdata[1].MSensor[0] >= -5) {
			count++;
		}
		if (b - sdata[1].MSensor[1] <= 5 && b - sdata[1].MSensor[1] >= -5) {
			count++;
		}
		if (count == 2) {
			x += x_go;
			y += y_go;
			map[x][y] = 1;
		}
		a = sdata[1].MSensor[0];
		b = sdata[1].MSensor[1];

		printf("%d %d %d %d\n", sdata[0].IRSensor[0], sdata[0].IRSensor[4], sdata[0].MSensor[0], sdata[0].MSensor[1]);
		if (sdata[0].IRSensor[0] > irsensor3 && sdata[0].IRSensor[4] > irsensor6) {
			Back(speed, sdata);
		}
		else if ((sdata[0].IRSensor[0] > irsensor1 && sdata[0].IRSensor[0] <= irsensor2) || (sdata[0].IRSensor[4] <= irsensor5 && sdata[0].IRSensor[4] > irsensor4)) {

			straight(speed, sdata);
		}
		else if ((sdata[0].IRSensor[0] > irsensor2 && sdata[0].IRSensor[0] <= irsensor3) || (sdata[0].IRSensor[4] <= irsensor6 && sdata[0].IRSensor[4] > irsensor5)) {
			right(speed, sdata);
		}
		else if (sdata[0].IRSensor[0] <= irsensor1 && sdata[0].IRSensor[4] <= irsensor4) {
			left(speed, sdata);
		}

		sdata[0] = Sensor(1);
		sdata[1] = Sensor(2);
		end = clock();
		fprintf(q, "%d\n", sdata[1].MSensor[0]);
		fprintf(w, "%d\n", sdata[1].MSensor[1]);
		fprintf(e, "%d\n", end - start);
		fprintf(r, "%d\n", steer);
	}

	return 0;
}

void go(int speed) {
	Go(speed, speed);
}

void left(int speed, SensorData sdata[]) {
	Steering(1);
	steer = 1;
	index -= 1;
	if (index < 0) {
		index = 7;
	}
	x_go = xy[index].x;
	y_go = xy[index].y;
	Led(0x0020);
	go(speed);

	while (sdata[0].IRSensor[0] <= irsensor1 && sdata[0].IRSensor[4] <= irsensor4) {
		sdata[0] = Sensor(1);
		sdata[1] = Sensor(2);
		end = clock();
		fprintf(q, "%d\n", sdata[1].MSensor[0]);
		fprintf(w, "%d\n", sdata[1].MSensor[1]);
		fprintf(e, "%d\n", end - start);
		fprintf(r, "%d\n", steer);
		count = 0;
		if (a - sdata[1].MSensor[0] <= 5 && a - sdata[1].MSensor[0] >= -5) {
			count++;
		}
		if (b - sdata[1].MSensor[1] <= 5 && b - sdata[1].MSensor[1] >= -5) {
			count++;
		}
		if (count == 2) {
			x += x_go;
			y += y_go;
			map[x][y] = 1;
		}
		a = sdata[1].MSensor[0];
		b = sdata[1].MSensor[1];
		printf("%d %d %d %d\n", sdata[0].IRSensor[0], sdata[0].IRSensor[4], sdata[0].MSensor[0], sdata[0].MSensor[1]);
		CDS(speed, sdata);
	}

	Led(0x0000);
}

void straight(int speed, SensorData sdata[]) {
	Steering(2);
	steer = 0;
	go(speed);

	while ((sdata[0].IRSensor[0] > irsensor1 && sdata[0].IRSensor[0] <= irsensor2) || (sdata[0].IRSensor[4] <= irsensor5 && sdata[0].IRSensor[4] > irsensor4)) {
		sdata[0] = Sensor(1);
		sdata[1] = Sensor(2);
		end = clock();
		fprintf(q, "%d\n", sdata[1].MSensor[0]);
		fprintf(w, "%d\n", sdata[1].MSensor[1]);
		fprintf(e, "%d\n", end - start);
		fprintf(r, "%d\n", steer);
		count = 0;
		if (a - sdata[1].MSensor[0] <= 5 && a - sdata[1].MSensor[0] >= -5) {
			count++;
		}
		if (b - sdata[1].MSensor[1] <= 5 && b - sdata[1].MSensor[1] >= -5) {
			count++;
		}
		if (count == 2) {
			x += x_go;
			y += y_go;
			map[x][y] = 1;
		}
		a = sdata[1].MSensor[0];
		b = sdata[1].MSensor[1];
		printf("%d %d %d %d\n", sdata[0].IRSensor[0], sdata[0].IRSensor[4], sdata[0].MSensor[0], sdata[0].MSensor[1]);
		CDS(speed, sdata);
	}

	Led(0x0000);
}

void right(int speed, SensorData sdata[]) {
	Steering(3);
	steer = -1;
	index += 1;
	if (index > 7) {
		index = 0;
	}
	x_go = xy[index].x;
	y_go = xy[index].y;
	Led(0x0010);
	go(speed);

	while ((sdata[0].IRSensor[0] > irsensor2 && sdata[0].IRSensor[0] <= irsensor3) || (sdata[0].IRSensor[4] <= irsensor6 && sdata[0].IRSensor[4] > irsensor5)) {
		sdata[0] = Sensor(1);
		sdata[1] = Sensor(2);
		end = clock();
		fprintf(q, "%d\n", sdata[1].MSensor[0]);
		fprintf(w, "%d\n", sdata[1].MSensor[1]);
		fprintf(e, "%d\n", end - start);
		fprintf(r, "%d\n", steer);
		count = 0;
		if (a - sdata[1].MSensor[0] <= 5 && a - sdata[1].MSensor[0] >= -5) {
			count++;
		}
		if (b - sdata[1].MSensor[1] <= 5 && b - sdata[1].MSensor[1] >= -5) {
			count++;
		}
		if (count == 2) {
			x += x_go;
			y += y_go;
			map[x][y] = 1;
		}
		a = sdata[1].MSensor[0];
		b = sdata[1].MSensor[1];
		printf("%d %d %d %d\n", sdata[0].IRSensor[0], sdata[0].IRSensor[4], sdata[0].MSensor[0], sdata[0].MSensor[1]);
		CDS(speed, sdata);
	}

	Led(0x0000);
}

void CDS(int speed, SensorData sdata[])
{
	int i, j;
	if (sdata[0].CDSSensor <= 100)
	{
		go(0);
		Led(0x0000);
		Steering(2);

		Close(szPort);

		for (i = 0; i < 100; i++) {
			for (j = 0; j < 100; j++) {
				if (map[i][j] == 1) {
					printf("1");
				}
				else {
					printf(" ");
				}
			}
			printf("\n");
		}

		exit(0);
	}
}

void Back(int speed, SensorData sdata[]) {
	Steering(1);
	steer = 1;
	index -= 1;
	if (index < 0) {
		index = 7;
	}
	x_go = xy[index].x;
	y_go = xy[index].y;
	speed *= -1;
	go(speed);

	while (sdata[0].IRSensor[0] > irsensor3 && sdata[0].IRSensor[4] > irsensor6) {
		sdata[0] = Sensor(1);
		sdata[1] = Sensor(2);
		end = clock();
		fprintf(q, "%d\n", sdata[1].MSensor[0]);
		fprintf(w, "%d\n", sdata[1].MSensor[1]);
		fprintf(e, "%d\n", end - start);
		fprintf(r, "%d\n", steer);
		count = 0;
		if (a - sdata[1].MSensor[0] <= 5 && a - sdata[1].MSensor[0] >= -5) {
			count++;
		}
		if (b - sdata[1].MSensor[1] <= 5 && b - sdata[1].MSensor[1] >= -5) {
			count++;
		}
		if (count == 2) {
			x += x_go;
			y += y_go;
			map[x][y] = 1;
		}
		a = sdata[1].MSensor[0];
		b = sdata[1].MSensor[1];
		printf("%d %d %d %d\n", sdata[0].IRSensor[0], sdata[0].IRSensor[4], sdata[0].MSensor[0], sdata[0].MSensor[1]);
		CDS(-speed, sdata);
	}
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
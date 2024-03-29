#include <stdio.h>
#include <wiringPi.h>

#define OUT1 4
#define OUT2 18
#define OUT3 22
#define OUT4 24

void setsteps(int w1, int w2, int w3, int w4)
{
	pinMode(OUT1,OUTPUT);
	digitalWrite(OUT1,w1);
	pinMode(OUT2,OUTPUT);
	digitalWrite(OUT2,w2);
	pinMode(OUT3,OUTPUT);
	digitalWrite(OUT3,w3);
	pinMode(OUT4,OUTPUT);
	digitalWrite(OUT4,w4);
}

void forward(int del,int steps){
	int i;
	for(i=0;i<=steps;i++)
	{
		setsteps(1,1,0,0);
		delay(del);
		setsteps(0,1,0,0);
		delay(del);
		setsteps(0,1,1,0);
		delay(del);
		setsteps(0,0,1,0);
		delay(del);
		setsteps(0,0,1,1);
		delay(del);
		setsteps(0,0,0,1);
		delay(del);
		setsteps(1,0,0,1);
		delay(del);
		setsteps(1,0,0,0);
		delay(del);
	}
}

void backward(int del,int steps){
	int k;
	for(k=0;k<=steps;k++){
		setsteps(1,0,0,0);
		delay(del);
		setsteps(1,0,0,1);
		delay(del);
		setsteps(0,0,0,1);
		delay(del);
		setsteps(0,0,1,1);
		delay(del);
		setsteps(0,0,1,0);
		delay(del);
		setsteps(0,1,1,0);
		delay(del);
		setsteps(0,1,0,0);
		delay(del);
		setsteps(1,1,0,0);
		delay(del);
		}
}

int main(void){

	if(wiringPiSetupGpio() ==-1)
	return 1;

	for(;;) {
		forward(10, 511);
		delay(1000);
		backward(10, 511);
		delay(1000);
	}
	return 0;
}

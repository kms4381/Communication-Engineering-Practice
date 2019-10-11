#include <stdio.h>
#include <wiringPi.h>

#define OUT1 4
#define OUT2 18
#define OUT3 22
#define OUT4 24

#define KEYPAD_PB1 6
#define KEYPAD_PB2 12

#define MAX_KEY_BT_NUM 2

const int KeypadTable[2] = {
	KEYPAD_PB1, KEYPAD_PB2
};

int KeypadRead()
{
	int i, nKeypadstate;
	nKeypadstate = 0;
	for(i=0; i<MAX_KEY_BT_NUM; i++){
		if(!digitalRead(KeypadTable[i])){
			nKeypadstate |= (1<<i);
		}
	}
	return nKeypadstate;
}

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

double forward(int del,int steps, double sum){
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
		sum += 0.703;
		if(sum >360 ) sum = 0;
	}
	return sum;
}

double backward(int del,int steps, double sum){
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
		sum -= 0.703;
		if(sum < 0 ) sum = 360;
	}
	return sum;
}

int main(void){

	if(wiringPiSetupGpio() ==-1)
	return 1;

	int i, state=0;
	double sum = 0;
	int nKeypadstate;
	
	for(i=0; i<MAX_KEY_BT_NUM; i++){
		pinMode(KeypadTable[i], INPUT);
	}
	
	while(1){
		nKeypadstate = KeypadRead();

		for(i=0; i<MAX_KEY_BT_NUM; i++){
			if((nKeypadstate & (1<<i)) && (state == 0) && (nKeypadstate == 1)){
				sum = forward(2,10,sum);
				printf("정방향 %f\n", sum);
				}
			if((nKeypadstate & (1<<i)) && (state == 1) && (nKeypadstate == 1)){
				sum = backward(2,10,sum);
				printf("역방향 %f\n", sum);
			}
			if((nKeypadstate & (1<<i)) && (nKeypadstate == 2)){
					delay(500);
					state = (state + 1)% 2;
			}
		}
	}
	return 0;
}

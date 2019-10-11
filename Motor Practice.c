#include <wiringPi.h>
#include <softPwm.h>

#define KEYPAD_PB1 6
#define KEYPAD_PB2 12
#define KEYPAD_PB3 13

#define MAX_KEY_BT_NUM 3

#define MOTOR_MT_N_PIN 25
#define MOTOR_MT_P_PIN 24
#define LEFT_ROTATE 1
#define RIGHT_ROTATE 2

void MotorStop(void);
void MotorControl(unsigned char speed, unsigned char rotate);

const int KeypadTable[3] = {
	KEYPAD_PB1, KEYPAD_PB2, KEYPAD_PB3
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

int main(void)
{
	if(wiringPiSetupGpio() == -1)
		return 1;
		
		
	int i, nKeypadstate;
	int speed = 0;
	int c=0;
	int x = LEFT_ROTATE;
	
	for(i=0; i<MAX_KEY_BT_NUM; i++){
		pinMode(KeypadTable[i], INPUT);
	}
		
	pinMode(MOTOR_MT_N_PIN, OUTPUT);
	pinMode(MOTOR_MT_P_PIN, OUTPUT);
	softPwmCreate(MOTOR_MT_N_PIN, 0, 100);
	softPwmCreate(MOTOR_MT_P_PIN, 0, 100);
	
	while(1){
	nKeypadstate = KeypadRead();
	
	for(i=0; i<MAX_KEY_BT_NUM; i++){
		if((nKeypadstate & (1<<i))){
			if(nKeypadstate == 1){
				MotorStop();
			}
			else if(nKeypadstate == 2){
				MotorStop();
				delay(1000);
				
				if(x == LEFT_ROTATE)
					x = RIGHT_ROTATE;
				else if(x == RIGHT_ROTATE)
					x = LEFT_ROTATE;
					
				MotorControl(speed, x);
			}
			else if(nKeypadstate == 4){
				delay(1000);
				c = c + 1;
					if(c == 0) {
						MotorControl(0, x);
						speed = 0;
					}
					if(c == 1) {
						MotorControl(30, x);
						speed = 30;
					}
					if(c == 2) {
						MotorControl(60, x);
						speed = 60;
					}
					if(c == 3) {
						MotorControl(90, x);
						speed = 90;
					}
				
				if(c > 3){
					c = 0;
					speed = 0;
					MotorControl(0, x);
					
				}
			}
		}
	}
	
	}
	return 0;
}

void MotorStop()
{
	softPwmWrite(MOTOR_MT_N_PIN, 0);
	softPwmWrite(MOTOR_MT_P_PIN, 0);
}

void MotorControl(unsigned char speed, unsigned char rotate)
{
	if(rotate == LEFT_ROTATE){
		digitalWrite(MOTOR_MT_P_PIN, LOW);
		softPwmWrite(MOTOR_MT_N_PIN, speed);
	}
	else if(rotate == RIGHT_ROTATE){
		digitalWrite(MOTOR_MT_N_PIN, LOW);
		softPwmWrite(MOTOR_MT_P_PIN, speed);
	}
}

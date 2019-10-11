#include <wiringPi.h> // GPIO Access Library Header File

#define LED_PIN_1 23 // LED Port pin Definition
#define LED_PIN_2 24
#define LED_PIN_3 25

#define KEYPAD_PB1 6 // KEYPAD Port pin Definition
#define KEYPAD_PB2 12
#define KEYPAD_PB3 13

#define LED_ON 1 // LED ON/OFF Definition
#define LED_OFF 0

#define MAX_LED_NUM 3 // LED & Keypad Button amount Definition
#define MAX_KEY_BT_NUM 3

const int LedPinTable[3] = { 
	LED_PIN_1, LED_PIN_2, LED_PIN_3 // LED Pin Table Definition
};

const int KeypadTable[3] = {
	KEYPAD_PB1, KEYPAD_PB2, KEYPAD_PB3 // KEYPAD Pin Table Definition
};

/* to confirm the button press KEYPAD
store the value in a variable nKeypadstate*/
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


/*Check LED Pin number and ON/OFF command
Output HIGH/LOW signal */
void LedControl(int LedNum, int Cmd){

	int i;
	for(i=0; i<MAX_LED_NUM; i++){
		if(i == LedNum){
			if(Cmd == LED_ON){
				digitalWrite(LedPinTable[i], HIGH);
			}
			else{
				digitalWrite(LedPinTable[i], LOW);
			}
		}
	}
}


int main(void)
{
	if(wiringPiSetupGpio() == -1) // Using GPIO to Wiring Pi Setting
		return 1;


	int i;
	int nKeypadstate;
	
	for(i=0; i<MAX_LED_NUM; i++){
		pinMode(LedPinTable[i], OUTPUT); // LED Pin Output Setting
	}
	
	for(i=0; i<MAX_KEY_BT_NUM; i++){
		pinMode(KeypadTable[i], INPUT); // KEYPAD pin Input Setting
	}

	while(1){
		nKeypadstate = KeypadRead(); // Read button input from KEYPAD and save state to variable

		for(i=0; i<MAX_KEY_BT_NUM; i++){  // check the KEYPAD state variable
			if((nKeypadstate & (1<<i))){  // LED ON / OFF Control
				LedControl(i, LED_ON);
			}
			else{
				LedControl(i, LED_OFF);
			}
		}
	}
}


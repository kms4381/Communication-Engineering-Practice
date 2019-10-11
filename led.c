#include <wiringPi.h>              // GPIO Access Library Header File Declaration
#define LED_RED_1 25               // LED Port pin Definition
#define LED_YELLOW_2 24
#define LED_GREEN_3 23
 
int main()
{
	if(wiringPiSetupGpio() == -1)  // Using GPIO to Wiring Pi Setting
		return 1;

	pinMode(LED_RED_1, OUTPUT);    //  LED Pin Output Setting
	pinMode(LED_YELLOW_2, OUTPUT); 
	pinMode(LED_GREEN_3, OUTPUT);

	digitalWrite(LED_RED_1, LOW);  //  LED Pin LOW Output Setting
	digitalWrite(LED_YELLOW_2, LOW); 
	digitalWrite(LED_GREEN_3, LOW);

	while(1)	// LED Alternately Output
	{
		digitalWrite(LED_RED_1, HIGH);  //  LED Pin HIGH Output Setting
		delay(500);						// 500ms delay
		digitalWrite(LED_RED_1, LOW);
		digitalWrite(LED_YELLOW_2, HIGH);
		delay(500);
		digitalWrite(LED_YELLOW_2, LOW);
		digitalWrite(LED_GREEN_3, HIGH);
		delay(500);
		digitalWrite(LED_GREEN_3, LOW);
	}
	return 0;
}

#include <wiringPi.h>              // GPIO Access Library ������� ����
#define LED_RED_1 25               // LED ��Ʈ ��ȣ ����
#define LED_YELLOW_2 24
#define LED_GREEN_3 23
 
int main()
{
	if(wiringPiSetupGpio() == -1)  // Wiring Pi�� GPIO�� ����ϱ� ���� ����
		return 1;

	pinMode(LED_RED_1, OUTPUT);    //  LED ��Ʈ �� �� ��� ���� 
	pinMode(LED_YELLOW_2, OUTPUT); 
	pinMode(LED_GREEN_3, OUTPUT);

	digitalWrite(LED_RED_1, LOW);  //  LED RED 1 �ɿ� LOW(0) ��� ����
	digitalWrite(LED_YELLOW_2, LOW); // ù �ɼ����δ� LOW�� �־� ���� ���·� �����Ѵ�.
	digitalWrite(LED_GREEN_3, LOW);

	while(1)
	{
		digitalWrite(LED_RED_1, HIGH);  //  LED RED 1 �ɿ� HIGH(1) ��� ����
		delay(500);						// 500ms ����
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

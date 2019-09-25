#include <wiringPi.h>              // GPIO Access Library 헤더파일 포함
#define LED_RED_1 25               // LED 포트 번호 정의
#define LED_YELLOW_2 24
#define LED_GREEN_3 23
 
int main()
{
	if(wiringPiSetupGpio() == -1)  // Wiring Pi의 GPIO를 사용하기 위한 설정
		return 1;

	pinMode(LED_RED_1, OUTPUT);    //  LED 포트 의 핀 출력 설정 
	pinMode(LED_YELLOW_2, OUTPUT); 
	pinMode(LED_GREEN_3, OUTPUT);

	digitalWrite(LED_RED_1, LOW);  //  LED RED 1 핀에 LOW(0) 출력 설정
	digitalWrite(LED_YELLOW_2, LOW); // 첫 옵션으로는 LOW을 주어 꺼진 상태로 시작한다.
	digitalWrite(LED_GREEN_3, LOW);

	while(1)
	{
		digitalWrite(LED_RED_1, HIGH);  //  LED RED 1 핀에 HIGH(1) 출력 설정
		delay(500);						// 500ms 지연
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

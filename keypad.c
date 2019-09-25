#include <wiringPi.h> // GPIO Access Library ������� ����

#define LED_PIN_1 23 // LED ��Ʈ �� ����
#define LED_PIN_2 24
#define LED_PIN_3 25

#define KEYPAD_PB1 6 // KEYPAD ��Ʈ �� ����
#define KEYPAD_PB2 12
#define KEYPAD_PB3 13

#define LED_ON 1 // LED ON/OFF ����
#define LED_OFF 0

#define MAX_LED_NUM 3 // LED ���� �� KEYPAD ��ư �� ����
#define MAX_KEY_BT_NUM 3

const int LedPinTable[3] = { 
	LED_PIN_1, LED_PIN_2, LED_PIN_3 // LED �� ���̺� ����
};

const int KeypadTable[3] = {
	KEYPAD_PB1, KEYPAD_PB2, KEYPAD_PB3 // KEYPAD �� ���̺� ����
};

/*KEYPAD ��ư ������ Ȯ���Ͽ�
nKeypadstate ���� ������ ���� ����*/
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


/*�ش��ϴ� LED ��ȣ��
ON/OFF ��� ������ Ȯ���Ͽ�
LED �ɿ� HIGH/LOW ��ȣ�� ���*/
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
	if(wiringPiSetupGpio() == -1) // Wiring Pi�� GPIO�� ����ϱ� ���� ����
		return 1;


	int i;
	int nKeypadstate;
	
	for(i=0; i<MAX_LED_NUM; i++){
		pinMode(LedPinTable[i], OUTPUT); // LED �� ��� ����
	}
	
	for(i=0; i<MAX_KEY_BT_NUM; i++){
		pinMode(KeypadTable[i], INPUT); // KEYPAD �� �Է� ����
	}

	while(1){
		nKeypadstate = KeypadRead(); // KEYPAD�κ��� ��ư �Է��� �о� ���¸� ������ ����

		for(i=0; i<MAX_KEY_BT_NUM; i++){  // KEYPAD ���� ������ Ȯ���Ͽ�
			if((nKeypadstate & (1<<i))){  // LED ON/OFF ����
				LedControl(i, LED_ON);
			}
			else{
				LedControl(i, LED_OFF);
			}
		}
	}
}


#include "include.h"

static bool fUartRxComplete = FALSE;
static uint8 UartRxBuffer[50];
uint8 Uart1RxBuffer[50];

static bool UartBusy = FALSE;

uint8 frameIndexSumSum[256];

void InitUart1(void)
{
  //bitSet(UCSR0A,U2X0);
  bitSet(UCSR0B,RXCIE0);//灏哢SART0 I/O 鏁版嵁瀵勫瓨鍣ㄧ殑RXCIE0浣嶇疆1锛屾帴鏀剁粨鏉熶腑鏂娇鑳�
  bitSet(UCSR0B,RXEN0); //bitSet锛坴alue锛宐it锛�= ((value) |= (1UL << (bit)))	鎺ユ敹浣胯兘			
  bitSet(UCSR0B,TXEN0); //鍙戦�佷娇鑳�				
  bitSet(UCSR0C,UCSZ01);//灏哢SART1娉㈢壒鐜囧瘎瀛樺櫒鐨刄CSZ01浣嶇疆1
  bitSet(UCSR0C,UCSZ00);//璁剧疆鏁版嵁甯у寘鍚殑鏁版嵁浣嶆暟,8浣�				
  UBRR0=(F_CPU/16/9600-1);//娉㈢壒鐜�9600 F_CPU绯荤粺棰戠巼 U2X0 = 0 锛屽紓姝ユ甯稿伐浣滄ā寮忥紝/16
}

void Uart1SendData(BYTE dat)
{
	loop_until_bit_is_set(UCSR0A,UDRE0);//姝ゅ嚱鏁扮畝鍗曞湴璋冪敤sbis鎸囦护鏉ユ祴璇曠鍙CSR0A鐨刄DRE0浣嶆槸鍚︾疆浣嶃��
	//UDRE0 涓� 1 璇存槑缂撳啿鍣ㄤ负绌猴紝宸插噯澶囧ソ杩涜鏁版嵁鎺ユ敹
	UDR0=dat;
}

void UART1SendDataPacket(uint8 dat[],uint8 count)
{
	uint8 i;
	for(i = 0; i < count; i++)
	{
		Uart1SendData(dat[i]);
	}
}

void McuToPCSendData(uint8 cmd,uint8 prm1,uint8 prm2)
{
	uint8 dat[8];
	uint8 datlLen = 2;
	switch(cmd)
	{
		default:
			datlLen = 2;
			break;
	}

	dat[0] = 0x55;
	dat[1] = 0x55;
	dat[2] = datlLen;
	dat[3] = cmd;
	dat[4] = prm1;
	dat[5] = prm2;
	UART1SendDataPacket(dat,datlLen + 2);
}




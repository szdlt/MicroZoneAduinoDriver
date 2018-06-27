#include "include.h"
//����:�������ֻ������Ƽ����޹�˾
//���ǵĵ���:lobot-zone.taobao.com

static bool UartBusy = FALSE;
uint16 BatteryVoltage;
PS2X ps2X;                                      
int TimeCounter  = 0;
int TimeCounter2 = 0;
unsigned short PSS_RX_VALUE = 0;
unsigned short PSS_RY_VALUE = 0;;

bool IsConnected  =  0;

char str_time1[5];
char str_time2[5];
char str_pulseC[10];
char str_pulseD[10];

int  PulseCounterC = 0;
int  PulseCounterD = 0;
#define  MOTORHIGHPWOER 1
#define DEBUG    0
void InitPS2()
{
	ps2X.config_gamepad(A2, A4, A3, A5);  //����PS2�ӿ� A2��IOΪclock,A4��IOΪcommand,A3��IOΪattention,A5��IOΪdata
}
void InitTimer2(void)		//100us@12.000MHz
{
	TCCR2A=0;
	TCCR2B=_BV(CS21)|_BV(CS20);
	TIMSK2=_BV(TOIE2);
	TCNT2=6;//(256-206)/500000=100us
	sei();
}

void InitTimer1(void)
{
	cli();
	TCCR1A=0; //�Ĵ���A������PWM�ģ���������ֻ��ʹ�ö�ʱ���ܣ���ʵ����Ҫ����
	TCCR1B=(1<<CS12)|(1<<CS10);//�Ĵ���B�����ö�ʱ���ܵģ��������õ���1024��Ƶ
	TCNT1=0XC2F6; //��������ֵ��1s��ʱ
//    TCNT1=0XFEC7;  // 20ms
	TIMSK1=(1<<TOIE1); //����ж�ʹ��
	sei(); //��ȫ���ж�
}




ISR(TIMER2_OVF_vect)
{
   TCNT2=6; //��ʱ��3�ж�  100us
   TimeCounter2++;
}

void ps2Handle() {                       //PS2 �ֱ� ����   
  static uint32_t Timer;                 //���徲̬����Timer�� ���ڼ�ʱ         
  if (Timer > millis())                 //Timer ���� millis���������е��ܺ�������ʱ���أ�//Timer С�� �����ܺ�����ʱ����������������
    return;
  ps2X.read_gamepad();                  //��ȡPS�ֱ���������
  Timer = millis() + 50;                    //?
}


ISR(TIMER1_OVF_vect)
{
    TCNT1=0xC2F6;//װֵ
 //   TCNT1=0xFEC7;//װֵ
    TimeCounter++;
	PulseCounterC = 0;
	PulseCounterD = 0;
	TimeCounter2 = 0;
}      



char str_pulseA[10];
unsigned long  PulsewidthA;

int PulseHandleA(void){
    static unsigned long micros_temp=0;
	static short Print_Count=0;
	unsigned long  microsT;
	microsT = micros();
     PulsewidthA = microsT-micros_temp > 10000 ? PulsewidthA : microsT-micros_temp;
	micros_temp = microsT;
	Print_Count++;
	if(0 &&Print_Count == 200){
	Print_Count = 0;	
	itoa(PulsewidthA, str_pulseA, 10);
    UART1SendDataPacket("PulsTime", sizeof("PulsTime"));
    UART1SendDataPacket(str_pulseA, strlen(str_pulseA) + 1);
    UART1SendDataPacket("\r\n", sizeof("\r\n"));
	}

}
char str_pulseB[10];
unsigned long  PulsewidthB;

int PulseHandleB(void){
    static unsigned long micros_temp=0;
	static short Print_Count=0;  
	unsigned long  microsT;
	microsT = micros();
    PulsewidthB = microsT-micros_temp > 10000 ? PulsewidthB : microsT-micros_temp;
	micros_temp = microsT;
	Print_Count++;
	if( 0 && Print_Count == 200){
	Print_Count = 0;
	itoa(PulsewidthB, str_pulseB, 10);
    UART1SendDataPacket("PulsBTime", sizeof("PulsBTime"));
    UART1SendDataPacket(str_pulseB, strlen(str_pulseB) + 1);
    UART1SendDataPacket("\r\n", sizeof("\r\n"));

	}

}
   unsigned long  PulsewidthC;
int PulseHandleC(void){   //����
    static unsigned long micros_temp=0;
	static short Print_Count=0;  
	unsigned long  microsT;
	microsT = micros();
    PulsewidthC = microsT-micros_temp > 5000 ? PulsewidthC : microsT-micros_temp;
	micros_temp = microsT;
	Print_Count++;
	if( 1 && Print_Count == 200){
	Print_Count = 0;
	itoa(PulsewidthC, str_pulseC, 10);
    UART1SendDataPacket("PulsCTime", sizeof("PulsCTime"));
    UART1SendDataPacket(str_pulseC, strlen(str_pulseC) + 1);
    UART1SendDataPacket("\r\n", sizeof("\r\n"));
	}
    if(PulsewidthC > 800 && PulsewidthC < 1000)
		 IsConnected = 0;
	else if(PulsewidthC > 1500 && PulsewidthC < 1700)
        IsConnected = 1;
	
   
}
int PulseHandleD(void){   // ����
    PulseCounterD++;
}
uint8 str_Y[] = {"y "};
uint8 str_X[] = {"x "};
unsigned short const ZeroAreaX  =  1470;
unsigned short const ZeroAreaY  =  1368;



#if MOTORHIGHPWOER

#if  Mega2560
#define  M0    6
#define  M0C0  7
#define  M0C1  8

#define  M1    9
#define  M1C0  10
#define  M1C1  11

#else
#define  M4  6
#define  M5  5
#define  M6  9
#define  M7  10
#endif

#else
#if  Mega2560
#define  M4  6
#define  M5  7
#define  M6  8
#define  M7  9
#else
#define  M4  6
#define  M5  5
#define  M6  9
#define  M7  10
#endif
#endif






void CarLTurn(void)
{
	analogWrite(M0, PSS_RX_VALUE);
	digitalWrite(M0C0,1);
	digitalWrite(M0C1,0);
	analogWrite(M1, PSS_RX_VALUE);
	digitalWrite(M1C0,1);
	digitalWrite(M1C1,0);
}

void CarRTurn(void)
{
   analogWrite(M0, PSS_RX_VALUE);
   digitalWrite(M0C0,0);
   digitalWrite(M0C1,1);
   analogWrite(M1, PSS_RX_VALUE);
   digitalWrite(M1C0,0);
   digitalWrite(M1C1,1);
}
void CarFoward(void){
  analogWrite(M0, PSS_RY_VALUE);
  digitalWrite(M0C0,1);
  digitalWrite(M0C1,0);
  analogWrite(M1, PSS_RY_VALUE);
  digitalWrite(M1C0,0);
  digitalWrite(M1C1,1);
}
void CarBack(){
   analogWrite(M0, PSS_RY_VALUE);
   digitalWrite(M0C0,0);
   digitalWrite(M0C1,1);
   analogWrite(M1, PSS_RY_VALUE);
   digitalWrite(M1C0,1);
   digitalWrite(M1C1,0);
}
	void CarStop(void)
{
    analogWrite(M0, 0);
    digitalWrite(M0C0,0);
    digitalWrite(M0C1,0);
    analogWrite(M1, 0);
    digitalWrite(M1C0,0);
    digitalWrite(M1C1,0);
}
void HighPowerMotorDriver(void)

{
      static uint32_t Timer;
      char str_x[5];
      char str_y[5];
      if (Timer > millis())
       return;
      if(IsConnected == 0){
	    CarStop();
        Timer > millis()+50;
        return;
	}
	 
	 PSS_RX_VALUE =  PulsewidthA > ZeroAreaX ?   (PulsewidthA- ZeroAreaX ):  (ZeroAreaX - PulsewidthA);
	 PSS_RY_VALUE =  PulsewidthB > ZeroAreaY ?   (PulsewidthB- ZeroAreaY ): (ZeroAreaY - PulsewidthB);

     if(PSS_RX_VALUE > 300)
	 	return;
	 else if(PSS_RX_VALUE > 255)
	 	{
		
		itoa(PSS_RX_VALUE, str_x, 10);
		#if DEBUG
		UART1SendDataPacket(str_X, sizeof(str_X));
		UART1SendDataPacket(str_x, strlen(str_x) + 1);
		#endif
	 	PSS_RX_VALUE = 254;
     	}

	  if(PSS_RY_VALUE > 300)
	 	return;
      else if(PSS_RY_VALUE > 254)
	 	PSS_RY_VALUE = 254;

	  if (PulsewidthA < ZeroAreaX - 45) {
	  	#if DEBUG
	    {
	  	static short Print_Count=0;
		if(1 || Print_Count == 100){
		Print_Count = 0;
		itoa(PSS_RX_VALUE, str_x, 10);
		UART1SendDataPacket(str_X, sizeof(str_X));
		UART1SendDataPacket(str_x, strlen(str_x) + 1);
			}
		Print_Count++;
		
	  	}
		#endif
	      CarLTurn();
	 }
	   
	  else if (PulsewidthA > ZeroAreaX + 45)
	  {
       #if DEBUG
		  {
		  static short Print_Count=0;
		  if(1 || Print_Count == 100){
		  Print_Count = 0;
		  itoa(PSS_RX_VALUE, str_x, 10);
		  UART1SendDataPacket(str_X, sizeof(str_X));
		  UART1SendDataPacket(str_x, strlen(str_x) + 1);
		  }
		  Print_Count++;
       	}
        #endif
	       CarRTurn();
	  	}
	  else{
	  if (PulsewidthB < ZeroAreaY - 45)
	  {
	    #if DEBUG
		itoa(PSS_RY_VALUE, str_y, 10);
		UART1SendDataPacket(str_Y, sizeof(str_Y));
		UART1SendDataPacket(str_y, strlen(str_y) + 1);
		UART1SendDataPacket("\r\n", sizeof("\r\n"));
	    #endif
		
	    CarFoward();
	  }
	  else if (PulsewidthB > ZeroAreaY + 45)
	  	{
	  	#if DEBUG
		itoa(PSS_RY_VALUE, str_y, 10);
		UART1SendDataPacket(str_Y, sizeof(str_Y));
		UART1SendDataPacket(str_y, strlen(str_y) + 1);
		UART1SendDataPacket("\r\n", sizeof("\r\n"));
	    #endif
		 CarBack();
	  }
	  else {
		CarStop();
	  }
      
    }
	  Timer = millis() + 50;
  
}

 #if !MOTORHIGHPWOER
void LowPowerMotorDriver(void)
{
	   static uint32_t Timer;
	   unsigned short PSS_RX_VALUE = 0;
	   unsigned short PSS_RY_VALUE = 0;;
	   char str_x[5];
	   char str_y[5];
	   if (Timer > millis())
		 return;

	 
	 PSS_RX_VALUE =  PulsewidthA > ZeroAreaX ?   (PulsewidthA- ZeroAreaX ):  (ZeroAreaX - PulsewidthA);
	 PSS_RY_VALUE =  PulsewidthB > ZeroAreaY ?   (PulsewidthB- ZeroAreaY ): (ZeroAreaY - PulsewidthB);

     if(PSS_RX_VALUE > 350)
	 	return;
	 else if(PSS_RX_VALUE > 255)
	 	{
		
		itoa(PSS_RX_VALUE, str_x, 10);
		#if DEBUG
		UART1SendDataPacket(str_X, sizeof(str_X));
		UART1SendDataPacket(str_x, strlen(str_x) + 1);
		#endif
	 	PSS_RX_VALUE = 255;
     	}

	  if(PSS_RY_VALUE > 350)
	 	return;
      else if(PSS_RY_VALUE > 255)
	 	PSS_RY_VALUE = 255;

      #if 1
	  if (PulsewidthA < ZeroAreaX - 45) {
	  	#if 1
	    {
	  	static short Print_Count=0;
		if(1 || Print_Count == 100){
		Print_Count = 0;
		itoa(PSS_RX_VALUE, str_x, 10);
		UART1SendDataPacket(str_X, sizeof(str_X));
		UART1SendDataPacket(str_x, strlen(str_x) + 1);
			}
		Print_Count++;
		#endif
	  	}
		analogWrite(M4, PSS_RX_VALUE);
		analogWrite(M5, 0);
		analogWrite(M7, PSS_RX_VALUE);
		analogWrite(M6, 0);
	  
	 
	 }
	   
	  else if (PulsewidthA > ZeroAreaX + 45)
	  {
       #if 1
		  {
		  static short Print_Count=0;
		  if(1 || Print_Count == 100){
		  Print_Count = 0;
		  itoa(PSS_RX_VALUE, str_x, 10);
		  UART1SendDataPacket(str_X, sizeof(str_X));
		  UART1SendDataPacket(str_x, strlen(str_x) + 1);
		  }
		  Print_Count++;
       	}
        #endif
	  analogWrite(M5, PSS_RX_VALUE);
		analogWrite(M4, 0);
		analogWrite(M6, PSS_RX_VALUE);
		analogWrite(M7, 0);
	  	}
	  else{
		   analogWrite(M5, 0);
		   analogWrite(M4, 0);
		   analogWrite(M6, 0);
		   analogWrite(M7, 0);
	  }
	  #endif
   #if 1
	  if (PulsewidthB < ZeroAreaY - 45)
	  {
	    #if DEBUG
		itoa(PSS_RY_VALUE, str_y, 10);
		UART1SendDataPacket(str_Y, sizeof(str_Y));
		UART1SendDataPacket(str_y, strlen(str_y) + 1);
		UART1SendDataPacket("\r\n", sizeof("\r\n"));
	    #endif
		analogWrite(M4, PSS_RY_VALUE);
		analogWrite(M5, 0);
		analogWrite(M7, PSS_RY_VALUE);
		analogWrite(M6, 0);
	
	  }
	  else if (PulsewidthB > ZeroAreaY + 45)
	  	{
	  	#if DEBUG
		itoa(PSS_RY_VALUE, str_y, 10);
		UART1SendDataPacket(str_Y, sizeof(str_Y));
		UART1SendDataPacket(str_y, strlen(str_y) + 1);
		UART1SendDataPacket("\r\n", sizeof("\r\n"));
	    #endif
		analogWrite(M5, PSS_RY_VALUE);
		analogWrite(M4, 0);
		analogWrite(M6, PSS_RY_VALUE);
		analogWrite(M7, 0);
	  }
	  else {
		analogWrite(M4, 0);
		analogWrite(M5, 0);
		analogWrite(M6, 0);
		analogWrite(M7, 0);
	  }
 #endif
	  Timer = millis() + 50;


}
#endif


void TaskRun(void)
{
	HighPowerMotorDriver();
}




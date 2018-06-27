#ifndef _APP_H_
#define _APP_H_


void InitPS2();
void InitTimer2(void);
void InitTimer1(void);
void InitUart2(void);
void Uart1SendData(BYTE dat);
int PulseHandleA();
int PulseHandleB();
int PulseHandleC();
int PulseHandleD();
void TaskRun(void);

#endif


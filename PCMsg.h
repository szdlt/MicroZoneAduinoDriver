#ifndef _PC_MSG_H_
#define _PC_MSG_H_

 //鎸囦护
#define CMD_MULT_SERVO_MOVE					3	//澶氫釜鑸垫満鐩稿悓鏃堕棿杩愬姩
#define CMD_FULL_ACTION_RUN					6
#define CMD_FULL_ACTION_STOP				7
#define CMD_FULL_ACTION_ERASE				8
#define CMD_ACTION_DOWNLOAD					25
 
 //瀛樻斁璧峰鍦板潃
#define MEM_LOBOT_LOGO_BASE					0L	//"LOBOT"瀛樻斁鍩哄湴鍧�锛岀敤浜庤瘑鍒槸鍚︽槸鏂癋LASH
#define MEM_FRAME_INDEX_SUM_BASE			4096L//姣忎釜鍔ㄤ綔缁勬湁澶氬皯鍔ㄤ綔锛屼粠杩欎釜鍦板潃寮�濮嬪瓨鏀撅紝鍏辫256涓姩浣滅粍
#define MEM_ACT_FULL_BASE					8192L//鍔ㄤ綔缁勬枃浠朵粠杩欎釜鍦板潃寮�濮嬪瓨鏀�
 
 //澶у皬
#define ACT_SUB_FRAME_SIZE					64L		//涓�涓姩浣滃抚鍗�64瀛楄妭绌洪棿
#define ACT_FULL_SIZE						16384L	//16KB,涓�濂楀畬鏁村姩浣滅粍鍗�16kb瀛楄妭

void InitUart1(void);
void UART1SendDataPacket(uint8 dat[],uint8 count);

void TaskPCMsgHandle(void);
void InitMemory(void);

#endif



#include "include.h"
const byte interruptPinA = 2;
const byte interruptPinB = 3;
const byte interruptPinC = 18;
const byte interruptPinD = 19;
void setup()
{
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(interruptPinA, INPUT_PULLUP);
  pinMode(interruptPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinA), PulseHandleA,  CHANGE);
  
  attachInterrupt(digitalPinToInterrupt(interruptPinB), PulseHandleB,  CHANGE);
  #if 1  
  pinMode(interruptPinC, INPUT_PULLUP);
//  pinMode(interruptPinD, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinC), PulseHandleC,  CHANGE);
//  attachInterrupt(digitalPinToInterrupt(interruptPinD), PulseHandleD,  RISING);
  #endif
//InitTimer2();
//InitTimer1();
  InitUart1();
}
void loop() 
{
   TaskRun(); 
}





#include <CapacitiveSensor.h>
#include <Keyboard.h>

unsigned long signal_len,t1,t2;   //time for which button is pressed
int inputPin = 2;                 //input pin for push button
int ledPin = 4;                   //outpu pin for LED
String code = "";                 //string in which one alphabet is stored

void setup()

{
  Serial.begin(9600);
  pinMode(inputPin, INPUT_PULLUP); //internal pullup resistor is used to simplify the circuit
  pinMode(ledPin,OUTPUT);
   //  初始化键盘控制:
    Keyboard.begin();
  
}

void loop()
{
  while (digitalRead(inputPin) == HIGH) {}
  t1 = millis();                                 //按键开始时间
  digitalWrite(ledPin, HIGH);                    //LED on while button pressed
  while (digitalRead(inputPin) == LOW) {}
  t2 = millis();                                 //按键结束时间
  digitalWrite(ledPin, LOW);                     //LED off on button release
  signal_len = t2 - t1;                          //按键时间差
   if (signal_len < 600 && signal_len > 50)      //50-600毫秒输出点
  {
      Keyboard.println(".");
  }
  else if (signal_len > 600)                     //600毫秒以上输出横
  {
     Keyboard.println("-");
  }
}

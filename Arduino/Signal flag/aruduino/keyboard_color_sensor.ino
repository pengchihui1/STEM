#include <CapacitiveSensor.h>
#include <Keyboard.h>

#define NO_SAMPLES 100u  
#define THRESHOLD  5u  
 
 // Sensor Connections  
 const byte S0  = 8;  
 const byte S1  = 9;  
 const byte S2  = 10;  
 const byte S3  = 11;  
 const byte Sout = 12;  
 uint16_t sumOfSamples = 0;  
 uint16_t redData = 0;  
 uint16_t greenData = 0;  
 uint16_t blueData = 0;  

unsigned long signal_len,t1,t2;   //time for which button is pressed
int inputPin = 2;                 //input pin for push button

void setup(){
  pinMode(S0, OUTPUT);  
  pinMode(S1, OUTPUT);  
  pinMode(S2, OUTPUT);  
  pinMode(S3, OUTPUT);  
  pinMode(Sout, INPUT);  
  // Setting frequency-scaling to 20%  
  digitalWrite(S0,HIGH);  
  digitalWrite(S1,LOW);  

  Serial.begin(9600);
  pinMode(inputPin, INPUT_PULLUP); //internal pullup resistor is used to simplify the circuit
    //  初始化键盘控制:
    Keyboard.begin();
  
}

void loop(){
  while (digitalRead(inputPin) == HIGH) {}      //按键开始
  while (digitalRead(inputPin) == LOW) {}       //按键结束
  
   int i = 0;  
  // Apply Red Filter  
  digitalWrite(S2,LOW);  
  digitalWrite(S3,LOW);  
  delay(1);  
  sumOfSamples = 0;  
  for (i=0; i < NO_SAMPLES; i++)  
  {  
   // Reading the Pulse Width  
   sumOfSamples += pulseIn(Sout, LOW);  
  }  
  redData = sumOfSamples/NO_SAMPLES;  
  delay(100);  
  // Apply Green Filter  
  digitalWrite(S2, HIGH);  
  digitalWrite(S3, HIGH);  
  delay(1);  
  sumOfSamples = 0;  
  for (i=0; i < NO_SAMPLES; i++)  
  {  
   // Reading the Pulse Width  
   sumOfSamples += pulseIn(Sout, LOW);  
  }  
  greenData = sumOfSamples/NO_SAMPLES;  
  delay(100);  
  // Apply Blue Filter  
  digitalWrite(S2, LOW);  
  digitalWrite(S3, HIGH);  
  delay(1);  
  sumOfSamples = 0;  
  for (i=0; i < NO_SAMPLES; i++)  
  {  
   // Reading the Pulse Width  
   sumOfSamples += pulseIn(Sout, LOW);  
  }  
  blueData = sumOfSamples/NO_SAMPLES;  
  delay(100);  
  //调用函数
  decide(redData,greenData,blueData);
  delay(100);  
}


void decide(int R,int G, int B){
  if(R>35 && R<40 && G>111 && G<124 && B>84 && B<93){
       Serial.println("红色"); //红
       Serial.println("*****");
       Keyboard.println("A");
       Keyboard.println(" ");
   }else if(R>169 && R<180 && G>181 && G<191 && B>134 && B<146){
       Serial.println("黑色");//黑
       Serial.println("****");
       Keyboard.println("B");
       Keyboard.println("  ");
  }else if(R>22 && R<28 && G>21 && G<27 && B>15 && B<20){
       Serial.println("白色");//白
       Serial.println("****");
       Keyboard.println("C");
       Keyboard.println("  ");
  }else{
       Serial.println("没有定义颜色");
       Serial.println("****");
  }
}
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
   
  if(R>32 && R<40 && G>107 && G<127 && B>80 && B<95){//红
       Keyboard.println("A");
   }else if(R>159 && R<180 && G>168 && G<191 && B>128 && B<146){//黑
       Keyboard.println("C");
  }else if(R>20 && R<28 && G>19 && G<27 && B>14 && B<20){//白
       Keyboard.println("D");
  }else  if(R>47 && R<57 && G>55 && G<65 && B>72 && B<83){//1 屎绿色
       Keyboard.println("E");
  }else if(R>90 && R<103 && G>62 && G<73 && B>73 && B<85){// 2  淡绿色
       Keyboard.println("G");
  }else if(R>55 && R<69 && G>122 && G<148 && B>74 && B<92){// 3  紫红色
       Keyboard.println("H");
  }else if(R>29 && R<39 && G>80 && G<97 && B>75 && B<93){// 4  橘黄色
       Keyboard.println("I");
  }else if(R>25 && R<32 && G>40 && G<47 && B>55 && B<67){// 5  黄色
       Keyboard.println("J");
  }else if(R>32 && R<40 && G>32 && G<39 && B>52 && B<63){// 6  黄绿色
       Keyboard.println("L");
  }else if(R>90 && R<100 && G>53 && G<60 && B>52 && B<60){// 7  墨绿色
       Keyboard.println("N");
  }else if(R>76 && R<91 && G>40 && G<50 && B>26 && B<35){// 8  青蓝色
       Keyboard.println("O");
  }else if(R>118 && R<151 && G>90 && G<110 && B>43 && B<54){// 9  深蓝色
       Keyboard.println("P");
  }else if(R>115 && R<142 && G>56 && G<70 && B>26 && B<35){// 10  蓝色
       Keyboard.println("S");
  }else if(R>88 && R<106 && G>122 && G<145 && B>58 && B<72){// 11  紫色
       Keyboard.println("U");
  }else if(R>133 && R<157 && G>114 && G<137 && B>54 && B<67){// 12  紫蓝色
       Keyboard.println("V");
  }else if(R>33 && R<41 && G>83 && G<102 && B>41 && B<54){// 13  粉色
       Keyboard.println("W");
  }
}
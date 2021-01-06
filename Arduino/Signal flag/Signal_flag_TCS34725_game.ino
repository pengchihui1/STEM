#include <Adafruit_TCS34725.h>
#include <Keyboard.h>
#include <Wire.h>

//TCS34725
//SCL to SCL
//SDA to SDA
//VIN to 5V
//GND to common GND

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);
uint16_t r, g, b, c;
int inputPin = 8;
const int interruptPin = 2;
volatile boolean state = false;

void isr() 
{
  state = true;
}

void setup(){
  Serial.begin(9600);
  pinMode(inputPin, INPUT_PULLUP);
  
  pinMode(interruptPin, INPUT_PULLUP); //TCS interrupt output is Active-LOW and Open-Drain
  attachInterrupt(digitalPinToInterrupt(interruptPin), isr, FALLING);

  // Set persistence filter to generate an interrupt for every RGB Cycle, regardless of the integration limits
  tcs.write8(TCS34725_PERS, TCS34725_PERS_NONE); 
  tcs.setInterrupt(true);
  Serial.flush();
}

void loop(){
  //2pins botton
  while (digitalRead(inputPin) == HIGH){}
  while (digitalRead(inputPin) == LOW){}
  tcs.getRawData(&r, &g, &b, &c);
  decide(r, g, b, c);
  Serial.flush();

  tcs.clearInterrupt();
  state = false;
}

void decide(uint16_t R, uint16_t G, uint16_t B, uint16_t C){
    if(R>460 && R<550 && G>136 && G<178 && B>138 && B<169){//红
       Keyboard.println("A");
   }else if(R>72 && R<107 && G>83 && G<119 && B>75 && B<109){//黑
       Keyboard.println("C");
  }else if(R>970 && R<1140 && G>1199 && G<1415 && B>1108 && B<1305){//白
       Keyboard.println("D");
  }else  if(R>362 && R<440 && G>150 && G<483 && B>199 && B<250){//1 屎绿色
       Keyboard.println("E");
  }else if(R>173 && R<213 && G>340 && G<400 && B>195 && B<238){// 2  淡绿色
       Keyboard.println("G");
  }else if(R>272 && R<323 && G>120 && G<154 && B>152 && B<190){// 3  紫红色
       Keyboard.println("H");
  }else if(R>548 && R<657 && G>226 && G<288 && B>163 && B<207){// 4  橘黄色
       Keyboard.println("I");
  }else if(R>838 && R<907 && G>644 && G<734 && B>288 && B<343){// 5  黄色
       Keyboard.println("J");
  }else if(R>637 && R<716 && G>812 && G<910 && B>325 && B<371){// 6  黄绿色
       Keyboard.println("L");
  }else if(R>188 && R<222 && G>125 && G<484 && B>299 && B<346){// 7  墨绿色
       Keyboard.println("N");
  }else if(R>232 && R<273 && G>242 && G<619 && B>593 && B<680){// 8  青蓝色
       Keyboard.println("O");
  }else if(R>97 && R<129 && G>185 && G<222 && B>335 && B<384){// 9  深蓝色
       Keyboard.println("P");
  }else if(R>127 && R<155 && G>358 && G<406 && B>576 && B<660){// 10  蓝色
       Keyboard.println("S");
  }else if(R>158 && R<191 && G>123 && G<162 && B>135 && B<266){// 11  紫色
       Keyboard.println("U");
  }else if(R>97 && R<133 && G>142 && G<181 && B>260 && B<306){// 12  紫蓝色
       Keyboard.println("V");
  }else if(R>193 && R<557 && G>186 && G<228 && B>304 && B<356){// 13  粉色
       Keyboard.println("W");
  }
}

/********颜色测试程序*******
 * Arduino型号：Arduino UNO
 **************************/

#include "SoftWire.h"
#include "Adafruit_APDS9960.h"

SoftWire sw(6,7);   //sda,scl
Adafruit_APDS9960 apds=Adafruit_APDS9960(sw);

#define RED   1
#define GREEN 2
#define BLUE  3
#define WHITE 4

int R_F = 13000;
int G_F = 19000;
int B_F = 25000;
int r_f = 768;
int g_f = 1024;
int b_f = 1280;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //enable color sensign mode
  apds.enableColor(true);

  delay(500);
}

int colorDetect()
{
  uint16_t r, g, b, c;
  int t;
  String s;
  //wait for color data to be ready
  while(!apds.colorDataReady()){
    delay(5);
  }
  apds.getColorData(&r, &g, &b, &c);

  r = map(r, r_f, R_F, 0, 255);
  g = map(g, g_f, G_F, 0, 255);
  b = map(b, b_f, B_F, 0, 255);
     Serial.println("--------");
     Serial.print("r=");
     Serial.println(r);
     Serial.print("g=");
     Serial.println(g);
     Serial.print("b=");
     Serial.println(b);
     if(r <280 & r >249 & g>125 & g<145 & b< 175 & b>150 ){  //  255 0 12  A  红色

         s="A";
     }else if (r<275 & r>250 & g>125 & g<145 &b>140 & b<160){    // 255 0 138  C  淡红

         s="C";
     }else if(g<45 & g>20 & b>30 & b< 48){ // 96 0 255 D   紫色

         s="D";
     }else if(g<45 & g>28 & b>40 & b<50){      //210 0 255   E   紫红

         s="E";
     }else if( b < 53 & b > 38 & g>25 & g<45){      //0 138 255  G 淡蓝

         s="G";
     }else if(g<40& g>22 & b>30 & b<45){      //0 12 255  H  深蓝

         s="H";
     }else if(r >30 & r<50 & b>40 & b<50){      //0 246 255 I 浅蓝

         s="I";
     }else if(b<50& b>35 & g>70 & g<80 ){      //0 255 156  J  浅绿

         s="J";
     }else if(b<70 & b>50 & g>80 & g<100){      //255 255 255 L  白色

         s="L";
     }else if(r<135 & r>115 & g>70 & g<90 & b>40 & b<60 ){      //210 255 0 N   黄色

         s="N";
     }else if(g<30 & g>10 & b<65 & b>50){      //255 186 0 O   桔浅黄

         s="O";
     }else if(b<25 & b>12 & g<40 & g>20){      //255 90 0 P  橘色

         s="P";
     }else if(b<20 & b>5 & g<28 & g>9){       // 146 33 73 S   暗红

         s="S";
     }else if(b<20 & b>10 & g>20 & g< 40){      //33 146 67  U  深绿色

         s="U";
     }else if(b>10 & b<30 & g>20 & g<40){      //145 146 33 V  草绿色

        s="V";
     }else if(r<35 & r> 18 & g>5 & g<20){     //0 0 0  W  黑色

         s="W";
     }else{
         s="M";
     }
     Serial.println(s);

     delay(500);


}

void loop() {
  colorDetect();
  delay(200);
}

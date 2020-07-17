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
  //wait for color data to be ready
  while(!apds.colorDataReady()){
    delay(5);
  }
  apds.getColorData(&r, &g, &b, &c);

  r = map(r, r_f, R_F, 0, 255);  
  g = map(g, g_f, G_F, 0, 255);
  b = map(b, b_f, B_F, 0, 255);
  
  //Find the largest value in R, G, B. For example, the maximum is R means that the object is Red
  if (r > g)
    t = RED;
  else
    t = GREEN;
  if (t == GREEN && g < b)
    t = BLUE;
  if (t == RED && r < b)
    t = BLUE;

  //Returns the color only if the RGB value is greater than 30, otherwise returns 0
  if(t == BLUE && b > 50)
  {
    Serial.println("Blue");
    return t;
  }
  else if(t == GREEN && g > 50)
  {
    Serial.println("Green");
    return t;
  }
  else if(t == RED && r > 50)
  {
    Serial.println("Red");
    return t;
  }
  else 
    return 0;
  return 0;
}

void loop() {
  colorDetect();
  delay(200);
}

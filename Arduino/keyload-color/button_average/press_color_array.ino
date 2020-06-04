/*
  Keyboard Message test

  For the Arduino Leonardo and Micro.

  Sends a text string when a button is pressed.

  The circuit:
  - pushbutton attached from pin 4 to +5V
  - 10 kilohm resistor attached from pin 4 to ground

  created 24 Oct 2011
  modified 27 Mar 2012
  by Tom Igoe
  modified 11 Nov 2013
  by Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardMessage
*/


#include "SoftWire.h"
#include "Adafruit_APDS9960.h"

SoftWire sw(6,7);   //sda,scl
Adafruit_APDS9960 apds=Adafruit_APDS9960(sw);

int R_F = 13000;
int G_F = 19000;
int B_F = 25000;
int r_f = 768;
int g_f = 1024;
int b_f = 1280;

int num=0;
int r_jj[0];
int g_jj[0];
int b_jj[0];

const int buttonPin = 4;          // input pin for pushbutton
int previousButtonState = HIGH;   // for checking the state of a pushButton
int counter = 0;                  // button push counter



void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);

    if(!apds.begin()){
        Serial.println("failed to initialize device! Please check your wiring.");
    }
    else Serial.println("Device initialized!");

    //enable color sensign mode
    apds.enableColor(true);

    // make the pushButton pin an input:
    pinMode( buttonPin , INPUT);
    // initialize control over the keyboard:

}


void colorDetect(){
    uint16_t r, g, b, c;
    // constant variable indicating size of array
    //wait for color data to be ready
    while(!apds.colorDataReady()){
        delay(5);
    }
    apds.getColorData(&r, &g, &b, &c);
    r = map(r, r_f, R_F, 0, 255);
    g = map(g, g_f, G_F, 0, 255);
    b = map(b, b_f, B_F, 0, 255);
    r_jj[num]=r;
    g_jj[num]=g;
    b_jj[num]=b;
    Serial.println(num);
    num++;
}
//Average

double avg(int kk[ ]){
    int sumber=0;
    int length=sizeof(kk)/sizeof(kk[0]);
    for(int i=0;i<length;i++){
          sumber=sumber+kk[i];
    }
    double avgs=(double)sumber/length;
    return avgs;
}


int n=50;
void loop() {
       int buttonState = digitalRead(buttonPin);
       if(buttonState == HIGH) {
       counter++;
       Serial.println(counter);
      // for(int i=0;i<n;i++){
           // colorDetect();
       //}
    }else if(buttonState == LOW) {
         Serial.println("A");
        //Serial.println(avg(r_jj));
        //Serial.println(avg(g_jj));
        //Serial.println(avg(b_jj));
    }else {
        Serial.println("other");
    }
    delay(1000);
}
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
 void setup()   
 {  
  pinMode(S0, OUTPUT);  
  pinMode(S1, OUTPUT);  
  pinMode(S2, OUTPUT);  
  pinMode(S3, OUTPUT);  
  pinMode(Sout, INPUT);  
  // Setting frequency-scaling to 20%  
  digitalWrite(S0,HIGH);  
  digitalWrite(S1,LOW);  
  Serial.begin(9600);  
 }  
 void loop()   
 {  
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
  // Serial.print("R = ");  
  // Serial.print(redData);  
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
  // Serial.print(" G = ");  
  // Serial.print(greenData);  
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
  // Serial.print(" B = ");  
  // Serial.print(blueData);  
  delay(100);  
  //调用函数
  decide(redData,greenData,blueData);
  delay(1000);  
 }  
 
void decide(int R,int G, int B){
  //红
  if(R>35 && R<40 && G>115 && G<124 && B>84 && B<93){
    Serial.println("红");
  }
  //黑
  if(R>171 && R<180 && G>183 && G<191 && B>138 && B<144){
   Serial.println("黑");
  }
  //白
  if(R>22 && R<28 && G>21 && G<27 && B>15 && B<20){
   Serial.println("白");
  }
}

 
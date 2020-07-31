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
 void loop()   {  
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
  delay(200);  
 }  
 
void decide(int R,int G, int B){
  Serial.print(R);
  Serial.print("---");
  Serial.print(G);
  Serial.print("---");
  Serial.println(B);
  //14 红色
  if(R>32 && R<40 && G>107 && G<124 && B>80 && B<93){
    Serial.println("14");
  }
  //15 黑色
  if(R>159 && R<180 && G>168 && G<191 && B>128 && B<146){
    Serial.println("15");
  }
  //16 白色
  if(R>20 && R<28 && G>19 && G<27 && B>14 && B<20){
   Serial.println("16");
  }
  //1 屎绿色
  if(R>47 && R<57 && G>55 && G<65 && B>72 && B<83){
   Serial.println("1");
  }
  // 2  淡绿色
  if(R>92 && R<103 && G>62 && G<73 && B>73 && B<85){
   Serial.println("2");
  }
  // 3  紫红色
  if(R>55 && R<69 && G>122 && G<148 && B>74 && B<92){
   Serial.println("3");
  }
  // 4  橘黄色
   if(R>29 && R<39 && G>80 && G<97 && B>75 && B<93){
   Serial.println("4");
  }
  // 5  黄色
   if(R>25 && R<31 && G>40 && G<47 && B>55 && B<64){
   Serial.println("5");
  }
  // 6  黄绿色
  if(R>32 && R<40 && G>32 && G<39 && B>52 && B<63){
   Serial.println("6");
  }
  // 7  墨绿色
  if(R>90 && R<100 && G>53 && G<60 && B>52 && B<60){
   Serial.println("7");
  }
  // 8  青蓝色
  if(R>78 && R<88 && G>42 && G<50 && B>28 && B<34){
   Serial.println("8");
  }
  // 9  深蓝色
  if(R>123 && R<137 && G>87 && G<96 && B>37 && B<47){
   Serial.println("9");
  }
  // 10  蓝色
  if(R>115 && R<130 && G>56 && G<65 && B>26 && B<33){
   Serial.println("10");
  }
  // 11  紫色
   if(R>89 && R<99 && G>124 && G<136 && B>60 && B<68){
   Serial.println("11");
  }
  // 12  紫蓝色
   if(R>136 && R<154 && G>114 && G<130 && B>54 && B<63){
   Serial.println("12");
  }
  // 13  粉色
 if(R>33 && R<41 && G>83 && G<102 && B>41 && B<54){
   Serial.println("13");
  }
}


 
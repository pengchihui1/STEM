
// the used PINs
const int s0=2;
const int s1=3;
const int s2=4;
const int s3=5;
const int sensorData=7;

int dataR=0;
int dataG=0;
int dataB=0;

void setup() 
{
   pinMode(s0,OUTPUT);
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(sensorData,INPUT);
   Serial.begin(9600);

   digitalWrite(s0,HIGH);
   digitalWrite(s1,HIGH);
   
}

void loop()
{
   digitalWrite(s2,LOW);
   digitalWrite(s3,LOW);
   dataR=pulseIn(sensorData,LOW);
   delay(20);

   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   dataG=pulseIn(sensorData,LOW);
   delay(20);

   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   dataB=pulseIn(sensorData,LOW);
   delay(20);
   Serial.print("R===");
   Serial.print(dataR);
   Serial.print("G===");
   Serial.print(dataG);
   Serial.print("B===");
   Serial.println(dataB);
   delay(1000);
   if(isRed())
   {
    Serial.println("this is the RED color");
  
   }
   if(isBlue())
   {
    Serial.println("this is the Blue color");
   
   }
   if(isGreen())
   {
    Serial.println("this is the GREEN color");
  
   }
   if(isYellow())
   {
    Serial.println("this is the YELLOW color");
   
   }
}

bool isRed()
{
  if((dataR<18 && dataR>12) && (dataG<49 && dataG>43) && (dataB<70 && dataB>64))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool isGreen()
{
  if((dataR<53 && dataR>47) && (dataG<44 && dataG>38) && (dataB<34 && dataB>28))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool isBlue()
{
  if((dataR<103 && dataR>90) && (dataG<41 && dataG>27) && (dataB<88 && dataB>73))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool isYellow()
{
  if((dataR<14 && dataR>8) && (dataG<31 && dataG>25) && (dataB<19 && dataB>13))
  {
    return true;
  }
  else
  {
    return false;
  }
}

int LDR_pin = A5;   //定义灰度模拟口 A5
void setup(){
  //设置波特率9600
  Serial.begin(9600);
}
int previousGrayScale;
int GrayScale;
int num=0;
void loop(){ 
    while (analogRead(LDR_pin)) {        //存在模拟值时
    int value=analogRead(LDR_pin);       //模拟值
    if(num==0){
        previousGrayScale=value;
        GrayScale=value;
    }else if(num==1){
        GrayScale=value; 
    }else{  
         previousGrayScale= GrayScale;
         GrayScale=value;   
         int val=GrayScale-previousGrayScale;  //  绝对值 0-10 
         compare(previousGrayScale,GrayScale,val);
    }
    num++;
    delay(200);
   }
}

void compare(int before,int after,int dff){  
     if(dff<-4 && dff>-100){
           Serial.print("顺");
           Serial.println(dff);
       }else if(dff>4 && dff<100){
           Serial.print("逆");
           Serial.println(dff);
       }else if(dff<-100){
           Serial.print("逆");
           Serial.println(dff);
       }else if(dff>100){
           Serial.print("顺");
           Serial.println(dff);
       }
}










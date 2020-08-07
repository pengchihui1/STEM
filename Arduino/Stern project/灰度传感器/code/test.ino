int LDR_pin = A5;   //定义灰度模拟口 A5
void setup(){
  Serial.begin(9600); //设置波特率9600
}
int previousGrayScale=0; //前一个值
int GrayScale=0; //当前值
void loop(){   
       previousGrayScale=GrayScale;      //前一个值当前值
       GrayScale=analogRead(LDR_pin);    //当前值为最新的值
       compare(previousGrayScale,GrayScale);
       delay(100); 
}
void compare(int before,int after){  //白过度到黑的过程 读取的值越来越小 顺时针  小-大=负数
     int dff=after-before;
     if(dff<-5 && dff>-100){        //白过度到黑的过程  变化大于5时  
           Serial.print("顺");
           Serial.println(dff);
       }else if(dff>5 && dff<100){    //黑过度到白  变化大于5时 
           Serial.print("逆");
           Serial.println(dff);
       }else if(dff<-100){     //黑色跳白色 很快时
           Serial.print("逆");
           Serial.println(dff);
       }else if(dff>100){
           Serial.print("顺");  //白色跳黑色  很快时
           Serial.println(dff);
       }
}

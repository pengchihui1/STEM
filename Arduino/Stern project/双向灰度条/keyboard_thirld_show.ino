#include <Keyboard.h>
int pinA = A5;   //定义灰度模拟   外部传感器(A)
int pinB = A4;   //定义灰度模拟   内部传感器(B)
void setup(){
  Keyboard.begin(); //  初始化键盘控制:
  Serial.begin(9600); //设置波特率9600
}
int previousGrayScaleA=0; //A传感器前一个值
int GrayScaleA=0; //A传感器当前值

int previousGrayScaleB=0; //前一个值
int GrayScaleB=0; //当前值

void loop(){   
       previousGrayScaleA=GrayScaleA;      //A传感器 前一个值当前值
       GrayScaleA=analogRead(pinA);        //A传感器 当前值为最新的值
	   
	    previousGrayScaleB=GrayScaleB;      //B传感器 前一个值当前值
	    GrayScaleB=analogRead(pinB);        //B传感器 当前值为最新的值
	   
       compare(previousGrayScaleA,GrayScaleA,previousGrayScaleB,GrayScaleB);
       delay(100); 
}

void compare(int beforeA,int nowA,int beforeB,int nowB){  
	   //黑过度到白
		 if(nowA>=395 && nowA<=510){           //外部的传感器(A)在395-510   内部传感器在黑白中间线的两侧   信外部的传感器(A)
		     contrast(beforeA,nowA);
		 }else if(nowB>=395 && nowB<=510){    //内部的传感器(B)在395-510    外部传感器在黑白中间线的两侧   信外部的传感器(B)
			 	 contrast(beforeB,nowB);
		 }else if((nowA>200 && nowA<395)||(nowA>510 && nowA<750)){    //外部的传感器(A)在200-395 510-750    信外部的传感器(A)
			   contrast(beforeA,nowA);
		 }
}

void contrast(int prev,int after){
	int dff=after-prev;
	if(dff>5 ){    
		    Serial.println("顺");
				Keyboard.println("A");
				// Keyboard.println(KEY_RIGHT_ARROW);  //右键  
	  }else if(dff<-5){
			 Serial.println("逆");  
			 Keyboard.println("B");
				// Keyboard.println(KEY_LEFT_ARROW);  //左键       
	  }
	
}

#include <Keyboard.h>
int pinA = A2;   //定义灰度模拟   A传感器
int pinB = A4;   //定义灰度模拟   B传感器
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
	
		 if(nowA>350 && nowA<450){           //A传感器在350-450   相信B
		 
			 contrast(beforeB,nowB);
			 
		 }else if(nowB>350 && nowA<nowB){    //B传感器在350-450   相信A
		 
			  contrast(beforeA,nowA);
			  
		 }else if(nowA>=450 && nowA<=550){    //A传感器在450-550  相信A
			  
			 contrast(beforeA,nowA);
			 
		 }else if(nowA>=250 && nowA<=350 ){   //A传感器在250-350  相信A
		   
		      contrast(beforeA,nowA);
			 
		 } 
}

void contrast(int prev,int after){
	//黑过度到白
	int dff=after-prev;
	if(dff<-5){
	        Keyboard.press(KEY_LEFT_ARROW);   //按下方向左鍵  逆方向
	  }else if(dff>5 ){    
		   Keyboard.press(KEY_RIGHT_ARROW);  //按下方向右鍵  顺方向 
	  }
}

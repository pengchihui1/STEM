#include <Keyboard.h>
#include <MPU6050.h>      //MPU6050的库文件
#include <Wire.h>        //IIC通讯库文件

int pinA = A5;   //定义灰度模拟   外部传感器(A)
int pinB = A4;   //定义灰度模拟   内部传感器(B)

MPU6050 mpu6050;     //实例化一个MPU6050对象，对象名称为mpu6050
int16_t ax, ay, az, gx, gy, gz;     //定义三轴加速度，三轴陀螺仪的变量

float AngleX;   //角度变量
float AngleY;   //角度变量
float AngleZ;   //角度变量
int16_t Gyro_x;   //角速度变量

int previousGrayScaleA=0; //A传感器前一个值
int GrayScaleA=0; //A传感器当前值

int previousGrayScaleB=0; //前一个值
int GrayScaleB=0; //当前值

void setup(){
	Wire.begin();    //加入 I2C 总线序列
	mpu6050.initialize();   //初始化MPU6050
  Keyboard.begin();    //  初始化键盘控制:
  Serial.begin(9600); //设置波特率9600
}

void loop(){   
        previousGrayScaleA=GrayScaleA;      //A传感器 前一个值当前值
        GrayScaleA=analogRead(pinA);        //A传感器 当前值为最新的值
	   
	      previousGrayScaleB=GrayScaleB;      //B传感器 前一个值当前值
	      GrayScaleB=analogRead(pinB);        //B传感器 当前值为最新的值
	   
        compareColor(previousGrayScaleA,GrayScaleA,previousGrayScaleB,GrayScaleB); //方向判断
			 
			  mpu6050.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);     //IIC获取MPU6050六轴数据 ax ay az gx gy gz
				AngleX = atan2(ay , az) * (180/ PI);           //弧度转角度计算公式,负号为方向处理
				AngleY = atan2(ax , az) * (180/ PI);           //弧度转角度计算公式,负号为方向处理
				compareAngle(AngleY);

       delay(100); 
}
//黑白过度处理
void compareColor(int beforeA,int nowA,int beforeB,int nowB){  
	   //黑过度到白
		 if(nowA>=395 && nowA<=510){           //外部的传感器(A)在395-510   内部传感器在黑白中间线的两侧   信外部的传感器(A)
		     contrast(beforeA,nowA);
		 }else if(nowB>=395 && nowB<=510){    //内部的传感器(B)在395-510    外部传感器在黑白中间线的两侧   信外部的传感器(B)
			 	 contrast(beforeB,nowB);
		 }else if((nowA>200 && nowA<395)||(nowA>510 && nowA<750)){    //外部的传感器(A)在200-395 510-750    信外部的传感器(A)
			   contrast(beforeA,nowA);
		 }
}
//方向
void contrast(int prev,int after){
	int dff=after-prev;
	if(dff>5 ){    
				Keyboard.press(KEY_RIGHT_ARROW);//右键  
				Keyboard.release(KEY_LEFT_ARROW); 
				// Keyboard.release(KEY_RIGHT_ARROW);  
	  }else if(dff<-5){
				Keyboard.press(KEY_LEFT_ARROW); //左键
				Keyboard.release(KEY_RIGHT_ARROW);     
				// Keyboard.release(KEY_LEFT_ARROW);  
	  }else{
				Keyboard.release(KEY_RIGHT_ARROW);  
				Keyboard.release(KEY_LEFT_ARROW);  
		}
}
//速度
void compareAngle(float y){
   if(y>-45 &&  y<=-15){
        Keyboard.println(1);
   }else if(y>-15 &&  y<=15){
        Keyboard.println(2);
   }else if(y>15 && y<=45){
        Keyboard.println(3);
   }else if(y>45 && y<=75){
        Keyboard.println(4);
   }else if(y>75 && y<=105){
        Keyboard.println(5);
   }else if(y>105 && y<=135){
        Keyboard.println(6);
   }else if(y>135&& y<=165){
        Keyboard.println(7);
   }else if(y>165 && y<=180 || y< -165 && y>-180 ){
        Keyboard.println(8);
   }else if(y<=-135 && y>=-165){
        Keyboard.println(9);
   }
}
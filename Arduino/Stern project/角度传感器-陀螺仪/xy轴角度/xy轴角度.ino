#include <MPU6050.h>      //MPU6050的库文件
#include <Wire.h>        //IIC通讯库文件

MPU6050 mpu6050;     //实例化一个MPU6050对象，对象名称为mpu6050
int16_t ax, ay, az, gx, gy, gz;     //定义三轴加速度，三轴陀螺仪的变量

float AngleX;   //角度变量
float AngleY;   //角度变量
float AngleZ;   //角度变量
int16_t Gyro_x;   //角速度变量

void setup() 
{
  // 加入I2C总线
  Wire.begin();                            //加入 I2C 总线序列
  Serial.begin(9600);                       //开启串口，设置波特率为9600
  delay(1500);
  mpu6050.initialize();                       //初始化MPU6050
  delay(500);
}

void loop() 
{
  mpu6050.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);     //IIC获取MPU6050六轴数据 ax ay az gx gy gz
  AngleX = atan2(ay , az) * (180/ PI);           //弧度转角度计算公式,负号为方向处理
  AngleY = atan2(ax , az) * (180/ PI);           //弧度转角度计算公式,负号为方向处理
  compare(AngleX);
  delay(1000);
}


void compare(float y){
   Serial.println(y);
   if(y>-45 &&  y<=-15){
      Serial.println("倒退全速");
   }else if(y>-15 &&  y<=15){
       Serial.println("倒退半速");
   }else if(y>15 && y<=45){
       Serial.println("倒退慢速");
   }else if(y>45 && y<=75){
       Serial.println("倒退微速");
   }else if(y>75 && y<=105){
       Serial.println("停止");
   }else if(y>105 && y<=135){
       Serial.println("前进微速");
   }else if(y>135&& y<=165){
       Serial.println("前进慢速");
   }else if(y>165 && y<=180 || y< -165 && y>-180 ){
       Serial.println("前进半速");
   }else if(y<=-135 && y>=-165){
       Serial.println("前进全速");
   }
}
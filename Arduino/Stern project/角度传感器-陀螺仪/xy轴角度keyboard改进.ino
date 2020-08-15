#include <MPU6050.h>      //MPU6050的库文件
#include <Wire.h>        //IIC通讯库文件
#include <Keyboard.h>

MPU6050 mpu6050;     //实例化一个MPU6050对象，对象名称为mpu6050
int16_t ax, ay, az, gx, gy, gz;     //定义三轴加速度，三轴陀螺仪的变量

float AngleX;   //角度变量
float AngleY;   //角度变量
float AngleZ;   //角度变量
int16_t Gyro_x;   //角速度变量

void setup() {
  Wire.begin();                            //加入 I2C 总线序列
  Serial.begin(9600);                       //开启串口，设置波特率为9600
  delay(100);
  mpu6050.initialize();                       //初始化MPU6050
  delay(100);
  Keyboard.begin(); //  初始化键盘控制

}

void loop() {
  mpu6050.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);     //IIC获取MPU6050六轴数据 ax ay az gx gy gz
  AngleX = atan2(ay , az) * (180/ PI);           //弧度转角度计算公式,负号为方向处理
  AngleY = atan2(ax , az) * (180/ PI);           //弧度转角度计算公式,负号为方向处理
  compare(AngleX);
  delay(300);
}

void compare(float y){
   if(y>-33.5 &&  y<=-3){ //倒退全速
        Keyboard.println(1);
   }else if(y>-3 &&  y<=21.5){ //倒退半速
        Keyboard.println(2);
   }else if(y>21.5 && y<=45.5){//倒退慢速
        Keyboard.println(3);
   }else if(y>45.5 && y<=74){//倒退微速
        Keyboard.println(4);
   }else if(y>74 && y<=101.5){//停止
        Keyboard.println(5);
   }else if(y>101.5 && y<=125.5){//前进微速
        Keyboard.println(6);
   }else if(y>125.5&& y<=149.5){//前进慢速
        Keyboard.println(7);
   }else if(y>149.5 && y<=174 ){//前进半速
        Keyboard.println(8);
   }else if(y>1745 && y<=180||y>=-180&&y>-155.5){//前进全速
        Keyboard.println(9);
   }
}



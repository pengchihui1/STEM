#include <MPU6050.h>      //MPU6050的库文件
#include <Wire.h>        //IIC通讯库文件

MPU6050 mpu6050;     //实例化一个MPU6050对象，对象名称为mpu6050
int16_t ax, ay, az, gx, gy, gz;     //定义三轴加速度，三轴陀螺仪的变量

float AngleX;   //角度变量 
float AngleY;   //角度变量
float AngleZ;   //角度变量
int16_t GyrogX,GyrogY,GyrogZ;   //角速度变量

//一阶滤波  
float K1 =0.05; // 对加速度计取值的权重  
//float dt=20*0.001;//注意：dt的取值为滤波器采样时间  
float angle1;//一阶滤波角度输出  
//二阶滤波  
float K2 =0.2; // 对加速度计取值的权重  
float x1,x2,y1;//运算中间变量  
//float dt=20*0.001;//注意：dt的取值为滤波器采样时间  
float angle2;//er阶滤波角度输出  

//卡尔曼滤波参数与函数  
float dt=0.001;//注意：dt的取值为kalman滤波器采样时间  
float angle, angle_dot;//角度和角速度  
float P[2][2] = {{ 1, 0 },  
                 { 0, 1 }};  
float Pdot[4] ={ 0,0,0,0};  
float Q_angle=0.001, Q_gyro=0.005; //角度数据置信度,角速度数据置信度  
float R_angle=0.5 ,C_0 = 1;  
float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;  

void setup() {
  // 加入I2C总线
  Wire.begin();                            //加入 I2C 总线序列
  Serial.begin(9600);                       //开启串口，设置波特率为9600
  delay(100);
  mpu6050.initialize();                       //初始化MPU6050
  delay(100);
}

void loop() {
    mpu6050.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);     //IIC获取MPU6050六轴数据 ax ay az gx gy gz
    AngleX=angles(ax,ay,az,1);    //计算与x轴夹角  
    GyrogX=-gy/131.00;            //x轴计算角速度  gy正负都无影响
    AngleY=angles(ax,ay,az,2);    //计算与Y轴夹角  
    GyrogY=-gx/131.00;            //Y轴计算角速度  
    AngleZ=angles(ax,ay,az,0);    //计算与Z轴夹角  
    GyrogZ=-gz/131.00;            //Y轴计算角速度  
    float value= getangle(AngleX, GyrogX);
    compare(value);
    delay(100);
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

double angles(float x,float y,float z,int dir ){
   float temp;
   float res=0;
   switch(dir){
       case 0: //自然Z轴的角度
          temp=sqrt((x*x+y*y))/z;
          res=atan(temp);
          break;
       case 1://自然X轴的角度
          temp=x/sqrt((y*y+z*z));
          res=atan(temp);
          break;
       case 2://自然Y轴的角度
          temp=y/sqrt((x*x+z*z));
          res=atan(temp);
          break;

   }
   return res*(180/ PI);//把弧度转换成角度
}

float getangle(double angleAx,double gyroGy){  
    Yijielvbo(angleAx,gyroGy);//一阶滤波  
    Erjielvbo(angleAx,gyroGy);//二阶滤波  
    return  Kalman_Filter(angleAx,gyroGy);   //卡尔曼滤波  
} 


//一阶滤波  
void Yijielvbo(float angle_m, float gyro_m)  {  
    angle1 = K1 * angle_m+ (1-K1) * (angle1 + gyro_m * dt);  
}  
 //二阶滤波   
void Erjielvbo(float angle_m,float gyro_m)  {  
    x1=(angle_m-angle2)*(1-K2)*(1-K2);  
    y1=y1+x1*dt;  
    x2=y1+2*(1-K2)*(angle_m-angle2)+gyro_m;  
    angle2=angle2+ x2*dt;  
} 

//卡尔曼滤波  
float Kalman_Filter(float angle_m, float gyro_m){ //angleAx 和 gyroGy   
        angle+=(gyro_m-q_bias) * dt;  
        angle_err = angle_m - angle;  
        Pdot[0]=Q_angle - P[0][1] - P[1][0];  
        Pdot[1]=- P[1][1];  
        Pdot[2]=- P[1][1];  
        Pdot[3]=Q_gyro;  
        P[0][0] += Pdot[0] * dt;  
        P[0][1] += Pdot[1] * dt;  
        P[1][0] += Pdot[2] * dt;  
        P[1][1] += Pdot[3] * dt;  
        PCt_0 = C_0 * P[0][0];  
        PCt_1 = C_0 * P[1][0];  
        E = R_angle + C_0 * PCt_0;  
        K_0 = PCt_0 / E;  
        K_1 = PCt_1 / E;  
        t_0 = PCt_0;  
        t_1 = C_0 * P[0][1];  
        P[0][0] -= K_0 * t_0;  
        P[0][1] -= K_0 * t_1;  
        P[1][0] -= K_1 * t_0;  
        P[1][1] -= K_1 * t_1;  
        angle += K_0 * angle_err; //最优角度  
        q_bias += K_1 * angle_err;  
        angle_dot = gyro_m-q_bias;//最优角速度  
        
        return angle;  
} 
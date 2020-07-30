/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         color_recognition.c
* @author       Danny
* @version      V1.0
* @date         2017.07.26
* @brief        颜色识别实验
* @details
* @par History  见如下说明
*
*/
//定义引脚
int LDR_pin = A5;      //定义光敏电阻模拟口A5

int Intensity = 0;     //光照度数值

/**
* Function       setup
* @author        Danny
* @date          2017.07.25
* @brief         初始化配置
* @param[in]     void
* @retval        void
* @par History   无
*/
void setup()
{
  Serial.begin(9600);//设置波特率9600
}

/**
* Function       loop
* @author        Danny
* @date          2017.07.25
* @brief         读出光敏电阻的模拟，每秒通过串口打印一次
* @param[in]     void
* @retval        void
* @par History   无
*/
void loop()
{
  Intensity = analogRead(LDR_pin);  //读取模拟口A5的值，存入Intensity变量
  Serial.print("Intensity = ");    //串口输出"Intensity = "
  Serial.println(Intensity);       //串口输出Intensity变量的值，并换行
  delay(1000);                      //延时1000ms
}

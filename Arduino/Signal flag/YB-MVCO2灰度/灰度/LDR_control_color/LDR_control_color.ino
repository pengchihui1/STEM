/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         LDR_control_color.c
* @author       Danny
* @version      V1.0
* @date         2017.07.26
* @brief        灰度传感器颜色识别并显示相应的颜色
* @details
* @par History  见如下说明
*
*/
//定义引脚
int LDR_pin = A5;   //定义光敏电阻模拟口A5

int Intensity = 0;  //光照度数值

#define ON 1        //使能LED
#define OFF 0       //禁止LED

//定义RGBLED引脚
int LED_R = 11;  //LED_R接在arduino上的数字11口
int LED_G = 10;  //LED_G接在arduino上的数字10口
int LED_B =  9;  //LED_B接在arduino上的数字9口

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
  //设置波特率9600
  Serial.begin(9600);

  //初始化RGB三色LED的IO口为输出方式
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  //初始化RGB三色LED为低电平
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
}

/**
* Function       color_led_pwm
* @author        Danny
* @date          2017.07.25
* @brief         pwm控制七彩灯亮指定的颜色
* @param[in1]    v_iRed:指定的颜色值（0-255）
* @param[in2]    v_iGreen:指定的颜色值（0-255）
* @param[in3]    v_iBlue:指定的颜色值（0-255）
* @param[out]    void
* @retval        void
* @par History   无
*/
void color_led_pwm(int v_iRed, int v_iGreen, int v_iBule)
{
  analogWrite(LED_R, v_iRed);
  analogWrite(LED_G, v_iGreen);
  analogWrite(LED_B, v_iBule);
  return;
}

/**
* Function       LDR_test
* @author        Danny
* @date          2017.07.25
* @brief         灰度传感器识别颜色,并返回相应的灰度值
*                多次测试取平均，提高测试精度
* @param[in]     void
* @retval        void
* @par History   无
*/
void LDR_test()
{
  unsigned long color[5] = {0};
  int num = 0;
  while (num < 5)
  {
    color[num] = analogRead(LDR_pin);
    num++;
  }
  num = 0;
  bubble(color, 5);
  Intensity = (color[1] + color[2] + color[3]) / 3;
  Serial.print("Intensity = ");         //串口输出"Intensity = "
  Serial.println(Intensity);            //串口输出Intensity变量的值，并换行
  return;
}

/**
* Function       bubble
* @author        Danny
* @date          2017.07.26
* @brief         超声波测五次的数据进行冒泡排序
* @param[in1]    a:超声波数组首地址
* @param[in2]    n:超声波数组大小
* @param[out]    void
* @retval        void
* @par History   无
*/
void bubble(unsigned long *a, int n) /*定义两个参数：数组首地址与数组大小*/

{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++) /*注意循环的上下限*/
    {
      if (a[i] > a[j])
      {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
  }
}

/**
* Function       loop
* @author        Danny
* @date          2017.07.25
* @brief         读出光敏电阻的模拟，每秒通过串口打印一次
*                以下灰度值的读取以实际实验环境为准
* @param[in]     void
* @retval        void
* @par History   无
*/
void loop()
{
  //灰度测试
  LDR_test(); 
  if (Intensity >= 130 && Intensity <= 150)
  {
    color_led_pwm(0, 255, 0);   //绿色
  }
  if (Intensity >= 190 && Intensity <= 200)
  {
    color_led_pwm(0, 0, 255);   //蓝色
  }
  if (Intensity >= 90 && Intensity <= 126)
  {
    color_led_pwm(255, 255, 0); //黄色
  }
  if (Intensity >= 165 && Intensity <= 189)
  {
    color_led_pwm(255, 0, 0);   //红色
  }
}

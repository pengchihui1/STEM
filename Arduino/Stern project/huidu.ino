void setup(){
    Serial.begin(9600);     //打开串口，设置串口波特率为9600bps
}
void loop(){
    int val;
    val=analogRead(0);      //将灰度传感器连接到模拟接口0
    Serial.print("Grayscale is ");//通过串口打印读取到的模拟值
    Serial.println(val,DEC);//通过串口打印读取到的模拟值
    delay(100);
}





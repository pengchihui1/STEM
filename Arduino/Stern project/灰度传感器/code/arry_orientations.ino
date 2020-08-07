int LDR_pin = A5;   //定义灰度模拟口 A5
void setup(){
	//设置波特率9600
	Serial.begin(9600);
}
int previousGrayScale;
int arr[0];
int num=1;
void loop(){ 
	  while (analogRead(LDR_pin)) {        //存在模拟值时
	  int grayscale=analogRead(LDR_pin);       //模拟值
	  
		for(int i=0;i<num;i++){
	     arr[i]=grayscale;    //从零开始记录
		}
	  num++;
	  previousGrayScale=arr[num-1];
		// Serial.print("新：");
		// Serial.println(grayscale);
		// Serial.print("旧：");
		// Serial.println(previousGrayScale);
		Serial.println(arr[num]);
	  
		// if(grayscale > previousGrayScale){
		//   Serial.println("逆");
	  // }else{
		//   Serial.println("顺");
	  // }
	  delay(1000);
	 }
}











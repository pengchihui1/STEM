/*
 * TCS3200ģ��
 * 
 * ��;��TCS3200��ɫ����,��ȡRGBֵ,LCD1602��ʾR,G,Bֵ
 * 
 * ����					����				��ע
 * Huafeng Lin			2010/12/10			����
 * Huafeng Lin			2010/12/11			�޸�
 * 
 */

//����˵����
//ģ��S2-----��Ƭ��P1.1
//ģ��S3-----��Ƭ��P1.0
//ģ��OUT----��Ƭ��P3.5(������1����)
//ģ��VCC----��Ƭ��VCC
//ģ��GND----��Ƭ��GND

#include<REG52.H>	
#include<math.h>       //Keil library  
#include<stdio.h>      //Keil library	
#include<INTRINS.H>

#define uchar unsigned char
#define uint  unsigned int	
#define DataPort P2	   //LCD1602 ���ݶ˿�
	
sbit    LCM_RS=P0^2;   //LCD1602 ���ƶ˿�		
sbit    LCM_RW=P0^1;   //LCD1602 ���ƶ˿�	
sbit    LCM_EN=P0^0;   //LCD1602 ���ƶ˿�

/**���Ŷ���**/  
sbit s2=P1^1;        //TCS3200 S2 
sbit s3=P1^0;        //TCS3200 S3
                     //TCS3200 S0 ģ���ڲ�Ĭ������
                     //TCS3200 S1 ģ���ڲ�Ĭ������
                     //TCS3200 OE ģ���ڲ��ӵ�
sbit test_pin=P1^2;  //��ʾ������������ţ���֪����ʱ���ж�Ƶ��
//��������������
uchar ge,shi,bai ;
uchar rp=3,gp=3,bp=6; //����������ӣ����廷�������޸�
uchar count;          //��ɫ��־λ��0:�� 1:�� 2:����

//��ʾ����
uchar disp_R[3];  //��
uchar disp_G[3];  //��
uchar disp_B[3];  //��

//********���庯��*****************************
void    delay(unsigned int k);
void    InitLcd();
void    WriteDataLCM(uchar dataW);
void    WriteCommandLCM(uchar CMD,uchar Attribc);
void    DisplayOneChar(uchar X,uchar Y,uchar DData);

//*********LCD1602��ʼ��**********************
void InitLcd()				
{			
	WriteCommandLCM(0x38,1);	
	WriteCommandLCM(0x08,1);	
	WriteCommandLCM(0x01,1);
	WriteCommandLCM(0x06,1);	
	WriteCommandLCM(0x0c,1);
}

//**********���æ�ź�************************
void WaitForEnable(void)	
{					
	DataPort=0xff;		
	LCM_RS=0;LCM_RW=1;_nop_();
	LCM_EN=1;_nop_();_nop_();
	while(DataPort&0x80);	
	LCM_EN=0;				
}
					
//**********д������LCD***********************
void WriteCommandLCM(uchar CMD,uchar Attribc)
{					
	if(Attribc)WaitForEnable();	
	LCM_RS=0;LCM_RW=0;_nop_();
	DataPort=CMD;_nop_();	
	LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}	
				
//**********д������LCD************************
void WriteDataLCM(uchar dataW)
{					
	WaitForEnable();		
	LCM_RS=1;LCM_RW=0;_nop_();
	DataPort=dataW;_nop_();	
	LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}
					
//*********дһ���ַ����ݵ�ָ����Ŀ��***********
void DisplayOneChar(uchar X,uchar Y,uchar DData)
{						
	Y&=1;						
	X&=15;						
	if(Y)X|=0x40;					
	X|=0x80;			
	WriteCommandLCM(X,0);		
	WriteDataLCM(DData);		
}

//**********��ʱ����***************
void delay(unsigned int k)	
{						
	unsigned int i,j;				
	for(i=0;i<k;i++)
	{			
		for(j=0;j<121;j++)			
		{;}
	}						
}						            

/*******************************************
* ��������: t0_init()
* ��������: ��ʱ��0��ʼ��
* ��ڲ���: ��
* ���ڲ���: ��
/********************************************/
void t0_init()
{
	TMOD=0x51;        //T1���� T0��ʱ ������ʽ1
	
	TH1=0x00;        //������ֵ
	TL1=0x00;
	
	TH0=0xE0;
	TL0=0x00;        //11��0592M ����10ms
	EA=1;            //���ж�
	
	ET0=1;        
	TR0=1;           //����
	TR1=1;
}

//*********************************************
//��ֵת������ʮ��ǧ��ASCII��
//*********************************************
void conversion(uint temp_data)  
{  
    bai=temp_data/100+0x30 ;
    temp_data=temp_data%100;   //ȡ������
    shi=temp_data/10+0x30 ;
    ge=temp_data%10+0x30;      //ȡ������
}

/*******************************************
* ��������: main()
/********************************************/
void main()
{
	delay(10); 
	InitLcd();      //lcd��ʼ��
	s2=0;           //��ʼ�趨S2����
	s3=0;           //��ʼ�趨S3����
	t0_init();      //��ʱ������ʹ�

	while(1)
	{
		DisplayOneChar(0, 0, 'T');
		DisplayOneChar(1, 0, 'C');
		DisplayOneChar(2, 0, 'S');
		DisplayOneChar(3, 0, '2');
		DisplayOneChar(4, 0, '3');
		DisplayOneChar(5, 0, '0');

		DisplayOneChar(10, 0, 'R'); 
		DisplayOneChar(11, 0, '['); 
		DisplayOneChar(12, 0, disp_R[0]); 
		DisplayOneChar(13, 0, disp_R[1]); 
		DisplayOneChar(14, 0, disp_R[2]);
		DisplayOneChar(15, 0, ']');	
	
		DisplayOneChar(0, 1, 'G'); 
		DisplayOneChar(1, 1, '['); 
		DisplayOneChar(2, 1, disp_G[0]); 
		DisplayOneChar(3, 1, disp_G[1]); 
		DisplayOneChar(4, 1, disp_G[2]);
		DisplayOneChar(5, 1, ']');
		
		DisplayOneChar(10, 1, 'B'); 
		DisplayOneChar(11, 1, '['); 
		DisplayOneChar(12, 1, disp_B[0]); 
		DisplayOneChar(13, 1, disp_B[1]); 
		DisplayOneChar(14, 1, disp_B[2]);
		DisplayOneChar(15, 1, ']');				
		
		delay(100) ;	
	}
}

/*******************************************
* ��������: c10ms_out() 
* ��������: ��ʱ�ж�0�������
            �޸���ɫ��־disp_tc��0:�� 1:�� 2:����
            ����S0 S1 S2 ѡ���˲���
            �������壬��ȡɫֵ
* ��ڲ���: ��
* ���ڲ���: ��
/********************************************/
void c10ms_out() interrupt 1
{
	uint temp;
	test_pin=!test_pin; //���Զ�ʱ���ж�Ƶ�����ţ�������ʾ�����۲�
	TR0=0;              //�رն�ʱ
	TR1=0;              //�رռ���
	//   count+1ʵ���ȼ����ɫ,�ټ����ɫ,Ȼ�����ɫ,ѭ�����       
	if(count==0)
	{
		count++;    
		s2=1;s3=1;             //ѡ���˲���Ϊ��ɫ     
		
		temp=(8<<TH1)+TL1;    //�������ʱ���� TCS230 �����������	
		temp/=rp;			
		conversion(temp);
		disp_R[2]=ge;         //��Ϊ��ε��жϣ����ϴ�ѡ���˲�������ֵ
		disp_R[1]=shi;
		disp_R[0]=bai;
	}	
	else if(count==1)
	{            
		count++;
		s2=1;s3=0;            //ѡ���˲���Ϊ��ɫ
		temp=(8<<TH1)+TL1;    //�������ʱ���� TCS230 �����������	
		temp/=gp;			
		conversion(temp);
		disp_G[2]=ge;         //��Ϊ��ε��жϣ����ϴ�ѡ���˲�������ֵ
		disp_G[1]=shi;
		disp_G[0]=bai;
	}	
	else if(count==2)
	{            
		count=0;
		s2=0;s3=0;            //ѡ���˲���Ϊ��ɫ
		
		temp=(8<<TH1)+TL1;    //�������ʱ���� TCS230 �����������	
		temp/=bp;		
		conversion(temp);
		disp_B[2]=ge;         //��Ϊ��ε��жϣ����ϴ�ѡ���˲�������ֵ
		disp_B[1]=shi;
		disp_B[0]=bai;	
	}
	
	//��ʱ���������ظ���ֵ
	TH0=0xE0;
	TL0=0x00; //11��0592M ����Ϊ10ms
	TL1=0x00;//����������
	TH1=0x00;//����������
	TR0=1;   //�򿪶�ʱ��
	TR1=1;   //�򿪼�����
}

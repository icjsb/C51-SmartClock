/*******************************************************************************
* ʵ��Ч��       :1602��ʾʱ�ӣ���K3����ʱ�����ã���K1ѡ�����õ�ʱ�������£���K2ѡ��
*ѡ�����ü�1�� 
*******************************************************************************/
#include"lcd.h"
#include"ds1302.h"
#include "lcd1602.h"
sbit K1=P3^0;	//+
sbit K2=P3^1;	//��һ������
sbit K3=P3^2;   //ʱ��������������
sbit K4=P3^3;	//��������
sbit K5=P3^4;	//-
void Int0Configuration();
void Int1Configuration();
void DisDate();
void DisTime();
void Clocker();
unsigned char SetState,ClockState,SetPlace=0,SetNao=0;
void Delay10ms(void);   //��� 0us
extern unsigned char clockdata[];
unsigned char naozhongdata[]={0,28,10,0};
extern unsigned char jz;
unsigned char evd;
/*******************************************************************************
* ������         : main
* ��������		   : ������
*******************************************************************************/

void Buttons()
{
    
    unsigned char i;
	Int0Configuration();
	Int1Configuration();
/**********************************************************************/	
		while(SetState)
		{
		  DS1302_settime();
		  /***********************************/
		 switch( jz )
		{
		case 2:
		LCD1602_PrintChar(1,1,clockdata[2]/10 + '0');
		LCD1602_PrintChar(1,2,clockdata[2]%10 + '0');
		LCD1602_PrintChar(1,9,' ');
		 LCD1602_PrintChar(1,10,' ');
		break;
		case 1:	
		if(clockdata[2]>12)
		{
	 	 LCD1602_PrintChar(1,1,12/clockdata[2] + '0');
		 LCD1602_PrintChar(1,2,clockdata[2]%12 + '0');
		 LCD1602_PrintChar(1,9,'p');
		 LCD1602_PrintChar(1,10,'m');
		}
		else
		{
		 LCD1602_PrintChar(1,1,clockdata[2]/12 + '0');
		 LCD1602_PrintChar(1,2,clockdata[2]%12 + '0');
		 LCD1602_PrintChar(1,9,'a');
		 LCD1602_PrintChar(1,10,'m');
		}
		break;
		}
		    LCD1602_PrintChar(1,3,':');
			//��
			LCD1602_PrintChar(1,4,clockdata[1]/10 + '0');
			LCD1602_PrintChar(1,5,clockdata[1]%10 + '0');
			LCD1602_PrintChar(1,6,':');
			//��
			LCD1602_PrintChar(1,7,clockdata[0]/10 + '0');
			LCD1602_PrintChar(1,8,clockdata[0]%10 + '0');
		  /************************************/
		  	LCD1602_PrintChar(2,7,clockdata[8]/10 + '0');
			LCD1602_PrintChar(2,8,clockdata[8]%10 + '0');
			LCD1602_PrintChar(2,9,clockdata[5]/10 + '0');
			LCD1602_PrintChar(2,10,clockdata[5]%10 + '0');
			LCD1602_PrintChar(2,11,'/');
			//�·�
			LCD1602_PrintChar(2,12,clockdata[4]/10 + '0');
			LCD1602_PrintChar(2,13,clockdata[4]%10 + '0');
		    LCD1602_PrintChar(2,14,'/');
			//����
			LCD1602_PrintChar(2,15,clockdata[3]/10 + '0');
			LCD1602_PrintChar(2,16,clockdata[3]%10 + '0');
	
			switch( clockdata[6] )
			{
				case 1:
					//������
					LCD1602_PrintString(1,14,"Sun");
					break;
				case 2:
					//����һ
					LCD1602_PrintString(1,14,"Mon");
					break;
				case 3:
					//���ڶ�
					LCD1602_PrintString(1,14,"The");
					break;
				case 4:
					//������
					LCD1602_PrintString(1,14,"Wed");
					break;
				case 5:
					//������
					LCD1602_PrintString(1,14,"Thu");
					break;
				case 6:
					//������
					LCD1602_PrintString(1,14,"Fri");
					break;
				case 7:
					//������
					LCD1602_PrintString(1,14,"Sat");
					break;
				default:
					LCD1602_PrintString(1,14,"Ero");
					break;
			}
		  /************************************/
		  		if(K1==0)		//��ⰴ��K1�Ƿ���	  //+
			{
				Delay10ms();	//��������
				if(K1==0)
				{
					clockdata[SetPlace]++;
					if(SetPlace>=7)
					{
					  SetPlace=0;
					}
					if(clockdata[0]>=60)	  //��
					{
					   clockdata[0]=0;
					}
					if(clockdata[1]>=60)	  //��
					{
					   clockdata[1]=0;
					}
					if((jz==2)&&(clockdata[2]==24))	  //24ʱ
					{
					   clockdata[2]=0;
					}
					if((jz==1)&&(clockdata[2]>12))	  //12ʱ
					{
					   clockdata[2]=0;
					}
					if(clockdata[3]>=32)	  //��
					{
					   clockdata[3]=1;
					}
					if(clockdata[4]>=13)	  //��
					{
					   clockdata[4]=1;
					}
					if(clockdata[5]>=99)	  //��
					{
					   clockdata[5]=0;
					}
					if(clockdata[6]>=7)		  //����
					{
					   clockdata[6]=1;
					}					
				}

				while((i<50)&&(K1==0))	 //��ⰴ���Ƿ��ɿ�
				{
					Delay10ms();
					i++;
				}
				i=0;
			}
			/****************************************/
			if(K5==0)		//��ⰴ��K5�Ƿ���		//-
			{
				Delay10ms();	//��������
				if(K5==0)
				{
					clockdata[SetPlace]--;
					if(SetPlace>=7)
					{
					 SetPlace=0;
				 	 }
					 if(clockdata[0]<0)	  //��
					{
					   clockdata[0]=59;
					}
					if(clockdata[1]<0)	  //��
					{
					   clockdata[1]=59;
					}
					if((jz==2)&&(clockdata[2]<0))	  //24ʱ
					{
					   clockdata[2]=23;
					}
					if((jz==1)&&(clockdata[2]<0))	  //12ʱ
					{
					   clockdata[2]=11;
					}
					if(clockdata[3]<0)	  //��
					{
					   clockdata[3]=31;
					}
					if(clockdata[4]<0)	  //��
					{
					   clockdata[4]=12;
					}
					if(clockdata[5]<0)	  //��
					{
					   clockdata[5]=99;
					}
					if(clockdata[6]<0)	  //����
					{
					   clockdata[6]=7;
					}								
				}

				while((i<50)&&(K5==0))	 //��ⰴ���Ƿ��ɿ�
				{
					Delay10ms();
					i++;
				}
				i=0;
			}
			/**************************************************/
		
			/***************************************************/
			if(K2==0)		//��ⰴ��K2�Ƿ���
			{
				Delay10ms();	//��������
				if(K2==0)
				{
					SetPlace++;
					if(SetPlace>=7)
					{
					  SetPlace=0;
					}
				/*	if((clockdata[SetPlace]&0x0f)>9)					 //����BCD�롣
					{
						clockdata[SetPlace]=clockdata[SetPlace]+6;
					}  */
					if((clockdata[SetPlace]>=60)&&(SetPlace<2))		//����ֻ�ܵ�59
					{
						clockdata[SetPlace]=0;
					}
					if((jz==2)&&(clockdata[SetPlace]>24)&&(SetPlace==2))		//24Сʱֻ�ܵ�23
					{
						clockdata[SetPlace]=0;
					}
					if((jz==1)&&(clockdata[SetPlace]>=12)&&(SetPlace==2))		//12Сʱֻ�ܵ�12
					{
						clockdata[SetPlace]=0;
					}   
					if((clockdata[SetPlace]>=32)&&(SetPlace==3))		//��ֻ�ܵ�31
					{
						clockdata[SetPlace]=0;	
					}
					if((clockdata[SetPlace]>=13)&&(SetPlace==4))		//��ֻ�ܵ�12
					{
						clockdata[SetPlace]=0;
					}
					if((clockdata[SetPlace]>=99)&&(SetPlace==5))		//��ֻ�ܵ�99
					{
						clockdata[SetPlace]=1;
					}	
					if((clockdata[SetPlace]>=7)&&(SetPlace==6))		//��ֻ�ܵ�7
					{
						clockdata[SetPlace]=1;
					}		
	
				}
				
				while((i<50)&&(K2==0))	 //��ⰴ���Ƿ��ɿ�
				{
					Delay10ms();
					i++;
				}
				i=0;
				
			}
								
		}
/***********************************************************/
//��������
/***********************************************************/
   while(ClockState)
		{
		  /***********************************/
			//ʱ
			LCD1602_PrintChar(1,1,naozhongdata[2]/10 + '0');
			LCD1602_PrintChar(1,2,naozhongdata[2]%10 + '0');
			LCD1602_PrintChar(1,9,' ');
			LCD1602_PrintChar(1,10,' ');
			//��
			LCD1602_PrintChar(1,4,naozhongdata[1]/10 + '0');
			LCD1602_PrintChar(1,5,naozhongdata[1]%10 + '0');
			
			//��
			LCD1602_PrintChar(1,7,naozhongdata[0]/10 + '0');
			LCD1602_PrintChar(1,8,naozhongdata[0]%10 + '0');
			/****************************************************/
		    if(K1==0)		//��ⰴ��K1�Ƿ���	  //+
			{
				Delay10ms();	//��������
				if(K1==0)
				{
				   naozhongdata[SetNao]++;
					if(naozhongdata[0]>=60)	  //��
					{
					   naozhongdata[0]=0;
					}
					if(naozhongdata[1]>=60)	  //��
					{
					   naozhongdata[1]=0;
					}
					if((naozhongdata[2]==24))	  //24ʱ
					{
					   clockdata[2]=0;
					}
					if(naozhongdata[3]>1)		  //����
					{
					   naozhongdata[3]=0;
					}					
				}

				while((i<50)&&(K1==0))	 //��ⰴ���Ƿ��ɿ�
				{
					Delay10ms();
					i++;
				}
				i=0;
			}
			/*****************************************************/
			if(K5==0)		//��ⰴ��K5�Ƿ���		//-
			{
				Delay10ms();	//��������
				if(K5==0)
				{
					naozhongdata[SetNao]--;
					 if(naozhongdata[0]<0)	  //��
					{
					   naozhongdata[0]=0;
					}
					if(naozhongdata[1]<0)	  //��
					{
					   naozhongdata[1]=59;
					}
					if((naozhongdata[2]<0))	  //24ʱ
					{
					   naozhongdata[2]=23;
					}
					if(naozhongdata[3]==0)	  //����
					{
					   naozhongdata[3]=0;
					}								
				}

				while((i<50)&&(K5==0))	 //��ⰴ���Ƿ��ɿ�
				{
					Delay10ms();
					i++;
				}
				i=0;
			}
			/***************************************************/
			if(K2==0)		//��ⰴ��K2�Ƿ���		������һ��
			{
				Delay10ms();	//��������
				if(K2==0)
				{
					SetNao++;
					if(SetNao>3)
					{
					  SetNao=0;
					}
					if((naozhongdata[SetNao]>=60)&&(SetNao<2))		//����ֻ�ܵ�59
					{
						naozhongdata[SetNao]=0;
					}
					if((naozhongdata[SetNao]>24)&&(SetNao==2))		//24Сʱֻ�ܵ�23
					{
						naozhongdata[SetNao]=0;
					}
			 
					if((naozhongdata[SetNao]>1)&&(SetNao==3))		//��ֻ�ܵ�7
					{
						naozhongdata[SetNao]=1;
					}		
				}	
				while((i<50)&&(K2==0))	 //��ⰴ���Ƿ��ɿ�
				{
					Delay10ms();
					i++;
				}
				i=0;	
			}
			if(naozhongdata[3]==1)
			{
				LCD1602_PrintChar(1,11,'E');
				LCD1602_PrintChar(1,12,'v');
				LCD1602_PrintChar(1,13,'D');
		      }
		  if(naozhongdata[3]==0)
			{
				LCD1602_PrintChar(1,11,' ');
				LCD1602_PrintChar(1,12,' ');
				LCD1602_PrintChar(1,13,' ');
		      } 
		 
	   }
	   if((naozhongdata[0]==clockdata[0])&&(naozhongdata[1]==clockdata[1])
		     &&(naozhongdata[2]==clockdata[2])&&(naozhongdata[3]==1))
		 { 
		 while(1)
		  { 
	 	   Clocker();
		  if(K1==0)
			{
			   Delay10ms();	//��������
			   if(K1==0)
			   { 	
		 	    break;
			   }
			}
	        
		  }
		 }
		

/*****************************************************************/		
}
/*******************************************************************************
* ������         : Int0Configuration()
* ��������		   : �����ⲿ�ж�0
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void Int0Configuration()
{
	//����INT0
	IT0=1;//�����س�����ʽ���½��أ�
	EX0=1;//��INT0���ж�����
	EA=1;//�����ж�	
}

/*******************************************************************************
* ������         : Int0() 
* ��������		   : �ⲿ�ж�0 �жϺ���
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void Int0() interrupt 0		 
{
	Delay10ms();
	if(K3==0)
	{
		SetState=~SetState;
		SetPlace=0;	
	}
}
/*******************************************************************************
* ������         : Int1Configuration()
* ��������		   : �����ⲿ�ж�0
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Int1Configuration()
{
	//����INT0
	IT1=1;//�����س�����ʽ���½��أ�
	EX1=1;//��INT0���ж�����
	EA=1;//�����ж�	
}
/*******************************************************************************
* ������         : Int0() 
* ��������		   : �ⲿ�ж�0 �жϺ���
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Int1() interrupt 2		 
{
	Delay10ms();
	if(K4==0)
	{
	 ClockState=~ClockState;
	 SetPlace=0;		
	}
}
/*******************************************************************************
* ������         : Delay10ms
* ��������		   : ��ʱ��������ʱ10ms
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Delay10ms(void)   //��� 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
} 
 
/*******************************************************************************

* ����������:   ������ʾ

*******************************************************************************/
#include"lcd.h"
#include"lcd1602.h"
#include "DS1302.h"
#include<temp.h>
void DisTime();
void DisTemperture();
void DisDate();
extern unsigned char clockdata[9];
void DisDate()
{
  	
 /*   clockdata[0] = 0;			//��
	clockdata[1] = 42;			//��
	clockdata[2] = 10;			//Сʱ
	clockdata[3] = 10;		    //����
	clockdata[4] = 1;		    //�·�
	clockdata[5] = 19;		    //��
	clockdata[6] = 3;			//���ڼ�
	clockdata[7] = 0;
	clockdata[8] = 20;	*/

//	LCD1602_Initialize();

//	DS1302_settime();
//	while (1)
//	{
//		DS1302_gettime();
		
		//���
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
//    }
}
  




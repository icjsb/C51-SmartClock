#include<reg51.h>
#include<intrins.h>		  			 
#define GPIO_KEY P1
sbit LED = P2^3	;  //���ڿ��Ƿ�����޸�

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef UINT 
#define UINT unsigned int
#endif

extern UCHAR clock_week[2], clock_hour[2], clock_minute[2],clock_number;
extern UCHAR show,key,z; //show ѡ����ʾ���� ��key �������º�ȡֵ������ʶ���Ǹ���������
						//z 	����TIME�±�����index���±�
extern bit flag,digit,KEY_clock_stop,clock_number_logo; //flag �ж��Ƿ����޸� 1 �ǣ�0��
					   //digit �ж�ʮλ���Ǹ�λ ��1ʮλ 0��λ
					   // KEY_clock_stop �����������ӱ�־

void judge(UCHAR logo);//�������������ж�	
UCHAR calc(UCHAR l,bit x);//�����Ӧ�����LCD1602λ��	

void KeyDown();		//ʶ�𰴼�����
void KeyDown_clock_stop(); // ���ӽ�����ť
void KEY_Pro(UCHAR k);	//������
void number_input_date(UCHAR number); //�������봦��
void number_input_week(UCHAR number);
void number_input_time(UCHAR number);
	
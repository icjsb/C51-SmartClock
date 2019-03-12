#ifndef DS1302_H
#define DS1302_H
#include "reg51.h"
#include "intrins.h"
#include "common.h"
#endif
/*********************************************************************************************/
//---����ȫ�ֺ���---//
void Ds1302Write(unsigned char addr, unsigned char dat);
unsigned char Ds1302Read(unsigned char addr);
void Ds1302Init();
void Ds1302ReadTime();

//---����ȫ�ֱ���--//
//extern unsigned char TIME[7];
extern unsigned char code WRITE_RTC_ADDR[7];	//����ȫ�ֱ���

/*********************************************************************************************/

//��������
#define DS1302_WRITE	0x00			 //д
#define DS1302_READ		0x01			 //��

//�롢�֡�ʱ���ա��¡��ܡ���Ĵ�����ַ	     |  7  |  6  |     5     |  4  | 3 | 2 | 1 | 0 |
#define DS1302_SECOND	0x80			//	 | CH  |     10     SEC        |      SEC      |
#define DS1302_MINUTE	0x82			//	 |  0  |     10     MIN        |      MIN      |
#define DS1302_HOUR		0x84			//	 |12/24|  0  |  10/(A/P) | HR  |      HR       |
#define DS1302_DATE		0x86			//	 |  0  |  0  |    10 DATE      |     DATE      |
#define DS1302_MONTH	0x88			//	 |  0  |  0  |     0     | 10 M|     MONTH     |
#define DS1302_WEEKDAY	0x8A			//	 |  0  |  0  |     0     |0    |  0 |   DAY    |
#define DS1302_YEAR		0x8C			//	 |           10 YEAR           |     YEAR      | 

//���ƼĴ�����ַ 		               |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
#define DS1302_CONTROL	0x8E	    // | W/P |  0  |  0  |  0  |  0  |  0  |  0	 |  0  |

//��γ����ƼĴ���д������ַ	               |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
#define DS1302_TRICKLECHARGE	0x90        // | TCS | TCS | TCS | TCS |  DS |  DS |  RS |  RS |

//ʱ��ͻ��д������ַ
#define DS1302_CLOCKBURST		0xBE

//BRAM
#define DS1302_BRAMSTART			0xC0			 //BRAM��ʼ��ַ
#define DS1302_BRAMEND				0xFC			 //BRAM������ַ
#define DS1302_BRAMBURST			0xFE			 //BRAMͻ��������ַ





//��DS1302дһ���ֽڵ�����
void DS1302_SPIwritebyte( unsigned char dat );
//��DS1302��һ���ֽڵ�����
unsigned char DS1302_SPIreadbyte( );

//��DS1302дһ���ֽڵ����ݵ���ַΪaddress�ĵ�Ԫ���Ĵ�����
void DS1302_writeybyte( unsigned char address, unsigned char dat );
//��DS1302��address�ĵ�Ԫ���Ĵ�������һ���ֽڵ�����
unsigned char DS1302_readbyte( unsigned char address );

//ͻ��ģʽдʱ�����ݣ����ݴ����clockdataBCD[8]��
void DS1302_writeclockburst( );
//ͻ��ģʽ��ʱ�����ݣ����ݴ����clockdataBCD[8]��
void DS1302_readclockburst( );

//ͻ��ģʽдram���ݣ����ݴ����BRAMdata[31]��
void DS1302_writeramburst( );
//ͻ��ģʽ��ram���ݣ����ݴ����BRAMdata[31]��
void DS1302_readramburst( );

//����������д������
void DS1302_lock();

//������ȡ��д������
void DS1302_unlock();


//���ʱ�����ݣ����Ϊ������
unsigned char DS1302_getsecond();				  //��
unsigned char DS1302_getminute();				  //��
unsigned char DS1302_gethour();					  //ʱ
unsigned char DS1302_getdate();					  //��
unsigned char DS1302_getmonth();				  //��
unsigned char DS1302_getweekday();				  //��
unsigned char DS1302_getyear();					  //��

//����ʱ�����ݣ�����Ϊ������
void DS1302_setsecond( unsigned char second );	  //��
void DS1302_setminute( unsigned char minute );	  //��
void DS1302_sethour( unsigned char hour );		  //ʱ
void DS1302_setdate( unsigned char date );		  //��
void DS1302_setmonth( unsigned char month );	  //��
void DS1302_setweekday( unsigned char weekday );  //��
void DS1302_setyear( unsigned char year );		  //��


//��ÿ��ƼĴ������ݣ����Ϊ������
unsigned char DS1302_getcontrol();					  //���ƼĴ���
//���ÿ��ƼĴ�������
void DS1302_setcontrol( unsigned char con );					  //���ƼĴ���

//����DS1302��ʱ�䣬����Ϊһ���ַ�������ʽΪ��YYYY-MM-DD HH:MM:SS �� YYYY/MM/DD HH:MM:SS
void DS1302_settime( );

//��ȡDS1302��ʱ�䣨�ַ���������ʽΪ��YYYY-MM-DD HH:MM:SS �� YYYY/MM/DD HH:MM:SS 
void DS1302_gettime( );

#ifndef LCD1602_H
#define LCD1602_H
#include <reg51.h>
#include <intrins.h>
#endif

//#define LCD1602_MODE_4BIT  1

#define delay_5us()	{_nop_();_nop_();_nop_();_nop_();_nop_();}
#define LCD1602_CMD_RESET	0x01			//LCD��λ����긴λ���Դ�����

#define LCD1602_CMD_CURSOR_TO_LEFT	0x04 	//�������
#define LCD1602_CMD_SCREEN_TO_RIGHT	0x05	//��Ļ����
#define LCD1602_CMD_CURSOR_TO_RIGHT	0x06	//�������
#define LCD1602_CMD_SCREEN_TO_LEFT	0x07	//��Ļ����

#define LCD1602_CMD_LCD_OFF_CURSOR_OFF_BLANK_OFF				0x08		//��Ļ�ء����ء���˸��
#define LCD1602_CMD_LCD_ON_CURSOR_OFF_BLANK_OFF					0x0C		//��Ļ�������ء���˸��
#define LCD1602_CMD_LCD_ON_CURSOR_ON_BLANK_OFF					0x0E		//��Ļ������꿪����˸��
#define LCD1602_CMD_LCD_ON_CURSOR_ON_BLANK_ON					0x0F		//��Ļ������꿪����˸��

//�������߼������⣡��
#define LCD1602_CMD_LCD_OFF_CURSOR_ON_BLANK_OFF					0x0A		//��Ļ�ء���꿪����˸��
#define LCD1602_CMD_LCD_ON_CURSOR_OFF_BLANK_ON					0x0D		//��Ļ�������ء���˸��
#define LCD1602_CMD_LCD_OFF_CURSOR_OFF_BLANK_ON					0x09		//��Ļ�ء����ء���˸��
#define LCD1602_CMD_LCD_OFF_CURSOR_ON_BLANK_ON					0x09		//��Ļ�ء���꿪����˸��

//���λ���ƶ������ı�DDRAM��ֵ
#define LCD1602_CMD_CURSORPOSITION_TO_LEFT						0x10 		//�������
#define LCD1602_CMD_CURSORPOSITION_TO_RIGHT						0x14 		//�������
#define LCD1602_CMD_SCREENPOSITION_TO_RIGHT						0x18 		//��Ļ����
#define LCD1602_CMD_SCREENPOSITION_TO_LEFT						0x1C 		//��Ļ����

#define LCD1602_CMD_8BIT_2LINE_5X7								0x38 		//8λ��˫�С�5*7ģʽ
#define LCD1602_CMD_8BIT_1LINE_5X7								0x30 		//8λ�����С�5*7ģʽ
#define LCD1602_CMD_4BIT_2LINE_5X7								0x28 		//4λ��˫�С�5*7ģʽ
#define LCD1602_CMD_4BIT_1LINE_5X7								0x20 		//4λ�����С�5*7ģʽ

#define LCD1602_CMD_8BIT_2LINE_5X10								0x39 		//8λ��˫�С�5*10ģʽ
#define LCD1602_CMD_8BIT_1LINE_5X10								0x31 		//8λ�����С�5*10ģʽ
#define LCD1602_CMD_4BIT_2LINE_5X10								0x29 		//4λ��˫�С�5*10ģʽ
#define LCD1602_CMD_4BIT_1LINE_5X10								0x21 		//4λ�����С�5*10ģʽ

#define LCDDATAPORT P0

sbit LCDRW = P2^5;
sbit LCDRS = P2^6;
sbit LCDEN = P2^7;

//�ȴ�LCD1602����
void LCD1602_Wait();

//��LCD1602д������
void LCD1602_WriteCommand( unsigned char cmd );

//��LCD1602д������
void LCD1602_WriteData( unsigned char dat);

//��ʼ��LCD1602
void LCD1602_Initialize( );

//���Զ����ַ���������д��CGRAM
void LCD1602_WriteCGRAM( unsigned char cgramdata[][8], unsigned char n);//���Զ����ַ���������д��CGRAM 

//��DDRAM����ָ�붨λ����row�С���column�У�rowȡ1��2��column��ΧΪ1~16
void LCD1602_Locate( unsigned char row, unsigned char column );

//�ڵ�row�С���column����ʾ�ַ�c,rowȡ1��2��column��ΧΪ1~16
void LCD1602_PrintChar(  unsigned char row, unsigned char column, unsigned char c );

//�ӵ�row�С���column�п�ʼ��ʾ�ַ���str,rowȡ1��2��column��ΧΪ1~16,str��'\0'����
void LCD1602_PrintString(  unsigned char row, unsigned char column, unsigned char *str );
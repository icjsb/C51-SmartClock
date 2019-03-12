#include "LCD1602.h"
#include "common.h"

//�ȴ�LCD1602����
void LCD1602_Wait()
{
#ifdef	LCD1602_MODE_4BIT				//////////////////////////////4λģʽ
	unsigned char lcdstatus_low;
#endif

	unsigned char lcdstatus;
	
	do {

#ifdef LCD1602_MODE_4BIT				   //-------------------------4λģʽ
		LCDDATAPORT = 0xF0;	   	          //������Ʒ����Ϊ0xF0
#else									  /////////////////////////8λģʽ
		LCDDATAPORT = 0xFF;	   	          //������Ʒ����Ϊ0xFF
#endif

		LCDEN = 0; LCDRS = 0; LCDRW = 1;  //��ֹLCD; ѡ������Ĵ���; ������

#ifdef LCD1602_MODE_4BIT			 //-------------------------4λģʽ
		LCDEN = 1; delay_5us();	   	//ʹ��LCD
		lcdstatus = LCDDATAPORT; delay_5us();  //��ȡ״̬��4λ
		LCDEN = 0;delay_5us();     	//��ֹLCD

		LCDEN = 1; delay_5us();		 //ʹ��LCD
		lcdstatus_low = LCDDATAPORT; delay_5us();  //��ȡ״̬��4λ
		LCDEN = 0;delay_5us(); 		//��ֹLCD
#else								//+++++++++++++++++++++++8λģʽ
		LCDEN = 1; delay_5us();		//ʹ��LCD
		lcdstatus = LCDDATAPORT;delay_5us();  //��ȡ״̬
		LCDEN = 0;delay_5us();	   //��ֹLCD
#endif								  
	} while ( lcdstatus & 0x80);
}

//��LCD1602д������
void LCD1602_WriteCommand( unsigned char cmd )
{
	LCD1602_Wait();						 //�ȴ�LCD����

	LCDEN = 0;	LCDRS = 0; LCDRW = 0;	 //��ֹLCD��ѡ������Ĵ�����д����

#ifdef LCD1602_MODE_4BIT				 //---------------------------------4λģʽ
	LCDDATAPORT = cmd & 0xF0;			 //д�������4λ
	LCDEN = 1; delay_5us();				 //ʹ��LCD
	LCDEN = 0; delay_5us();				 //��ֹLCD

	LCDDATAPORT = (( cmd & 0x0F) << 4 );//д�������4λ
	LCDEN = 1; delay_5us();				//ʹ��LCD
	LCDEN = 0; delay_5us();				//��ֹLCD
#else									 //+++++++++++++++++++++++++++++++++8λģʽ
	LCDDATAPORT = cmd;					 //д������
	LCDEN = 1; delay_5us();				//ʹ��LCD
	LCDEN = 0; delay_5us();				//��ֹLCD
#endif
}

//��LCD1602д������
void LCD1602_WriteData( unsigned char dat)
{
	LCD1602_Wait();			  			//�ȴ�LCD����

	LCDEN = 0;	LCDRS = 1; LCDRW = 0;	//��ֹLCD��ѡ�����ݼĴ�����д����

#ifdef LCD1602_MODE_4BIT				 //-----------------------------4λģʽ
	LCDDATAPORT = dat & 0xF0;			 //д�������4λ
	LCDEN = 1;delay_5us(); 				 //ʹ��LCD
	LCDEN = 0; delay_5us(); 			 //��ֹLCD

	LCDDATAPORT = ((dat & 0x0F) << 4);	 //д�������4λ
	LCDEN = 1; delay_5us();				 //ʹ��LCD
	LCDEN = 0; delay_5us();				 //��ֹLCD
#else									 //+++++++++++++++++++++++++++++8λģʽ
	LCDDATAPORT = dat;					 //д������
	LCDEN = 1; delay_5us();				 //ʹ��LCD
	LCDEN = 0; delay_5us();				 //��ֹLCD
#endif
}

//��ʼ��LCD1602
void LCD1602_Initialize( )
{
#ifdef LCD1602_MODE_4BIT			//-----------------------------4λģʽ
	LCD1602_WriteCommand( LCD1602_CMD_4BIT_2LINE_5X7 ); 
#else								//+++++++++++++++++++++++++++++8λģʽ
	LCD1602_WriteCommand( LCD1602_CMD_8BIT_2LINE_5X7 );
#endif 
	
	delay_ms(1);
	LCD1602_WriteCommand( LCD1602_CMD_RESET ); delay_ms(1);
	LCD1602_WriteCommand( LCD1602_CMD_CURSOR_TO_RIGHT ); delay_ms(1);
	LCD1602_WriteCommand( LCD1602_CMD_LCD_ON_CURSOR_OFF_BLANK_OFF ); delay_ms(1);

}

//���Զ����ַ���������д��CGRAM
void LCD1602_WriteCGRAM( unsigned char cgramdata[][8], unsigned char n) 
{
	unsigned char i,j;
	LCD1602_WriteCommand( 0x40 );			//����CGRAM�ĵ�ַΪ0x40
	for ( j = 0; j < n; j++ )
	for ( i = 0; i < 8; i++ )				//д��8���ֽڵ��Զ�����ģ����
		LCD1602_WriteData( cgramdata[j][i] );					   
}


//��DDRAM����ָ�붨λ����row�С���column�У�rowȡ1��2��column��ΧΪ1~16
void LCD1602_Locate( unsigned char row, unsigned char column )
{
	unsigned char address;
  	if( row == 1 )
  		address = 0x80 + column - 1; // - - ��һ��λ��
  	else
    	address = 0xc0 + column - 1; // - - �ڶ���λ��
	
	LCD1602_WriteCommand(address);	//д���ַ
}

//�ڵ�row�С���column����ʾ�ַ�c,rowȡ1��2��column��ΧΪ1~16
void LCD1602_PrintChar(  unsigned char row, unsigned char column, unsigned char c )
{
	LCD1602_Locate( row, column);			  //��λ��дDDRAMָ��
    LCD1602_WriteData( c );					  //д��DDRAM����
}

//�ӵ�row�С���column�п�ʼ��ʾ�ַ���str,rowȡ1��2��column��ΧΪ1~16,str��'\0'����
void LCD1602_PrintString(  unsigned char row, unsigned char column, unsigned char *str )
{
	unsigned int i;
	unsigned char *strpointer;			//����ָ��
	unsigned char rowtmp, columntmp; 	//��ǰ�С���ǰ��

	//���row��column��Ч����ʾ��ʾ��Ϣ�����˳�
	unsigned char errorstring[12] = "(1,1)~(2,16)";				
	if ( row < 1 || row > 2 || column < 1 || column > 16 )
	{
		for ( i = 0; i < 12; i++ )
			LCD1602_PrintChar( 1, i+1, errorstring[i]);	 //�ڵ�1����ʾerrorstring�ַ���
		return;											 //�˳�
	}
	
	rowtmp = row; columntmp = column;					//��ǰ�С���ǰ�зֱ�Ϊrow��column
	strpointer = str;									//����ָ���ȸ�ֵΪstr

	while ( *strpointer != '\0' )						//�ַ����Ƿ������
	{
		LCD1602_PrintChar( rowtmp, columntmp, *strpointer );  //�ڵ�ǰ�С���ǰ�д�ӡһ���ַ�
		
		strpointer++;										  //�޸�����ָ�룬ָ����һ��Ҫ��ӡ���ַ�
		columntmp++;										  //��ǰ��������һ��

		if ( columntmp > 16 )								  //������˵�ǰ�е����һ�У�����һ�еĵ�1�п�ʼ
		{
			columntmp = 1;									  //��1��

			rowtmp++;										  //��һ��
			if ( rowtmp > 2 )								  //�Ѿ��ǵ�2���ˣ���ص���1��
				rowtmp = 1;
		}	
	}

}
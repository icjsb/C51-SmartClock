#include "DS1302.h"

sbit CE		=	P3^5;	
sbit SCLK	=	P3^6;	
sbit SDA	=	P3^4;

unsigned char clockdata[8];
unsigned char clockdataBCD[8];
unsigned char BRAMdata[31];

//��DS1302дһ���ֽڵ�����
void DS1302_SPIwritebyte( unsigned char dat )
{
	unsigned char i;

	for ( i = 0; i < 8; i++ )
	{	
		SCLK = 0;
		SDA = ( dat >> i ) & 0x01;
				
		_nop_();
		SCLK = 1;
	}
}

//��DS1302��һ���ֽڵ�����
unsigned char DS1302_SPIreadbyte( )
{
	unsigned char i, tmp;
	
	tmp  = 0;
	for ( i = 0; i < 8; i++ )
	{
		if ( SDA )
			tmp = tmp | 0x80;
		tmp = tmp >> 1;

		SCLK = 1;
		_nop_();
		_nop_();
		SCLK = 0;
	}

	SDA = 0; _nop_(); _nop_();			 //���ӻ���������ʾ85����

	return tmp;
}

//��DS1302дһ���ֽڵ����ݵ���ַΪaddress�ĵ�Ԫ���Ĵ�����
void DS1302_writeybyte( unsigned char address, unsigned char dat )
{
	CE = 0; _nop_();; 
	SCLK = 0; _nop_();
	SDA = 0; _nop_();
	CE = 1; _nop_();

	DS1302_SPIwritebyte( address );
	DS1302_SPIwritebyte( dat );	
	
	CE = 0; _nop_();_nop_();
	SCLK = 1; _nop_();_nop_();
	SDA = 1; _nop_();_nop_();	 

}

//��DS1302��address�ĵ�Ԫ���Ĵ�������һ���ֽڵ�����
unsigned char DS1302_readbyte( unsigned char address )
{
	unsigned char tmp;

	tmp = 0;

	CE = 0; _nop_(); 
	SCLK = 0; _nop_();
	SDA = 0; _nop_();
	CE = 1; _nop_();

	DS1302_SPIwritebyte( address );
	tmp =  DS1302_SPIreadbyte( );

	CE = 0; _nop_();_nop_();
	SCLK = 1; _nop_();_nop_();
	SDA = 1; _nop_();_nop_();

	return tmp;
}


//ͻ��ģʽдʱ�����ݣ����ݴ����clockdataBCD[8]��
void DS1302_writeclockburst( )
{	 
	 unsigned char i;
	 
	 //ȡ��д����
	 DS1302_unlock();

	 CE = 0; _nop_();; 
	SCLK = 0; _nop_();
	SDA = 0; _nop_();
	CE = 1; _nop_();

	//д��ͻ��ģʽд�Ĵ�����ַ
	DS1302_SPIwritebyte( DS1302_CLOCKBURST + DS1302_WRITE );

	for ( i = 0; i < 8; i++ )	 //����д��8���ֽ�����
		DS1302_SPIwritebyte( clockdataBCD[i] );	
	
	CE = 0; _nop_();_nop_();
	SCLK = 1; _nop_();_nop_();
	SDA = 1; _nop_();_nop_();
	 
	 	 	
	 //����д����
	 DS1302_lock();
}


//ͻ��ģʽ��ʱ�����ݣ����ݴ����clockdataBCD[8]��
void DS1302_readclockburst( )
{
	unsigned char i;
	 
	 //ȡ��д����
	DS1302_unlock();

	CE = 0; _nop_();; 
	SCLK = 0; _nop_();
	SDA = 0; _nop_();
	CE = 1; _nop_();

	//д��ͻ��ģʽд�Ĵ�����ַ
	DS1302_SPIwritebyte( DS1302_CLOCKBURST + DS1302_READ );

	for ( i = 0; i < 8; i++ )	  //������ȡ8���ֽ�����
		clockdataBCD[i] = DS1302_SPIreadbyte( );	
	
	CE = 0; _nop_();_nop_();
	SCLK = 1; _nop_();_nop_();
	SDA = 1; _nop_();_nop_(); 
	 	 	
	 //����д����
	 DS1302_lock();
}


//ͻ��ģʽдram���ݣ����ݴ����BRAMdata[31]��
void DS1302_writeramburst( )
{
	 unsigned char i;
	 
	 //ȡ��д����
	 DS1302_unlock();

	 CE = 0; _nop_();; 
	SCLK = 0; _nop_();
	SDA = 0; _nop_();
	CE = 1; _nop_();

	//д��ͻ��ģʽд�Ĵ�����ַ
	DS1302_SPIwritebyte( DS1302_BRAMBURST + DS1302_WRITE );

	for ( i = 0; i < 31; i++ )	 //����д��31���ֽ�����
		DS1302_SPIwritebyte( BRAMdata[i] );	
	
	CE = 0; _nop_();_nop_();
	SCLK = 1; _nop_();_nop_();
	SDA = 1; _nop_();_nop_();	 
	 	 	
	//����д����
	DS1302_lock();	
}

//ͻ��ģʽ��ram���ݣ����ݴ����BRAMdata[31]��
void DS1302_readramburst( )
{
	unsigned char i;
	 
	 //ȡ��д����
	DS1302_unlock();

	CE = 0; _nop_();; 
	SCLK = 0; _nop_();
	SDA = 0; _nop_();
	CE = 1; _nop_();

	//д��ͻ��ģʽд�Ĵ�����ַ
	DS1302_SPIwritebyte( DS1302_BRAMBURST + DS1302_READ );

	for ( i = 0; i < 31; i++ )	 //������ȡ31���ֽ�����
		BRAMdata[i] = DS1302_SPIreadbyte( );	
	
	CE = 0; _nop_();_nop_();
	SCLK = 1; _nop_();_nop_();
	SDA = 1; _nop_();_nop_();
	 
	 	 	
	//����д����
	DS1302_lock();
}


//����������д������
void DS1302_lock()
{
	DS1302_writeybyte( DS1302_CONTROL +  DS1302_WRITE, 0x80 );
}

//������ȡ��д������
void DS1302_unlock()
{
	DS1302_writeybyte( DS1302_CONTROL +  DS1302_WRITE, 0x00 );
}


//����������ݣ����Ϊ������
unsigned char DS1302_getsecond()				  //��
{
	unsigned char tmp;

	//��ȡ�����ݣ�tmpΪBCD��
	tmp = DS1302_readbyte ( DS1302_SECOND + DS1302_READ );
	
	//(tmp & 0x70) >> 4�õ����ʮλ���֣�(tmp & 0x0F)�õ���ĸ�λ����
	return ( ((tmp & 0x70) >> 4) * 10 + (tmp & 0x0F) );
}

//��÷������ݣ����Ϊ������
unsigned char DS1302_getminute()				  //��
{
	unsigned char tmp;

	//��ȡ�����ݣ�tmpΪBCD��
	tmp = DS1302_readbyte ( DS1302_MINUTE + DS1302_READ );
	
	//(tmp & 0x70) >> 4�õ��ֵ�ʮλ���֣�(tmp & 0x0F)�õ��ֵĸ�λ����
	return ( ((tmp & 0x70) >> 4) * 10 + (tmp & 0x0F) );
}

//���Сʱ���ݣ����Ϊ�����룬24����
unsigned char DS1302_gethour()					  //ʱ
{
	unsigned char tmp;

	//��ȡСʱ���ݣ�tmpΪBCD��
	tmp = DS1302_readbyte ( DS1302_HOUR + DS1302_READ );

	//���λ��7������12���ơ�24����
	if ( tmp & 0x80 ) //==========================12Сʱ��
		//(( tmp & 0x20 ) >> 5)����AM(0)��PM(1),0x20��Ӧ��5λ,PM��Ҫ��12, AM����Ҫ��12
		//( tmp & 0x10 ) >> 4)�õ�ʱ��ʮλ���֣�0x10��Ӧ��4λ
		//(tmp & 0x0F)�õ�ʱ�ĸ�λ����  
		return ( (( tmp & 0x20 ) >> 5) * 12 + (( tmp & 0x10 ) >> 4) * 10  + ( tmp & 0x0F ) ) ;	
	else			//==========================24Сʱ��
		//( tmp & 0x20 ) >> 5)�õ�ʱ�ĵڶ���ʮλ���֣�(( tmp & 0x10 ) >> 4)�õ�ʱ�ĵ�һ��ʮλ���֣�(tmp & 0x0F)�õ�ʱ�ĸ�λ����
	    return ( (( tmp & 0x20 ) >> 5) * 10 + (( tmp & 0x10 ) >> 4) * 10  + ( tmp & 0x0F ) ) ;
}

//�������
unsigned char DS1302_getdate()					  //��
{
	unsigned char tmp;

	//��ȡ�������ݣ�tmpΪBCD��
	tmp = DS1302_readbyte ( DS1302_DATE + DS1302_READ );
	
	//(tmp & 0x30) >> 4�õ����ڵ�ʮλ���֣�(tmp & 0x0F)�õ����ڵĸ�λ����
	return ( ((tmp & 0x30) >> 4) * 10 + (tmp & 0x0F) );	
}

//����·�
unsigned char DS1302_getmonth()				  //��
{
	unsigned char tmp;

	//��ȡ�·����ݣ�tmpΪBCD��
	tmp = DS1302_readbyte ( DS1302_MONTH + DS1302_READ );
	
	//(tmp & 0x10) >> 4�õ��µ�ʮλ���֣�(tmp & 0x0F)�õ��µĸ�λ����
	return ( ((tmp & 0x10) >> 4) * 10 + (tmp & 0x0F) );	
}

//�������
unsigned char DS1302_getweekday()				  //��
{
	unsigned char tmp;

	//��ȡ�������ݣ�tmpΪBCD��
	tmp = DS1302_readbyte ( DS1302_WEEKDAY + DS1302_READ );
	
	//(tmp & 0x07)�õ����ڼ�
	return ( tmp & 0x07 );	
}

//������
unsigned char DS1302_getyear()					  //��
{
	unsigned char tmp;

	//��ȡ�������ݣ�tmpΪBCD��
	tmp = DS1302_readbyte ( DS1302_YEAR + DS1302_READ );
	
	//��4λΪ���ʮλ���֣���4λΪ��ĸ�λ����
	return ( ((tmp & 0xF0) >> 4) * 10 + (tmp & 0x0F) );
}



//����ʱ��---�����ݣ�����Ϊ������
void DS1302_setsecond( unsigned char second )	  //��
{
	if ( second > 59 )
		return;
	
	//�Ƚ���
	DS1302_unlock();

	//д�����ݣ���ַΪDS1302_SECOND + DS1302_WRITE����Ҫת��ΪBCD��
	//(second/10)�õ����ʮλ��( second %10 )�õ���ĸ�λ
	DS1302_writeybyte( DS1302_SECOND + DS1302_WRITE, (((second/10) & 0x07) << 4) | ( second %10 ) );
	
	//����
	DS1302_lock();
}

//����ʱ��---�����ݣ�����Ϊ������
void DS1302_setminute( unsigned char minute )	  //��
{
	if ( minute > 59 )
		return;
	
	//�Ƚ���
	DS1302_unlock();

	//д�����ݣ���ַΪDS1302_MINUTE + DS1302_WRITE����Ҫת��ΪBCD��
	//(second/10)�õ��ֵ�ʮλ��( second %10 )�õ��ֵĸ�λ
	DS1302_writeybyte( DS1302_MINUTE + DS1302_WRITE, (((minute/10) & 0x07) << 4) | ( minute %10 ) );
	
	//����
	DS1302_lock();
}

//����ʱ��---ʱ���ݣ�����Ϊ24Сʱ���ƶ����� 
void DS1302_sethour( unsigned char hour )		  //ʱ
{
	unsigned char tmp;	

	tmp = 0;

	//���DS1302��ǰ��Сʱ����
	if ( DS1302_readbyte ( DS1302_HOUR + DS1302_READ ) & 0x80 )						 //12Сʱ��
	{
		tmp = tmp | 0x80;				//����12Сʱ��
		if ( hour > 12 )				//PM
		{
			tmp = tmp | 0x20;			//��5λΪ1��ʾPM,Ϊ0��ʾAM��ʡ�ԣ�
		   	hour = hour - 12;
		}				
	}
	else									 //24Сʱ��
	{
		if ( hour > 20 )
		{
			tmp = tmp | 0x20;				//�ڶ���ʮ
		   	hour = hour - 10;;
		}
	}
	
	if ( hour > 9 )				//����12Сʱ�Ƶ�ʮλ��24Сʱ�Ƶĵ�һ��ʮ;
			tmp = tmp | 0x10;		//��4λ

	tmp = tmp | (( hour % 10 ) & 0x0F);	//��λΪ��4λ	

	//�Ƚ���
	DS1302_unlock();

	//д�����ݣ���ַΪDS1302_HOUR + DS1302_WRITE��tmp�Ѿ�ת��ΪBCD��
	DS1302_writeybyte( DS1302_HOUR + DS1302_WRITE, tmp );
	
	//����
	DS1302_lock();	
}

//����ʱ��---�������ݣ�����Ϊ������
void DS1302_setdate( unsigned char date )		  //��
{
	if ( date > 31 )
		return;
	
	//�Ƚ���
	DS1302_unlock();

	//д�����ݣ���ַΪDS1302_DATE + DS1302_WRITE����Ҫת��ΪBCD��
	//(date/10)�õ����ڵ�ʮλ��( date %10 )�õ����ڵĸ�λ
	DS1302_writeybyte( DS1302_DATE + DS1302_WRITE, (((date/10) & 0x03) << 4) | ( date %10 ) );
	
	//����
	DS1302_lock();
}

//����ʱ��---�·����ݣ�����Ϊ������
void DS1302_setmonth( unsigned char month )		//��
{
	if ( month > 12 || month < 1 )
		return;
	
	//�Ƚ���
	DS1302_unlock();

	//д�����ݣ���ַΪDS1302_MONTH + DS1302_WRITE����Ҫת��ΪBCD��
	//(month/10)�õ��µ�ʮλ��( month %10 )�õ��µĸ�λ
	DS1302_writeybyte( DS1302_MONTH + DS1302_WRITE, (((month/10) & 0x01) << 4) | ( month % 10 ) );
	
	//����
	DS1302_lock();	
}

//����ʱ��---�������ݣ�����Ϊ������
void DS1302_setweekday( unsigned char weekday )  //��
{
   	if ( weekday > 7 || weekday < 1 )			//���������Ч��
		return;
	
	//�Ƚ���
	DS1302_unlock();

	//д�����ݣ���ַΪDS1302_WEEKDAY + DS1302_WRITE����Ҫת��ΪBCD��
	//(weekday & 0x07)�õ�����ֵ
	DS1302_writeybyte( DS1302_WEEKDAY + DS1302_WRITE, ( weekday & 0x07 ) );
	
	//����
	DS1302_lock();
}

//����ʱ��---�����ݣ�����Ϊ������
void DS1302_setyear( unsigned char year )	  	//��
{
	if ( year > 99 )			//���������Ч��
		return;

	//�Ƚ���
	DS1302_unlock();

	//д�����ݣ���ַΪDS1302_YEAR + DS1302_WRITE����Ҫת��ΪBCD��
	//(weekday & 0x07)�õ�����ֵ
	DS1302_writeybyte( DS1302_YEAR + DS1302_WRITE, ( ((year/10) & 0x0F) << 4) | ((year % 10) & 0x0F) );
	
	//����
	DS1302_lock();
}



//����DS1302��ʱ�䣬�������ݴ����clockdata������
void DS1302_settime( )
{
	 DS1302_setsecond( clockdata[0] );	  		//��
	 DS1302_setminute( clockdata[1] );	  		//��
	 DS1302_sethour( clockdata[2] );		  //ʱ
	 DS1302_setdate( clockdata[3] );		  //��
	 DS1302_setmonth( clockdata[4] );	  		//��
	 DS1302_setyear( clockdata[5] );		  //��
	 DS1302_setweekday( clockdata[6] );  		//��
	 		
}

//��ȡDS1302��ʱ�䣬������ݴ����clockdata������ 
void DS1302_gettime( )
{
	clockdata[0]  = DS1302_getsecond();				  //��
	clockdata[1]  = DS1302_getminute();				  //��
	clockdata[2]  = DS1302_gethour();					  //ʱ
	clockdata[3]  = DS1302_getdate();					  //��
	clockdata[4]  = DS1302_getmonth();				  //��
	clockdata[5]  = DS1302_getyear();					  //��
	clockdata[6]  = DS1302_getweekday();				  //��	
}


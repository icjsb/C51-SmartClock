#include <reg51.h>
#define Timer(fr) 65536 - (12000000 / 12) / (fr << 1)
#define DIAO(n) (n << 1) / 3    //附点n分音符的换算
typedef unsigned char UCHAR;
typedef unsigned int UINT;
typedef unsigned long ULONG;
sbit BUZZ = P2^3;
UINT code Fre[] = 
{                                             //低音1-7，中音 1-7 和高音 1-7对应的频率列表
	262, 294, 330, 349, 392, 440, 494,
	523, 587, 659, 698, 784, 880, 988,
	1047, 1175, 1319, 1397, 1568, 1760, 1976
};
				    	
UINT code Time[] = 
{      //低音1-7，中音 1-7 和高音 1-7对应的定时器重载值
	Timer(262), Timer(294), Timer(330), Timer(349), Timer(392), Timer(440), Timer(494),
    Timer(523), Timer(587), Timer(659), Timer(698), Timer(784), Timer(880), Timer(988),
    Timer(1047), Timer(1175), Timer(1319), Timer(1397), Timer(1568), Timer(1760), Timer(1976),
	};
	
//小星星
UCHAR code xiaoxingxing[] = 
{      			   
   									 8,8,12,12,
                                    /* 13,13,12,
									 11,11,10,10,
									 9,9,8,
									 12,12,11,11,
									 10,10,9,
									 12,12,11,11,
									 10,10,9,*/
};
UCHAR code fenyinfu[] = 
{       //音名对应的时值，4表示4分音符，8表示8分音符，16表示16分音符
    4,4,4,4,
/*	4,4,2,
	4,4,4,4,
	4,4,2,
	4,4,4,4,
	4,4,2,
	4,4,4,4,
	4,4,2,*/	
};

bit enable = 1, TimeFlag = 0;
UCHAR T0RH = 0XFF, T0RL = 0X00;

void Timer0()
{
	EA = 1;
    TMOD |= 0X01;
    TH0 = T0RH;
    TL0 = T0RL;
    ET0 = 1;
    TR0 = 1;	
}

void Timer1()
{
    TMOD |= 0X10;
    TH1 = (65536-10)/256;
	TL1 = (65536-10)%256;
    ET1 = 1;	
}

void Delay(UINT n) 
{
    UINT i,j;
	for (j = 0; j < 110; j++)
      for (i = 0; i < n; i++) ;
}

UINT flag = 0; 
UCHAR i;
UCHAR idx;
void PlayMusic(UCHAR speed)  //speed 播放速度
{	   
    
    	//
    UINT Time_long = 0;	//当前音符的时值对应的定时器计数
    UINT Time_flag = 0;		//当前音符的发声时值对应的计数值
    for (i = 0; i < sizeof (xiaoxingxing); ) 
	{
        while (!TimeFlag) ;
        TimeFlag = 0;
        if (flag == 0) 
		{							  
            Time_long = (ULONG)240 * (ULONG)Fre[idx] / ((ULONG)fenyinfu[i] * (ULONG)speed);
            Time_flag = Time_long - (Time_long >> 2);       	//当前音符时值的前3/4发声，后1/4静音
            enable = 1;
            flag++;
     	}
        else 
		{
            if (flag == Time_long) 
			{
                flag = 0;
                i++;									
        	}
            else 
			{
                flag++;
                if (flag == Time_flag) 
				{
                    enable = 0;
                }
            }
        }
    }
}


void Clocker() 
{
    Timer0();
	Timer1();
    PlayMusic(90); 
}

void InterruptTmr0() interrupt 1 
{
    TH0 = T0RH;
    TL0 = T0RL;
    TimeFlag = 1;
	TR1 = 1;
    if (enable)
        BUZZ = ~BUZZ;
    else
        BUZZ = 1;
}

void InterruptTmr1() interrupt 3
{
	TR1 = 0;
	if (flag == 0) 
	{							  
		idx = xiaoxingxing[i] - 1;
		T0RH = Time[idx] >> 8;
		T0RL = Time[idx];
	}
	TH1=(65536-10)/256;
	TL1=(65536-10)%256;
}
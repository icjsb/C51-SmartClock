#define Timer(fr) 65536 - (12000000 / 12) / (fr << 1)
#define DIAO(n) (n << 1) / 3    //����n�������Ļ���


#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef UINT 
#define UINT unsigned int
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

UINT code Fre[] = 
{    //����1-7������ 1-7 �͸��� 1-7��Ӧ��Ƶ���б�
	262, 294, 330, 349, 392, 440, 494,
	523, 587, 659, 698, 784, 880, 988,
	1047, 1175, 1319, 1397, 1568, 1760, 1976
};
				    	
UINT code Tone[] = 
{      //����1-7������ 1-7 �͸��� 1-7��Ӧ�Ķ�ʱ������ֵ
	Timer(262), Timer(294), Timer(330), Timer(349), Timer(392), Timer(440), Timer(494),
    Timer(523), Timer(587), Timer(659), Timer(698), Timer(784), Timer(880), Timer(988),
    Timer(1047), Timer(1175), Timer(1319), Timer(1397), Timer(1568), Timer(1760), Timer(1976),
	};
UCHAR code music[] = 
{      //����  /*С����*/			   
	10,12,15,13,12,
	10,12,13,15,12,
	15,17,16,15,
	16,15,13,15,12,
	10,12,13,12,13,
	15,16,12,13,
	10,9,8,9,
	9,9,10,12,12,
	15,9,10,12,
	10,12,15,13,15,
	10,12,13,15,12,
	15,17,16,15,
	16,15,13,15,12,
	10,12,13,12,13,
	15,16,12,13,
	10,15,13,12,
	10,9,8,9,
	9,10,12,
	15,17,16,15,
	16,15,12,13,15,
};
UCHAR code Die[] = 
{       //������Ӧ��ʱֵ��4��ʾ4��������8��ʾ8��������16��ʾ16������
	DIAO(8),DIAO(8),DIAO(8),DIAO(8),2,
	DIAO(8),DIAO(8),DIAO(8),DIAO(8),2,
	2,DIAO(8),4,4,
	DIAO(8),DIAO(8),DIAO(8),DIAO(8),2,
	2,DIAO(8),4,DIAO(8),DIAO(8),
	4,DIAO(8),DIAO(8),2,
	DIAO(8),DIAO(8),4,4,
	4,DIAO(8),DIAO(8),4,4,
	4,DIAO(8),DIAO(8),2,
	DIAO(8),DIAO(8),DIAO(8),DIAO(8),2,
	DIAO(8),DIAO(8),DIAO(8),DIAO(8),2,
	2,DIAO(8),4,4,
	DIAO(8),DIAO(8),DIAO(8),DIAO(8),2,
	2,DIAO(8),4,DIAO(8),DIAO(8),
	4,DIAO(8),DIAO(8),2,
	2,DIAO(8),4,4,
	DIAO(8),DIAO(8),4,2,
	4,DIAO(8),2,
	2,DIAO(8),4,4,
	DIAO(8),DIAO(8),DIAO(8),DIAO(8),2,			 		 	
};
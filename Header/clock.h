#include<reg51.h>

extern bit clock_flag,show_clock_number,clock_logo;

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef UINT 
#define UINT unsigned int
#endif

void CLOCK_judge(UCHAR w,UCHAR hour,UCHAR minute);   //	����ʱ���ж�

void CLOCK_stop(UCHAR hour,UCHAR minute);	 //�ж����ӽ���
#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PAout(8)	// PA8  in1
#define LED1 PAout(11)	// PD2	in4
#define Yout PCout(6)	// in2
#define Xout PCout(7)	// in3
#define Wireless PAout(4)  //���߹��翪��
void LED_Init(void);//��ʼ��

		 				    
#endif

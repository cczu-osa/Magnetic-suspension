#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

extern vu32 ADC_value[];
extern vu16 Vx,Vy;
void Adc1_Init(void);
void Adc2_Init(void);
void  Adc3_Init(void);
u16 Get_Adc_Average1(void);
u16 Get_Adc_Average2(void);
u16 Get_Adc_Average3(void);
#endif 



























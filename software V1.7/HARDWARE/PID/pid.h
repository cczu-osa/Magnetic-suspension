#ifndef __PID_H
#define __PID_H	 
#include "sys.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "adc.h"
#include "math.h"

typedef struct
{
	float xK;                  //��Ԫ����ϵ��
    float xP;                  //�˴���P��I��D����������ѧϰ����
    float xI;
    float xD;
    float xError;  			   //��ǰ���
    float xError_1;			   //ǰһ�����
	float xError_2;			   //ǰǰ�����
	float wX[3];               //x��Ȩ��
	float xX[3];               //x��״ֵ̬
	int xout;				   //���
    
} XPID_typedef;


typedef struct
{
	float yK;                  //��Ԫ����ϵ��
	float yP;
	float yI;
	float yD;
	float yError;  		   //��ǰ���
	float yError_1;  		   //��һ�����
	float yError_2;		   	   //���ϴ����
	float wY[3];
	float yX[3];               //y��״ֵ̬
	int yout;
} YPID_typedef;

extern XPID_typedef XPID;
extern YPID_typedef YPID;

extern volatile int Xpwm,Ypwm;
extern volatile float PX,IX,DX,PY,IY,DY;
void TIM3_IRQHandler(void); 				//��ʱ����ʼ��
void TIM3_Int_Init(u16 arr, u16 psc);                 //pid���㺯���Ѿ������õ��жϺ�����
void PID_Init(void);															//pid��ʼ��
void PID_setpara(u16 xKp, u16 xKi, u16 xKd,u16 yKp, u16 yKi, u16 yKd);


#endif



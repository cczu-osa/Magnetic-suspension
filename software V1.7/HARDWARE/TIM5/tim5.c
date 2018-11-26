#include "tim5.h"
/*****************************************************************************************
�������ܣ���ʱ��5�жϳ�ʼ������
���룺u16 ��������, u16 Ԥ��Ƶ
�������
���ڣ�2017/4/21
*****************************************************************************************/
void TIM5_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); //ʹ�ܻ���ʧ��ָ����TIM�ж�	TIM2  ʹ��

    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    //TIM_Cmd(TIM5, ENABLE);  //ʹ��TIMx����

}
/*****************************************************************************************
�������ܣ���ʱ��5�ж�
���룺void
�������
���ڣ�2017/4/21
*****************************************************************************************/
void TIM5_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //����ж�
    {
	  //printf("Vx=%d  Vy=%d\r\n",Vx,Vy);
      //printf("Vx=%dXOUT=%dVy=%dYOUT=%d\r\n",Vx,XPID.xout,Vy,YPID.yout);
		printf("xw0=%.4f xw1=%.4f xw2=%.4f yw0=%.4f yw1=%.4f yw2=%.4f ",XPID.wX[0],XPID.wX[1],XPID.wX[2],YPID.wY[0],YPID.wY[1],YPID.wY[2]);
    }
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update );  //���TIMx���жϴ�����λ:TIM �ж�Դ
}



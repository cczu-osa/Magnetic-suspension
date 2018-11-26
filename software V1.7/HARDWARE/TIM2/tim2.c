#include "usart.h"
#include "tim2.h"
#include "usmart.h"
/*****************************************************************************************
�������ܣ���ʱ��2�жϳ�ʼ������
���룺u16 ��������, u16 Ԥ��Ƶ
�������
���ڣ�2017/4/21
*****************************************************************************************/
void TIM2_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //ʹ�ܻ���ʧ��ָ����TIM�ж�	TIM2  ʹ��

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����

}
/*****************************************************************************************
�������ܣ���ʱ��2�ж�
���룺void
�������
���ڣ�2017/4/21
*****************************************************************************************/
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //����ж�
    {
        float adcx3;
        adcx3 = Get_Adc_Average3();
        //printf("%.2f\r\n", adcx3);
        if(adcx3 > 1000)
        {
            PID_SWITCH(0x01);
        } else
        {
            PID_SWITCH(0x00);
        }
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update );  //���TIMx���жϴ�����λ:TIM �ж�Դ
}



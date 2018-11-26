#include "init.h"


void all_init(void)
{
    delay_init();	    	 //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
    uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
    LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�	
    PID_Init();         	//PID��ʼ��
	DMA_init();             //DMA��ʼ��  ���ȼ�3��3
    Adc1_Init();		  	//ADC��ʼ��    
    Adc2_Init();
    Adc3_Init();    
	TIM5_Int_Init(499, 7199);		//50ms------3,2----���ڴ�ӡ������Ϣ
    usmart_dev.init(72); 	//��ʼ��USMART  00ms-----1,3----����ɨ�贮��
	TIM1_PWM_Init(1999, 8); 		//0.25ms----pwmƵ�� 4Khz
    TIM3_Int_Init(499, 71);		//0.5ms------0,3----����PID���㣬���ö�ʱ��3    2Khz    
    TIM2_Int_Init(3999, 35999);  	//4000ms----3,1----���ڵ͹��Ŀ���---��ʱ��2�������趨�͹���  APB1 36Mhz*2 

}







#include "dma.h"


void DMA_init(void)
{
	DMA_InitTypeDef DMA_InitStructure;         //ʹ��DMA1��ͨ��1
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	
/***********************************************��ʼ��DMA1*************************************************/

	DMA_DeInit(DMA1_Channel1); 															//��ʼ��DMA1ͨ��1
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(ADC1->DR);						//�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_value;								//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 									//���赽�ڴ�
	DMA_InitStructure.DMA_BufferSize = 6; 												//����ͨ����С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 					//�����ַ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 							//�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; 		//��=4�ֽ�=32bit
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word; 				//��=4�ֽ�=32bit
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 									//ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; 								//ͨ�����ȼ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 										//�����ڴ浽�ڴ�
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); 										//��ʼ��
	
/***********************************************DMA�ж�����*************************************************/	
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_InitStructure);            // Enable the DMA Interrupt 
	
	DMA_ClearFlag(DMA1_FLAG_TC1);
    DMA_ClearITPendingBit(DMA1_IT_TC1);
  
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);  //DMA��������ж�
    DMA_Cmd(DMA1_Channel1, ENABLE);						//ʹ��DMA1	
}

/**************************ƽ���˲�*****************************************/
void filter(void)
{
	u8 i=0;
	u16 x=0;
	u16 y=0;
	do
	{
		y+=(u16)(ADC_value[i]&0x0000ffff);  //��λ��ADC1
		x+=(u16)((ADC_value[i]&0xffff0000)>>16);
		i++;
	}
	while(i<6);
	Vy=y/6;
	Vx=x/6;
}

void DMA1_Channel1_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC1) != RESET)
    {
        filter();
        DMA_ClearITPendingBit(DMA1_IT_TC1);
    }
}	







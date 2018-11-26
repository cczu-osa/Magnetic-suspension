#include "adc.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//ADC ����
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
vu32 ADC_value[6]={0};
vu16 Vx,Vy;

//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3
void  Adc1_Init(void)
{
/***********************************************��ʼ���ṹ��*************************************************/
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

/***********************************************��ʼ��ʱ��*************************************************/
   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE );	 //ʹ��ADC1ͨ��ʱ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	
/***********************************************��ʼ��io*************************************************/
    //PA1\PA2 ��Ϊģ��ͨ����������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
/***********************************************��ʼ��ADC1*************************************************/
   
	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

    ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;									//ADC����ģʽ:ͬ������ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;										//ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;									//ģ��ת�������ڶ��ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;					//ת���������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;								//ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;												//˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC1, &ADC_InitStructure);													//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
/*********************************************ͬ��������**************************************************/
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5 );  		//����71.5����

/***********************************************����ADC1*************************************************/
	
	ADC_DMACmd(ADC1, ENABLE);//����ADC DMA֧��
    ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
    ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼
    while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
    ADC_StartCalibration(ADC1);	 //����ADУ׼
    while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
/***********************************************����ת��*************************************************/	
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1������ת����������
}


/*************************************************ADC2��ʼ��****************************/
void  Adc2_Init(void)
{
/***********************************************��ʼ���ṹ��*************************************************/
    ADC_InitTypeDef  ADC_InitStructure;

/***********************************************��ʼ��ʱ��*************************************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE );	 //ʹ��ADC1ͨ��ʱ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M	
	
/***********************************************��ʼ��ADC2************************************************/

    ADC_DeInit(ADC2);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

    ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;	//ADC����ģʽ:ͬ������ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת�������ڶ��
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת���������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC2, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
	
/*********************************************ͬ��������**************************************************/
	
	ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 1, ADC_SampleTime_239Cycles5);

/***********************************************����ADC2*************************************************/
   
	ADC_DMACmd(ADC1, ENABLE);//����ADC DMA֧��
	ADC_Cmd(ADC2, ENABLE);	//ʹ��ָ����ADC1
    ADC_ResetCalibration(ADC2);	//ʹ�ܸ�λУ׼
    while(ADC_GetResetCalibrationStatus(ADC2));	//�ȴ���λУ׼����
    ADC_StartCalibration(ADC2);	 //����ADУ׼
    while(ADC_GetCalibrationStatus(ADC2));	 //�ȴ�У׼����
	
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);		//ʹ��ָ����ADC2������ת����������
}

/*************************************************ADC3��ʼ��****************************/
void  Adc3_Init(void)
{
    ADC_InitTypeDef  ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC3, ENABLE );	 //ʹ��ADC3ͨ��ʱ��

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

    //PA1 ��Ϊģ��ͨ����������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_DeInit(ADC3);  //��λADC3,������ ADC3 ��ȫ���Ĵ�������Ϊȱʡֵ

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת���������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC3, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���


    ADC_Cmd(ADC3, ENABLE);	//ʹ��ָ����ADC1
    ADC_ResetCalibration(ADC3);	//ʹ�ܸ�λУ׼
    while(ADC_GetResetCalibrationStatus(ADC3));	//�ȴ���λУ׼����
    ADC_StartCalibration(ADC3);	 //����ADУ׼
    while(ADC_GetCalibrationStatus(ADC3));	 //�ȴ�У׼����

}


/**************************���ADC1ֵ  ch:ͨ��ֵ 1*****************************************/

//u16 Get_Adc_Average1(void)
//{
//    u32 temp_val = 0;
//    u8 t;
//    for(t = 0; t < 6; t++)
//    {
//		//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
//    ADC_RegularChannelConfig(ADC1,1, 1, ADC_SampleTime_71Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����
//    ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1������ת����������
//    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
//        temp_val += ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
//    }
//    return temp_val / 6;
//}


///**************************���ADC2ֵ  ch:ͨ��ֵ 2*****************************************/

//u16 Get_Adc_Average2(void)
//{
//    u32 temp_val = 0;
//    u8 t;
//    for(t = 0; t < 6; t++)
//    {    //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
//    ADC_RegularChannelConfig(ADC2, 2, 1, ADC_SampleTime_71Cycles5 );	//ADC2,ADCͨ��,����ʱ��Ϊ239.5����
//    ADC_SoftwareStartConvCmd(ADC2, ENABLE);		//ʹ��ָ����ADC1������ת����������
//    while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//�ȴ�ת������
//        temp_val += ADC_GetConversionValue(ADC2);//�������һ��ADC2�������ת�����
//    }
//    return temp_val / 6;
//}

/**************************���ADC3ֵ  ch:ͨ��ֵ 3*****************************************/

u16 Get_Adc_Average3(void)
{
    u32 temp_val = 0;
    u8 t;
    for(t = 0; t < 4; t++)
    {
        //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
        ADC_RegularChannelConfig(ADC3, 3, 1, ADC_SampleTime_71Cycles5 );	//ADC3,ADCͨ��,����ʱ��Ϊ239.5����
        ADC_SoftwareStartConvCmd(ADC3, ENABLE);		//ʹ��ָ����ADC1������ת����������
        while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//�ȴ�ת������
        temp_val += ADC_GetConversionValue(ADC3); //�������һ��ADC2�������ת�����
    }
    return temp_val / 4;
}








#include "usmart.h"
#include "usmart_str.h"
////////////////////////////�û�������///////////////////////////////////////////////
//������Ҫ�������õ��ĺ�����������ͷ�ļ�(�û��Լ����)



//�������б��ʼ��(�û��Լ����)
//�û�ֱ������������Ҫִ�еĺ�����������Ҵ�
struct _m_usmart_nametab usmart_nametab[] =
{
#if USMART_USE_WRFUNS==1 	//���ʹ���˶�д����
    (void*)read_addr, "u32 read_addr(u32 addr)",
    (void*)write_addr, "void write_addr(u32 addr,u32 val)",
#endif
    (void*)PID_setpara, "PID_setpara(u16 xKp, u16 xKi, u16 xKd,u16 yKp, u16 yKi, u16 yKd)",	//(void*)fun(int a);��������һ��ָ�룬��void����
    (void*)Debug, "void Debug(u8 flag)",
    (void*)PID_SWITCH, "void PID_SWITCH(u8 flag)",
};
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//�������ƹ�������ʼ��
//�õ������ܿغ���������
//�õ�����������
struct _m_usmart_dev usmart_dev =
{
    usmart_nametab,
    usmart_init,
    usmart_cmd_rec,
    usmart_exe,
    usmart_scan,
    sizeof(usmart_nametab) / sizeof(struct _m_usmart_nametab), //��������
    0,	  	//��������
    0,	 	//����ID
    1,		//������ʾ����,0,10����;1,16����
    0,		//��������.bitx:,0,����;1,�ַ���
    0,	  	//ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ��
    0,		//�����Ĳ���,��ҪPARM_LEN��0��ʼ��
};

/*****************************************************************************************
�������ܣ�����ģʽ����
���룺u8 flag
�������
���ڣ�2017/4/22
*****************************************************************************************/
void Debug(u8 flag)
{
    if(0x01==flag)
    {
        TIM_Cmd(TIM5, ENABLE); //ʹ��TIM5
    }
    else
    {
        TIM_Cmd(TIM5, DISABLE); //ʹ��TIM5
    }
}

/*****************************************************************************************
�������ܣ�pid���أ����ڿ������幦�ܣ���͹���ģʽ
���룺u8 flag
�������
���ڣ�2017/4/22
*****************************************************************************************/
u8 pow_state=0x01;       //ϵͳ����״ֵ̬��0001�����������У�0000����͹���
void PID_SWITCH(u8 flag)
{
    if((flag==0x01)&&(pow_state!=flag))             
    {
		GPIOA->CRH&=0XFFFF0FF0; 
		GPIOA->CRH|=0X0000B00B;//PA8 ����������� 
        TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3����
        TIM_Cmd(TIM1, ENABLE); //ʹ��TIM1
		pow_state=0x01;
    }
    else if((flag==0x00)&&(pow_state!=flag))
    {
		TIM_Cmd(TIM3, DISABLE);  //�ر�PID����
        TIM_Cmd(TIM1, DISABLE); //ʹ��TIM1
		GPIOA->CRH&=0XFFFF0FF0; 
		GPIOA->CRH|=0X00003003;//PA8 ��ͨ������� 
		GPIOA->ODR|=0<<8;      //PA8 �����
		GPIOA->ODR|=0<<1;      //PA11 �����
        Xout=0;
		Yout=0;
		pow_state=0x00;
    }
}

















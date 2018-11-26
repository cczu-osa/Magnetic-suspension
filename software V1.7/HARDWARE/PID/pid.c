#include "pid.h"


volatile int Xpwm, Ypwm;
volatile float PX, IX, DX, PY, IY, DY;
XPID_typedef XPID;
YPID_typedef YPID;
u8 Xdirection, Ydirection;


//PID_setpara(22,0,135,24,0,148)
//PID_setpara(22,0,150,23,0,150)
//#define XP 2.2f                  			//PID������ֵ
//#define XI 0.0f               		    //��f��ʾ�ø������ʽ����
//#define XD 15.0f                   		//
//#define YP 2.3f
//#define YI 0.0f
//#define YD 15.0f
#define X_DIRECTION_FLAG	0x01         //���������־λ
#define Y_DIRECTION_FLAG	0x01         //


/*****************************************************************************************
�������ܣ�PID���Ƴ�ʼ�����Ը��������г�ʼ����������ʱ��
���룺��
�������
���ڣ�2016/7/15
*****************************************************************************************/
void PID_Init(void)
{					// 
	XPID.xK=3; 		//5		5
	XPID.xP=0.8;	//0.8	0.8
	XPID.xI=0.8;	//0.8	0.8
	XPID.xD=0.8;	//0.8	6
	XPID.xError=0;
	XPID.xError_1=0;
	XPID.xError_2=0;
	XPID.wX[0]=1;
	XPID.wX[1]=1;
	XPID.wX[2]=1;
	//y
	YPID.yK=3;       //5	5
	YPID.yP=0.8;      //0.8	0.8
	YPID.yI=0.8;	 //0.8	0.8
	YPID.yD=0.8;      //0.8	6
	YPID.yError=0;          
	YPID.yError_1=0;
	YPID.yError_2=0;
	YPID.wY[0]=1;
	YPID.wY[1]=1;
	YPID.wY[2]=1;
    
}

/*****************************************************************************************
????:XPID????????
??:Current:???,PID�data
??:??????
??:2017/4/25
*****************************************************************************************/
int XNNPIDcalc(float current,XPID_typedef* xPID)
{
	float sumw=0;
	xPID->xError=2048-current;      

/***********************�Ľ�Hebbѧϰ�㷨************************************************************/	
	xPID->wX[0]=xPID->wX[0]+(xPID->xP)*(xPID->xError)*(xPID->xout)*(xPID->xX[0]);
	xPID->wX[1]=xPID->wX[1]+(xPID->xI)*(xPID->xError)*(xPID->xout)*(xPID->xX[1]);
	xPID->wX[2]=xPID->wX[2]+(xPID->xD)*(xPID->xError)*(xPID->xout)*(xPID->xX[2]);
	
	sumw=fabs(xPID->wX[0])+fabs(xPID->wX[1])+fabs(xPID->wX[2]);  
	
	xPID->wX[0]=fabs(xPID->wX[0]/=sumw);   
	xPID->wX[1]=fabs(xPID->wX[1]/=sumw);   
	xPID->wX[2]=fabs(xPID->wX[2]/=sumw);   
	
	xPID->xX[0]=xPID->xError;         			//P ����λ����PID����
	xPID->xX[1]=xPID->xError-xPID->xError_1;	 //I	   
	xPID->xX[2]=xPID->xError-2*xPID->xError_1+xPID->xError_2;    //D
	
	xPID->xout=xPID->xK*((xPID->wX[0]*xPID->xX[0])+(xPID->wX[2]*xPID->xX[2]));  
	//xPID->xout=2*xPID->xX[0]+12*xPID->xX[1]+2*xPID->xX[2];	
	
	xPID->xError_2=xPID->xError_1;   
	xPID->xError_1=xPID->xError;	

	return xPID->xout<-2000?(-2000):(xPID->xout>2000?2000:xPID->xout);
}


/*****************************************************************************************
????:YPID????????
??:Current:???,PID�data
??:??????
??:2017/4/25
*****************************************************************************************/
int YNNPIDcalc(float current,YPID_typedef* yPID)
{
	float sumw=0;
	yPID->yError=2048-current;      //??????
/***********************�Ľ�Hebbѧϰ�㷨************************************************************/
	yPID->wY[0]=yPID->wY[0]+(yPID->yP)*(yPID->yError)*(yPID->yout)*(yPID->yX[0]);
	yPID->wY[1]=yPID->wY[1]+(yPID->yI)*(yPID->yError)*(yPID->yout)*(yPID->yX[1]);//wkp_1+xiteP*error(k)*u_1*(2*error(k)-error_1)
	yPID->wY[2]=yPID->wY[2]+(yPID->yD)*(yPID->yError)*(yPID->yout)*(yPID->yX[2]);

	sumw=fabs(yPID->wY[0])+fabs(yPID->wY[1])+fabs(yPID->wY[2]);   
	
	yPID->wY[0]=fabs(yPID->wY[0]/=sumw);   //???? ???????  0?P
	yPID->wY[1]=fabs(yPID->wY[1]/=sumw);	//1?i
	yPID->wY[2]=fabs(yPID->wY[2]/=sumw);	//2?d
	
	yPID->yX[0]=yPID->yError;   //P
	yPID->yX[1]=yPID->yError-yPID->yError_1;				   //I
	yPID->yX[2]=yPID->yError-2*yPID->yError_1+yPID->yError_2;   //D
	
	yPID->yout=yPID->yK*((yPID->wY[0]*yPID->yX[0])+(yPID->wY[2]*yPID->yX[2]));  //????
	//yPID->yout=2*yPID->yX[0]+12*yPID->yX[1]+2*yPID->yX[2];
	
	yPID->yError_2=yPID->yError_1;   
	yPID->yError_1=yPID->yError;	
	
	return yPID->yout<-2000?(-2000):(yPID->yout>2000?2000:yPID->yout);
}



/*****************************************************************************************
�������ܣ�PID���Ʋ������ԣ��޸�Kp��Ki,Kd�Ĳ���
���룺u16 Kp,u16 Ki,u16 Kd
�������
���ڣ�2017/4/8
*****************************************************************************************/
void PID_setpara(u16 xKp, u16 xKi, u16 xKd, u16 yKp, u16 yKi, u16 yKd)
{
    XPID.xP = (float)xKp / 10;
    XPID.xI = (float)xKi / 10;
    XPID.xD = (float)xKd / 10;
    YPID.yP = (float)yKp / 10;
    YPID.yI = (float)yKi / 10;
    YPID.yD = (float)yKd / 10;
    printf("xP=%.2fxI=%.2fxD=%.2fyP=%.2fyI=%.2fyD=%.2f\r\n", XPID.xP, XPID.xI, XPID.xD, YPID.yP, YPID.yI, YPID.yD);
}
/*****************************************************************************************
�������ܣ���ʱ��3�жϳ�ʼ������
���룺u16 ��������, u16 Ԥ��Ƶ
�������
���ڣ�2016/12/13
*****************************************************************************************/
void TIM3_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //ʹ�ܻ���ʧ��ָ����TIM�ж�	TIM3  ʹ��

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����

}


/*****************************************************************************************
�������ܣ��жϷ����������AD�ɵ�ѹ�͵�����PID����PWM���
���룺��
�������
���ڣ�2016/7/15
*****************************************************************************************/

void TIM3_IRQHandler(void)      //TIM1�ж�
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update );  //���TIMx���жϴ�����λ:TIM �ж�Դ
        /********************************PID����*******************************/
        Xpwm = XNNPIDcalc(Vx, &XPID);  						//����PID�㷨
        Ypwm = YNNPIDcalc(Vy, &YPID);  						//����PID�㷨
        if(Xpwm >= 0)
        {   //Xpwm>0ʱ��˵��������������Ҫ������
            Xdirection = 0x01;
            TIM_OC1PolarityConfig(TIM1, TIM_OCPolarity_Low);
        }
        else                                                      //Xpwm<0ʱ��˵���������ң�����Ҫ������
        {
            Xdirection = 0x02;
            TIM_OC1PolarityConfig(TIM1, TIM_OCPolarity_High);
            Xpwm = -Xpwm;
        }
        if(Ypwm >= 0)   											 //Ypwm>0ʱ��˵���������ϣ�����Ҫ������
        {
            Ydirection = 0x01;
            TIM_OC4PolarityConfig(TIM1, TIM_OCPolarity_Low);
        }
        else                                                      //Ypwm<0ʱ��˵���������£�����Ҫ������
        {
            Ydirection = 0x02;
            TIM_OC4PolarityConfig(TIM1, TIM_OCPolarity_High);
            Ypwm = -Ypwm;
        }
        /*******************************�������*******************************/

        if(Xdirection & X_DIRECTION_FLAG)
        {
            Xout = 0;        //x��������
        }
        else
        {
            Xout = 1;        //x��������
        }
        if (Ydirection & Y_DIRECTION_FLAG)
        {
            Yout = 0;			//y��������
        }
        else
        {
            Yout = 1;		  //y��������
        }
        TIM_SetCompare1(TIM1, Xpwm); //����pwmֵ
        TIM_SetCompare4(TIM1, Ypwm); //����pwmֵ
    }
}




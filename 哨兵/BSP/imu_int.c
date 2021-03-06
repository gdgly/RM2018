#include "headfile.h"
/**********************************
函数名：ImuInt_Gpio_Config
入口参数：无
出口参数：无
功能：配置PE1即MPU_INT引脚
*********************************/
static void ImuInt_Gpio_Config()
{
	 GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);// GPIOE时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // MPU_INT引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE1

}
/**********************************
函数名：IMU_NVIC_Config
入口参数：无
出口参数：无
功能：配置外部中断1中断优先级
*********************************/
static void IMU_NVIC_Config()
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断1
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
}
/**********************************
函数名：IMU_NVIC_Config
入口参数：无
出口参数：无
功能：配置外部中断1触发方式
*********************************/
static void IMU_EXTI_Config()
{
  EXTI_InitTypeDef   EXTI_InitStructure;
	
	/* 配置EXTI_Line1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);//连接中断线1
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
}
/*****************************************
函数名：IMU_NVIC_Config
入口参数：无
出口参数：无
功能：配置外部中断1的引脚，NVIC，和触发方式
******************************************/
void IMU_INT_Config()
{
  ImuInt_Gpio_Config();
	IMU_NVIC_Config();
	IMU_EXTI_Config();

}
/*****************************************
函数名：EXTI1_IRQHandler
入口参数：无
出口参数：无
功能：外部中断1中断函数，对陀螺仪数据采样，得
出Y轴P轴的角速度，并积分出Y轴角度
******************************************/
void EXTI1_IRQHandler(void)
{
  	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
		{
		   GetPitchYawGxGyGz(&mydata);
		}
	   EXTI_ClearITPendingBit(EXTI_Line1);//清除LINE1上的中断标志位 
}


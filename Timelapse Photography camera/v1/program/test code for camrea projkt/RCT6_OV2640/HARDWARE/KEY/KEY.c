#include "KEY.h"
#include "delay.h"

//KEY0:PC1 KEY1:PC13
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	//PC13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;		//PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

u8 KEY_Scan(u8 mode)
{ 
	static u8 key_up=1;
	if(mode)key_up=1;
	if(key_up&&(KEY0==0||KEY1==0))
	{
	delay_ms(10);
	key_up=0;
	if(KEY0==0)return KEY0_PRES;
	else if(KEY1==0)return KEY1_PRES;
	}else if(KEY0==1&&KEY1==1)key_up=1;
	return 0;
}
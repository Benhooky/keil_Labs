
#include <stm32f10x.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Sound (int iL, int iH) {
  int iC=iH;
  while (iL>0) {
    iL--;
    iC--;
    if (iC == 0) {
      GPIOA->ODR  ^= 1<<5;
      iC=iH;
    }
  }
  for (iC=100000;iC>0;iC--); // В конце можно сделать паузу
}  


void Delay(int i)
{
  while(i--);
}
GPIO_InitTypeDef GPIO_InitStructure;//динамик
GPIO_InitTypeDef KeyBoardIn;// 4 пина на вход
GPIO_InitTypeDef KeyBoardOut;// 3 пина на выход
int main()
{
	int iDel = 1000000;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  KeyBoardIn.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	KeyBoardIn.GPIO_Speed=GPIO_Speed_50MHz;
	KeyBoardIn.GPIO_Mode=GPIO_Mode_IPD;
  GPIO_Init(GPIOC,&KeyBoardIn);
	KeyBoardOut.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4;
	KeyBoardOut.GPIO_Speed=GPIO_Speed_50MHz;
	KeyBoardOut.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_Init(GPIOA,&KeyBoardOut);
	
/*
	while(22)
	{
				Sound(200000, 200);
				Sound(200000, 400);
				Sound(200000, 600);
				Sound(200000, 800);
				Sound(200000, 1000);
		
		
	}
	*/
    while(22)
		{	
			GPIOC->ODR|=0xf;
			GPIOA->ODR = 0x12;
			if(!(GPIOC->IDR & 1))
				Sound(200000, 100);
			if(!(GPIOC->IDR & 2))
				Sound(200000, 300);
			if(!(GPIOC->IDR & 8))
				Sound(200000, 500);
			if(!(GPIOC->IDR & 4))	
				Sound(200000, 700);	
			GPIOA->ODR = 0x3;
			if(!(GPIOC->IDR & 1))
				Sound(200000, 900);
			if(!(GPIOC->IDR & 2))
				Sound(200000, 1100);
			if(!(GPIOC->IDR & 8))
				Sound(200000, 1300);
			if(!(GPIOC->IDR & 4))	
				Sound(200000, 1500);		
			GPIOA->ODR = 0x11;
			if(!(GPIOC->IDR & 1))
				Sound(200000, 1700);
			if(!(GPIOC->IDR & 2))
				Sound(200000, 1900);
			if(!(GPIOC->IDR & 8))
				Sound(200000, 2100);
			if(!(GPIOC->IDR & 4))	
				Sound(200000, 2300);		
//			GPIOA->ODR = 0xA;
// ..
		}

}

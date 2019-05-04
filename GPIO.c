#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

int main(void){
	GPIO_InitTypeDef gpio;
	GPIO_InitTypeDef gpio_in;

	//Enable Clock for GPIOC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB,ENABLE);

	//Configure PC13 as Push-Pull output
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&gpio);

	gpio_in.GPIO_Pin = GPIO_Pin_9;
	gpio_in.GPIO_Speed = GPIO_Speed_2MHz;
	gpio_in.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&gpio_in);

	uint8_t state=0;

	while(1){
		if((GPIOB->IDR & (1<<9))==0){
			if(state==0) state=1;
			else state=0;
		}

		if(state==0)
			GPIOC->BSRR = (1<<13);
		else
			GPIOC->BRR = (1<<13);

		for(int x=0;x<55000;x++);
	}
}

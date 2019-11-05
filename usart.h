#ifndef USART_H
#define USART_H

//#include <stm32f10x.h>
//#include <stm32f10x_gpio.h>
//#include <stm32f10x_rcc.h>
//#include <stm32f10x_usart.h>
#include "stm32f10x_conf.h"


#define  RED    GPIO_Pin_6
#define  BLUE   GPIO_Pin_7
#define  ORANGE GPIO_Pin_8
#define  GREEN  GPIO_Pin_9

//static __IO uint32_t TimingDelay;

void Delay(uint32_t);
void SysTick_Handler(void);

void usart_init(void);

int uart_open(USART_TypeDef* USARTx, uint32_t baud, uint32_t flags);
int uart_close(USART_TypeDef* USARTx);
int uart_putc(int c, USART_TypeDef* USARTx);
int uart_getc(USART_TypeDef* USARTx);
int u_putc(uint8_t c);
void u_print(uint8_t* string);
int u_getc(void);
void u_gets(char*);

#endif

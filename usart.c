//#include <stm32f10x.h>
//#include <stm32f10x_rcc.h>
//#include <stm32f10x_gpio.h>
//#include <stm32f10x_usart.h>
#include "usart.h"

//#include <stdint.h>

// 5 -- Timer Code

static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime)
{
    TimingDelay = nTime;
    while(TimingDelay != 0);
}

void SysTick_Handler(void)
{
    if(TimingDelay != 0x00)
        TimingDelay--;
}

int u_putc(uint8_t c)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART1->DR = ( c & 0xff);
    return 0;
}

int uart_putc(int c, USART_TypeDef* USARTx)
{
    while(USART_GetFlagStatus(USARTx , USART_FLAG_TXE) == RESET);
    USARTx->DR = ( c & 0xff);
    return 0;
}


int uart_getc(USART_TypeDef* USARTx)
{
    while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
    return USARTx->DR & 0xff;
}

void u_print(uint8_t* str)
{
    int i = 0;
    while(str[i])
        u_putc(str[i++]);
}

int u_getc(void)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return USART1->DR & 0xff;
}

void u_gets(char* tmp)
{
    while(*tmp)
    {
        *tmp++ = u_getc();
    }    
}

void usart_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStructure;
    
  //Initialize usart/gpio clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 |
                           RCC_APB2Periph_AFIO |
                           RCC_APB2Periph_GPIOA, ENABLE);
    
    //Configure usart pins
    
    GPIO_StructInit(&GPIO_InitStruct);
    // Initialize USART1_Tx
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // Initialize USART1_RX
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);


    // Initialize USART structure
    USART_StructInit(&USART_InitStructure);
    // Modify USART_InitStructure for non-default values, e.g.
    // USART_InitStructure.USART_BaudRate = 38400;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1,&USART_InitStructure);
    //void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);

    USART_Cmd(USART1, ENABLE);
    //void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
}

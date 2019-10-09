
#include "stm32f10x.h"

volatile __IO uint32_t TimingDelay;
void Delay(uint32_t nTime);
void SysTick_Handler(void);

int main(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    GPIOC->CRL &= ~GPIO_CRL_CNF;
    GPIOC->CRL |= GPIO_CRL_MODE6;

    while(1)
    {
        GPIOC->BSRR |= GPIO_BSRR_BS6;
        Delay(250);
        GPIOC->BSRR |= GPIO_BSRR_BR6;
        Delay(250);
    }
}

void Delay(uint32_t nTime)
{
    TimingDelay = nTime;
    while(TimingDelay != 0);
}

void SysTick_Handler(void)
{
    if(TimingDelay != 0)
        TimingDelay--;
}

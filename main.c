
#include "spi.h"
#include "usart.h"

uint8_t txbuf[4], rxbuf[4];
uint16_t txbuf16[4], rxbuf16[4];
uint8_t* message = "CQ CQWW CONTEST DE RA7KF";
 
uint8_t size(uint8_t*); //calculate the number of bytes

int main()
{
	
	uint8_t received[30];
	
	usart_init();
    eepromInit();
    eepromReadStatus();
   
    //eepromWrite(message, sizeof(message)/ sizeof(uint8_t), 0x0000);
	eepromRead(received, size(message), 0x0005);
	u_print(received);
	u_print("\n\r");
	
  
	/*
    for(int i = 0; i < 7; i++) 
    {
       __nop;
    } */
	
    eepromReadStatus();
      
}

uint8_t size(uint8_t* msg)
{
	return (sizeof(msg) / sizeof (uint8_t));
}
	



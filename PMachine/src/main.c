#include "clk_conf.h"
#include <iostm8s103f3.h>
#include "led.h"
#include "uart.h"

int main( void )
{
  // Configure CLK to internal 16M clock
  Clk_conf();
  uart_conf();
  LED_Conf();
  EnableInterrupt;
  while(1)
  {
    UART1_SendByte('|');
    Delay(40000);
    Delay(60000);
    Blink(1);
    UART1_SendString(RxBuffer, UART_RX_NUM & 0x3F);
  }
  
  return 0;
}

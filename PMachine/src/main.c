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
  while(1)
  {
    UART1_SendByte('a');
    Delay(20000);
    Delay(20000);
    Blink(5);
  }
  
  return 0;
}

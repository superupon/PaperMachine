#include "clk_conf.h"
#include <iostm8s103f3.h>
#include "led.h"
#include "uart.h"

int main( void )
{
  // Configure CLK to internal 16M clock
  Clk_conf();
  uart_conf();
  while(1)
  {
    UART1_SendByte('a');
    Delay(20000);
    Delay(20000);
  }
  
  return 0;
}

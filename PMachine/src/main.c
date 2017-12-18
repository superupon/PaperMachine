#include "clk_conf.h"
#include <iostm8s103f3.h>
#include "led.h"


int main( void )
{
  // Configure CLK to internal 16M clock
  Clk_conf();
  
  return 0;
}

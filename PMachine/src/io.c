#include "io.h"


// Set PA1 as Output Port to Trigger Paper machine to work
void Output_Conf(void)
{
  PA_DDR |= 0x02;
  PA_CR1 |= 0x02;
  PA_CR2 |= 0x00;
}

// Set PA1 to high voltage
void Output_High()
{
  PA_ODR |= 0x02;
}

// Set PA1 to low voltage
void Output_Low()
{
  PA_ODR &= ~0x02;
}

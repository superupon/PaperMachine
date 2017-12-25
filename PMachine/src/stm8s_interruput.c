/**************************************************************************************
 * File Name : stm8s_interrupt.c
 * Description : interrupt service function   
 * Writer : superupon@126.com
****************************************************************************************/

#include "uart.h"
u8 RxBuffer[RxBufferSize];
u8 UART_RX_NUM=0;
#pragma vector=1
__interrupt void TRAP_IRQHandler(void)
{
  
}
#pragma vector=2
__interrupt void TLI_IRQHandler(void)
{
  
}
#pragma vector=3
__interrupt void AWU_IRQHandler(void)
{
  
}
#pragma vector=4
__interrupt void CLK_IRQHandler(void)
{
  
  
}
#pragma vector=5
__interrupt void EXTI_PORTA_IRQHandler(void)
{
  
}
#pragma vector=6
__interrupt void EXTI_PORTB_IRQHandler(void)
{
  
}
#pragma vector=7
__interrupt void EXTI_PORTC_IRQHandler(void)
{
  
}
#pragma vector=8
__interrupt void EXTI_PORTD_IRQHandler(void)
{
 
  
}
#pragma vector=9
__interrupt void EXTI_PORTE_IRQHandler(void)
{
   
}


#pragma vector=0xC
__interrupt void SPI_IRQHandler(void)
{
  
}
#pragma vector=0xD
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{
  

}
#pragma vector=0xE
__interrupt void TIM1_CAP_COM_IRQHandler(void)
{
  
}

#pragma vector=0xF
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
     
}
#pragma vector=0x10
__interrupt void TIM2_CAP_COM_IRQHandler(void)
{
  
}


#pragma vector=0x11
__interrupt void TIM3_UPD_OVF_BRK_IRQHandler(void)
{
  
}
#pragma vector=0x12
__interrupt void TIM3_CAP_COM_IRQHandler(void)
{
  
}


#pragma vector=0x13
__interrupt void UART1_TX_IRQHandler(void)
{
  
}
#pragma vector=0x14
__interrupt void UART1_RX_IRQHandler(void)
{
  u8 Res;
  if (UART1_SR & UART1_FLAG_RXNE)
  {
    /*Receive Interrupt, must ended by 0x0d or 0x0a*/
    Res = (uint8_t)UART1_DR;
    /*(USART1->DR);*/
    /*Read received data, when finished, clear RXNE Interrupt Flag*/
    if ((UART_RX_NUM & 0x80) == 0) /*Received is not finished*/
    {
      if (UART_RX_NUM & 0x40) /*Recived 0x0d*/
      {
        if (Res != 0x0a)
          UART_RX_NUM = 0; /*Receive error, restart*/
        else
          UART_RX_NUM |= 0x80; /*Reviced finshed*/
      }
      else /*No receive 0x0d*/
      {
        if (Res == 0x0d)
          UART_RX_NUM |= 0x40;
        else
        {
          RxBuffer[UART_RX_NUM & 0X3F] = Res;
          UART_RX_NUM++;
          if (UART_RX_NUM > 63)
            UART_RX_NUM = 0; /*Receive Error, restart*/
        }
      }
    }
  }
}

#pragma vector=0x15
__interrupt void I2C_IRQHandler(void)
{
  
}


#pragma vector=0x16
__interrupt void UART3_TX_IRQHandler(void)
{
  
}
#pragma vector=0x17
__interrupt void UART3_RX_IRQHandler(void)
{
  
}


#pragma vector=0x18
__interrupt void ADC2_IRQHandler(void)
{
   
}


#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
  
}

#pragma vector=0x1A
__interrupt void EEPROM_EEC_IRQHandler(void)
{
  
}


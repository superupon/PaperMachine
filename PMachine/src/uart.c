/***************************************************************************
 * File Name: uart.c
 * Description: Serial Port Functions
 * Writer: superupon@126.com
 * Revision: 2011-12-20
    |--------------------|
    |  USART1_TX-PD5     |
    |  USART1_RX-PD6     |
    |--------------------|
***************************************************************************/

#include "uart.h"
#include "string.h"

/**************************************************************************
 * Fuction Name: uart_conf
 * Description: Configure uart
 *************************************************************************/
void uart_conf(void)
{
  unsigned int baud_div=0;
  
  UART1_CR1 = (0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0); 
  /*1 start bit, 8 data bit, stop bit set by CR3, no parity, disable parity interrupt*/
  UART1_CR2 = (0<<7)|(0<<6)|(1<<5)|(0<<4)|(1<<3)|(1<<2); 
  /*Enable send and receive, enable receive interrupt, disable send interrupt*/
  UART1_CR3 = (0<<6)|(0<<4)|(0<<3); /*Set 1 stop bit, not enable SCLK*/        
  UART1_CR5 = (0<<2)|(0<<1);     
  /*Keep Default Setting*/
  
  /*Set baud rate*/
  baud_div = HSIClockFreq / BaudRate;           /*Calculate frequency division factor*/
  UART1_BRR2 = baud_div & 0x0f;
  UART1_BRR2 |= ((baud_div & 0xf000) >> 8);
  UART1_BRR1 = ((baud_div & 0x0ff0) >> 4);    /*Set BRR2 first, then BRR1*/
  
  UART1_CR1 |= (0<<5);                        /*Enable UART*/
}

/**************************************************************************
 * Function Name: UART1_SendByte
 * Description ��uart port will send a byte
 * Input  ��u8 data
 * Example: UART1_SendByte('a')
 *************************************************************************/
void UART1_SendByte(u8 data)
{
  UART1_DR = data;
  /* Loop until the end of transmission */
  while (!(UART1_SR & UART1_FLAG_TXE));
}

/**********************************************************************************
 * Function Name: UART1_SendByte
 * Description: Use uart to send string 
 * Input: u8* Data,u16 len
 * Example: UART1_SendString("iCreate STM8",sizeof("iCreate STM8"))
 **********************************************************************************/
void UART1_SendString(u8* Data,u16 len)
{
  u16 i = 0;
  for (; i < len; i++)
    UART1_SendByte(Data[i]);
}

/**********************************************************************************
 * Function Name: UART1_ReceiveByte
 * Description: uart receive a byte
 * Return: return a byte data
 * Example: temp=UART1_ReceiveByte()
 **********************************************************************************/
u8 UART1_ReceiveByte(void)
{
  u8 USART1_RX_BUF;
  while (!(UART1_SR & UART1_FLAG_RXNE))
    ;
  USART1_RX_BUF = (uint8_t)UART1_DR;
  return USART1_RX_BUF;
}

void Clear_ReceiveBuff()
{
  u8 i = 0;
  for(i = 0; i < RxBufferSize; i++)
  {
    RxBuffer[i] = 0x00;
  }
  UART_RX_NUM = 0;
}

u8 Find_Recv_Str(u8* str_to_find)
{
  return (strstr(RxBuffer, str_to_find)!= NULL);
}

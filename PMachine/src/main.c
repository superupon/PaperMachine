#include "clk_conf.h"
#include <iostm8s103f3.h>
#include "led.h"
#include "uart.h"
#include "gprs.h"

int send_command()
{
  Clear_ReceiveBuff();
  UART1_SendString("AT", strlen("AT"));
  UART1_SendByte(0x0D);
  Delay(50000);
  return Find_Recv_Str("OK");
}
int main( void )
{
  int i = 0;
  // Configure CLK to internal 16M clock
  Clk_conf();
  uart_conf();
  LED_Conf();
  EnableInterrupt;
  while(1)
  {
    i = Check_Status();
    //Clear_ReceiveBuff();
    //UART1_SendByte(0x41);
    //UART1_SendByte(0x54);
    //UART1_SendByte(0x47);
    //UART1_SendByte(0x0D);
    //UART1_SendByte(0x0A);
    //UART1_SendByte('|');
    //UART1_SendString("AT", strlen("AT"));
    //UART1_SendByte(0x0D);
    //Delay(500000);
    //Delay(600000);
    //i = Find_Recv_Str("OK");
    //i = send_command();
    if(i)
    {
      Blink(1);
      send_data_to_server("\"115.159.154.49\",3000","hello,GA6 tcp test!");//发送数据到服务器
    }
    else
    {
      Blink(5);
    }
    //UART1_SendString(RxBuffer, UART_RX_NUM & 0x3F);
  }
  
  return 0;
}

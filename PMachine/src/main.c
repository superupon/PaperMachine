#include "clk_conf.h"
#include <iostm8s103f3.h>
#include "led.h"
#include "uart.h"
#include "gprs.h"
#include "io.h"

int main( void )
{
  int i = 0;
  u8 index = 0;
  int ret = 0;
  char end_char[2];
  int counter = 0;

  end_char[0] = 0x1A; //End Character
  end_char[1] = '\0';

  // Configure CLK to internal 16M clock
  Clk_conf();
  uart_conf();
  LED_Conf();
  Output_Conf();
  EnableInterrupt;


  while(1)
  {
    if(!i)
      i = Check_Status();

    if(i)
    {
      if (counter == 50)
      {
        ret = send_data_to_server("\"115.159.154.49\",3000", phone_str);//发送数据到服务器
        // Get Phone Number from SIM CARD
        Get_PhoneNumber();
        counter = 0;
      }

      ret = send_at_command("AT+CIPSTATUS", "CONNECT OK", 50 * 2);
      if(ret)
      {
        send_at_command("AT+CIPSEND", ">", 50); 
        UART1_SendString("b",1);
        send_at_command_end(end_char, "SEND OK", 50);
        Delay(50000);
      }
      ret = Find_Recv_Str("ONE");
      if(ret)
      {
        Blink(1);
        Output_Low();
        Delay(200000);
        Output_High();
      }

      ret = Find_Recv_Str("THREE");
      if(ret)
      {
        for(index = 0; index < 3; index++)
        {
          Output_Low();
          Delay(200000);
          Output_High();
          Delay(600000);
        }
      }
    }
    counter++;
  }

  return 0;
}

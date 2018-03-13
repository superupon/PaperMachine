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
  int counter = 100;
  int close_counter = 0;
  u8 response_flag = 0;
  u8 response_3_flag = 0;
  u16 heart_beat_count = 0;
  u16 check_gprs_count = 0;

  end_char[0] = 0x1A; //End Character
  end_char[1] = '\0';

  // Configure CLK to internal 16M clock
  Clk_conf();
  uart_conf();
  LED_Conf();
  Output_Conf();
  //Output_High();
  ResetGPRS_Conf();
  Reset_GPRS();
  EnableInterrupt;


  while(1)
  {    
    if(!i)
      i = Check_Status();
    
    if(response_flag)
    {
      response_flag = 0;
      Blink(1);
      Output_Low();
      Delay(300000);
      Output_High();
      Delay(300000);
    }
    
    if(response_3_flag)
    {
      response_3_flag = 0;
      Blink(1);
      for(index = 0 ; index < 3; index++)
      {
        Output_Low();
        Delay(300000);
        Output_High();
        Delay(600000);
      }   
    }
    
    if(i)
    {
      if (counter == 2000)
      {
        // Get Phone Number from SIM CARD
        Get_PhoneNumber();
        if(close_counter == 100)
        {
           send_at_command("AT+CIPCLOSE", "OK", 50 * 2);
           close_counter = 0;
        }
        close_counter++;
        if(check_gprs_count == 6)
        {
          check_gprs_count = 0;
          if(heart_beat_count == 0)
          {
            Reset_GPRS();
            Delay(10000);
            send_data_to_server("\"www.jiqizhixing.cn\",3000", "Reset GPRS Device");
          }
          heart_beat_count = 0;
        }
        check_gprs_count++;
        ret = send_data_to_server("\"www.jiqizhixing.cn\",3000", phone_str);//发送数据到服务器
        counter = 0;
      }

      ret = Find_Recv_Str("ONE");
      if(ret)
      {
        Clear_ReceiveBuff();
        response_flag = 1;
      }

      ret = Find_Recv_Str("THREE");
      if(ret)
      {
        Clear_ReceiveBuff();
        response_3_flag = 1;     
      }
      
      ret = Find_Recv_Str("TWO");
      if(ret)
      {
        heart_beat_count++;
        Clear_ReceiveBuff();   
      }
      Delay(1000);
    }
    counter++;
    Output_High();
  }

  return 0;
}

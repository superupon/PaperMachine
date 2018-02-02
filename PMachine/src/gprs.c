#include "gprs.h"
#include "uart.h"
#include "string.h"
#include "stdlib.h"
char server_ip_port_cmd[45];
char phone_str[128];

static void delay(u32 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

int send_at_command(u8* send_buff, u8* answer, u16 interval_time)
{
  Clear_ReceiveBuff();
  UART1_SendString(send_buff, strlen((char*)send_buff));
  UART1_SendByte(0x0D);
  delay(50000);
  return Find_Recv_Str(answer);
}

int send_at_command_end(u8* send_buff, u8* answer, u16 interval_time)
{
  Clear_ReceiveBuff();
  UART1_SendString(send_buff, strlen((char *)send_buff));
  delay(500000);
  return Find_Recv_Str(answer);
}

int Check_Status(void)
{
  int ret;
  ret = send_at_command("AT", "OK", 50);

  ret = send_at_command("AT+CPIN?", "READY", 50);

  ret = send_at_command("ATE0","OK", 50);
  return ret;
}

int send_data_to_server(char *server_IP_and_port, char *content)
{
  u8 ret;
  char end_char[2];

  end_char[0] = 0x1A; //End Character
  end_char[1] = '\0';

  ret = send_at_command("AT+CIPSTATUS", "CONNECT OK", 50 * 2); //查询连接状态
  if (ret == 1)                                                //说明服务器处于连接状态
  {
    ret = send_at_command("AT+CIPSEND", ">", 50); //开发发送数据
    if (ret == 0)
    {
      return AT_CIPSEND_ERROR;
    }

    UART1_SendString(content, strlen(content));

    ret = send_at_command_end(end_char, "SEND OK", 250); //发送结束符，等待返回ok,等待5S发一次，因为发送数据时间可能较长
    if (ret == 0)
    {
      return END_CHAR_ERROR;
    }

    return 1;
  }

  ret = send_at_command("AT+CGATT=1", "OK", 50 * 7); //附着网络
  if (ret == 0)
  {
    return AT_CGATT_ERROR;
  }

  ret = send_at_command("AT+CGACT=1,1", "OK", 50 * 2); //激活网络
  if (ret == 0)
  {
    return AT_CGATT1_ERROR;
  }

  memset(server_ip_port_cmd, '\0', 45);
  strcpy(server_ip_port_cmd, "AT+CIPSTART=\"TCP\",");
  strcat(server_ip_port_cmd, server_IP_and_port);

  ret = send_at_command(server_ip_port_cmd, "CONNECT OK", 50 * 2); //连接服务器
  if (ret == 0)
  {
    return AT_CIPSTART_ERROR;
  }
  ret = send_at_command("AT+CIPSEND", ">", 50); //开发发送数据
  if (ret == 0)
  {
    return AT_CIPSEND_ERROR;
  }

  UART1_SendString(content, strlen(content));
  ret = send_at_command_end(end_char, "SEND OK", 250); //发送结束符，等待返回ok,等待5S发一次，因为发送数据时间可能较长
  if (ret == 0)
  {
    return END_CHAR_ERROR;
  }
  return 1;
}

void Get_PhoneNumber()
{
  Clear_ReceiveBuff();
  UART1_SendString("AT+CIMI", strlen("AT+CIMI"));
  UART1_SendByte(0x0D);
  delay(50000);
  strncpy(phone_str, RxBuffer, 64);
}

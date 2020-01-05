#include "OLED12864.h"
#include "uart1.h"
int main( void )
{
  u8 ACK=0;
  CLK_CKDIVR=0X00;
  delay(200);  
  uart1_init();
  I2C_init();
  printf("≤‚ ‘IIC—∞÷∑at24c02:\r\n");
  I2C_Start();
  ACK=I2C_WBit(0XA0);
  if (ACK)
  {
    printf("there's no at24c02\r\n");
  }
  else
  {
    printf("FIND a at24c02!\r\n");
  }
  I2C_Stop();
  ACK=0;
  printf("≤‚ ‘IIC—∞÷∑OLED12864:\r\n");
  I2C_Start();
  ACK=I2C_WBit(0X78);
  if (ACK)
  {
    printf("there's no OLED12864\r\n");
  }
  else
  {
    printf("FIND a OLED12864\r\n");
  }
  I2C_Stop();
  ACK=0;
  printf("≤‚ ‘IIC—∞÷∑fake hardwear:\r\n");
  I2C_Start();
  ACK=I2C_WBit(0X89);
  if (ACK)
  {
    printf("there's no hardwear\r\n");
  }
  else
  {
    printf("FIND a hardwear\r\n");
  }
  I2C_Stop();
  ACK=0;
  OLED_init();
  for (u8 j = 0; j < 8; j++)
  {
    for (u8 i = 0; i < 128; i++)
    {
      OLED_SetPos(i,j);
      OLED_Wdata(0X81);
    }
  }
}
#include "OLED12864.h"
#include "OLED_codetab.h"

/*********************OLEDд����************************************/
void OLED_Wcmd(u8 cmd)
{
    I2C_Start();
    I2C_WBit(0X78);
    I2C_WBit(0X00);
    I2C_WBit(cmd);
    I2C_Stop();
}
/*********************OLEDд����************************************/
void OLED_Wdata(u8 data)
{
    I2C_Start();
    I2C_WBit(0X78);
    I2C_WBit(0X40);
    I2C_WBit(data);
    I2C_Stop();
}
/*********************OLED������ʾ�����************************************/
void OLED_SetPos(u8 x,u8 y)
{
    OLED_Wcmd(0xb0+y);
    OLED_Wcmd((( x & 0xf0)>>4)|0x10);
    OLED_Wcmd(( x & 0x0f)|0x00);
}
/*********************OLEDȫ��************************************/
void OLED_Fill(u8 bmp_data) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_Wcmd(0xb0+y);
		OLED_Wcmd(0x01);
		OLED_Wcmd(0x10);
		for(x=0;x<128;x++)
		OLED_Wdata(bmp_data);
	}
}
/*********************OLED��λ************************************/
void OLED_CLS(void)
{
	u8 y,x;
	for(y=0;y<8;y++)
	{
		OLED_Wcmd(0xb0+y);
		OLED_Wcmd(0x01);
		OLED_Wcmd(0x10);
		for(x=0;x<128;x++)
		OLED_Wdata(0);
	}
}
/*********************OLED��ʼ��************************************/
void OLED_init(void)
{
    delayms(500);
    OLED_Wcmd(0xae);//--turn off oled panel  //�ر����
    OLED_Wcmd(0x00);//---set low column address    //���õ��е�ַ
    OLED_Wcmd(0x10);//---set high column address   //���ø��е�ַ
    OLED_Wcmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F) //���ÿ�ʼ��ַ
    OLED_Wcmd(0x81);//--set contrast control register  //���õ��е�ַ
    OLED_Wcmd(Brightness); // Set SEG Output Current Brightness  //���öԱȶȿ��ƼĴ���
    OLED_Wcmd(0xa1);//--Set SEG/Column Mapping     //���÷ֶ�/��ӳ��
	OLED_Wcmd(0xc8);//Set COM/Row Scan Direction   ������/��ɨ�跽��
    OLED_Wcmd(0xa6);//--set normal display         ����������ʾ
    OLED_Wcmd(0xa8);//--set multiplex ratio(1 to 64)  ���ö�·���ñ���
    OLED_Wcmd(0x3f);//--1/64 duty  
    OLED_Wcmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)  ������ʾƫ����λӳ��RAM������
	OLED_Wcmd(0x00);//-not offset  ��ƫ��
	OLED_Wcmd(0xd5);//--set display clock divide ratio/oscillator frequency  ������ʾ��ʱ��/����Ƶ��
	OLED_Wcmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec ���÷�Ƶ�ȣ���ʱ������Ϊ100֡/��
	OLED_Wcmd(0xd9);//--set pre-charge period ����Ԥ���׶�
	OLED_Wcmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock Ԥ�����Ϊ15��ʱ�ӣ��ŵ���Ϊ1��ʱ��
	OLED_Wcmd(0xda);//--set com pins hardware configuration ����com����Ӳ������
	OLED_Wcmd(0x12);
	OLED_Wcmd(0xdb);//--set vcomh     ����VCOM h
	OLED_Wcmd(0x40);//Set VCOM Deselect Level 
	OLED_Wcmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02) ����ҳ��Ѱַģʽ
	OLED_Wcmd(0x02);// 
	OLED_Wcmd(0x8d);//--set Charge Pump enable/disable ���ó�������/����
	OLED_Wcmd(0x14);//--set(0x10) disable              ������
	OLED_Wcmd(0xa4);// Disable Entire Display On (0xa4/0xa5) ����0xa4/0xa5�ϵ�������ʾ
	OLED_Wcmd(0xa6);// Disable Inverse Display On (0xa6/a7)  ����0xa6/a7������ʾ
	OLED_Wcmd(0xaf);//--turn on oled panel //�����
	OLED_CLS(); //��ƽ
	OLED_SetPos(0,0);
}
// void OLED_P8x16Str(u8 x, y,u8 ch[])
// {

// }
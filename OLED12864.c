#include "OLED12864.h"

extern u8 F6x8[][6];
extern u8 F8X16[];
extern u8 F16x16[];
extern u8 F16x32[];
extern u8 F32x32[];
/*********************OLED写命令************************************/
void OLED_Wcmd(u8 cmd)
{
    I2C_Start();
    I2C_WBit(0X78);
    I2C_WBit(0X00);
    I2C_WBit(cmd);
    I2C_Stop();
}
/*********************OLED写数据************************************/
void OLED_Wdata(u8 data)
{
    I2C_Start();
    I2C_WBit(0X78);
    I2C_WBit(0X40);
    I2C_WBit(data);
    I2C_Stop();
}
/*********************OLED设置显示坐标点************************************/
void OLED_SetPos(u8 x,u8 y)
{
    OLED_Wcmd(0xb0+y);
    OLED_Wcmd((( x & 0xf0)>>4)|0x10);
    OLED_Wcmd(( x & 0x0f)|0x01);
}
/*********************OLED全屏************************************/
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
/*********************OLED复位************************************/
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
/*********************OLED初始化************************************/
void OLED_init(void)
{
    delayms(500);
    OLED_Wcmd(0xae);//--turn off oled panel  //关闭面板
    OLED_Wcmd(0x00);//---set low column address    //设置低列地址
    OLED_Wcmd(0x10);//---set high column address   //设置高列地址
    OLED_Wcmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F) //设置开始地址
    OLED_Wcmd(0x81);//--set contrast control register  //设置低列地址
    OLED_Wcmd(Brightness); // Set SEG Output Current Brightness  //设置对比度控制寄存器
    OLED_Wcmd(0xa1);//--Set SEG/Column Mapping     //设置分段/列映射
	OLED_Wcmd(0xc8);//Set COM/Row Scan Direction   设置列/行扫描方向
    OLED_Wcmd(0xa6);//--set normal display         设置正常显示
    OLED_Wcmd(0xa8);//--set multiplex ratio(1 to 64)  设置多路复用比率
    OLED_Wcmd(0x3f);//--1/64 duty  
    OLED_Wcmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)  设置显示偏移移位映射RAM计数器
	OLED_Wcmd(0x00);//-not offset  不偏移
	OLED_Wcmd(0xd5);//--set display clock divide ratio/oscillator frequency  设置显示分时比/振荡器频率
	OLED_Wcmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec 设置分频比，将时钟设置为100帧/秒
	OLED_Wcmd(0xd9);//--set pre-charge period 设置预充电阶段
	OLED_Wcmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock 预充电设为15个时钟，放电设为1个时钟
	OLED_Wcmd(0xda);//--set com pins hardware configuration 设置com引脚硬件配置
	OLED_Wcmd(0x12);
	OLED_Wcmd(0xdb);//--set vcomh     设置VCOM h
	OLED_Wcmd(0x40);//Set VCOM Deselect Level 
	OLED_Wcmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02) 设置页面寻址模式
	OLED_Wcmd(0x02);// 
	OLED_Wcmd(0x8d);//--set Charge Pump enable/disable 设置充电泵启用/禁用
	OLED_Wcmd(0x14);//--set(0x10) disable              不启用
	OLED_Wcmd(0xa4);// Disable Entire Display On (0xa4/0xa5) 禁用0xa4/0xa5上的整个显示
	OLED_Wcmd(0xa6);// Disable Inverse Display On (0xa6/a7)  禁用0xa6/a7反向显示
	OLED_Wcmd(0xaf);//--turn on oled panel //打开面板
	OLED_CLS(); //清平
	OLED_SetPos(0,0);
}
void OLED_P6x8Str(u8 x,u8 y,u8 ch[])
{
	u8 c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		OLED_SetPos(x,y);
		for(i=0;i<6;i++)
        	OLED_Wdata(F6x8[c][i]);
		x+=6;
		j++;
	}
}
void OLED_P8x16Str(u8 x,u8 y,u8 ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		OLED_SetPos(x,y);
		for(i=0;i<8;i++)
			OLED_Wdata(F8X16[c*16+i]);
		OLED_SetPos(x,y+1);
		for(i=0;i<8;i++)
			OLED_Wdata(F8X16[c*16+i+8]);
		x+=8;
		j++;
	}
}
void OLED_P16x16Ch(u8 x,u8 y,u8 N)
{
	u8 wm=0;
	unsigned int adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Wdata(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Wdata(F16x16[adder]);
		adder += 1;
	} 	  	
}
void OLED_P16x32Ch(u8 x,u8 y,u8 N)
{
	u8 wm=0;
	unsigned int adder=64*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Wdata(F16x32[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Wdata(F16x32[adder]);
		adder += 1;
	} 	
	OLED_SetPos(x,y + 2);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Wdata(F16x32[adder]);
		adder += 1;
	} 
	OLED_SetPos(x,y + 3);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Wdata(F16x32[adder]);
		adder += 1;
	}
}
void OLED_P32x32Ch(u8 x,u8 y,u8 N)
{
	u8 wm=0;
	unsigned int adder=64*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 32;wm++)
	{
		OLED_Wdata(F32x32[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 32;wm++)
	{
		OLED_Wdata(F32x32[adder]);
		adder += 1;
	} 	
	OLED_SetPos(x,y + 2);
	for(wm = 0;wm < 32;wm++)
	{
		OLED_Wdata(F32x32[adder]);
		adder += 1;
	} 
	OLED_SetPos(x,y + 3);
	for(wm = 0;wm < 32;wm++)
	{
		OLED_Wdata(F32x32[adder]);
		adder += 1;
	}
}
void OLED_Display()
{
	OLED_init();
	OLED_P16x16Ch(0,0,13);
	OLED_P16x16Ch(32,0,21);
	// OLED_P8x16Str(64,0,17);
	// OLED_P8x16Str(72,0,16);
	// OLED_P8x16Str(80,0,16);
	// OLED_P8x16Str(88,0,16);
	// OLED_P8x16Str(96,0,16);
	// OLED_P8x16Str(104,0,16);
	OLED_P16x16Ch(112,0,17);

	OLED_P16x32Ch(0,2,12);
	OLED_P16x32Ch(16,2,2);
	OLED_P16x32Ch(32,2,5);
	OLED_P16x32Ch(48,2,10);
	OLED_P16x32Ch(64,2,3);
	OLED_P16x32Ch(80,2,7);
	OLED_P32x32Ch(96,2,0);
}
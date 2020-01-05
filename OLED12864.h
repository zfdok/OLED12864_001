#include "iic.h"
void OLED_Wcmd(u8 cmd);
void OLED_Wdata(u8 data);
void OLED_SetPos(u8 x,u8 y);
void OLED_Fill(u8 bmp_dat);
void OLED_CLS(void);
void OLED_init(void);
//void OLED_P8x16Str(u8 x, y,u8 ch[]);
//void OLED_P16x16Ch(u8 x,u8 y,u8 N);

#define Brightness 0xCF
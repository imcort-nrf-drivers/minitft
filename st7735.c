/* vim: set ai et ts=4 sw=4: */
#include "st7735.h"
#include "transfer_handler.h"

#define USE_HORIZONTAL 0

static void ST7735_WriteCommand(uint8_t cmd) {

		digitalWrite(TFT_DC, 0);
		digitalWrite(TFT_CS, 0);
		spi_transfer(&cmd, 1, NULL, 0);
		digitalWrite(TFT_CS, 1);
	
}

static void ST7735_WriteData(uint8_t* buff, size_t buff_size) {

		digitalWrite(TFT_DC, 1);
		digitalWrite(TFT_CS, 0);
		
		spi_send(buff, buff_size);
		
		digitalWrite(TFT_CS, 1);

}

static void ST7735_WriteData8(uint8_t buff) {

		ST7735_WriteData(&buff, 1);

}

static void ST7735_WriteData16(uint16_t buff) {

		uint8_t sendbuf[2];
		sendbuf[0] = buff >> 8;
		sendbuf[1] = buff;
		ST7735_WriteData(sendbuf, 2);

}

void ST7735_SetAddressWindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    
		if(USE_HORIZONTAL==0)
		{
				ST7735_WriteCommand(0x2a);
				ST7735_WriteData16(x1+26);
				ST7735_WriteData16(x2+26);
				ST7735_WriteCommand(0x2b);
				ST7735_WriteData16(y1+1);
				ST7735_WriteData16(y2+1);
				ST7735_WriteCommand(0x2c);
		}
		else if(USE_HORIZONTAL==1)
		{
				ST7735_WriteCommand(0x2a);
				ST7735_WriteData16(x1+26);
				ST7735_WriteData16(x2+26);
				ST7735_WriteCommand(0x2b);
				ST7735_WriteData16(y1+1);
				ST7735_WriteData16(y2+1);
				ST7735_WriteCommand(0x2c);
		}
		else if(USE_HORIZONTAL==2)
		{
				ST7735_WriteCommand(0x2a);
				ST7735_WriteData16(x1+1);
				ST7735_WriteData16(x2+1);
				ST7735_WriteCommand(0x2b);
				ST7735_WriteData16(y1+26);
				ST7735_WriteData16(y2+26);
				ST7735_WriteCommand(0x2c);
		}
		else
		{
				ST7735_WriteCommand(0x2a);//????????
				ST7735_WriteData16(x1+1);
				ST7735_WriteData16(x2+1);
				ST7735_WriteCommand(0x2b);//????????
				ST7735_WriteData16(y1+26);
				ST7735_WriteData16(y2+26);
				ST7735_WriteCommand(0x2c);//???????
		}
	
}

void ST7735_Init() {
		
		//pinMode(TFT_RESET, OUTPUT);
		pinMode(TFT_DC, OUTPUT);
		pinMode(TFT_CS, OUTPUT);
		pinMode(TFT_BL, OUTPUT);
		
		digitalWrite(TFT_CS, 1);
		digitalWrite(TFT_BL, 1);
	
    ST7735_WriteCommand(0x11);     //Sleep out
		delay(120);                //Delay 120ms
		ST7735_WriteCommand(0xB1);     //Normal mode
		ST7735_WriteData8(0x05);   
		ST7735_WriteData8(0x3C);   
		ST7735_WriteData8(0x3C);   
		ST7735_WriteCommand(0xB2);     //Idle mode
		ST7735_WriteData8(0x05);   
		ST7735_WriteData8(0x3C);   
		ST7735_WriteData8(0x3C);   
		ST7735_WriteCommand(0xB3);     //Partial mode
		ST7735_WriteData8(0x05);   
		ST7735_WriteData8(0x3C);   
		ST7735_WriteData8(0x3C);   
		ST7735_WriteData8(0x05);   
		ST7735_WriteData8(0x3C);   
		ST7735_WriteData8(0x3C);   
		ST7735_WriteCommand(0xB4);     //Dot inversion
		ST7735_WriteData8(0x03);   
		ST7735_WriteCommand(0xC0);     //AVDD GVDD
		ST7735_WriteData8(0xAB);   
		ST7735_WriteData8(0x0B);   
		ST7735_WriteData8(0x04);   
		ST7735_WriteCommand(0xC1);     //VGH VGL
		ST7735_WriteData8(0xC5);   //C0
		ST7735_WriteCommand(0xC2);     //Normal Mode
		ST7735_WriteData8(0x0D);   
		ST7735_WriteData8(0x00);   
		ST7735_WriteCommand(0xC3);     //Idle
		ST7735_WriteData8(0x8D);   
		ST7735_WriteData8(0x6A);   
		ST7735_WriteCommand(0xC4);     //Partial+Full
		ST7735_WriteData8(0x8D);   
		ST7735_WriteData8(0xEE);   
		ST7735_WriteCommand(0xC5);     //VCOM
		ST7735_WriteData8(0x0F);   
		ST7735_WriteCommand(0xE0);     //positive gamma
		ST7735_WriteData8(0x07);   
		ST7735_WriteData8(0x0E);   
		ST7735_WriteData8(0x08);   
		ST7735_WriteData8(0x07);   
		ST7735_WriteData8(0x10);   
		ST7735_WriteData8(0x07);   
		ST7735_WriteData8(0x02);   
		ST7735_WriteData8(0x07);   
		ST7735_WriteData8(0x09);   
		ST7735_WriteData8(0x0F);   
		ST7735_WriteData8(0x25);   
		ST7735_WriteData8(0x36);   
		ST7735_WriteData8(0x00);   
		ST7735_WriteData8(0x08);   
		ST7735_WriteData8(0x04);   
		ST7735_WriteData8(0x10);   
		ST7735_WriteCommand(0xE1);     //negative gamma
		ST7735_WriteData8(0x0A);   
		ST7735_WriteData8(0x0D);   
		ST7735_WriteData8(0x08);   
		ST7735_WriteData8(0x07);   
		ST7735_WriteData8(0x0F);   
		ST7735_WriteData8(0x07);   
		ST7735_WriteData8(0x02);   
		ST7735_WriteData8(0x07);   
		ST7735_WriteData8(0x09);   
		ST7735_WriteData8(0x0F);   
		ST7735_WriteData8(0x25);   
		ST7735_WriteData8(0x35);   
		ST7735_WriteData8(0x00);   
		ST7735_WriteData8(0x09);   
		ST7735_WriteData8(0x04);   
		ST7735_WriteData8(0x10);
			 
		ST7735_WriteCommand(0xFC);    
		ST7735_WriteData8(0x80);  
			
		ST7735_WriteCommand(0x3A);     
		ST7735_WriteData8(0x05);   
		ST7735_WriteCommand(0x36);
		if(USE_HORIZONTAL==0)ST7735_WriteData8(0x08);
		else if(USE_HORIZONTAL==1)ST7735_WriteData8(0xC8);
		else if(USE_HORIZONTAL==2)ST7735_WriteData8(0x78);
		else ST7735_WriteData8(0xA8);   
		ST7735_WriteCommand(0x21);     //Display inversion
		ST7735_WriteCommand(0x29);     //Display on
		ST7735_WriteCommand(0x2A);     //Set Column Address
		ST7735_WriteData8(0x00);   
		ST7735_WriteData8(0x1A);  //26  
		ST7735_WriteData8(0x00);   
		ST7735_WriteData8(0x69);   //105 
		ST7735_WriteCommand(0x2B);     //Set Page Address
		ST7735_WriteData8(0x00);   
		ST7735_WriteData8(0x01);    //1
		ST7735_WriteData8(0x00);   
		ST7735_WriteData8(0xA0);    //160
		ST7735_WriteCommand(0x2C); 
	
}

void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
        return;


    ST7735_SetAddressWindow(x, y, x+1, y+1);
    uint8_t data[] = { color >> 8, color & 0xFF };
    ST7735_WriteData(data, sizeof(data));

}

static void ST7735_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor) {
    uint32_t i, b, j;

    ST7735_SetAddressWindow(x, y, x+font.width-1, y+font.height-1);

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                uint8_t data[] = { color >> 8, color & 0xFF };
                ST7735_WriteData(data, sizeof(data));
            } else {
                uint8_t data[] = { bgcolor >> 8, bgcolor & 0xFF };
                ST7735_WriteData(data, sizeof(data));
            }
        }
    }
}

/*
Simpler (and probably slower) implementation:

static void ST7735_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color) {
    uint32_t i, b, j;

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                ST7735_DrawPixel(x + j, y + i, color);
            } 
        }
    }
}
*/

void ST7735_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor) {
  

    while(*str) {
        if(x + font.width >= ST7735_WIDTH) {
            x = 0;
            y += font.height;
            if(y + font.height >= ST7735_HEIGHT) {
                break;
            }

            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        ST7735_WriteChar(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }

}

void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    if((x + w - 1) >= ST7735_WIDTH) w = ST7735_WIDTH - x;
    if((y + h - 1) >= ST7735_HEIGHT) h = ST7735_HEIGHT - y;

    ST7735_SetAddressWindow(x, y, x+w-1, y+h-1);

    uint8_t data[] = { color >> 8, color & 0xFF };
    //HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_SET);
    for(y = h; y > 0; y--) {
        for(x = w; x > 0; x--) {
					ST7735_WriteData((uint8_t*)data, sizeof(data));
            //HAL_SPI_Transmit(&ST7735_SPI_PORT, data, sizeof(data), HAL_MAX_DELAY);
        }
    }

}

void ST7735_FillScreen(uint16_t color) {
    ST7735_FillRectangle(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}

void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data) {
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    if((x + w - 1) >= ST7735_WIDTH) return;
    if((y + h - 1) >= ST7735_HEIGHT) return;

    ST7735_SetAddressWindow(x, y, x+w-1, y+h-1);
    ST7735_WriteData((uint8_t*)data, sizeof(uint16_t)*w*h);

}

void ST7735_InvertColors(bool invert) {

    ST7735_WriteCommand(invert ? ST7735_INVON : ST7735_INVOFF);

}



/* vim: set ai et ts=4 sw=4: */
#include "st7735.h"

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
		
		spi_init();
		pinMode(TFT_DC, OUTPUT);
		pinMode(TFT_CS, OUTPUT);
		//pinMode(TFT_BL, OUTPUT);
		
		digitalWrite(TFT_CS, 1);
		//digitalWrite(TFT_BL, 1);
	
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
    
//	if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
//        return;

    ST7735_SetAddressWindow(x, y, x+1, y+1);
    uint8_t data[] = { color >> 8, color & 0xFF };
    ST7735_WriteData(data, sizeof(data));

}


void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
//    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
//    if((x + w - 1) >= ST7735_WIDTH) w = ST7735_WIDTH - x;
//    if((y + h - 1) >= ST7735_HEIGHT) h = ST7735_HEIGHT - y;

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

void ST7735_DrawImage(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const uint16_t* data) {
	
//    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
//    if((x + w - 1) >= ST7735_WIDTH) return;
//    if((y + h - 1) >= ST7735_HEIGHT) return;

    ST7735_SetAddressWindow(x1, y1, x2, y2);
    ST7735_WriteData((uint8_t*)data, sizeof(uint16_t)*(x2-x1+1)*(y2-y1+1));

}

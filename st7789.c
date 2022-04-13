/* vim: set ai et ts=4 sw=4: */
#include "st7789.h"

static void ST7789_WriteCommand(uint8_t cmd) {

		digitalWrite(TFT_DC, 0);
		digitalWrite(TFT_CS, 0);
		spi_transfer(&cmd, 1, NULL, 0);
		digitalWrite(TFT_CS, 1);
	
}

static void ST7789_WriteData(uint8_t* buff, size_t buff_size) {

		digitalWrite(TFT_DC, 1);
		digitalWrite(TFT_CS, 0);
		
		spi_send(buff, buff_size);
		
		digitalWrite(TFT_CS, 1);

}

static void ST7789_WriteData8(uint8_t buff) {

		ST7789_WriteData(&buff, 1);

}

static void ST7789_WriteData16(uint16_t buff) {

		uint8_t sendbuf[2];
		sendbuf[0] = buff >> 8;
		sendbuf[1] = buff;
		ST7789_WriteData(sendbuf, 2);

}

void ST7789_SetAddressWindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    
		if(USE_HORIZONTAL==0)
		{
				ST7789_WriteCommand(0x2a);
				ST7789_WriteData16(x1+52);
				ST7789_WriteData16(x2+52);
				ST7789_WriteCommand(0x2b);
				ST7789_WriteData16(y1+40);
				ST7789_WriteData16(y2+40);
				ST7789_WriteCommand(0x2c);
		}
		else if(USE_HORIZONTAL==1)
		{
				ST7789_WriteCommand(0x2a);
				ST7789_WriteData16(x1+53);
				ST7789_WriteData16(x2+53);
				ST7789_WriteCommand(0x2b);
				ST7789_WriteData16(y1+40);
				ST7789_WriteData16(y2+40);
				ST7789_WriteCommand(0x2c);
		}
		else if(USE_HORIZONTAL==2)
		{
				ST7789_WriteCommand(0x2a);
				ST7789_WriteData16(x1+40);
				ST7789_WriteData16(x2+40);
				ST7789_WriteCommand(0x2b);
				ST7789_WriteData16(y1+53);
				ST7789_WriteData16(y2+53);
				ST7789_WriteCommand(0x2c);
		}
		else
		{
				ST7789_WriteCommand(0x2a);//????????
				ST7789_WriteData16(x1+40);
				ST7789_WriteData16(x2+40);
				ST7789_WriteCommand(0x2b);//????????
				ST7789_WriteData16(y1+52);
				ST7789_WriteData16(y2+52);
				ST7789_WriteCommand(0x2c);//???????
		}
	
}

void ST7789_Init() {
		
    spi_init();
    pinMode(TFT_DC, OUTPUT);
    pinMode(TFT_CS, OUTPUT);
    pinMode(TFT_BL, OUTPUT);
    
    digitalWrite(TFT_CS, 1);
    digitalWrite(TFT_BL, 1);

    ST7789_WriteCommand(0x11);     //Sleep out
    delay(120);                //Delay 120ms
    
    ST7789_WriteCommand(0x36); 
    if(USE_HORIZONTAL==0)ST7789_WriteData8(0x00);
    else if(USE_HORIZONTAL==1)ST7789_WriteData8(0xC0);
    else if(USE_HORIZONTAL==2)ST7789_WriteData8(0x70);
    else ST7789_WriteData8(0xA0);

    ST7789_WriteCommand(0x3A);
    ST7789_WriteData8(0x05);

    ST7789_WriteCommand(0xB2);
    ST7789_WriteData8(0x0C);
    ST7789_WriteData8(0x0C);
    ST7789_WriteData8(0x00);
    ST7789_WriteData8(0x33);
    ST7789_WriteData8(0x33); 

    ST7789_WriteCommand(0xB7); 
    ST7789_WriteData8(0x35);  

    ST7789_WriteCommand(0xBB);
    ST7789_WriteData8(0x19);

    ST7789_WriteCommand(0xC0);
    ST7789_WriteData8(0x2C);

    ST7789_WriteCommand(0xC2);
    ST7789_WriteData8(0x01);

    ST7789_WriteCommand(0xC3);
    ST7789_WriteData8(0x12);   

    ST7789_WriteCommand(0xC4);
    ST7789_WriteData8(0x20);  

    ST7789_WriteCommand(0xC6); 
    ST7789_WriteData8(0x0F);    

    ST7789_WriteCommand(0xD0); 
    ST7789_WriteData8(0xA4);
    ST7789_WriteData8(0xA1);

    ST7789_WriteCommand(0xE0);
    ST7789_WriteData8(0xD0);
    ST7789_WriteData8(0x04);
    ST7789_WriteData8(0x0D);
    ST7789_WriteData8(0x11);
    ST7789_WriteData8(0x13);
    ST7789_WriteData8(0x2B);
    ST7789_WriteData8(0x3F);
    ST7789_WriteData8(0x54);
    ST7789_WriteData8(0x4C);
    ST7789_WriteData8(0x18);
    ST7789_WriteData8(0x0D);
    ST7789_WriteData8(0x0B);
    ST7789_WriteData8(0x1F);
    ST7789_WriteData8(0x23);

    ST7789_WriteCommand(0xE1);
    ST7789_WriteData8(0xD0);
    ST7789_WriteData8(0x04);
    ST7789_WriteData8(0x0C);
    ST7789_WriteData8(0x11);
    ST7789_WriteData8(0x13);
    ST7789_WriteData8(0x2C);
    ST7789_WriteData8(0x3F);
    ST7789_WriteData8(0x44);
    ST7789_WriteData8(0x51);
    ST7789_WriteData8(0x2F);
    ST7789_WriteData8(0x1F);
    ST7789_WriteData8(0x1F);
    ST7789_WriteData8(0x20);
    ST7789_WriteData8(0x23);

    ST7789_WriteCommand(0x21); 

    ST7789_WriteCommand(0x29); 
	
}

void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    
//	if((x >= ST7789_WIDTH) || (y >= ST7789_HEIGHT))
//        return;

    ST7789_SetAddressWindow(x, y, x+1, y+1);
    uint8_t data[] = { color >> 8, color & 0xFF };
    ST7789_WriteData(data, sizeof(data));

}


void ST7789_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
//    if((x >= ST7789_WIDTH) || (y >= ST7789_HEIGHT)) return;
//    if((x + w - 1) >= ST7789_WIDTH) w = ST7789_WIDTH - x;
//    if((y + h - 1) >= ST7789_HEIGHT) h = ST7789_HEIGHT - y;

    ST7789_SetAddressWindow(x, y, x+w-1, y+h-1);

    uint8_t data[] = { color >> 8, color & 0xFF };
    //HAL_GPIO_WritePin(ST7789_DC_GPIO_Port, ST7789_DC_Pin, GPIO_PIN_SET);
    for(y = h; y > 0; y--) {
        for(x = w; x > 0; x--) {
					ST7789_WriteData((uint8_t*)data, sizeof(data));
            //HAL_SPI_Transmit(&ST7789_SPI_PORT, data, sizeof(data), HAL_MAX_DELAY);
        }
    }

}

void ST7789_FillScreen(uint16_t color) {
    ST7789_FillRectangle(0, 0, ST7789_WIDTH, ST7789_HEIGHT, color);
}

void ST7789_DrawImage(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const uint16_t* data) {
	
//    if((x >= ST7789_WIDTH) || (y >= ST7789_HEIGHT)) return;
//    if((x + w - 1) >= ST7789_WIDTH) return;
//    if((y + h - 1) >= ST7789_HEIGHT) return;

    ST7789_SetAddressWindow(x1, y1, x2, y2);
    ST7789_WriteData((uint8_t*)data, sizeof(uint16_t)*(x2-x1+1)*(y2-y1+1));

}

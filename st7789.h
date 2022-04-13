/* vim: set ai et ts=4 sw=4: */
#ifndef __ST7789_H__
#define __ST7789_H__

#include "transfer_handler.h"

#define USE_HORIZONTAL 3
#define ST7789_WIDTH 240
#define ST7789_HEIGHT 135

// Color definitions
#define	ST7789_BLACK   0x0000
#define	ST7789_BLUE    0x001F
#define	ST7789_RED     0xF800
#define	ST7789_GREEN   0x07E0
#define ST7789_CYAN    0x07FF
#define ST7789_MAGENTA 0xF81F
#define ST7789_YELLOW  0xFFE0
#define ST7789_WHITE   0xFFFF
#define ST7789_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

void ST7789_Init(void);
void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7789_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7789_FillScreen(uint16_t color);
void ST7789_DrawImage(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const uint16_t* data);

#endif // __ST7789_H__

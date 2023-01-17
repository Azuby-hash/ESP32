#include "display.h"
#include "ssd1306.h"
#include "MathExtern.h"

void display() {
    valueShow();

    SSD1306_UpdateScreen();
}

void valueShow() {
  SSD1306_GotoXY(10,0);
  SSD1306_Puts("Temp: ", &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts((char *)numberToString(temp), &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts(".", &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts((char *)numberToString((temp - (uint16_t)temp) * 10), &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts("C", &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts("             ", &Font_7x10, SSD1306_COLOR_WHITE);

  SSD1306_GotoXY(10,15);
  SSD1306_Puts("Air Humi: ", &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts((char *)numberToString(airHum), &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts(".", &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts((char *)numberToString((airHum - (uint16_t)airHum) * 10), &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts("%", &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts("             ", &Font_7x10, SSD1306_COLOR_WHITE);

  SSD1306_GotoXY(10,30);
  SSD1306_Puts("PH Humi: ", &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts((char *)numberToString(pHHum), &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts("%", &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts("             ", &Font_7x10, SSD1306_COLOR_WHITE);

  SSD1306_GotoXY(10,45);
  SSD1306_Puts("Light: ", &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts((char *)numberToString(lightHum), &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts("Lux", &Font_7x10, SSD1306_COLOR_WHITE);
  SSD1306_Puts("             ", &Font_7x10, SSD1306_COLOR_WHITE);
}
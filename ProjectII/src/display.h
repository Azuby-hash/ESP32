#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "stm32f1xx_hal.h"

extern float temp;
extern float airHum;
extern uint16_t pHHum;
extern uint16_t lightHum;

void display();
void valueShow();

#endif
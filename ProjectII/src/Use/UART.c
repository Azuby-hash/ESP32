#include "UART.h"
#include "MathExtern.h"

void transmitInterval() {
    transmitString((uint8_t *)"Temperature: ");
    // transmitNumber(pHHum);
    transmitString((uint8_t *)"\n");
}
#include "key.h"
#include "display.h"
#include "main.h"

static char key = '\0';
static uint32_t time = 0;

void action() {

}

void enterKey() {
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 1) {
        if (key != 'M') {
            time = 0;
        }
        key = 'M';
        action();
        return;
    }
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 1) {
        if (key != 'E') {
            time = 0;
        }
        key = 'E';
        action();
        return;
    }
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 1) {
        if (key != '+') {
            time = 0;
        }
        key = '+';
        action();
        return;
    }
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 1) {
        if (key != '-') {
            time = 0;
        }
        key = '-';
        action();
        return;
    }

    key = '\0';
    time = 0;
}
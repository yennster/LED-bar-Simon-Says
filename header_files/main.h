#include "mbed.h"
#include "LED_Bar.h"

LED_Bar top(D6, D5);
LED_Bar right(D8, D7);
LED_Bar left(D4, D3);
InterruptIn button_left(A2);
InterruptIn button_top(A1);
InterruptIn button_right(A0);
DigitalOut buzzer(D2);
int input_index;
int input[100];

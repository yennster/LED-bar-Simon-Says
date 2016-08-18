#include "mbed.h"
#include "LED_Bar.h"
#include "loops.h"
#include "start.h"
#include "win_or_lose.h"
#include "level.h"

LED_Bar top(D6, D5);
LED_Bar right(D8, D7);
LED_Bar left(D4, D3);
DigitalIn button_left(A2);
DigitalIn button_top(A1);
DigitalIn button_right(A0);
DigitalOut buzzer(D2);
Ticker input_timer;
int input[50];
int sequence[] = {3, 2, 1, 3, 2, 1};
int level_index = 0;
//int length = 15;
//char notes[] = "ccggaagffeeddc ";
//int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
//int tempo = 300;

/* 
DigitalOut buzzer(D8);
Ticker buzzer_timer;
 
int on = 1, off = 0; 
 
void timer_handler(){
    buzzer = buzzer ^ 1; // invert the buzzer value    
}
 
int main(){
    buzzer = off; // initialize buzzer
    buzzer_timer.attach(&timer_handler, 0.5); // Every .5s call the timer_handler function
    
    while(1){
        // do something else    
    }
}
*/

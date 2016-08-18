#include "mbed.h"
#include "LED_Bar.h"

LED_Bar top(D6, D5);
LED_Bar right(D8, D7);
LED_Bar left(D4, D3);
InterruptIn button_left(A2);
InterruptIn button_top(A1);
InterruptIn button_right(A0);
DigitalOut buzzer(D2);
Ticker input_timer;
int input[50];
int input_index;
int sequence[] = {3, 2, 1, 3, 2, 1};
int sequence_size;
int level_index = 0;

void level() {
    //generate random simon says sequence
    
    //wait for user input
    while(!(button_left or button_right or button_top)){
        
    }
    
}

/*  simon says loop: turn on corresponding LED Bars according to the # 
    in the sequence array (1=right, 2=top, 3=left) */
void simon_loop() { 
    for(int i = 0; i < sequence_size; i++) {  
        if (sequence[i] == 1) {
            right.setLevel(10);
            wait(0.4);
            right.setLevel(0);
        }
        else if (sequence[i] == 2) {
            top.setLevel(10);
            wait(0.4);
            top.setLevel(0);
        }
        else {
            left.setLevel(10);
            wait(0.4);
            left.setLevel(0);
        }
    }
}

void right_input() {
    input[input_index] = 1;
    input_index++;
    while(button_right) {
        right.setLevel(10);
    }
    right.setLevel(0);
    return;
}

void top_input() {
    input[input_index] = 2;
    input_index++;
    while(button_top) {
        top.setLevel(10);
    }
    top.setLevel(0);
    return;
}

void left_input() {
    input[input_index] = 3;
    input_index++;
    while(button_left) {
        left.setLevel(10);
    }
    left.setLevel(0);
    return;
}

/*  gather user input based on buttons pressed, then store button # into
    the input array (1=button_right, 2=button_top, 3=button_left) */
void input_loop() {
    button_right.rise(&right_input); //interrupt when right button is pressed
    button_top.rise(&top_input);
    button_left.rise(&left_input);
    while(input_index < sequence_size) {
        wait(0.2);
    }
    input_index = 0;
}

/*  compare input array to simon says sequence array, if they are a match
    return true, if they are not a match return false */
bool win_or_lose() {
    for(int k = 0; k < sequence_size; k++) { 
        if (input[k] == sequence[k]) { continue; }
        else { return false; }
    }
    return true;
}

/*  display a happy LED animation for winning (LED levels 0 to 10 fast) */
void success() {
    for(int h = 0; h <=10; h++){
        top.setLevel(h);
        right.setLevel(h);
        left.setLevel(h);
        wait(0.05);
    } 
    for(int h = 0; h <=10; h++){
        top.setLevel(h);
        right.setLevel(h);
        left.setLevel(h);
        wait(0.05);
    }  
    top.setLevel(0);
    right.setLevel(0);
    left.setLevel(0); 
}

/*  display a sad LED animation for losing (LED levels 10 to 0 slow) */
void failure() {
    for(int g = 0; g <= 10; g++){
        top.setLevel(10-g);
        right.setLevel(10-g);
        left.setLevel(10-g);
        wait(0.1);
    }
}

void start_game() {
    input_index = 0;
    sequence_size = sizeof(sequence)/sizeof(sequence[0]);
    top.setLevel(0);
    right.setLevel(0);
    left.setLevel(0);
    //level();
    wait(0.3);
    simon_loop();
    wait(0.3);
    input_loop();
    wait(0.2);
    bool winner = win_or_lose();
    if (winner == true) { success(); } 
    else { failure(); }
}

int main() {
    start_game();
}
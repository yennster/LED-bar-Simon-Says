#include "mbed.h"
#include "LED_Bar.h"

LED_Bar mid(D6, D5);
LED_Bar right(D8, D7);
LED_Bar left(D4, D3);
InterruptIn button_left(A2);
InterruptIn button_mid(A1);
InterruptIn button_right(A0);
DigitalOut buzzer(D2);
int input_index;
int input[100];
bool start_flag = false;

/*  start the game: animation/buzzer sounds */
void start_level() {  
    for(int i = 0; i < 3; i++) {
        right.setLevel(10);
        mid.setLevel(10);
        left.setLevel(10);
        buzzer = 1;
        wait(0.4 - i*0.1);
        right.setLevel(0);
        mid.setLevel(0);
        left.setLevel(0);
        buzzer = 0;
        wait(0.4 - i*0.1);
    }   
    start_flag = true;
}

/*  generate random simon says sequence:
    level 1 will have a 3 LED blink combination, with each subsequent level
    having 1 more LED blink, so level 2 has a 4 blink combination, etc. */
int level(int level_index, int sequence_size, int* sequence) {
    for(int i = 0; i < sequence_size; i++) {
        sequence[i] = rand() % 3 + 1;
    }
    button_right.rise(&start_level);
    button_mid.rise(&start_level);
    button_left.rise(&start_level);
    while(!start_flag) {
        wait(0.1);
    }
    return level_index++;
}

/*  simon says loop: turn on corresponding LED Bars according to the # 
    in the sequence array (1=right, 2=mid, 3=left) */
void simon_loop(int sequence_size, int* sequence) { 
    for(int i = 0; i < sequence_size; i++) {  
        if (sequence[i] == 1) {
            right.setLevel(10);
            wait(0.4);
            right.setLevel(0);
        } else if (sequence[i] == 2) {
            mid.setLevel(10);
            wait(0.4);
            mid.setLevel(0);
        } else {
            left.setLevel(10);
            wait(0.4);
            left.setLevel(0);
        }
        wait(0.4);
    }
}

void right_input() {
    input[input_index] = 1;
    input_index++;
    while(button_right) {
        right.setLevel(10);
    }
    right.setLevel(0);
}

void mid_input() {
    input[input_index] = 2;
    input_index++;
    while(button_mid) {
        mid.setLevel(10);
    }
    mid.setLevel(0);
}

void left_input() {
    input[input_index] = 3;
    input_index++;
    while(button_left) {
        left.setLevel(10);
    }
    left.setLevel(0);
}

/*  gather user input based on buttons pressed, then store button index into
    the input array (1=button_right, 2=button_mid, 3=button_left) */
void input_loop(int sequence_size) {
    button_right.rise(&right_input);
    button_mid.rise(&mid_input);
    button_left.rise(&left_input);
    while(input_index < sequence_size) {
        wait(0.2);
    }
    input_index = 0;
}

/*  compare input array to simon says sequence array, if they are a match
    return true, if they are not a match return false */
bool win_or_lose(int sequence_size, int* sequence) {
    for(int k = 0; k < sequence_size; k++) { 
        if (input[k] == sequence[k]) { continue; }
        else { return false; }
    }
    return true;
}

/*  display a happy LED animation for winning (LED levels 0 to 10 fast) */
void success() {
    for(int i = 0; i < 2; i ++){
        for(int h = 0; h <=10; h++){
            mid.setLevel(h);
            right.setLevel(h);
            left.setLevel(h);
            wait(0.05);
        } 
    }
}

/*  display a sad LED animation for losing (LED levels 10 to 0 slow) */
void failure() {
    for(int g = 0; g <= 10; g++){
        mid.setLevel(10-g);
        right.setLevel(10-g);
        left.setLevel(10-g);
        wait(0.1);
    }
}

int main() {
    int win_count = 0;
    int lose_count = 0;
    int level_index = 1;
    int sequence_size = 2;
    int sequence[100];
    while(1) {
        input_index = 0;
        mid.setLevel(0);
        right.setLevel(0);
        left.setLevel(0);
        sequence_size++;
        level_index = level(level_index, sequence_size, sequence);
        simon_loop(sequence_size, sequence);
        input_loop(sequence_size);
        wait(0.3);
        bool winner = win_or_lose(sequence_size, sequence);
        if (winner == true) { 
            win_count++; 
            success(); 
        } else { 
            lose_count++; 
            failure(); 
        }
        if (lose_count > 0) { 
            start_flag = false;
            win_count = 0;
            lose_count = 0;
            level_index = 1;
            sequence_size = 2;
        }
    }
}
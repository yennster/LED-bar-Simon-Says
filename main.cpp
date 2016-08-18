#include "mbed.h"
#include "LED_Bar.h"
#include "main.h"

int sequence_size;
int sequence[100];
int level_index = 1;
int level_array;
int win_count = 0;
int lose_count = 0;
bool start_flag = false;

void start_level() {    
    right.setLevel(10);
    top.setLevel(10);
    left.setLevel(10);
    wait(0.2);
    right.setLevel(0);
    top.setLevel(0);
    left.setLevel(0);
    wait(0.2);
    right.setLevel(10);
    top.setLevel(10);
    left.setLevel(10);
    wait(0.2);
    right.setLevel(0);
    top.setLevel(0);
    left.setLevel(0);
    start_flag = true;
    return;
}

void level() {
    /*  generate random simon says sequence:
        level 1 will have a 3 LED blink combination, with each subsequent level
        having 1 more LED blink, so level 2 has a 4 blink combination, etc. */
    for (int i = 0; i < level_array; i++) {
        sequence[i] = rand() % 3 + 1;   // choose a random number b/w 1 to 3
    }
    
    level_index++;
    
    /*  button interrupts when user wants to begin the game/level */
    button_right.rise(&start_level);
    button_top.rise(&start_level);
    button_left.rise(&start_level);
    while(!start_flag) {
        wait(0.2); // waiting for user to begin game LED animation
        // perfect time to play waiting buzzer music
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
            wait(0.4);
        } else if (sequence[i] == 2) {
            top.setLevel(10);
            wait(0.4);
            top.setLevel(0);
            wait(0.4);
        } else {
            left.setLevel(10);
            wait(0.4);
            left.setLevel(0);
            wait(0.4);
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
    top.setLevel(0);
    right.setLevel(0);
    left.setLevel(0);
    level_array = ((level_index - 1) + 3);
    sequence_size = level_array;
    level();
    wait(0.3);
    simon_loop();
    wait(0.3);
    input_loop();
    wait(0.3);
    bool winner = win_or_lose();
    if (winner == true) { win_count++; success(); } 
    else { lose_count++; failure(); }
    if (lose_count > 0) { 
        start_flag = false;
        wait(1); // add in end game buzzer music
        win_count = 0;
        lose_count = 0;
        level_index = 1;
        start_game();
    } else { start_game(); }
}

int main() {
    start_game();
}
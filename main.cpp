#include "mbed.h"
#include "LED_Bar.h"

LED_Bar top(D6, D5);
LED_Bar right(D8, D7);
LED_Bar left(D4, D3);
DigitalIn button_left(A2);
DigitalIn button_top(A1);
DigitalIn button_right(A0);
int input[50];
int sequence[] = {3, 2, 1, 3, 2, 1};

void start_up() {
    //generate random simon says sequence
    
    //wait for user input
    while(!(button_left or button_right or button_top)){
        
    }
    
}

/*  simon says loop: turn on corresponding LED Bars according to the # 
    in the sequence array (1=right, 2=top, 3=left) */
void simon_loop() { 
    for(int i = 0; i < (sizeof(sequence)/sizeof(sequence[0])); i++) {  
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

/*  gather user input based on buttons pressed, then store button # into
    the input array (1=button_right, 2=button_top, 3=button_left) */
void input_loop() {

    for(int j = 0; j < (sizeof(sequence)/sizeof(sequence[0])); j++) { 
        wait(0.4);
        if (button_top) {
            input[j] = 2;
            while(button_top){
                top.setLevel(10);
            };
            top.setLevel(0);
        }
        if (button_right) {
            input[j] = 1;
            while(button_right){
                right.setLevel(10);
            };
            right.setLevel(0);
        }
        if (button_left) {
            input[j] = 3;
            while(button_left){
                left.setLevel(10);
            };
            left.setLevel(0);
        }
    }
    return;
}

/*  compare input array to simon says sequence array, if they are a match
    return true, if they are not a match return false */
bool win_or_lose() {
    for(int k = 0; k < (sizeof(sequence)/sizeof(sequence[0])); k++) { 
        if (input[k] == sequence[k]) { continue; }
        else { return false; }
    }
    return true;
}

/*  display a happy LED animation for winning (LED levels 0 to 10 fast, twice) */
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

int main() {
    top.setLevel(0);
    right.setLevel(0);
    left.setLevel(0);
    start_up();
    wait(0.3);
    simon_loop();
    input_loop();
    wait(0.2);
    bool winner = win_or_lose();
    if (winner == true) { success(); } 
    else { failure(); }
}

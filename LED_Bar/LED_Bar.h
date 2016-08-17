/*
LED bar library V1.0
2010 Copyright (c) Seeed Technology Inc. All right reserved.

Original Author: LG
Modify: Loovee, 2014-2-26
User can choose which Io to be used.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "mbed.h"

#ifndef LED_Bar_H
#define LED_Bar_H

#define CMDMODE 0x0000 // Work on 8-bit mode
#define ON 0x00ff // 8-bit 1 data
#define SHUT 0x0000 // 8-bit 0 data

/**
 * The LED_Bar interface
 */
class LED_Bar
{

public:
    LED_Bar(PinName pinClk, PinName pinDta);

    /**
     * Set led single bit, a bit contrl a led
     * @param index_bits which bit. if 0x05, then led 0 and led 3 will on, the others will off
     */
    void ledIndexBit(unsigned int index_bits);

    /**
     * Set level, frm 0 to 10.
     * @param level Level 0 means all leds off while level 5 means 5led on and the other will off
     */
    void setLevel(int level);
    
    /**
     * Control a single led
     * @param num which led
     * @param st  1: on 0: off
     */
    void setSingleLed(int num, int st);

private:
    /**
     * Pin for clock
     */
    DigitalOut __pinClk;
    
    /**
     * Pin for data
     */
    DigitalOut __pinDta;

    /**
     * LED State
     */
    unsigned int __led_state;

    void send16bitData(unsigned int data);
    void latchData(void);

};

#endif
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "mcp2515/mcp2515.h"
#include "pico_neopixels/include/Adafruit_NeoPixel.hpp"
#include "utils/NeoPixel_utils.h"


MCP2515 can0;
struct can_frame rx;

#define NEO_PIXEL 21 // On the CAN feather, the neoPixel is on pin 21
#define NEO_PIXEL_PWR 20 // On the CAN feather, the neoPixel power is on pin 20
#define LED 13 // On the CAN feather, the onboard LED is on pin 13

Adafruit_NeoPixel onboard = Adafruit_NeoPixel(1, NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void core1_main() {

    //Initialize the NeoPixel power
    gpio_init(NEO_PIXEL_PWR);
    gpio_set_dir(NEO_PIXEL_PWR, GPIO_OUT);
    gpio_put(NEO_PIXEL_PWR, 1);

    //Initialize the NeoPixel
    onboard.begin();
    onboard.setBrightness(50);
    onboard.show(); // Initialize all pixels to 'off'


    while(true) {

        //Some example animations
        colorWipe(onboard, onboard.Color(255, 0, 0), 1000); // Red
        colorWipe(onboard, onboard.Color(255, 0, 0), 1000); // Red
        colorWipe(onboard, onboard.Color(0, 255, 0), 1000); // Green
        colorWipe(onboard, onboard.Color(0, 0, 255), 1000); // Blue

        rainbow(onboard, 1000); // Rainbow

    }
}

int main() {
    stdio_init_all();

    //Start the second core
    multicore_launch_core1(core1_main);

    //Initialize the onboard LED
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(LED, 1);
   
    //Initialize interface
    can0.reset();
    can0.setBitrate(CAN_500KBPS, MCP_16MHZ);
    can0.setNormalMode();

    //Listen loop
    while(true) {
        
        //printf("Listening...\n");
        if(can0.readMessage(&rx) == MCP2515::ERROR_OK) {
            printf("New frame from ID: %10X\nData: ", rx.can_id);
            for (int i = 0; i < rx.can_dlc; i++) {
                printf("%02X", rx.data[i]);
            }
            printf("\n");
        }

        // if the canbus goes down, turn off the led and restart the bus. 
        if(can0.checkError()) {
            gpio_put(LED, 0);
            can0.reset();
            can0.setBitrate(CAN_500KBPS, MCP_16MHZ);
            can0.setNormalMode();
        } else {
            gpio_put(LED, 1);
        }
    }

    return 0;
}


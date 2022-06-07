/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include <stdio.h>
#include <string>



/// \tag::uart_advanced[]

#define UART_ID uart0
#define BAUD_RATE 57600
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

using namespace std;

const uint delay = 1000; // 1s delay

static int chars_rxed = 0;



int main() {

     stdio_init_all();
 

     adc_init();
     adc_gpio_init(26);
     adc_select_input(0);
     
    // Set up our UART with a basic baud rate.
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

 

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);

    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, false);
    
     while (uart_is_writable(UART_ID)) {
        //char ch = uart_getc(UART_ID);
        const float conversion_factor = 3.3f / (1 << 12);
        gpio_pull_up(20);
        // Can we send it back?
        //if (uart_is_writable(UART_ID) && ch == '1') 
       // {
        	uint16_t result = adc_read();
        	double x = result * conversion_factor;
        	string buf;
        	buf = to_string(x);
        	auto str_buf = (const char *)buf.c_str();
        //	uart_putc_raw(UART_ID, ch);
        	uart_puts(UART_ID, "\n");
            	uart_puts(UART_ID, str_buf);
            	uart_puts(UART_ID, "\n");
       // }
       // chars_rxed++;
        sleep_ms(delay);
    }

    // OK, all set up.
    // Lets send a basic string out, and then run a loop and wait for RX interrupts
    // The handler will count them, but also reflect the incoming data back with a slight change!
    //uart_puts(UART_ID, "\nHello, uart interrupts\n");

    while (1)
        tight_loop_contents();
}

/// \end:uart_advanced[]



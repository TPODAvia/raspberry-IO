#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // Set PB5 (pin 13 on Arduino Uno) as an output
  DDRB |= (1 << PB5);

  while (1) {
    // Turn the LED on
    PORTB |= (1 << PB5);
    _delay_ms(1); // Wait for 1 second

    // Turn the LED off
    PORTB &= ~(1 << PB5);
    _delay_ms(100); // Wait for 1 second
  }

  return 0;
}

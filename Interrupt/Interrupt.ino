#include <avr/io.h>
#include <avr/interrupt.h>

void setupTimerInterrupt() {
  // Set timer1 to CTC mode
  TCCR1B |= (1 << WGM12);

  // Set the compare value to create a 1-second interval
  OCR1A = 15624;

  // Enable the timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Set the prescaler to 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Enable global interrupts
  sei();
}

ISR(TIMER1_COMPA_vect) {
  // Toggle the LED on PB5 (pin 13 on Arduino Uno)
  PORTB ^= (1 << PB5);
}

int main(void) {
  // Set PB5 (pin 13 on Arduino Uno) as an output
  DDRB |= (1 << PB5);

  // Initialize the timer interrupt
  setupTimerInterrupt();

  while (1) {
    // The interrupt will handle the LED blinking
  }

  return 0;
}
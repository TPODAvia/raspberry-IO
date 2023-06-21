#include <avr/io.h>
#include <util/delay.h>

void setup() {
  // Set baud rate to 9600
  uint16_t baud_setting = (F_CPU / 4 / 9600 - 1) / 2;
  UBRR0H = baud_setting >> 8;
  UBRR0L = baud_setting;

  // Set frame format: 8 data bits, no parity, 1 stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  // Enable transmitter and receiver
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
}

void uart_send_char(char c) {
  // Wait until transmit buffer is empty
  while (!(UCSR0A & (1 << UDRE0)));

  // Send character
  UDR0 = c;
}

char uart_receive_char() {
  // Wait until data is available
  while (!(UCSR0A & (1 << RXC0)));

  // Return received character
  return UDR0;
}

void loop() {
  // Receive a character from UART
  char received = uart_receive_char();

  // Send the received character back
  uart_send_char(received);
}
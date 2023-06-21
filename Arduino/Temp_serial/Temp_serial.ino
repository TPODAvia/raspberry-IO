#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void setup() {
  // Set voltage reference to internal 1.1V
  ADMUX |= (1 << REFS1) | (1 << REFS0);

  // Select temperature sensor channel (channel 8)
  ADMUX |= (1 << MUX3);

  // Enable the ADC and set the prescaler to 128
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t read_temperature_adc() {
  // Start ADC conversion
  ADCSRA |= (1 << ADSC);

  // Wait for the conversion to complete
  while (ADCSRA & (1 << ADSC));

  // Read and combine the ADC result
  uint16_t adc_result = ADCL | (ADCH << 8);
  return adc_result;
}

float adc_to_temperature(uint16_t adc_value) {
  // Calculate the voltage from the ADC value
  float voltage = (adc_value * 1.1) / 1024;

  // Convert the voltage to temperature in Celsius
  float temperature = (voltage - 0.5) * 100;
  return temperature;
}

void loop() {
  // Read the temperature ADC value
  uint16_t adc_value = read_temperature_adc();

  // Convert the ADC value to temperature in Celsius
  float temperature = adc_to_temperature(adc_value);

  // Print the temperature
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "Temperature: %.2f C\n", temperature);
  for (int i = 0; buffer[i] != '\0'; i++) {
    uart_send_char(buffer[i]);
  }

  // Wait for 1 second before reading again
  _delay_ms(1000);
}

int main() {
  setup();
  while (1) {
    loop();
  }
  return 0;
}

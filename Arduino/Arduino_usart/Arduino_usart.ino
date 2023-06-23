void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Send "Hello, World!" followed by a newline to the Serial Monitor
  Serial.println("Hello, World!");

  // Wait for one second before sending the message again
  delay(1000);
}
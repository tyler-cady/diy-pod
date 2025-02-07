#include <Particle.h>

int buttonPin = D3; // GPIO pin for button
int mosfetPin = D4; // GPIO pin to control the MOSFET
bool state = false; // To store the toggle state
unsigned long lastPressTime = 0; // For debouncing

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as input with pull-up
  pinMode(mosfetPin, OUTPUT); // Set the MOSFET control pin as output
  digitalWrite(mosfetPin, LOW); // Initially turn off the MOSFET
}

void loop() {
  // Check for button press with debounce
  if (digitalRead(buttonPin) == LOW && millis() - lastPressTime > 300) {
    state = !state; // Toggle the state
    digitalWrite(mosfetPin, state ? HIGH : LOW); // Turn on or off the MOSFET
    lastPressTime = millis(); // Update the debounce timer
  }

  // Other code goes here
}

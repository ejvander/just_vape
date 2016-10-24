#include "Arduino.h"


#define LED_PIN 13
#define BUTTON_PIN 12

int buttonState;
int lastButtonState = LOW;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    pinMode(BUTTON_PIN, INPUT);
    Serial.begin(9600);
}

void loop() {
    Serial.println("Example arduino project in CLion");

    int buttonVal = digitalRead(BUTTON_PIN);
    Serial.print("Current Button Val: ");
    Serial.println(buttonVal);

    for (int i = 0; i < 2; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
    }

    delay(1000);
}

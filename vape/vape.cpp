#include "Arduino.h"

#define LED_PIN 13
// Pins used for buttons
#define POW_BUTTON_PIN 12
#define LOW_TEMP_BUTTON_PIN 8
#define RAI_TEMP_BUTTON_PIN 7

//Debounce value milliseconds
#define DEB_CUTOFF 100

// Number of heating elements
#define NUM_BARS 2

// Button states/debounce variables
int  powBtnSt;
int  lastPowBtnVal = LOW;
long lastPowBtnTime;
int  lowerTempBtnSt;
int  lastLowerTempBtnVal = LOW;
long lastLowerTempBtnTime;
int  raiseTempBtnSt;
int  lastRaiseTempBtnVal = LOW;
long lastRaiseTempBtnTime;

// Amount of time that 
//long powPushTime = 0;

// Current targetTemp
int targetTemp = 400;
// Temp change on each button push
const int tempDelta = 20;

// Arduino uno PWM pins 3,5,6,9,10,11
const int pwm_pins[] = {3, 5, 6, 9, 10, 11};
// Arduino uno analog in pins
const int temp_pins[] = {0, 1, 2, 3, 4, 5, 6};

// Bar currently being powered
int current_bar = 0;

void setup() {
  //pinMode(LED_PIN, OUTPUT);
  //digitalWrite(LED_PIN, LOW);

  pinMode(POW_BUTTON_PIN, INPUT);
  pinMode(LOW_TEMP_BUTTON_PIN, INPUT);
  pinMode(RAI_TEMP_BUTTON_PIN, INPUT);

  for (int i = 0; i < NUM_BARS; i++) {
    pinMode(pwm_pins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void debounce(int btnVal, int lastBtnVal, long* lastChangeTime, int* btnSt) {
  if(btnVal != lastBtnVal) {
    *lastChangeTime = millis();
  }
  if((millis() - *lastChangeTime) > DEB_CUTOFF) {
    *btnSt = btnVal;
  }
} 

void reset(){
  // Turn off current bar
  analogWrite(pwm_pins[current_bar], 0);
  targetTemp = 400;
  current_bar = 0;
}

void loop() {
  // Start debounce logic
  int lastPowSt = powBtnSt;
  int lastLowerSt = lowerTempBtnSt;
  int lastRaiseSt = raiseTempBtnSt;

  // Read current button staes
  int powBtnVal = digitalRead(POW_BUTTON_PIN);
  int lowerTempBtnVal = digitalRead(LOW_TEMP_BUTTON_PIN);
  int raiseTempBtnVal = digitalRead(RAI_TEMP_BUTTON_PIN);

  debounce(powBtnVal, lastPowBtnVal, &lastPowBtnTime, &powBtnSt);
  debounce(lowerTempBtnVal, lastLowerTempBtnVal, &lastLowerTempBtnTime, &lowerTempBtnSt);
  debounce(raiseTempBtnVal, lastRaiseTempBtnVal, &lastRaiseTempBtnTime, &raiseTempBtnSt);
  
  // Save last button state for debouncing purposes
  lastLowerTempBtnVal = lowerTempBtnVal;
  lastRaiseTempBtnVal = raiseTempBtnVal;
  lastPowBtnVal = powBtnVal;
  // End debounce logic

  // Update values based on button presses

  // We can have these buttons perform different functions depending on the state
  // We can figure that out later

  // These analogWrite PWM writes are only for testing, 
  // we will use these PWM output to enable the heating elements

  // If power button is pressed, change bar
  if(powBtnSt == HIGH && (lastPowSt != powBtnSt)) {
    Serial.print("Bar Chan: Current targetTemp Val: ");
    Serial.println(targetTemp);
    analogWrite(pwm_pins[current_bar], 0);
    current_bar = (current_bar+1) % NUM_BARS;
    Serial.print("Bar Chan: Current Pin: ");
    Serial.println(pwm_pins[current_bar]);
    analogWrite(pwm_pins[current_bar], targetTemp/4);
  }
  // If holding down the power longer than 1 second, reset
  if(powBtnSt == HIGH && ((millis() - lastPowBtnTime) > 1000)){
    reset();
    Serial.print("Temp Res:  Current targetTemp Val: ");
    Serial.println(targetTemp);
    analogWrite(pwm_pins[current_bar], targetTemp/4);
  }
  // Decrease targetTemp if lower button pressed
  if(lowerTempBtnSt == HIGH && (lastLowerSt != lowerTempBtnSt)) {
    targetTemp  = ((targetTemp - tempDelta) < 0) ? 0 : (targetTemp - tempDelta);
    Serial.print("Temp Decr: Current targetTemp Val: ");
    Serial.println(targetTemp);
    analogWrite(pwm_pins[current_bar], targetTemp/4);
  }
  // Increate targetTemp if raise button pressed
  if(raiseTempBtnSt == HIGH && (lastRaiseSt != raiseTempBtnSt)) {
    targetTemp += tempDelta;
    Serial.print("Temp incr: Current targetTemp Val: ");
    Serial.println(targetTemp);
    analogWrite(pwm_pins[current_bar], targetTemp/4);
  }

  // Read from thermistor
  // int tempIn = analogRead(temp_pins[current_bar])
  // calculate temp difference based on thermistor values
  // do a pwm write to set value needed

  // Small delay, save a little power
  delay(20);
}

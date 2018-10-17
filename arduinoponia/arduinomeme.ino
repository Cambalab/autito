#include <ShiftRegister74HC595.h>

int numberOfShiftRegisters = 1; // number of shift registers attached in series
int serialDataPin = 11; // DS
int clockPin = 12; // SHCP
int latchPin = 8; // STCP
int buttonPin = 9;     // the number of the pushbutton pin
int selectedSensor = 0;
int buttonState = 0;         // variable for reading the pushbutton status

unsigned long masterStartMillis;  //some global variables available anywhere in the program
unsigned long uiStartMillis;  //some global variables available anywhere in the program
unsigned long sensorStartMillis;  //some global variables available anywhere in the program
unsigned long blinkStartMillis;  //some global variables available anywhere in the program

unsigned long masterCurrentMillis;
unsigned long uiCurrentMillis;
unsigned long sensorCurrentMillis;
unsigned long blinkCurrentMillis;

const unsigned long masterCoolDown = 100;  //the value is a number of milliseconds
const unsigned long uiRefreshCoolDown = 1000;  //the value is a number of milliseconds
const unsigned long sensorsCoolDown = 10000;  //the value is a number of milliseconds
const unsigned long blinkCoolDown = 1000;  //the value is a number of milliseconds
ShiftRegister74HC595 sr (numberOfShiftRegisters, serialDataPin, clockPin, latchPin);

int nivelHumedadS0 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(buttonPin, INPUT);
  #define PHOTOCELL_MIN 300 // Minimum reading from Photocell
  #define PHOTOCELL_MAX 880 // Maximum reading from Photocell
}

void drawHumedad(int nivelHumedad) {
  for (int i = 0; i <= 4; i++) {
    sr.set(i, LOW);
  }
  sr.set(nivelHumedad, HIGH);
}


void clearSensorLeds() {
  for (int i = 5; i <= 7; i++) {
    sr.set(i, LOW);
  }
}

void blinkALed(int led) {
  blinkCurrentMillis = millis();
  if (blinkCurrentMillis - blinkStartMillis >= blinkCoolDown) {
    sr.set(5+led, !sr.get(5+led));
    blinkStartMillis = blinkCurrentMillis;  //IMPORTANT to save the start time of the current LED state.
  }
}


void loop() {
  uiCurrentMillis = millis();
  sensorCurrentMillis = millis();
  masterCurrentMillis = millis();

  blinkALed(selectedSensor);

  if (masterCurrentMillis - masterStartMillis >= masterCoolDown) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      selectedSensor = selectedSensor+1;
      if (selectedSensor > 2) {
        selectedSensor = 0;
      }
      clearSensorLeds();
    }
    masterStartMillis = masterCurrentMillis;
  }

  if (uiCurrentMillis - uiStartMillis >= uiRefreshCoolDown) {
    Serial.println("UI REFRESH");
    drawHumedad(nivelHumedadS0);
    uiStartMillis = uiCurrentMillis;
  }

  if (sensorCurrentMillis - sensorStartMillis >= sensorsCoolDown) {
    Serial.println("SENSOR REFRESH");
    Serial.println(selectedSensor);
    nivelHumedadS0 = map( constrain(analogRead(selectedSensor), PHOTOCELL_MIN, PHOTOCELL_MAX) , PHOTOCELL_MIN, PHOTOCELL_MAX, 0, 4);
    Serial.println(nivelHumedadS0);
    sensorStartMillis = sensorCurrentMillis;
  }
  sr.set(0, HIGH);
}

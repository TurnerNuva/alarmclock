//HackGT 9 Alarm Clock
//Date started: 10/22/2022
//Written by: Turner Flynn, Evan Fulkerson, Tyler Beach

#include <Keypad.h>

const int photoResistor = 11;
const int sevenLED = 10;
int alarmOn = 0;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad


//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(0));
  pinMode(alarmInput, INPUT);
  pinMode(photoResistor, INPUT);

  pinMode(alarmButtonInput, INPUT);
  pinMode(snoozeInput, INPUT);

  pinMode(sevenLED, OUTPUT);

  Serial.begin(9600);

}

void loop() {
int randomDigit = random(0, 10);
Serial.println("Press " + customKey);
if(customKeypad.getKey() == randomDigit)
  Serial.println("Correct");

}

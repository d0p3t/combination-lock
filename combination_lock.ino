#include <pitches.h>
#define BUTTON_A_PIN  10                    // ----------Button Safe-----------
#define BUTTON_B_PIN  11                    // Written for Arduino Uno + Dangershield
#define BUTTON_C_PIN  12                    // --------by Remco Troost----------
#define LED_G_PIN     5                     // defining the pins that the components are attached to.
#define LED_R_PIN     6                     //

int pressedCounter  = 0;                    // number of times any button has been pressed.
String combination  = "331";                // <--change safe combination HERE.
String guessCode    = "";                   // the string to store the code that user enters

int currState_A = 0;                        //
int lastState_A = 1;                        // currState and lastState are used to store states of the buttons.
int currState_B = 0;                        // they are used in the debounce algorithm to make sure a button isn't
int lastState_B = 1;                        // pressed twice.
int currState_C = 0;                        // currentState = state after entering first if().
int lastState_C = 1;                        // lastState = last known state to store for when loop is started again.
int reading_A;                              //
int reading_B;                              // reading is a variable for reading the initial state of a button at
int reading_C;                              // the beginning of the loop
int debounceDelay = 200;                    // this is the delay in ms for the debounce algorithm. time user can press button

void setup() {
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);      //
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);      // setting buttons as INPUT_PULLUP due to Dangershield config
  pinMode(BUTTON_C_PIN, INPUT_PULLUP);      //
  pinMode(LED_G_PIN, OUTPUT);               // and leds as OUTPUT
  pinMode(LED_R_PIN, OUTPUT);               //
  digitalWrite(LED_R_PIN, HIGH);            // turn on red led on initial startup
}

void loop() {
  reading_A = digitalRead(BUTTON_A_PIN);    //
  reading_B = digitalRead(BUTTON_B_PIN);    // read the current states of the buttons
  reading_C = digitalRead(BUTTON_C_PIN);    //

  storeCombo(reading_A, lastState_A, currState_A, "1");
  storeCombo(reading_B, lastState_B, currState_B, "2");
  storeCombo(reading_C, lastState_C, currState_C, "3");
  checkCombo();
}

// FUNCTIONS
void storeCombo (int reading, int lastState, int currState, String value) {
  if(reading != lastState) 
  {
    delay(debounceDelay);
    currState = reading;
    if(currState == LOW)
    {
      pressedCounter++;
      guessCode += value;
    }
  }
  lastState = reading;
}

void checkCombo() {
  if(guessCode == combination && pressedCounter == 3)
  {
    digitalWrite(LED_R_PIN, LOW);           // turn off red led first
    digitalWrite(LED_G_PIN, HIGH);          // if correct, turn on green led for 3 seconds
    delay(3000);                            //
    digitalWrite(LED_G_PIN, LOW);           //
    digitalWrite(LED_R_PIN, HIGH);          // turn on red led afterwards
    guessCode   =      "";                  // and then reset the guessCode so you can open
    pressedCounter  =   0;                  // the safe again after you closed it
  }
  else if(guessCode != combination && pressedCounter == 3)
  {
    for(int i = 0; i < 3; i++)
    {
      digitalWrite(LED_R_PIN, LOW);         // if wrong, blink red led 3 times
      delay(250);                           // 0.5 sec between each blink, so
      digitalWrite(LED_R_PIN, HIGH);        // 250mx per value change
      delay(250);                            
    }
    guessCode  =       "";                  // and then again, reset the vaRIABLES
    pressedCounter  =   0;                  // so you can retry the safe combination
  }
}

void bootSequence()
{
  //sound+display when booting
}

void correctSound()
{
  //sound played for correct combo
}

void incorrectSound()
{
  //sound played for incorrect combo
}

void displayValue(String value)
{
  //method to display pressed button
}



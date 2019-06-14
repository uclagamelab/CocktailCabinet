//
// *** Sketch to emulate a USB gamepad with the cocktail cabinet
//     joysticks for use with the UCLA Game Lab switcher.
//
// *** Currently setup assuming a digital (not-analog) joystick
//
// *** This sketch file is for use with Arduino Leonardo and
//     Arduino Micro only.
//
// *** Requires this Arduino library
// https://github.com/MHeironimus/ArduinoJoystickLibrary
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID+1,JOYSTICK_TYPE_GAMEPAD,
  8, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering


  /*//pin values from keyboard version of sketch
  int upPin = 2;
  int downPin = 3;
  int leftPin = 4;
  int rightPin = 5;
  int buttonOnePin = 6;
  int buttonTwoPin = 7;
  int buttonThreePin = 8;
  int buttonFourPin = 9;
  int buttonFivePin = 10;
  int buttonSixPin = 11;
  int playerSelectBitOnePin = 12;
  int playerSelectBitTwoPin = 13;
  */
#define pinGamepadButtonPairs_SIZE 12
int pinGamepadButtonPairs[] =
{
  6, 3,
  7, 4,
  8, 5,
  9, 0,
  10, 1,
  11, 2
};

int lastQuitButtonChordState;
#define quitButtonPinChord_LENGTH 3
int quitButtonPinChord[] = { 9, 10, 11 };
#define USE_QUIT_BUTTON_CHORD true
#define QUIT_JOYSTICK_BUTTON 7


//UP >  DOWN > LEFT > RIGHT
#define pinJoystickDirectionPins_SIZE 4
//horizontal -> vertical
int pinJoystickDirectionPins[] =
{
  2,
  3,
  4,
  5
};

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 6;

// Last state of the button
int lastButtonState[pinGamepadButtonPairs_SIZE];//= {0,0,0,0};

void setup() {
  // Initialize Button Pins
  for (int i = 0; i < pinGamepadButtonPairs_SIZE; i += 2)
  {
    int pin = pinGamepadButtonPairs[i];
    pinMode(pin, INPUT_PULLUP);
  }

  for (int i = 0; i < pinJoystickDirectionPins_SIZE; i++)
  {
    int pin = pinJoystickDirectionPins[i];
    pinMode(pin, INPUT_PULLUP);
  }


  pinMode(A0, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
  Joystick.setButton(6,0); //set button 7 off
}



void loop() {

  // Read pin values
  for (int i = 0; i < pinGamepadButtonPairs_SIZE; i += 2)
  {
    int pin = pinGamepadButtonPairs[i];
    int joystickButton = pinGamepadButtonPairs[i + 1];
    int currentButtonState = !digitalRead(pin);
    if (currentButtonState != lastButtonState[i])
    {
      Joystick.setButton(joystickButton, currentButtonState);
      lastButtonState[i] = currentButtonState;
    }
  }

  for (int i = 0; i < pinJoystickDirectionPins_SIZE / 2; i++)
  {
    int posPin = !digitalRead(pinJoystickDirectionPins[(2 * i) + 1]);
    int negativePin = !digitalRead(pinJoystickDirectionPins[(2 * i)]);
    
    int finalAxisVal = 0;
    
    bool isHorizontal = i == 1;
    
    if (posPin)
    {

      finalAxisVal = 127;

    }
    else if (negativePin)
    {
      finalAxisVal = -127;
    }
    

    if (isHorizontal)
    {
      Joystick.setXAxis(finalAxisVal);
    }
    else
    {
      Joystick.setYAxis(finalAxisVal);
    }
  }

  //--- QUIT BUTTON SIMULATED ----
  if (USE_QUIT_BUTTON_CHORD)
  {
    bool currentQuitButtonChordState = true;

    for (int i = 0; i < quitButtonPinChord_LENGTH; i++)
    {
      currentQuitButtonChordState &= !digitalRead(quitButtonPinChord[i]);
    }

    if (currentQuitButtonChordState != lastQuitButtonChordState)
    {
      Joystick.setButton(QUIT_JOYSTICK_BUTTON, currentQuitButtonChordState);
    }

    lastQuitButtonChordState = currentQuitButtonChordState;
  }
  //------
 ZeroUnusedAxes();
  delay(10);
}

void ZeroUnusedAxes()
{
  //fishy looking, but without this line, Unity games with default input 
  //get constant spurious input
  Joystick.setZAxis(-127);
}

//
// *** Sketch to emulate a USB gamepad with the cocktail cabinet
//     joysticks for use with the UCLA Game Lab switcher.
//
// *** Currently setup assuming a digital (not-analog) joystick
//
// relies on these:
//https://www.partsnotincluded.com/tutorials/how-to-emulate-an-xbox-controller-with-arduino-xinput/
//https://github.com/dmadison/ArduinoXInput_AVR
//
//--------------------------------------------------------------------

#include <XInput.h>
#define pinGamepadButtonPairs_SIZE 12
int pinGamepadButtonPairs[] =
{
  6, 4,
  7, 5,
  8, 6,
  9, 1,
  10, 2,
  11, 3
};

int lastQuitButtonChordState;
#define quitButtonPinChord_LENGTH 3
int quitButtonPinChord[] = { 9, 10, 11 };
#define USE_QUIT_BUTTON_CHORD true
#define QUIT_JOYSTICK_BUTTON 8
#define ADC_MAX 4095
#define JOYMIN -32768 
#define JOYMID 0
#define JOYMAX 32767

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

  // Initialize Joystick Library
  //Joystick.begin();
  //Joystick.setXAxisRange(-1, 1);
  //Joystick.setYAxisRange(-1, 1);
  //Joystick.setZAxisRange(-1, 1);
  //Joystick.setButton(6,0); //set button 7 off
  //XInput.setJoystickRange(0, ADC_MAX);  // Set joystick range to the ADC
  XInput.setAutoSend(false); 
  XInput.begin();
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
      //Joystick.setButton(joystickButton, currentButtonState);
      if (currentButtonState)
      {    
        XInput.press(joystickButton);
      }
      else
      {
         XInput.release(joystickButton);
      }
      lastButtonState[i] = currentButtonState;
    }
  }

int finalX = JOYMID;
int finalY = JOYMID;
  for (int i = 0; i < pinJoystickDirectionPins_SIZE / 2; i++)
  {
    int posPin;
    int negativePin;
    
    
    int finalAxisVal = JOYMID;
    
    bool isHorizontal = i == 1;

    if (!isHorizontal)
    {
       posPin = !digitalRead(pinJoystickDirectionPins[(2 * i)]);
      negativePin = !digitalRead(pinJoystickDirectionPins[(2 * i) + 1]);
    }
    else
    {
      posPin = !digitalRead(pinJoystickDirectionPins[(2 * i) + 1]);
      negativePin = !digitalRead(pinJoystickDirectionPins[(2 * i)]);
    }
    if (posPin)
    {

      finalAxisVal = JOYMAX;

    }
    else if (negativePin)
    {
      finalAxisVal = JOYMIN;
    }
    

    if (isHorizontal)
    {
      finalX = finalAxisVal;
     // Joystick.setXAxis(finalAxisVal);
    }
    else
    {
      finalY = finalAxisVal;
    }
  }
  XInput.setJoystick(JOY_LEFT, finalX, finalY);

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
      if (currentQuitButtonChordState)
      {
        XInput.press(QUIT_JOYSTICK_BUTTON); 
      }
      else
      {
         XInput.release(QUIT_JOYSTICK_BUTTON); 
      }
      //Joystick.setButton(QUIT_JOYSTICK_BUTTON, currentQuitButtonChordState);
    }

    lastQuitButtonChordState = currentQuitButtonChordState;
  }
  //------
 ZeroUnusedAxes();
  XInput.send();
}

void ZeroUnusedAxes()
{
  //fishy looking, but without this line, Unity games with default input 
  //get constant spurious input
  //Joystick.setZAxis(0);
  //Joystick.setRxAxis(0);
  //Joystick.setRyAxis(0);
  //Joystick.setHatSwitch(0, -1);
  //Joystick.setHatSwitch(1, -1);
}

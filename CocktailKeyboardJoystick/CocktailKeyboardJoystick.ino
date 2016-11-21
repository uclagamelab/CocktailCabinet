// these are for pinMode setup
int pinBegin = 2;
int pinEnd = 13;

// joystick and button mappings
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

int menuSelectPin = A0;

int pinValues[10] = {1,1,1,1,1,1,1,1,1,1};
int menuValue = 1;
// keep track of the player number
// up to four players numbered 0 - 3 
int playerNumber = 0;

// keymappings for inputs
// array position maps to player number
char upKeys[] = {'w', 't', 'i', KEY_UP_ARROW};
char downKeys[] = {'s', 'g', 'k', KEY_DOWN_ARROW};
char leftKeys[] = {'a', 'f', 'j', KEY_LEFT_ARROW};
char rightKeys[] = {'d', 'h', 'l', KEY_RIGHT_ARROW};
char oneKeys[] = {'z', 'v', 'm', 'p'};
char twoKeys[] = {'x', 'b', ',', '['};
char threeKeys[] = {'c', 'n', '.', ']'};
char fourKeys[] = {'1', '4', '7', '0'};
char fiveKeys[] = {'2', '5', '8', '-'};
char sixKeys[] = {'3', '6', '9', '='};
char menuKey = KEY_TAB;

// float delay time after keypress events sent
int delayTime = 10;

void setup()
{
  // assign digital pins for joystick, button, and player select
  for (int i = pinBegin; i < pinEnd +1; i++)
  { 
    // keep all pins in high mode until grounded
    pinMode(i, INPUT_PULLUP);
  }
  
  // assign analog pin for menu button
  pinMode(A0, INPUT_PULLUP);
  
  Keyboard.begin();
}

void loop()
{
  // check the player number
  playerNumber = 0;
  if (digitalRead(playerSelectBitOnePin) == LOW)
  {
    playerNumber = 1;
  }
  if (digitalRead(playerSelectBitTwoPin) == LOW)
  {
    playerNumber += 2;
  }
  
  // check input all joystick directions
  if (digitalRead(upPin) == LOW) // up
  {
    Keyboard.press(upKeys[playerNumber]);
    pinValues[upPin-pinBegin] = LOW;
  }
  else
  {
    if (pinValues[upPin-pinBegin] == LOW)
      Keyboard.release(upKeys[playerNumber]);
    pinValues[upPin-pinBegin] = HIGH;
  }
    
  if (digitalRead(downPin) == LOW) // down
  {
    Keyboard.press(downKeys[playerNumber]);
    pinValues[downPin-pinBegin] = LOW;
  }
  else
  {
    if (pinValues[downPin-pinBegin] == LOW)
      Keyboard.release(downKeys[playerNumber]);
    pinValues[downPin-pinBegin] = HIGH;
  }
  
  if (digitalRead(leftPin) == LOW) // left
  {
    Keyboard.press(leftKeys[playerNumber]);
    pinValues[leftPin-pinBegin] = LOW;
  }
  else
  {
    if (pinValues[leftPin-pinBegin] == LOW)
      Keyboard.release(leftKeys[playerNumber]);
    pinValues[leftPin-pinBegin] = HIGH;
  }
  
  if (digitalRead(rightPin) == LOW) // right
  {
    Keyboard.press(rightKeys[playerNumber]);
    pinValues[rightPin-pinBegin] = LOW;
  }
  else
  {
    if (pinValues[rightPin-pinBegin] == LOW)
      Keyboard.release(rightKeys[playerNumber]);
    pinValues[rightPin-pinBegin] = HIGH;
  }
  
  // check input all buttons
  if (digitalRead(buttonOnePin) == LOW) // button one
  {
    Keyboard.press(oneKeys[playerNumber]);
    pinValues[buttonOnePin-pinBegin] = LOW;
  }
  else
  {
    if (pinValues[buttonOnePin-pinBegin] == LOW)
      Keyboard.release(oneKeys[playerNumber]);
    pinValues[buttonOnePin-pinBegin] = HIGH;
  }
  
  if (digitalRead(buttonTwoPin) == LOW) // button two
  {
    Keyboard.press(twoKeys[playerNumber]);
    pinValues[buttonTwoPin-pinBegin] = LOW;
  }
  else
  {
    if (pinValues[buttonTwoPin-pinBegin] == LOW)
      Keyboard.release(twoKeys[playerNumber]);
    pinValues[buttonTwoPin-pinBegin] = HIGH;
  }
  
  if (digitalRead(buttonThreePin) == LOW) // button three
  {
    Keyboard.press(threeKeys[playerNumber]);
    pinValues[buttonThreePin-pinBegin] = LOW;
  }
  else
  {
    if (pinValues[buttonThreePin-pinBegin] == LOW)
      Keyboard.release(threeKeys[playerNumber]);
    pinValues[buttonThreePin-pinBegin] = HIGH;
  }
  
  if (digitalRead(buttonFourPin) == LOW) // button four
  {
    Keyboard.press(fourKeys[playerNumber]);
    pinValues[buttonFourPin-pinBegin] = LOW;
  }
  else
  {
    if (pinValues[buttonFourPin-pinBegin] == LOW)
      Keyboard.release(fourKeys[playerNumber]);
    pinValues[buttonFourPin-pinBegin] = HIGH;
  }
  
  if (digitalRead(buttonFivePin) == LOW) // button five
  {
    Keyboard.press(fiveKeys[playerNumber]);
    pinValues[buttonFivePin-pinBegin] = LOW;
  }
  else
  {
    if (pinValues[buttonFivePin-pinBegin] == LOW)
      Keyboard.release(fiveKeys[playerNumber]);
    pinValues[buttonFivePin-pinBegin] = HIGH;
  }
  
  if (digitalRead(buttonSixPin) == LOW) // button six
  {
    Keyboard.press(sixKeys[playerNumber]);
    pinValues[buttonSixPin-pinBegin] = LOW;
  }
  else
  {
    if (pinValues[buttonSixPin-pinBegin] == LOW)
      Keyboard.release(sixKeys[playerNumber]);
    pinValues[buttonSixPin-pinBegin] = HIGH;
  }
  
  if (digitalRead(menuSelectPin) == LOW) // menu button
  {
    Keyboard.press(menuKey);
    menuValue = LOW;
  }
  else
  {
    if (menuValue == LOW)
     Keyboard.release(menuKey);
    menuValue = HIGH; 
  }
  
  // delay for computer to read
  delay(delayTime);
  
}

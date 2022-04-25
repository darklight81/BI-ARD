#define UP_TRESHOLD           // zde vhodně nastavte hranici, která určí, že je joystick v pozici nahoře
#define DOWN_TRESHOLD         // zde vhodně nastavte hranici, která určí, že je joystick v pozici dole
#define RIGHT_TRESHOLD        // zde vhodně nastavte hranici, která určí, že je joystick v pozici vpravo
#define LEFT_TRESHOLD         // zde vhodně nastavte hranici, která určí, že je joystick v pozici vlevo

#define CENTER 0
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4
#define PUSH 5

#define RED 11
#define GREEN 10
#define BLUE 9
int xval = 0, yval = 0, x, y;
int x_cor = A0;
int y_cor = A1;
/*
  int readJoystickKey(){
    if (button == LOW) {
      return PUSH;
    }

    if (yPos > UP_TRESHOLD) {     // joystick je nahoře
      return UP;
    }

    if (yPos < DOWN_TRESHOLD) {   // joystick je dole
      return DOWN;
    }

    if (xPos > RIGHT_TRESHOLD) {  // joystick je vpravo
      return RIGHT;
    }

    if (xPos < LEFT_TRESHOLD) {   // joystick je vlevo
      return LEFT;
    }

    return CENTER;
  }
*/

void setup()
{
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{
  xval = analogRead(x_cor);
  yval = analogRead(y_cor);
  x = map(xval, 0, 1023, 0, 255);
  y = map(yval, 0, 1023, 0, 255);

  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);

  if ( x > 120 && x < 130 && y > 120 && y < 130){
    analogWrite(RED, 0);
    analogWrite(BLUE, 0);
    analogWrite(GREEN, 0);
  }
  else {
    if (x > 127)
      analogWrite(GREEN, x-127);
    else
      analogWrite(GREEN, 127-x);
    if (y > 127)
      analogWrite(BLUE, y-127);
    else
      analogWrite(RED, 127-y);
    }
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" ,y: ");
  Serial.println(y);
  /*
      switch (pos_joystick)
      {
        case LEFT:
        case RIGHT:
        case UP:
        case DOWN:
        case CENTER:
        case PUSH:
      }
  */

}

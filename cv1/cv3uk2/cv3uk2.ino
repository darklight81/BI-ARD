#define UP_TRESHOLD 130           // zde vhodně nastavte hranici, která určí, že je joystick v pozici nahoře
#define DOWN_TRESHOLD         // zde vhodně nastavte hranici, která určí, že je joystick v pozici dole
#define RIGHT_TRESHOLD 130        // zde vhodně nastavte hranici, která určí, že je joystick v pozici vpravo
#define LEFT_TRESHOLD         // zde vhodně nastavte hranici, která určí, že je joystick v pozici vlevo

#define CENTER 0
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4
#define PUSH 5
int pos_joystick == 0;


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


void setup()
{
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{
  pos_joystick = readJoystickKey();
  
      switch (pos_joystick)
      {
        case LEFT:
        case RIGHT:
        case UP:
        case DOWN:
        case CENTER:
        case PUSH:
      }
}

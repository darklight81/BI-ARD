#define RED 13              // číslo pinu, na kterém je červená LED
#define GREEN 11            // číslo pinu, na kterém je zelená LED
#define BLUE 12             // číslo pinu, na kterém je modrá LED
int flag = 0;

void flash(int duration, int COLOR){
  digitalWrite(COLOR, 1);
  unsigned int myTime = millis();
  delay(duration);
  digitalWrite(COLOR, 0);
}


enum states {
  STATE_START, STATE_SW1, STATE_SW2, STATE_SW1SW2
};

enum states STATE, NEXT_STATE;

void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);
  STATE = STATE_START;
}


void loop() {
    int sw1_pressed = !digitalRead(2);
    int sw2_pressed = !digitalRead(3);
    switch (STATE)
    {
      case STATE_START:
          flag = 0;
          if (sw1_pressed == true) {
            NEXT_STATE = STATE_SW1;

          }
          else if (sw2_pressed == true) {
            NEXT_STATE = STATE_SW2;
          }

          break;

      case STATE_SW1:
         if(sw2_pressed == true){
          NEXT_STATE = STATE_SW1SW2;
         }
         else if (sw1_pressed == false) {
          NEXT_STATE = STATE_START;
          if (flag == 0){
            flag = 1;
            Serial.println("AKCE A");
            flash(100, RED);
            }
         }
         break;

      case STATE_SW2:
        if(sw1_pressed == true){
          NEXT_STATE = STATE_SW1SW2;
         }
         else if (sw2_pressed == false) {
          NEXT_STATE = STATE_START;
           if (flag == 0){
            flag = 1;
            Serial.println("AKCE B");
            flash(100, GREEN);
            }
         }
         break;

      case STATE_SW1SW2:
         if (sw2_pressed == false && sw1_pressed == false) {
          NEXT_STATE = STATE_START;
           if (flag == 0){
            flag = 1;
            Serial.println("AKCE C");
            flash(100, BLUE);
            }
         }
         break;

    }

    STATE = NEXT_STATE;
 }

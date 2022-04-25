#define RED 13              // číslo pinu, na kterém je červená LED
#define GREEN 11            // číslo pinu, na kterém je zelená LED
#define BLUE 12             // číslo pinu, na kterém je modrá LED

#define DOT 200             // doba bliknutí tečky
#define DASH 800            // doba bliknutí čárky
#define NO_LIGHT 200        // doba vypnutí LED mezi jednotlivými bliknutími
int flg1 = 0, flg2 = 0, flg3 = 0;
int COLOR = 11;
/*
void flash(int duration){
  digitalWrite(COLOR, 1);
  unsigned int myTime = millis();
  int res;
  while ( millis() < myTime + duration) {
    res = digitalRead(3);
    if (res == 0 && flag == 0){
      flag = 1;
      digitalWrite(COLOR, 0);
       if ( COLOR == 13 ){
          COLOR = 11;
       }
       else{ 
          COLOR += 1;
        }
       digitalWrite(COLOR, 1);
    }
    if (res == 1){
      flag = 0;
      delay(10);
    }
  }
  digitalWrite(COLOR, 0);
  delay(NO_LIGHT);
}
*/
void checkLED(int btn1, int col){
  if (btn1 == 0 && flg1 == 0){
      switch(col){
        case RED:
          digitalWrite(RED, 1);
          Serial.println("RED");
          break;
        case GREEN:
          digitalWrite(GREEN, 1);
          Serial.println("GREEN");
          break;
        case BLUE:
          digitalWrite(BLUE, 1);
          Serial.println("BLUE");
          break;
        default:
          break;
      }
  }
  if (btn1 == 1){
    flg1 = 0;
    switch(col){
        case RED:
          digitalWrite(RED, 0);
          break;
        case GREEN:
          digitalWrite(GREEN, 0);
          break;
         case BLUE:
          digitalWrite(BLUE, 0);
        default:
          break;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int btn1, btn2, btn3;
  btn1 = digitalRead(2);
  btn2 = digitalRead(3);
  btn3 = digitalRead(4);
  if (btn1 == 0 && flg1 == 0){
    flg1 = 1;
    digitalWrite(RED, 1);
    Serial.println("RED");
  }
  if (btn2 == 0 && flg2 == 0){
    flg2 = 1;
    digitalWrite(GREEN, 1);
    Serial.println("GREEN");
  }
  if (btn3 == 0 && flg3 == 0){
    flg3 = 1;
    digitalWrite(BLUE, 1);
    Serial.println("BLUE");
  }
  if (btn1 == 1){
    digitalWrite(RED, 0);
    flg1 = 0; 
  }
  if (btn2 == 1){
    digitalWrite(GREEN, 0);
    flg2 = 0; 
  }
  if (btn3 == 1){
    digitalWrite(BLUE, 0);
    flg3 = 0; 
  }
}

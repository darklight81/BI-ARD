#define RED 13              // číslo pinu, na kterém je červená LED
#define GREEN 11            // číslo pinu, na kterém je zelená LED
#define BLUE 12             // číslo pinu, na kterém je modrá LED

#define DOT 200             // doba bliknutí tečky
#define DASH 800            // doba bliknutí čárky
#define NO_LIGHT 200        // doba vypnutí LED mezi jednotlivými bliknutími
int flg1 = 0, flg2 = 0, flg3 = 0;
int COLOR = 11;
String incomingString;

char* letters[]={
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",  // A-G
    "...." , "..", ".---", "-.-", ".-..", "--", "-.", // H-N
    "---", ".--.", "--.-", ".-.", "...", "-", "..-",  // O-U
    "...-", ".--", "-..-", "-.--", "--.."             // V-Z
  };

void flash(int duration){
  digitalWrite(COLOR, 1);
  unsigned int myTime = millis();
  int res;
  delay(duration);
  digitalWrite(COLOR, 0);
  delay(NO_LIGHT);
}

void flashSequence(String sequence){
  for(int i = 0; i < sequence.length(); i++){
    if(sequence[i] - 65 < 0 || sequence[i] - 65 > 25)
      continue; 
    String letter = letters[sequence[i]-65];
      for ( int j = 0; j < letter.length(); j++){
        if(letter[j] == '.'){
          flash(DOT);
        }
        else
          flash(DASH);
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
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingString = Serial.readString();

    flashSequence(incomingString);
  }
}

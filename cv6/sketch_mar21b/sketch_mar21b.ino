#define BLUE_PIN  11
#define GREEN_PIN 12
#define RED_PIN   13
int incomingByte = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT); 
  pinMode(RED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //put your main code here, to run repeatedly:
  double temp = analogRead(A2) * 0.489  - 273; 
  Serial.println(temp);
  while ( Serial.available() > 0) {
    incomingByte = Serial.read();
    char x = (char) incomingByte;
    if (x == 'R'){
      digitalWrite(BLUE_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(RED_PIN, !LOW);
    }
    else if (x == 'G'){
      digitalWrite(BLUE_PIN, LOW);
      digitalWrite(GREEN_PIN, !LOW);
      digitalWrite(RED_PIN, LOW);
    }
    else if ( x == 'B'){
      digitalWrite(BLUE_PIN, !LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(RED_PIN, LOW);
    }
    else{
      digitalWrite(BLUE_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(RED_PIN, LOW);
    }
  }
}

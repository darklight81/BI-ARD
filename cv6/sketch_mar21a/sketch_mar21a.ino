#define BLUE_PIN  11
#define GREEN_PIN 12
#define RED_PIN   13
#define BUTTON 2
volatile byte state = 11;
volatile byte state2 = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT); 
  pinMode(RED_PIN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), blink, FALLING);
  Serial.begin(9600);


}

void loop() {
    Serial.println("TEST");
    delay(1000);
    //state2 = true;
    //digitalWrite(state, !LOW);
    //delay(1000);
    //state2 = false;
    //digitalWrite(state, LOW);
    //delay(1000);


}

void blink() {
  if (state2){
  digitalWrite(state, LOW);
  }
  if (state == 13)
    state = 11;
  else
    state+= 1;
  if (state2)
    digitalWrite(state, !LOW);
}

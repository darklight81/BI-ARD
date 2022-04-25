#include <Esplora.h>
#include <SPI.h>
#include <TFT.h>

bool gameStatus = true;
bool scoreUpdate = true;
int score = 0;
int highScore = 0;
String tmpScore;
char tmpScore2[3];
int screenHeight;
int screenWidth;

const renderSpeed = 1000; // in milis
const initialSnakeLength = 3;

void updateBackground(){
  if (gameStatus == false){
    //Render end screen;
  }
  else {
    EsploraTFT.stroke(0,0,0);
    EsploraTFT.fill(0,0,0);
    EsploraTFT.rect(22, 22, screenWidth-33, screenHeight-33);
    //check if score needs to be rerendered
    if (scoreUpdate){
        printScore();
        scoreUpdate = false;
    }
  }
}

void setBackground(){
   EsploraTFT.background(0,0,0);
   EsploraTFT.stroke(255,255,255);
   EsploraTFT.fill(0,0,0);
   EsploraTFT.rect(20, 20, screenWidth-30, screenHeight-30);
}

void renderSnake(){
    
}

void spawnFood(){
  //todo: check if food is already spawned, if yes dont spawn another one
  
  int height = random(22, screenHeight-38);
  int width  = random(22, screenWidth-38);
  Serial.println((String)"Height: "+height+", width: "+width);
  EsploraTFT.stroke(255,255,255);
  EsploraTFT.fill(255,255,255);
  EsploraTFT.rect(width, height, 5, 5);
}

void printScore(){
  EsploraTFT.stroke(0,0,0);
  EsploraTFT.fill(0,0,0);
  EsploraTFT.rect(0, 0, screenWidth, 20);
  EsploraTFT.setTextSize(2);
  EsploraTFT.stroke(255, 255, 255);
  EsploraTFT.text("Score: ", 0, 0);
  tmpScore = String(score);
  tmpScore.toCharArray(tmpScore2, 3);
  EsploraTFT.text(tmpScore2, 70, 0);
}

void setup() {
  screenHeight = EsploraTFT.height();
  screenWidth  = EsploraTFT.width();
  Serial.begin(9600);
  EsploraTFT.begin();
  setBackground();
  //load highscore from EEPROM if there's any;
}

void loop() {
  updateBackground();
  spawnFood();
  renderSnake();
  //continueCheck();
  delay(renderSpeed);
  // put your main code here, to run repeatedly:

}

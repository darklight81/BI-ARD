#include <Esplora.h>
#include <SPI.h>
#include <TFT.h>

bool gameStatus = true;
bool scoreUpdate = true;
bool foodEaten = true;
int score = 0;
int highScore = 0;
String tmpScore;
char tmpScore2[3];
int screenHeight;
int screenWidth;
int snake[3][2];
int tmpSnake[1][2];
int foodHeight;
int foodWidth;
int direction = 0; // 0 == UP, 1 == RIGHT, 2 == DOWN, 3 == LEFT

const int renderSpeed = 1000; // in milis
const int initialSnakeLength = 3;

void updateBackground(){
  if (gameStatus == false){
    EsploraTFT.background(0, 0, 0);
    EsploraTFT.stroke(255,255,255);
    EsploraTFT.fill(0,0,0);
    EsploraTFT.setTextSize(2);
    EsploraTFT.text("GAME OVER ", 30, 10);
    if (score > highScore){
       char cstr[16];
      EsploraTFT.setTextSize(1);
      EsploraTFT.text("!NEW HIGHSCORE!", 35, 40);
      EsploraTFT.text(itoa(score, cstr, 10), 70, 50);
    }
    else{
      char cstr[16];
      EsploraTFT.setTextSize(1);
      EsploraTFT.text("Highscore:", 10, 40);
      EsploraTFT.text(itoa(highScore, cstr, 10), 70, 40);
      EsploraTFT.text("Your score:", 10, 60);
      EsploraTFT.text(itoa(score, cstr, 10), 78, 60);
    }

    EsploraTFT.setTextSize(1);
    EsploraTFT.text("Press any button", 30, 100);
    EsploraTFT.text("to continue...", 40, 115);
    while(true){
      int buttonDown = Esplora.readButton(SWITCH_DOWN);
      int buttonRight =  Esplora.readButton(SWITCH_RIGHT);
      int buttonUp =  Esplora.readButton(SWITCH_UP);
      int buttonLeft =  Esplora.readButton(SWITCH_LEFT);
      if (buttonDown == LOW || buttonRight == LOW || buttonLeft == LOW || buttonUp == LOW){
        break;
      }
    }
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
void checkPosition(){
  if (tmpSnake[0][0] < 22 || tmpSnake[0][0] > screenHeight-15 
      || tmpSnake[0][1] < 22 || tmpSnake[0][1] > screenWidth-15){
        Serial.println("OUT OF BORDER");
        gameStatus = false;
      }
  else if(tmpSnake[0][0] >= foodHeight && tmpSnake[0][0] <= foodHeight+5 
          && tmpSnake[0][1] >= foodWidth && tmpSnake[0][1] <= foodWidth+5){
            Serial.println("EATEN");
            scoreUpdate = true;
            score += 1;
            foodEaten = true;
          }
  Serial.print("Snake Height: ");
  Serial.println(tmpSnake[0][0]);
  Serial.print("Snake Width: ");
  Serial.println(tmpSnake[0][1]);
  Serial.print("Food Height: ");
  Serial.println(foodHeight);
  Serial.print("Food Width: ");
  Serial.println(foodWidth);
}

void renderSnake(){
    EsploraTFT.stroke(255,255,255);
    EsploraTFT.fill(255,255,255);
    /*for(int i = 0; i < 3; i++){
      EsploraTFT.rect(snake[i][1], snake[i][0], 5, 5);
    }
    */
    switch(direction){
      case 0:
        tmpSnake[0][0] -= 5;
        break;
      case 1:
        tmpSnake[0][1] += 5;
        break;
      case 2:
        tmpSnake[0][0] += 5;
        break;
      case 3:
        tmpSnake[0][1] -= 5;
        break;
    }
    EsploraTFT.rect(tmpSnake[0][1], tmpSnake[0][0], 5, 5);
}

void spawnFood(){
  //todo: check if food is already spawned, if yes dont spawn another one
  if(foodEaten){
    foodHeight = random(22, screenHeight-38);
    foodWidth  = random(22, screenWidth-38);
    foodEaten = !foodEaten;
  }
  //Serial.println((String)"Height: "+foodHeight+", width: "+foodWidth);
  EsploraTFT.stroke(255,255,255);
  EsploraTFT.fill(255,255,255);
  EsploraTFT.rect(foodWidth, foodHeight, 5, 5);
}
void getDirection(){
  int buttonDown = Esplora.readButton(SWITCH_DOWN);
  int buttonRight =  Esplora.readButton(SWITCH_RIGHT);
  int buttonUp =  Esplora.readButton(SWITCH_UP);
  int buttonLeft =  Esplora.readButton(SWITCH_LEFT);
  if (buttonUp == LOW && direction != 2) 
    direction = 0;
  else if(buttonRight == LOW && direction != 3)
    direction = 1;
  else if(buttonDown == LOW && direction != 0)
    direction = 2;
  else if(buttonLeft == LOW && direction != 1)
    direction = 3;

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
  for(int i=0; i < 3; i++){
    snake[i][0] = EsploraTFT.height()/2;
    snake[i][1] = EsploraTFT.width()/2 - 5*i;
  }
  tmpSnake[0][0] = EsploraTFT.height()/2;
  tmpSnake[0][1] = EsploraTFT.width()/2;
  
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
  checkPosition();
  //continueCheck();
  getDirection();
  delay(renderSpeed);
}

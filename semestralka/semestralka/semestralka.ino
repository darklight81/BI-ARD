#include <Esplora.h>
#include <SPI.h>
#include <TFT.h>
#include <EEPROM.h>

bool gameStatus = true;
bool scoreUpdate = true;
bool foodEaten = true;
int score = 0;
int highScore = 0;
String tmpScore;
char tmpScore2[3];
int screenHeight;
int screenWidth;
int tmpSnake[10][2];
int foodHeight;
int foodWidth;
int myTime;
int snakeLen = 1;
int direction = 0; // 0 == UP, 1 == RIGHT, 2 == DOWN, 3 == LEFT
const int eepromAddress = 42;
const int renderSpeed = 200; // in milis

//loads highscore from EEPROM if there's any;
int setHighscore()
{
    highScore = EEPROM.read(eepromAddress);
    Serial.println(highScore);
    if (highScore == 255)
        highScore = 0;
}

//Calls after game is about to restart and resets all needed variables
void restartGame()
{
    score = 0;
    direction = 0;
    gameStatus = true;
    scoreUpdate = true;
    foodEaten = true;
    tmpSnake[0][0] = EsploraTFT.height() / 2 - (EsploraTFT.height() / 2 % 5);
    tmpSnake[0][1] = EsploraTFT.width() / 2 - (EsploraTFT.width() / 2 % 5);
    snakeLen = 1;
    setBackground();
}

// function to play music after end of the game
void gameOverMusic()
{
    Esplora.tone(523);
    delay(300);
    Esplora.noTone();
    Esplora.tone(392);
    delay(300);
    Esplora.noTone();
    Esplora.tone(262);
    delay(300);
    Esplora.noTone();
}

// updates background depending on the game state
void updateBackground()
{
    if (gameStatus == false)
    {
        EsploraTFT.background(0, 0, 0);
        EsploraTFT.stroke(255, 255, 255);
        EsploraTFT.fill(0, 0, 0);
        EsploraTFT.setTextSize(2);
        EsploraTFT.text("GAME OVER ", 30, 10);
        if (score > highScore)
        {
            char cstr[16];
            EEPROM.write(eepromAddress, score);
            EsploraTFT.setTextSize(1);
            EsploraTFT.text("!NEW HIGHSCORE!", 35, 40);
            EsploraTFT.text(itoa(score, cstr, 10), 70, 50);
            highScore = score;
        }
        else
        {
            char cstr[16];
            EsploraTFT.setTextSize(1);
            EsploraTFT.text("Highscore:", 10, 40);
            EsploraTFT.text(itoa(highScore, cstr, 10), 70, 40);
            EsploraTFT.text("Your score:", 10, 60);
            EsploraTFT.text(itoa(score, cstr, 10), 78, 60);
        }

        EsploraTFT.setTextSize(1);
        EsploraTFT.text("Press any button", 30, 100);
        EsploraTFT.text("to start again...", 40, 115);
        gameOverMusic();
        while (true)
        {
            int buttonDown = Esplora.readButton(SWITCH_DOWN);
            int buttonRight = Esplora.readButton(SWITCH_RIGHT);
            int buttonUp = Esplora.readButton(SWITCH_UP);
            int buttonLeft = Esplora.readButton(SWITCH_LEFT);
            if (buttonDown == LOW || buttonRight == LOW || buttonLeft == LOW || buttonUp == LOW)
            {
                restartGame();
                break;
            }
        }
    }
    else
    {
        EsploraTFT.stroke(0, 0, 0);
        EsploraTFT.fill(0, 0, 0);
        EsploraTFT.rect(22, 22, screenWidth - 33, screenHeight - 33);
        //check if score needs to be rerendered
        if (scoreUpdate)
        {
            printScore();
            scoreUpdate = false;
        }
    }
}

// sets the initial background of the game layout
void setBackground()
{
    EsploraTFT.background(0, 0, 0);
    EsploraTFT.stroke(255, 255, 255);
    EsploraTFT.fill(0, 0, 0);
    EsploraTFT.rect(20, 20, screenWidth - 30, screenHeight - 30);
}
// checks if the snake is not out of border or if he is at the place where food is
void checkPosition()
{
    if (tmpSnake[0][0] < 22 || tmpSnake[0][0] > screenHeight - 15 || tmpSnake[0][1] < 22 || tmpSnake[0][1] > screenWidth - 17)
    {
        Serial.println("OUT OF BORDER");
        gameStatus = false;
    }
    else if (tmpSnake[0][0] >= foodHeight && tmpSnake[0][0] <= foodHeight + 5 && tmpSnake[0][1] >= foodWidth && tmpSnake[0][1] <= foodWidth + 5)
    {
        Serial.println("EATEN");
        scoreUpdate = true;
        score += 1;
        foodEaten = true;
        if (snakeLen < 10)
            snakeLen++;
        Esplora.tone(523);
    }
}

void renderSnake()
{
    EsploraTFT.stroke(255, 255, 255);
    EsploraTFT.fill(255, 255, 255);
    for (int i = snakeLen - 1; i > 0; i--)
    {
        Serial.print(tmpSnake[i][0]);
        Serial.print(", ");
        Serial.println(tmpSnake[i][1]);
        tmpSnake[i][0] = tmpSnake[i - 1][0];
        tmpSnake[i][1] = tmpSnake[i - 1][1];
    }
    switch (direction)
    {
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
    Serial.print("snakelen: ");
    Serial.println(snakeLen);
    for (int i = 0; i < snakeLen; i++)
    {
        EsploraTFT.rect(tmpSnake[i][1], tmpSnake[i][0], 5, 5);
    }
}

void spawnFood()
{
    if (foodEaten)
    {
        foodHeight = random(22, screenHeight - 38);
        foodWidth = random(22, screenWidth - 38);
        // Calibration of the position to match the snake width
        foodHeight -= foodHeight % 5;
        foodWidth -= foodWidth % 5;
        foodEaten = !foodEaten;
    }
    //Serial.println((String)"Height: "+foodHeight+", width: "+foodWidth);
    EsploraTFT.stroke(255, 255, 255);
    EsploraTFT.fill(255, 255, 255);
    EsploraTFT.rect(foodWidth, foodHeight, 5, 5);
}
void getDirection()
{
    int buttonDown = Esplora.readButton(SWITCH_DOWN);
    int buttonRight = Esplora.readButton(SWITCH_RIGHT);
    int buttonUp = Esplora.readButton(SWITCH_UP);
    int buttonLeft = Esplora.readButton(SWITCH_LEFT);
    if (buttonUp == LOW && direction != 2)
        direction = 0;
    else if (buttonRight == LOW && direction != 3)
        direction = 1;
    else if (buttonDown == LOW && direction != 0)
        direction = 2;
    else if (buttonLeft == LOW && direction != 1)
        direction = 3;
}
void printScore()
{
    EsploraTFT.stroke(0, 0, 0);
    EsploraTFT.fill(0, 0, 0);
    EsploraTFT.rect(0, 0, screenWidth, 20);
    EsploraTFT.setTextSize(2);
    EsploraTFT.stroke(255, 255, 255);
    EsploraTFT.text("Score: ", 0, 0);
    tmpScore = String(score);
    tmpScore.toCharArray(tmpScore2, 3);
    EsploraTFT.text(tmpScore2, 70, 0);
}

void setup()
{
    tmpSnake[0][0] = EsploraTFT.height() / 2 - (EsploraTFT.height() / 2 % 5);
    tmpSnake[0][1] = EsploraTFT.width() / 2 - (EsploraTFT.width() / 2 % 5);

    screenHeight = EsploraTFT.height();
    screenWidth = EsploraTFT.width();
    Serial.begin(9600);
    EsploraTFT.begin();
    setBackground();
    setHighscore();
}

void loop()
{
    updateBackground();
    spawnFood();
    renderSnake();
    checkPosition();
    myTime = millis();
  while ( millis() - myTime < renderSpeed
     getDirection();
  Esplora.noTone();
}
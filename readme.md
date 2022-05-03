# Documentation - The Snake [BI-ARD]

## Summary

The game is implemented of the Arduino Esplora.

The game supports all features that were set out during theoretical preperation.

The game starts right away. Before the start it tries to load highscore from eeprom, if the highscore wasn't set yet, it is considered 0. Game ends when the user hits the outline of the level or hit the part of the snake. If the score reached during the game is higher than the highscore, the game sets the score as the new highscore.

After the snake encounters the food (meaning it is at the same place as the food), the game plays a sound. The snake gets larger (up to 10 'blocks'). It plays a sound when the game ends as well.

The game is controlled by the buttons.

## Documentation
```
void setHighscore()
```
Loads Highscore from EEPROM at the start of the game if there's any.

```
void restartGame()
```
Called after game is about to restart and resets all needed variables.

```
void gameOverMusic()
```
Plays music after the game is over.

```
void updateBackground()
```
Updates background depending on the gameStatus, if the game is false, renders the game over screen, else it checks if the score is higher, if yes rerenders the score.

```
void setBackground()
```
Sets the initial background of the game layout

```
void checkPosition()
```
Checks if the snake didn't colide with any object or himself or if it's  not at the place of food.


```
void renderSnake()

```
Renders the snake on the board

```
void spawnFood()
```
Spawns *food* on the random place on the board. 

```
void getDirection()
```
Reads the buttons of Esplora and adjusts the direction of the snake appropriately

```
void printScore()
```
Called by updateBackground() to update score on the display

```
void setup()
```
Initializes the game

```
void loop()
```
Main game loop




## User handbook
After uploading the game to the Esplora, your goal is to survive as long as possible while obtaining as much food as possible. But it won't be that easy. If you hit the border, game ends, so watch out! Also, when you obtain food, the snake will get bigger, dont hit any part of the snake either!

You control the movement of the snake by Esplora buttons. If you set a new highscore it will be perserved even after unplugging the Esplora.

Good luck!
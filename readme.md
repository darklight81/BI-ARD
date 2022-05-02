# Documentation - The Snake [BI-ARD]

## Summary

The game supports all features that were set out during theoretical preperation.

The game starts right away. Before the start it tries to load highscore from eeprom, if the highscore wasn't set yet, it is considered 0. Game ends when the user hits the outline of the level or hit the part of the snake. If the score reached during the game is higher than the highscore, the game sets the score as the new highscore.

After the snake encounter the food (meaning it is at the same place as the food), the game plays a sound. The snake gets larger (up to 10 'blocks') and the game speeds up. It plays a sound when the game ends as well.

The game is controlled by the the esplora buttons.

These are the most notable parts of code.

### Food spawning 
```
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
    EsploraTFT.stroke(255, 255, 255);
    EsploraTFT.fill(255, 255, 255);
    EsploraTFT.rect(foodWidth, foodHeight, 5, 5);
}
```
Food needs to be spawned everytime the snake eats it. The global boolean foodEaten represent the state of the eaten food, if the snake hits the place where food is, it is set to True, then with the help of random the position of food on the board is decided. Food is then calibrated to match the width of snake and printed on the TFT display.

### Snake rendering
```
void renderSnake()
{
    EsploraTFT.stroke(255, 255, 255);
    EsploraTFT.fill(255, 255, 255);
    for (int i = snakeLen - 1; i > 0; i--)
    {
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
    for (int i = 0; i < snakeLen; i++)
        EsploraTFT.rect(tmpSnake[i][1], tmpSnake[i][0], 5, 5);
}

```
Snake needs to be rerender every tick of the game as it is in move for the whole game. tmpSnake is a 2D array where the height and width where each 'body part' of the snake needs to be rerendered. In the first for loop we update all of the snakes body parts apart from head which is decided in the switch. It takes in mind direction in which the snake is going and puts it in the right place. Lastly loop is called to render the snake on the actual position. 


## User handbook
After uploading the game to the Esplora, your goal is to survive as long as possible while obtaining as much food as possible. But it won't be that easy. If you hit the border, game ends, so watch out! Also, when you obtain food, the snake will get bigger, dont hit any part of the snake either!

You control the movement of snake by Esplora buttons. If you set a new highscore it will be perserved even after unplugging the Esplora.

Good luck!
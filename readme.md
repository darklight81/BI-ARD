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
    //Serial.println((String)"Height: "+foodHeight+", width: "+foodWidth);
    EsploraTFT.stroke(255, 255, 255);
    EsploraTFT.fill(255, 255, 255);
    EsploraTFT.rect(foodWidth, foodHeight, 5, 5);
}
```



## User handbook
After uploading the game to the Esplora, your goal is to survive as long as possible while obtaining as much food as possible. But it won't be that easy. If you hit the border, game ends, so watch out! Also, when you obtain food, the snake will get bigger, dont hit any part of the snake either!

You control the movement of snake by Esplora buttons. If you set a new highscore it will be perserved even after unplugging the Esplora.

Good luck!
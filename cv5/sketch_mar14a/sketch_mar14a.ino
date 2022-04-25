#include <Esplora.h>
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <SD.h>

#define SD_CS    8  

Sd2Card card;
SdVolume volume;
File root;
int x = 0, y = 0;

void setup() {
    Serial.begin(9600);
    EsploraTFT.begin();
    EsploraTFT.background(0,0,0);
    EsploraTFT.stroke(200,20,180);
    SD.begin(SD_CS);
    root = SD.open("/");
    EsploraTFT.setTextSize(2);
    printDirectory(root, 0);

    //EsploraTFT.text("Degrees in C :\n ",0,0);

    EsploraTFT.setTextSize(5);

}

void loop() {
  
}


void printDirectory(File dir, int numTabs)
{
  while (true)
  {
    File entry = dir.openNextFile();
    if (! entry)
    {
      return;
    }
    Serial.print(entry.name());
    EsploraTFT.text(entry.name(), numTabs*10, y);
    if (entry.isDirectory())
    {
      String txt = entry.name();
      Serial.println(txt.length());
      EsploraTFT.text("/", 60, y);
      Serial.println("/");
      y+= 20;
      printDirectory(entry, numTabs + 1);
    }
    else
    {
      Serial.println("");
    }
    y+= 20;
    entry.close();
  }
}

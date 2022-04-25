#include <Esplora.h>
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <SD.h>

#define SD_CS    8  

Sd2Card card;
SdVolume volume;
File root, myFile;
int  num1 = 0, num2 = 0, num3 = 0, num4 = 0, pos = 0;
int secret_code[4];
void setup() {
    Serial.begin(9600);
    
    if (!SD.begin(8)) {
    Serial.println("initialization failed!");
    while (1);
    }
    
    EsploraTFT.begin();
    EsploraTFT.background(0, 0, 0);
    EsploraTFT.stroke(255,255,255); 
    EsploraTFT.setTextSize(2);
   
    myFile = SD.open("code.txt", FILE_READ);

    // if the file opened okay, write to it:
    if (myFile) {
      int i = 0;
      while (myFile.available()) {
      if ( i < 4){
        secret_code[i] = (char)myFile.read();
        //Serial.println(secret_code[i]);
      }
      Serial.write(myFile.read());
      i++;
    }
      myFile.close();
      Serial.println("done.");
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
    }
    printDisplay();
    /*
    EsploraTFT.println("");
    EsploraTFT.println("");
    EsploraTFT.println("      ^ ^ ^ ^");
    EsploraTFT.print("CODE: 0 0 0 0");
    EsploraTFT.println("      v v v v");
    */

}

void loop()
{
int buttonDown = Esplora.readButton(SWITCH_DOWN);
int buttonRight =  Esplora.readButton(SWITCH_RIGHT);
int buttonUp =  Esplora.readButton(SWITCH_UP);
int buttonLeft =  Esplora.readButton(SWITCH_LEFT);
if(buttonDown == LOW){
    switch(pos){
    case 0:
      if (num1 == 0)
        num1 = 9;
      else
        num1--;
      break;
    case 1:
      if (num2 == 0)
        num2 = 9;
      else
        num2--;
      break;
    case 2:
      if (num3 == 0)
        num3 = 9;
      else
        num3--;
      break;
    case 3:
      if (num4 == 0)
        num4 = 9;
      else
        num4--;
      break;
    default:
      break;
    
  }
  }
else if ( buttonRight == LOW){
  if ( pos < 3){
    pos++;
  }
}
else if (buttonUp == LOW){
  switch(pos){
    case 0:
      if (num1 == 9)
        num1 = 0;
      else
        num1++;
      break;
    case 1:
      if (num2 == 9)
        num2 = 0;
      else
        num2++;
      break;
    case 2:
      if (num3 == 9)
        num3 = 0;
      else
        num3++;
      break;
    case 3:
      if (num4 == 9)
        num4 = 0;
      else
        num4++;
      break;
    default:
      break;
    
  }
  
}
else if (buttonLeft == LOW){
  if (pos > 0){
    pos--;
  }
}
printDisplay();
delay(2000);
}

void printDisplay(){
  EsploraTFT.background(0, 0, 0);
  EsploraTFT.text("CODE: ", 0, 50);
  char cstr[16];
  EsploraTFT.text(itoa(num1, cstr, 10), 60, 50);
  EsploraTFT.text(itoa(num2, cstr, 10), 80, 50);
  EsploraTFT.text(itoa(num3, cstr, 10), 100, 50);
  EsploraTFT.text(itoa(num4, cstr, 10), 120, 50);

}

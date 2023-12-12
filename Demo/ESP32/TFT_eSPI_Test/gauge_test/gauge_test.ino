#include <TFT_eSPI.h> 
#include "gauge1.h"
#include "font.h"

#define ENCODER_CLK 25
#define ENCODER_DT 32
#define ENCODER_SW 33

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite img = TFT_eSprite(&tft);

const double rad = 0.01745;
int angle = 0;

const int sx = 120;
const int sy = 120;
const int r = 76;

float x[360];
float y[360];
float x2[360];
float y2[360];

int minValue = 0;
int maxValue = 40;
int result = 0;
int a1, a2;

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;

bool clkw = false; /* counter-clockwise direction*/

void setup() {
  Serial.begin(115200);

  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  attachInterrupt(ENCODER_CLK, cLK_ISR, RISING);
  
  int i = 0;
  int a = 136;
  while(a!=44)
  {
     x[i]  = r*cos(rad*a)+sx;
     y[i]  = r*sin(rad*a)+sy;
     x2[i] = (r-20)*cos(rad*a)+sx;
     y2[i] = (r-20)*sin(rad*a)+sy;
     i++;
     a++;
     if(a == 360)
        a=0;
  }

  tft.init();
  tft.setRotation(2);
  tft.setSwapBytes(true);
  img.setSwapBytes(true);
  tft.fillScreen(TFT_ORANGE);
  img.createSprite(240, 240);

  tft.setPivot(60, 60);
  img.setTextDatum(4);
  img.setTextColor(TFT_BLACK,0xAD55);
  img.setFreeFont(&Orbitron_Medium_28);
}

void loop() {
  angle = map(result, minValue, maxValue, 0, 267);
  img.pushImage(0,0,240,240,gauge1);
  img.drawString(String(result),120,114);

  a1 = angle - 4;
  a2 = angle + 4;
  
  if(a1 < 0)
    a1 = angle - 4 + 359;
  if(a2 >= 359)
    a2 = angle + 4 - 359;

  if(result <= minValue + 4)
    img.fillTriangle(x[angle],y[angle],x2[angle],y2[angle],x2[a2+2],y2[a2+2],TFT_RED);
  else if(result >= maxValue - 4)
    img.fillTriangle(x[angle],y[angle],x2[a1-2],y2[a1-2],x2[angle],y2[angle],TFT_RED);
  else
    img.fillTriangle(x[angle],y[angle],x2[a1],y2[a1],x2[a2],y2[a2],TFT_RED);
 
  img.pushSprite(0, 0);

  // recvWithEndMarker();
  // showNewNumber();

}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    if (Serial.available() > 0) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewNumber() {
    if (newData == true) {
        result = atoi(receivedChars);
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        Serial.print("Data as Number ... ");
        Serial.println(result); 
        newData = false;
    }
}

void cLK_ISR()
{
  if(digitalRead(ENCODER_DT) == LOW)
  {
    clkw = true;
    if(++result > maxValue) result = maxValue;
  }
  else
  {
    clkw = false;
    if(--result < minValue) result = minValue;
  }
}

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite img = TFT_eSprite(&tft);
int x = 0;

void setup() {
  Serial.begin(115200);
  Serial.print("TFT_MOSI: ");
  Serial.println(TFT_MOSI);
  Serial.print("TFT_MISO: ");
  Serial.println(TFT_MISO);
  Serial.print("TFT_SCLK: ");
  Serial.println(TFT_SCLK);
  Serial.print("TFT_CS: ");
  Serial.println(TFT_CS); 
  Serial.print("TFT_DC: ");
  Serial.println(TFT_DC); 
  
  tft.init();
  tft.setRotation(2);
  img.createSprite(240, 240);
  img.fillScreen(TFT_ORANGE);
}

void loop() {
  // tft.fillScreen(TFT_ORANGE);
  img.fillCircle(x, 120, 30, TFT_ORANGE);
  x += 1;
  if(x > 270) x = 0;
  img.fillCircle(x, 120, 30, TFT_RED);
  img.fillRect(80, 25, 100, 60, TFT_ORANGE);
  img.drawString(String(x),90, 30, 6);

  img.pushSprite(0, 0);
}

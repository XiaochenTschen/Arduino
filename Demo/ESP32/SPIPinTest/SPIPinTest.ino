#include <TFT_eSPI.h> 

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

}

void loop() {
  // put your main code here, to run repeatedly:

}

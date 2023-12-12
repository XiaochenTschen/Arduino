#include <WiFi.h>
#include "SimpleTimer.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

SimpleTimer timer;

const char* ssid = "Tschen";
const char* password = "tschen911";
const String apiURL = "http://api.openweathermap.org/data/2.5/weather?q=Ingolstadt,de&APPID=3db68afd41e7c9c5481019f83fe5bdfd";

void setup() {
  Serial.begin(115200);

  Serial.print("Connect to ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected . ");
  Serial.println("IP Addresse: ");
  Serial.println(WiFi.localIP());

  timer.setInterval(10000L, timerCallback);

}

void loop() {
  timer.run();  
}

void timerCallback(){
  HTTPClient http;
  http.begin(apiURL);

  int httpCode = http.GET();
  if(httpCode == HTTP_CODE_OK){
    String results = http.getString();

    // const size_t bufferSize = JSON_OBJECT_SIZE(9) + JSON_ARRAY_SIZE(1) + 260;
    // StaticJsonDocument<bufferSize> doc;
    DynamicJsonDocument doc(1024);
    // paese JSON data
    DeserializationError error = deserializeJson(doc, results);

    // check is parse successfully
    if (error) {
      Serial.print("Failed to parse JSON: ");
      Serial.println(error.c_str());
      return;
    }
    
    String weatherDescription = doc["weather"][0]["description"];;
    String city = doc["name"];

    Serial.println("------------------------------------");
    Serial.print(city);
    Serial.print("\t: ");
    Serial.println(weatherDescription);
    Serial.println();
  }
  else{
    Serial.println("GET Error.");
  }
  http.end();
}

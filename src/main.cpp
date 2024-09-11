#include <Arduino.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 11
#define DHTTYPE DHT11

#define BTN 2

DHT dht(DHTPIN, DHTTYPE);
int br = 115200;
int dw = 1000;
int measureDw = 500;
float tempC = 0;
float tempF = 0;
float humidity = 0;
int btnState;

String message = "";
ArduinoLEDMatrix matrix;

void setup() {
    Serial.begin(br);
    pinMode(BTN, INPUT_PULLUP);
    dht.begin();
    matrix.begin();
    delay(dw);
}

void messagePrint(String message, int x = 0, int y = 1) {
    matrix.clear();
    matrix.beginDraw();
    matrix.textFont(Font_4x6);
    matrix.beginText(0,1, 255,0,0);
    matrix.textScrollSpeed(80);
    matrix.print(message);
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();
}

void loop() {
    tempC = dht.readTemperature(false);
    tempF = dht.convertCtoF(tempC);
    humidity = dht.readHumidity();

    if (isnan(tempC) || isnan(tempF) || isnan(humidity)) {
        messagePrint("Error");
        delay(measureDw);
        return;
    }

    message = "Temperature: " + String(tempC) + " C / " + String(tempF) + " F - " + "Humidity: " + String(humidity) + " %";
    btnState = digitalRead(BTN);

    if (btnState == LOW) {
        messagePrint(message);
    }



    delay(measureDw);
}
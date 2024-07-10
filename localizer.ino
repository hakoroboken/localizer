#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SparkFun_Qwiic_OTOS_Arduino_Library.h"

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
QwiicOTOS myOtos;

void setup() {
    Serial.begin(115200);
    Serial.println("OLED initialized");
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
    display.display();
    delay(1000);
    // Clear the buffer.
    display.clearDisplay();
    display.display();
    // Text display settings
    display.setTextSize(1);
    display.setTextColor(WHITE);

    while (!myOtos.begin()) {
        Serial.println("OTOS not connected, check your wiring and I2C address!");
        delay(1000);
    }

    Serial.println("OTOS connected!");
    Serial.println("Calibrating IMU...");

    myOtos.setLinearUnit(kSfeOtosLinearUnitMeters);
    myOtos.setLinearScalar(0.968208313497);
    myOtos.setAngularScalar(0.990998430919);

    myOtos.calibrateImu();
    myOtos.resetTracking();
}

void loop() {
      sfe_otos_pose2d_t myPosition;
      myOtos.getPosition(myPosition);

      // Print measurement to Serial
      Serial.print("S");
      Serial.print(myPosition.x, 4);
      Serial.print(",");
      Serial.print(myPosition.y, 4);
      Serial.print(",");
      Serial.print(myPosition.h);
      Serial.print("E");

      // Display measurement on OLED
        display.clearDisplay();
      display.setCursor(0, 0);
      display.print("X: ");
      display.println(myPosition.x, 4);
      display.print("Y: ");
      display.println(myPosition.y, 4);
      display.print("H: ");
      display.println(myPosition.h);

      display.display();

      delay(10);
}

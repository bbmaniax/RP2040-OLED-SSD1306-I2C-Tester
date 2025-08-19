// OLED-SSD1306-I2C-Tester

#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON1_PIN 15
#define BUTTON2_PIN 29

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_I2C_ADDRESS 0x3C
#define DISPLAY_COLOR_WHITE SSD1306_WHITE

Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

int sceneIndex = 0;

void setup() {
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
}

void loop() {
  switch (sceneIndex) {
    case 0:
      displayLogo();
      break;
    case 1:
      displayHello();
      break;
    case 2:
      displayLines();
      break;
  }

  while (true) {
    if (digitalRead(BUTTON1_PIN) == LOW) {
      sceneIndex = (sceneIndex - 1 + 3) % 3;
      break;
    }
    if (digitalRead(BUTTON2_PIN) == LOW) {
      sceneIndex = (sceneIndex + 1) % 3;
      break;
    }
    delay(50);
  }
  delay(200);
}

void printCenter(int y, const String& text) {
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((DISPLAY_WIDTH - w) / 2, y);
  display.print(text);
}

void displayLogo() {
  display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_I2C_ADDRESS);
  display.display();
}

void displayHello() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(DISPLAY_COLOR_WHITE);
  printCenter(8, "HELLO");
  printCenter(24, "OLED");
  printCenter(40, "SSD1306");
  display.display();
}

void displayLines() {
  display.clearDisplay();
  for (int x = 0; x < DISPLAY_WIDTH; x += 8) {
    display.drawLine(x, 0, DISPLAY_WIDTH - 1 - x, DISPLAY_HEIGHT - 1, DISPLAY_COLOR_WHITE);
    display.display();
    delay(10);
  }
  for (int y = 0; y < DISPLAY_HEIGHT; y += 8) {
    display.drawLine(DISPLAY_WIDTH - 1, y, 0, DISPLAY_HEIGHT - 1 - y, DISPLAY_COLOR_WHITE);
    display.display();
    delay(10);
  }
}

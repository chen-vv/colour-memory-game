#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RED_LED_PIN 3
#define BLUE_LED_PIN 5
#define YELLOW_LED_PIN 9
#define GREEN_LED_PIN 11

#define RED_BUTTON_PIN 2
#define BLUE_BUTTON_PIN 4
#define YELLOW_BUTTON_PIN 8
#define GREEN_BUTTON_PIN 10

#define MAX_COLOURS 4          // Max number of colour LEDs
#define DEFAULT_BRIGHTNESS 50  // Default brightness to display LEDs
#define MS_IN_SECOND 1000
#define MIN_BLINK_TIME 200
#define MIN_PAUSE_TIME 100

// LCD has 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// The number of milliseconds to display an LED light
unsigned int blinkTime;

// The number of milliseconds to pause before displaying the next LED light
unsigned int pauseTime;

// The player's current level in the game
unsigned int level;

// The sequence of colours
unsigned int sequence[50] = { 0 };

// Contains the pin numbers of each colour LED
unsigned int colours[MAX_COLOURS] = { RED_LED_PIN, BLUE_LED_PIN, YELLOW_LED_PIN, GREEN_LED_PIN };

// Whether the game has started
// TODO: Use this value in the game
bool gameStarted;

// Whether the player has lost
bool playerLost;

// The pin number of the current colour LED that was added in this level
unsigned int currentColourLED;

// The number of points scored by the player in this game
unsigned int totalPoints;

void setup() {
  Serial.begin(9600);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  pinMode(RED_BUTTON_PIN, INPUT);
  pinMode(BLUE_BUTTON_PIN, INPUT);
  pinMode(YELLOW_BUTTON_PIN, INPUT);
  pinMode(GREEN_BUTTON_PIN, INPUT);

  randomSeed(analogRead(A0));

  setupLcd();

  initializeGame();
}

void setupLcd() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  while (gameStarted == false) {
    waitForGameStart();
  }

  delay(200);

  // Blink the LEDs to signal the memory sequence
  for (int i = 0; i < level; i++) {
    currentColourLED = sequence[i];
    delay(pauseTime);
    blinkLED(currentColourLED, blinkTime);

    Serial.print(mapPinToColour(currentColourLED));
    Serial.print(" ");
  }

  unsigned int count = 0;

  // Check the player's button presses
  while (count < level) {
    unsigned int currentColourButton = sequence[count] - 1;

    if (digitalRead(RED_BUTTON_PIN) == LOW) {
      while (digitalRead(RED_BUTTON_PIN) == LOW) {
        analogWrite(RED_LED_PIN, DEFAULT_BRIGHTNESS);
      }

      digitalWrite(RED_LED_PIN, LOW);

      if (currentColourButton == RED_BUTTON_PIN) {
        totalPoints++;
        count++;

        lcd.setCursor(7, 0);
        lcd.print(totalPoints);
      } else {
        Serial.print("You pressed red, but we expected ");
        Serial.println(mapPinToColour(currentColourButton));
        playerLost = true;
        break;
      }
    }

    else if (digitalRead(BLUE_BUTTON_PIN) == LOW) {
      while (digitalRead(BLUE_BUTTON_PIN) == LOW) {
        analogWrite(BLUE_LED_PIN, DEFAULT_BRIGHTNESS);
      }

      digitalWrite(BLUE_LED_PIN, LOW);

      if (currentColourButton == BLUE_BUTTON_PIN) {
        totalPoints++;
        count++;

        lcd.setCursor(7, 0);
        lcd.print(totalPoints);
      } else {

        Serial.print("You pressed blue, but we expected ");
        Serial.println(mapPinToColour(currentColourButton));
        playerLost = true;
        break;
      }
    }

    else if (digitalRead(YELLOW_BUTTON_PIN) == LOW) {
      while (digitalRead(YELLOW_BUTTON_PIN) == LOW) {
        analogWrite(YELLOW_LED_PIN, DEFAULT_BRIGHTNESS);
      }

      digitalWrite(YELLOW_LED_PIN, LOW);

      if (currentColourButton == YELLOW_BUTTON_PIN) {
        totalPoints++;
        count++;

        lcd.setCursor(7, 0);
        lcd.print(totalPoints);
      } else {

        Serial.print("You pressed yellow, but we expected ");
        Serial.println(mapPinToColour(currentColourButton));
        playerLost = true;
        break;
      }
    }

    else if (digitalRead(GREEN_BUTTON_PIN) == LOW) {
      while (digitalRead(GREEN_BUTTON_PIN) == LOW) {
        analogWrite(GREEN_LED_PIN, DEFAULT_BRIGHTNESS);
      }

      digitalWrite(GREEN_LED_PIN, LOW);

      if (currentColourButton == GREEN_BUTTON_PIN) {
        totalPoints++;
        count++;

        lcd.setCursor(7, 0);
        lcd.print(totalPoints);
      } else {

        Serial.print("You pressed green, but we expected ");
        Serial.println(mapPinToColour(currentColourButton));
        playerLost = true;
        break;
      }
    }

    delay(100);
  }

  delay(800);

  if (playerLost) {
    Serial.println("You lose!");
    blinkLED(sequence[count], 200);
    delay(100);
    blinkLED(sequence[count], 200);
    delay(100);
    blinkLED(sequence[count], 200);
    delay(100);
    initializeGame();
  } else {
    nextLevel();
  }
}

// Shows the LEDs in various brightness levels, in a fade-in and fade-out pattern.
// Turns all LEDs off when a button is pressed, and updates the LCD display to signal
// game start.
void waitForGameStart() {
  int brightnessIncrements = 5;
  int maxBrightness = 255;

  for (int i = 1; i <= brightnessIncrements; i++) {
    analogWrite(RED_LED_PIN, maxBrightness * i / brightnessIncrements);
    analogWrite(BLUE_LED_PIN, maxBrightness * i / brightnessIncrements);
    analogWrite(YELLOW_LED_PIN, maxBrightness * i / brightnessIncrements);
    analogWrite(GREEN_LED_PIN, maxBrightness * i / brightnessIncrements);

    if (digitalRead(RED_BUTTON_PIN) == LOW || digitalRead(BLUE_BUTTON_PIN) == LOW || digitalRead(YELLOW_BUTTON_PIN) == LOW || digitalRead(GREEN_BUTTON_PIN) == LOW) {
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
      digitalWrite(YELLOW_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, LOW);
      gameStarted = true;

      showStartText();
      return;
    }

    delay(200);
  }

  for (int i = brightnessIncrements; i >= 0; i--) {
    analogWrite(RED_LED_PIN, maxBrightness * i / brightnessIncrements);
    analogWrite(BLUE_LED_PIN, maxBrightness * i / brightnessIncrements);
    analogWrite(YELLOW_LED_PIN, maxBrightness * i / brightnessIncrements);
    analogWrite(GREEN_LED_PIN, maxBrightness * i / brightnessIncrements);

    if (digitalRead(RED_BUTTON_PIN) == LOW || digitalRead(BLUE_BUTTON_PIN) == LOW || digitalRead(YELLOW_BUTTON_PIN) == LOW || digitalRead(GREEN_BUTTON_PIN) == LOW) {
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
      digitalWrite(YELLOW_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, LOW);
      gameStarted = true;

      showStartText();
      return;
    }

    delay(200);
  }
}

// Clears the LCD and shows text signalling the start of a new game
void showStartText() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game starting in");
  lcd.setCursor(8, 1);
  lcd.print("3");
  delay(MS_IN_SECOND);
  lcd.setCursor(8, 1);
  lcd.print("2");
  delay(MS_IN_SECOND);
  lcd.setCursor(8, 1);
  lcd.print("1");
  delay(MS_IN_SECOND);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Score:");
  lcd.setCursor(7, 0);
  lcd.print(totalPoints);
}

// Resets the game from the start.
void initializeGame() {
  blinkTime = 800;
  pauseTime = 500;
  level = 0;
  gameStarted = false;
  playerLost = false;
  totalPoints = 0;

  getNextColour();
  level = 1;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press any button");
  lcd.setCursor(4, 1);
  lcd.print("to start!");
}

// Gets the next colour and appends it to [sequence]
void getNextColour() {
  unsigned int nextColour = colours[random(0, MAX_COLOURS)];
  sequence[level] = nextColour;
}

// Moves the game to the next level
void nextLevel() {
  getNextColour();

  double blinkResult = (double)(blinkTime * 4) / 5;
  double pauseResult = (double)(pauseTime * 4) / 5;

  blinkTime = (int)blinkResult;
  pauseTime = (int)pauseResult;

  if (blinkTime < MIN_BLINK_TIME) {
    blinkTime = MIN_BLINK_TIME;
  }

  if (pauseTime < MIN_PAUSE_TIME) {
    pauseTime = MIN_PAUSE_TIME;
  }

  level++;
}

// Blinks the LED light at [outputPin] for [time] milliseconds.
void blinkLED(unsigned int outputPin, unsigned int time) {
  analogWrite(outputPin, DEFAULT_BRIGHTNESS);
  delay(time);
  digitalWrite(outputPin, LOW);
}

// TODO: COMMENTS
String mapPinToColour(unsigned int pin) {
  if (pin == RED_LED_PIN || pin == RED_BUTTON_PIN) {
    return "red";
  } else if (pin == BLUE_LED_PIN || pin == BLUE_BUTTON_PIN) {
    return "blue";
  } else if (pin == YELLOW_LED_PIN || pin == YELLOW_BUTTON_PIN) {
    return "yellow";
  } else if (pin == GREEN_LED_PIN || pin == GREEN_BUTTON_PIN) {
    return "green";
  }
}
#define RED_LED_PIN 3
#define BLUE_LED_PIN 5
#define YELLOW_LED_PIN 7
#define GREEN_LED_PIN 9

#define RED_BUTTON_PIN 2
#define BLUE_BUTTON_PIN 4
#define YELLOW_BUTTON_PIN 6
#define GREEN_BUTTON_PIN 8

#define MAX_COLOURS 4  // Max number of colour LEDs

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

  randomSeed(analogRead(A5));

  initializeGame();
}

void loop() {
  // Blink the LEDs to signal the memory sequence
  for (int i = 0; i < level; i++) {
    currentColourLED = sequence[i];

    delay(pauseTime);

    blink(currentColourLED, blinkTime);
  }

  unsigned int count = 0;

  // Check the player's button presses
  while (count < level) {
    unsigned int currentColourButton = sequence[count] - 1;

    if (digitalRead(RED_BUTTON_PIN) == LOW) {
      while (digitalRead(RED_BUTTON_PIN) == LOW) {
        digitalWrite(RED_LED_PIN, HIGH);
      }

      digitalWrite(RED_LED_PIN, LOW);

      if (currentColourButton == RED_BUTTON_PIN) {
        count++;
      } else {
        playerLost = true;
        break;
      }
    }

    else if (digitalRead(BLUE_BUTTON_PIN) == LOW) {
      while (digitalRead(BLUE_BUTTON_PIN) == LOW) {
        digitalWrite(BLUE_LED_PIN, HIGH);
      }

      digitalWrite(BLUE_LED_PIN, LOW);

      if (currentColourButton == BLUE_BUTTON_PIN) {
        count++;
      } else {
        playerLost = true;
        break;
      }
    }

    else if (digitalRead(YELLOW_BUTTON_PIN) == LOW) {
      while (digitalRead(YELLOW_BUTTON_PIN) == LOW) {
        digitalWrite(YELLOW_LED_PIN, HIGH);
      }

      digitalWrite(YELLOW_LED_PIN, LOW);

      if (currentColourButton == YELLOW_BUTTON_PIN) {
        count++;
      } else {
        playerLost = true;
        break;
      }
    }

    else if (digitalRead(GREEN_BUTTON_PIN) == LOW) {
      while (digitalRead(GREEN_BUTTON_PIN) == LOW) {
        digitalWrite(GREEN_LED_PIN, HIGH);
      }

      digitalWrite(GREEN_LED_PIN, LOW);

      if (currentColourButton == GREEN_BUTTON_PIN) {
        count++;
      } else {
        playerLost = true;
        break;
      }
    }
  }

  if (playerLost) {
    Serial.println("You lose!");
    initializeGame();
  } else {
    totalPoints += count;
    nextLevel();
  }
}

// Resets the game from the start.
void initializeGame() {
  blinkTime = 800;
  pauseTime = 500;
  level = 0;
  gameStarted = false;
  playerLost = false;
  totalPoints = 0;

  nextLevel();
}

// Moves the game to the next level
void nextLevel() {
  unsigned int nextColour = colours[random(0, 2)];
  sequence[level] = nextColour;
  level++;
}

// Blinks the LED light at [outputPin] for [time] milliseconds.
void blink(unsigned int outputPin, unsigned int time) {
  digitalWrite(outputPin, HIGH);
  delay(time);
  digitalWrite(outputPin, LOW);
}
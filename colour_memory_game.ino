#define RED_LED_PIN 3
#define BLUE_LED_PIN 5
#define YELLOW_LED_PIN 7
#define GREEN_LED_PIN 9

#define RED_BUTTON_PIN 2
#define BLUE_BUTTON_PIN 4
#define YELLOW_BUTTON_PIN 6
#define GREEN_BUTTON_PIN 8

unsigned int blinkTime;  // TODO: COMMENTS
unsigned int pauseTime;
unsigned int level;  // Starts from 0
unsigned int sequence[50] = { 0 };
unsigned int colours[4] = { RED_LED_PIN, BLUE_LED_PIN, YELLOW_LED_PIN, GREEN_LED_PIN };
bool gameStarted = false;
unsigned int currentColourLED;
bool playerLost;

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
  // if (gameStarted == false) {
  //   if (digitalRead(GREEN_BUTTON_PIN) == LOW) {
  //     digitalWrite(GREEN_LED_PIN, HIGH);
  //     delay(1000);
  //   }

  //   digitalWrite(GREEN_LED_PIN, LOW);

  //   Serial.println("Press all four buttons to start");

  //   while (allButtonsPressed() == false) {}

  //   gameStarted = true;

  //   Serial.println("Starting...");
  //   delay(2000);
  // }

  delay(1000);

  level++;

  for (int i = 0; i < level; i++) {
    currentColourLED = sequence[i];

    digitalWrite(currentColourLED, HIGH);
    delay(blinkTime);

    digitalWrite(currentColourLED, LOW);

    if (i < level - 1) {
      delay(pauseTime);
    }
  }

  int count = 0;

  while (count < level) {
    unsigned int currentColourButton = sequence[count] - 1;

    if (digitalRead(RED_BUTTON_PIN) == LOW) {
      while (digitalRead(RED_BUTTON_PIN) == LOW) {
        digitalWrite(RED_LED_PIN, HIGH);
      }

      digitalWrite(RED_LED_PIN, LOW);

      if (currentColourButton == RED_BUTTON_PIN) {
        // Add point
        count++;
      } else {
        // you lose
        Serial.println("You lose!");
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
        // Add point
        count++;
      } else {
        // you lose
        Serial.println("You lose!");
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
        // Add point
        count++;
      } else {
        // you lose
        Serial.println("You lose!");
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
        // Add point
        count++;
      } else {
        // you lose
        Serial.println("You lose!");
        playerLost = true;
        break;
      }
    }
  }

  if (playerLost) {
    gameStarted = false;
    initializeGame();
  } else {
    // Add next colour - put this in function to use in init too
    unsigned int nextColour = colours[random(0, 2)];
    sequence[level] = nextColour;
  }
}

void initializeGame() {
  blinkTime = 800;
  pauseTime = 500;
  level = 0;
  playerLost = false;
  unsigned int nextColour = colours[random(0, 4)]; // TODO: PLACE 4 AS NUM_COLOURS CONST OR SMTH
  sequence[level] = nextColour;
}

bool noButtonsPressed() {
  return digitalRead(RED_BUTTON_PIN) == HIGH && digitalRead(BLUE_BUTTON_PIN) == HIGH && digitalRead(YELLOW_BUTTON_PIN) == HIGH && digitalRead(GREEN_BUTTON_PIN) == HIGH;
}
// TODO: COMMENTS
bool allButtonsPressed() {
  return digitalRead(RED_BUTTON_PIN) == LOW && digitalRead(BLUE_BUTTON_PIN) == LOW && digitalRead(YELLOW_BUTTON_PIN) == LOW && digitalRead(GREEN_BUTTON_PIN) == LOW;
}

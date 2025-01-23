#define RED_LED_PIN 3
#define BLUE_LED_PIN 5
#define YELLOW_LED_PIN 7
#define GREEN_LED_PIN 9

#define RED_BUTTON_PIN 2
#define BLUE_BUTTON_PIN 4
#define YELLOW_BUTTON_PIN 6
#define GREEN_BUTTON_PIN 8

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
}

void loop() {
  if (digitalRead(RED_BUTTON_PIN) == LOW) {
    digitalWrite(RED_LED_PIN, HIGH);
  } else {
    digitalWrite(RED_LED_PIN, LOW);
  }

  if (digitalRead(BLUE_BUTTON_PIN) == LOW) {
    digitalWrite(BLUE_LED_PIN, HIGH);
  } else {
    digitalWrite(BLUE_LED_PIN, LOW);
  }

  if (digitalRead(YELLOW_BUTTON_PIN) == LOW) {
    digitalWrite(YELLOW_LED_PIN, HIGH);
  } else {
    digitalWrite(YELLOW_LED_PIN, LOW);
  }

  if (digitalRead(GREEN_BUTTON_PIN) == LOW) {
    digitalWrite(GREEN_LED_PIN, HIGH);
  } else {
    digitalWrite(GREEN_LED_PIN, LOW);
  }
}

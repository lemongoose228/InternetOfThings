#define BUTTON_PIN 2 
#define BOUNCE_TIME 50
#define PRESSED HIGH

volatile long int press_time = 0;
volatile long int release_time = 0;
volatile bool pressed_candidate = false;
volatile long int hold_time = 0;
volatile int press_count = 0;
volatile bool button_pressed = false;
volatile bool true_pressed = false;
volatile long int pause_time = 0;

void setup() {
    pinMode(BUTTON_PIN, INPUT);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), process_button_click, RISING);
}

void loop() {
  if (pressed_candidate) {
      long int buffer = millis();
      if (buffer - press_time >= BOUNCE_TIME && digitalRead(BUTTON_PIN) == PRESSED) {
          true_pressed = true;
      }
      else {
        if (button_pressed && true_pressed) {
            release_time = millis();
            hold_time = release_time - press_time;  
            Serial.print("Press registered. Hold time: ");
            Serial.print(hold_time);
            Serial.print(" ms. Total press count: ");
            press_count++;  
            Serial.println(press_count);
            button_pressed = false; 
            pressed_candidate = false;
            true_pressed = false;
            pause_time = millis();
        }
      }
  } 
}

void process_button_click() {
  long int buffer = millis();
  if (!pressed_candidate && buffer - pause_time > BOUNCE_TIME) {
    press_time = millis(); 
    pressed_candidate = true; 
    button_pressed = true; 
    true_pressed = false;
    pause_time = 0;
  }
}

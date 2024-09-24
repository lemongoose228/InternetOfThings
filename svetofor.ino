#define LED_RED 13
#define LED_YEL 12
#define LED_GRN 11
#define SET_LED_ON 'u'
#define SET_LED_OFF 'd'
#define SET_LED_BLINK 'b'
#define SET_TRAFFIC_LIGHT 's'

#define STATE_IDLE 0
#define STATE_LED_ON 1
#define STATE_LED_OFF 2
#define STATE_LED_BLINK 3

#define BLINK_INTERVAL 500
#define LIGHT_INTERVAL 6000
#define LIGHT_INTERVAL_YEL 2000

int state;
int step = 1;
long int step_interval;
int PIN;

bool traffic_light = false;

long int blink_start;
bool led_status = LOW;

void update_state() {
    if (Serial.available() > 0) {
        char cmd = Serial.read();
        if (cmd == SET_LED_ON) {
            state = STATE_LED_ON;
        }
        else if (cmd == SET_LED_OFF) {
            state = STATE_LED_OFF;
        }
        else if (cmd == SET_LED_BLINK) {
            state = STATE_LED_BLINK;
            blink_start = millis();
        }
        else if (cmd == SET_TRAFFIC_LIGHT) {
            traffic_light = true;
        }
        
        
    }
}


void process_state2() {
    if (traffic_light) {
      if (step == 1) {

        // переменная для светодиода = красный
        PIN = LED_RED;
        state = STATE_LED_ON; 
        step_interval = millis();
        
        step += 1;
      }
      else if (step == 2 and millis() > step_interval + LIGHT_INTERVAL) {

        state = STATE_LED_BLINK; 
        step_interval = millis();
        blink_start = millis();
        step += 1;
      }
      else if(step == 3 and millis() > step_interval + (BLINK_INTERVAL * 5)){

        state = STATE_LED_OFF;
        step += 1;
      }
      else if (step == 4) {

        // переменная для светодиода = желтый
        PIN = LED_YEL;
        state = STATE_LED_ON; 
        step_interval = millis();
        step += 1;

      }
      else if (step == 5 and millis() > step_interval + LIGHT_INTERVAL_YEL) {

        state = STATE_LED_OFF;
        step += 1;
      }
      else if (step == 6) {   

        // переменная для светодиода = зелёный
        PIN = LED_GRN;
        state = STATE_LED_ON; 
        step_interval = millis();
        step += 1;
      }
      else if (step == 7 and millis() > step_interval + LIGHT_INTERVAL) {

        state = STATE_LED_BLINK; 
        step_interval = millis();
        step += 1;
        blink_start = millis();
      }
      else if (step == 8 and millis() > step_interval + (BLINK_INTERVAL * 5)) {

        state = STATE_LED_OFF; 
        step += 1;
      }
      else if (step == 9) {

        // переменная для светодиода = желтый
        PIN = LED_YEL;
        state = STATE_LED_ON; 
        step_interval = millis();
        step += 1;
      }
      else if (step == 10 and millis() > step_interval + LIGHT_INTERVAL_YEL) {

        state = STATE_LED_OFF; 
        step = 1;
      }
    } 
    if (state == STATE_LED_ON) { 
        digitalWrite(PIN, HIGH);
    }
    else if (state == STATE_LED_OFF) {
        digitalWrite(PIN, LOW);
    }
    else if (state == STATE_LED_BLINK) {
        if (millis() <= blink_start + BLINK_INTERVAL and led_status == LOW) {
            digitalWrite(PIN, HIGH);
            led_status = HIGH;
        }
        if (millis() >= blink_start + BLINK_INTERVAL and millis() <= blink_start + 2 * BLINK_INTERVAL and led_status == HIGH) {
            digitalWrite(PIN, LOW);
            led_status = LOW;
        }
        if (millis() >= blink_start + 2 * BLINK_INTERVAL) {
            blink_start = millis();
        }
    }
}


void setup() {
    Serial.begin(9600);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YEL, OUTPUT);
    pinMode(LED_GRN, OUTPUT);
}

void loop() {
    update_state();
    process_state2();
}

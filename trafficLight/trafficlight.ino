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


bool traffic_light = true; // Переменная для проверки автоматического режима
bool manual_mode = false; // Переменная для ручного режима

int state;
int stage = 1;
long int stage_interval;
int PIN;


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
      if (stage == 1) {
        
        // переменная для светодиода = красный
        PIN = LED_RED;
        state = STATE_LED_ON; 
        stage_interval = millis();
        
        stage += 1;
      }
      else if (stage == 2 and millis() > stage_interval + LIGHT_INTERVAL) {
        
        state = STATE_LED_BLINK; 
        stage_interval = millis();
        blink_start = millis();
        stage += 1;
      }
      else if(stage == 3 and millis() > stage_interval + BLINK_INTERVAL * 5){
        
        state = STATE_LED_OFF;
        stage += 1;
      }
      else if (stage == 4) {
        
        // переменная для светодиода = желтый
        PIN = LED_YEL;
        state = STATE_LED_ON; 
        stage_interval = millis();
        stage += 1;

      }
      else if (stage == 5 and millis() > stage_interval + LIGHT_INTERVAL_YEL) {
        
        state = STATE_LED_OFF;
        stage += 1;
      }
      else if (stage == 6) {   
        
        // переменная для светодиода = зелёный
        PIN = LED_GRN;
        state = STATE_LED_ON; 
        stage_interval = millis();
        stage += 1;
      }
      else if (stage == 7 and millis() > stage_interval + LIGHT_INTERVAL) {
        
        state = STATE_LED_BLINK; 
        stage_interval = millis();
        stage += 1;
        blink_start = millis();
      }
      else if (stage == 8 and millis() > stage_interval + BLINK_INTERVAL * 5) {
        
        state = STATE_LED_OFF; 
        stage += 1;
      }
      else if (stage == 9) {
        
        // переменная для светодиода = желтый
        PIN = LED_YEL;
        state = STATE_LED_ON; 
        stage_interval = millis();
        stage += 1;
      }
      else if (stage == 10 and millis() > stage_interval + LIGHT_INTERVAL_YEL) {
        
        state = STATE_LED_OFF; 
        stage = 1;
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
    
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n'); 

        if (command.equals("r")) {
            manual_mode = true; 
            state = STATE_LED_ON;
            digitalWrite(LED_RED, HIGH);
            digitalWrite(LED_YEL, LOW);
            digitalWrite(LED_GRN, LOW);
            Serial.println("Переключён на красный свет.");
            return; 
        } else if (command.equals("g")) {
            manual_mode = true; 
            state = STATE_LED_ON;
            digitalWrite(LED_RED, LOW);
            digitalWrite(LED_YEL, LOW);
            digitalWrite(LED_GRN, HIGH);
            Serial.println("Переключён на зеленый свет.");
            return; 
        } else if (command.equals("auto")) {
            manual_mode = false; 
            digitalWrite(LED_RED, LOW);
            digitalWrite(LED_YEL, LOW);
            digitalWrite(LED_GRN, LOW);
            Serial.println("Переключён в автоматический режим.");
            process_state2();
        }
    }

    if (!manual_mode) {
        process_state2(); 
    }
} 

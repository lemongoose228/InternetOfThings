#define PHOTO_SENSOR_PIN  A4
#define PHOTO_SENSOR_PIN2  A0
#define LED_R 13
#define LED_L 12

void setup() {
    Serial.begin(9600);
}

void loop() {
    int photo_val = analogRead(PHOTO_SENSOR_PIN);
    int photo_val2 = analogRead(PHOTO_SENSOR_PIN2);
    Serial.print("Photo val 1 = ");
    Serial.println(photo_val);
    Serial.print("Photo val 2 = ");
    Serial.println(photo_val2);
    delay(500);

    if ((photo_val - photo_val2) >= 10){
      digitalWrite(LED_L, LOW);
      digitalWrite(LED_R, HIGH);
      
    }
    else if((photo_val2 - photo_val) >= 10){
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_L, HIGH);
    }
    else{
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_L, LOW);
    }
}

#define PHOTO_SENSOR_PIN  A1
#define PHOTO_SENSOR_PIN2  A0
#define LED_R 3
#define LED_L 2

unsigned long previousMillis = 0; 
const long interval = 500;

void setup() {
    Serial.begin(9600);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_L, OUTPUT);
}

void loop() {
    unsigned long currentMillis = millis(); 

    int photo_val1 = analogRead(PHOTO_SENSOR_PIN);
    int photo_val2 = analogRead(PHOTO_SENSOR_PIN2);
    Serial.print("Photo val 1 = ");
    Serial.println(photo_val1);
    Serial.print("Photo val 2 = ");
    Serial.println(photo_val2);
    delay(500);

    if (photo_val1 > photo_val2 + 50) {
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            digitalWrite(LED_R, !digitalRead(LED_R)); 
            digitalWrite(LED_L, LOW);

    } 
    else if (photo_val2 > photo_val1 + 50) {
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            digitalWrite(LED_L, !digitalRead(LED_L));
            digitalWrite(LED_R, LOW); 
        }
    } 
    else{
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_L, HIGH);
    }
}

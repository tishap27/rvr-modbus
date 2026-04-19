void setup() {
    Serial.begin(9600);
}

void loop() {
    int rvr = random(8, 25);
    Serial.println("RVR:" + String(rvr));
    delay(10000);
}
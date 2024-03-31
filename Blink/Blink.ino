// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  Serial.println();
  Serial.println("start...");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("off");
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED off (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  Serial.println("on");
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on by making the voltage LOW
  delay(1000);                      // wait for a second
}

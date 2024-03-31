#include <Servo.h>

const uint8_t servo = 2;  //舵机在GPIO2
Servo my_ser;

void setup() {
  Serial.begin(115200);
  Serial.println();

  analogWriteFreq(50);    //设置频率为50Hz，即周期20ms
  analogWriteRange(200);  //将20ms分成200份，每份0.1ms

  my_ser.attach(servo);

  analogWrite(servo, 5);  //初始化
  delay(500);
  analogWrite(LED_BUILTIN, 200);
  delay(200);
}

void loop() {
  for (int i = 5; i < 26; i++) {
    analogWrite(servo, i);
    Serial.printf("i: %d\tdegree: %d\tpulse_width_us: %d\tanalog: %d\n", i, my_ser.read(), my_ser.readMicroseconds(), analogRead(servo));
    delay(1000);
  }
}

//analog,直接控制PWM

void setup() {
  analogWriteFreq(50);          //设置频率为50Hz，即一个周期20ms
  analogWriteRange(100);        //步长设置为100，即将一个周期平分为100份，这样便于得到pwm
  analogWrite(LED_BUILTIN, 100);  //初始化pwm为{arg2}%

  Serial.begin(115200);
  Serial.println();
  delay(1000);
}

void loop() {
  for (int i = 100; i > 85; i--) {
    analogWrite(LED_BUILTIN, i);
    Serial.println(i);
    delay(1000);
  }
  for (int i = 0; i <= 15; i++) {
    analogWrite(LED_BUILTIN, i);
    Serial.println(i);
    delay(1000);
  }
}

/*呼吸灯 规律
pwm 100%为暗
pwm 0%为最亮
通过改变pwm可以调节亮度
*/

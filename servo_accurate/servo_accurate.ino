#include <Servo.h>

Servo my_ser;

void setup()
{
    Serial.begin(115200);
    Serial.println();Serial.println();

    my_ser.attach(2, 500, 2500); //将舵机信号连接到GPIO2， D4，设置高电平脉冲时间上下限(保证实际转动角度的参数)
    my_ser.write(0);
    delay(100);
}
/* 舵机控制说明 (Servo.h里时间单位都是微秒us，角度是°)
舵机通过脉冲宽度的时间来控制(PWM)，频率是50Hz的(即一个周期是20ms)。(！！！脉宽是本质)
SG90舵机的控制参数范围是：0°: 0.5ms , 180°: 2.5ms。
然后对于每一度，将脉宽范围除以180°即得。

servo.attach(GIO, pulse_width_min, pulse_width_max); 这里就可以设置上面的脉宽min和max(出于安全考虑，Servo的默认值是1000,2000，导致实际运行时并不是满的180°)

使用，实际就是设置脉宽：
servo.write(degree_OR_pulse_width_in_us);
当值<200时，参数为度数，根据上面除法得到每度的脉宽然后内部设置对应脉宽(范围内)；
超过200后，值代表脉宽(范围内)，直接写入脉宽，和servo.writeMicroseconds()一样。
注意超出范围的值将被设为最低或最大值

舵机运行的实际脉宽：可用servo.read()查看度数，servo.readMicroseconds()查看实际脉宽。

总之，使用Servo的时候，要先确定自己舵机的pwm控制参数，然后在attach的时候设置好，才能得到对应的角度。
*/

//展示了脉宽变化和对应的实际脉宽
void loop()
{
    for (int i = 0; i < 181; i+=1) {
      my_ser.write(i);
      Serial.printf("i: %d\tdegree: %d\tpulse_width_us: %d\n", i, my_ser.read(), my_ser.readMicroseconds());
      delay(200);
    }

    for (int i = 500; i < 2501; i+=1) {
      my_ser.write(i);  //等价于my_ser.writeMicroseconds(i);
      Serial.printf("i: %d\tdegree: %d\tpulse_width_us: %d\n", i, my_ser.read(), my_ser.readMicroseconds());
      delay(200);
    }
}

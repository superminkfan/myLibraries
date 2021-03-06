#define DEADZONE 60  // "мёртвая зона" потенциометра
#define IN1 2
#define IN2 3
#define POT 0      // сюда подключен потенциометр

#include "GyverMotor.h"
GMotor motor1(IN1, IN2);

int left_min = 512 - DEADZONE;   // расчёт границ мёртвой зоны
int right_min = 512 + DEADZONE;  // расчёт границ мёртвой зоны

void setup() {
  motor1.init();
  motor1.reverse(true);
}

void loop() {
  int potent = analogRead(POT);                    // читаем с потенциометра

  if (potent > left_min && potent < right_min) {  // если мы в "мёртвой" зоне
    motor1.setMode(STOP);
  } else if (potent > right_min) {   // если мы вышли из мёртвой зоны справа
    motor1.setMode(FORWARD);
    byte duty = map(potent, right_min, 1023, 0, 255);
    motor1.setSpeed(duty);
  } else if (potent < left_min) {   // если мы вышли из мёртвой зоны слева
    motor1.setMode(BACKWARD);
    byte duty = map(potent, left_min, 0, 0, 255);
    motor1.setSpeed(duty);
  }

}

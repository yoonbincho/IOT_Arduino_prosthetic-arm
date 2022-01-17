#include <Servo.h>

#define WIFI_SSID "Kwangwoon_KT"
#define WIFI_PASSWORD "ilovekwu"

#define SERVO_ANGLE_MAX 145
#define SERVO_ANGLE_MIN 0

Servo hand;

void on_rock(void) {
  Serial.println("rock");
  hand.write(SERVO_ANGLE_MAX);
}

void on_paper(void) {
  Serial.println("paper");
  hand.write(SERVO_ANGLE_MIN);
}

void setup() {
  hand.attach(A0);
  Serial.begin(115200);
  ybiot_init();
}

void loop() {
  ybiot_process(on_rock, on_paper);
  delay(300);
}

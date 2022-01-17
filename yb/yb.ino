#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFi.h>


int MyServoPos=0; //서보모터 초기 위치를 MyServoPos변수로 정의하고 그 값을 0으로 설정
Servo MyServo;
int analogValue=0;

void setup() {
  
  MyServo.attach(10); //서보 모터가 연결될 핀을 아두이노 10번 핀으로 설정
  analogValue = MyServoPos; //서보 모터 위치를 MyServoPos 값인 0으로 초기화
 

}

void loop() {
 // analogValue=analogRead(analogIn); //analogIn으로 들어오는 가변저장 값을 읽어와서 analogValue에 넣어줍니다
 // analogValue = map(analogValue,0,1023,0,179);
  //가변저항에서 읽어온 0부터1023 사이의 값을 서보 모터에서 사용할 수 있는 0부터 179사이의 값으로 변환해줍니다.
  MyServo.write(1023);//서보모터에 변환된 값을 보내어 회전하게 합니다.
  delay(15);
  MyServo.write(0);//delay 함수를 이용해서 아두이노와 서보모터의 속도를 맞추어 줍니다.
 
}

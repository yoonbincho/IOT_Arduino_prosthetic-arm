#include <common.h>
#include <FirebaseESP8266.h>
#include <FirebaseFS.h>
#include <Utils.h>

#include "FirebaseESP8266.h" // 반드시 파이어베이스 라이브러리를 먼저 추가해야 합니다.
#include <ESP8266WiFi.h>
 
#define FIREBASE_HOST "an-artificial-limb-default-rtdb.firebaseio.com/" // http달린거 빼고 적어야 됩니다.
#define FIREBASE_AUTH "eEO7WvfwonkA7NXZHT6HKkb12h7BqNaFiPThXVy0" // 데이터베이스 비밀번호
#define WIFI_SSID "olleh_WiFi_8585" // 연결 가능한 wifi의 ssid
#define WIFI_PASSWORD "0000005605" // wifi 비밀번호
 
FirebaseData firebaseData;
FirebaseJson json;
 
void printResult(FirebaseData &data);
void setup() // wifi 접속 과정.
{
  Serial.begin(115200);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData.setBSSLBufferSize(1024, 1024);
  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData.setResponseSize(1024);
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
 
  pinMode(LED_BUILTIN, OUTPUT); // 출력 핀 잡아주기.
}
 
void loop()
{
  if (Firebase.getString(firebaseData, "iot/tag")) // 해당하는 key가 있으면 (앱 인벤터에서는 tag)
  {
    String value = firebaseData.stringData(); // 값을 문자열로 받아와서 value에
    Serial.println(value); // 시리얼모니터에 값을 출력
    
    if (value == "0")
    {
      digitalWrite(LED_BUILTIN, LOW); // WeMos D1의 빌트인 LED는 LOW로 해야 불이 들어오네요 -.-;;
    }
    
    if (value == "1")
    {
      digitalWrite(LED_BUILTIN, LOW); // WeMos D1의 빌트인 LED는 LOW로 해야 불이 들어오네요 -.-;;
    }    
    else if (value == "2")
    {
      digitalWrite(LED_BUILTIN, HIGH); // 이거는 반대
    }
  }
  else
  {
    Serial.println(firebaseData.errorReason()); // 에러 메시지 출력
  }
  delay(1000); // 1초마다 반복
}

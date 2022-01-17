#include "Firebase_Arduino_WiFiNINA.h"

#define FIREBASE_HOST "ybiot-1bcb2-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "MNCnyNK51km2RmTfiecNe3xKStFurmWq3ICYU7r8"

FirebaseData firebaseData;

String get_firebase_str(String endpoint)
{
  if (Firebase.getString(firebaseData, endpoint)) {
   
    if (firebaseData.dataType() == "string") {
      return firebaseData.stringData();
    }
  } else {
    Serial.println(firebaseData.errorReason());
  }
  return "";
}

void delete_firebase_data(String endpoint)
{
  Firebase.deleteNode(firebaseData, endpoint);
}

int get_firebase_int(String endpoint) {
  return get_firebase_str(endpoint).toInt();
}

void ybiot_init(void)
{
  Serial.print("Connecting to Wi-Fi");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
}

void ybiot_process(void (*on_rock)(void), void (*on_paper)(void))
{
  static int prev_rock = 0;
  int rock = get_firebase_int("/iot/rock_count");
  if (rock != prev_rock) {
    on_rock();
    prev_rock = rock;
    return;
  }

  static int prev_paper = 0;
  int paper = get_firebase_int("/iot/paper_count");
  if (paper != prev_paper) {
    on_paper();
    prev_paper = paper;
    return;
  }
  
  String mainly = get_firebase_str("/iot/mainly_used");
  delete_firebase_data("/iot/mainly_used");
  if (mainly.indexOf("same") > 0) {
    return;
  } else if (mainly.indexOf("rock") > 0) {
    on_rock();
  } else if (mainly.indexOf("paper") > 0) {
    on_paper();
  }
}

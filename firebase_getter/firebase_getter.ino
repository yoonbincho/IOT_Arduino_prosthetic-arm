/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2019 mobizt
 *
*/

//Example shows how to connect to Firebase RTDB and construct queries to filter data

//Required WiFiNINA Library for Arduino from https://github.com/arduino-libraries/WiFiNINA

#include "Firebase_Arduino_WiFiNINA.h"

#define FIREBASE_HOST "ybiot-1bcb2-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "MNCnyNK51km2RmTfiecNe3xKStFurmWq3ICYU7r8"
#define WIFI_SSID "WeWork"
#define WIFI_PASSWORD "P@ssw0rd"

//Define Firebase Data object
FirebaseData firebaseData;

String get_firebase_str(String endpoint)
{
  if (Firebase.getString(firebaseData, endpoint)) {
    //Success, then read the payload value

    //Make sure payload value returned from server is integer
    //This prevent you to get garbage data
    if (firebaseData.dataType() == "string") {
      return firebaseData.stringData();
    }
  } else {
    //Failed, then print out the error detail
    Serial.println(firebaseData.errorReason());
  }
  return "";
}

int get_firebase_int(String endpoint) {
  return get_firebase_str(endpoint).toInt();
}

void setup()
{

  Serial.begin(115200);
  delay(100);
  Serial.println();

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
  Serial.println();

  //Provide the autntication data
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);

  delay(1000);

  Serial.print("rock: ");
  Serial.println(get_firebase_int("/iot/rock_count"));
  
  Serial.print("paper: ");
  Serial.println(get_firebase_int("/iot/paper_count"));

  Serial.print("mainly: ");
  Serial.println(get_firebase_int("/iot/mainly_used"));
}

void loop()
{
}

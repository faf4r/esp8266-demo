#include <ESP8266WiFi.h>

//WiFi config
const char * ssid = "Tenda_D7BEA8";
const char * pwd = "tt174020";
//mqtt config
const char * mqtt_server = "121.41.80.56";
const char * topic = "/lock";

//timeout
const int timeout = 10; //seconds, value 0 means no timeout
/*  https://zhuanlan.zhihu.com/p/552731616
for (int i = 0; i < timeout*2; i++) {
  connect once;
  delay(500);
}
*/

//status variable
bool LED_status;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  LED_dark();

  Serial.println();
  Serial.println();

  connect();
}



void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    reconnect();
  }
  Serial.println("ok");
  delay(1000);
}



void connect() {
  Serial.printf("connecting to WiFi %s ...", ssid);

  WiFi.begin(ssid, pwd);
  while (!WiFi.isConnected()) {
    if (LED_status) LED_dark(); else LED_bright();
    delay(500);
  }

  Serial.println("connected.");
  LED_dark();
}

void reconnect() {
  Serial.printf("connecting to WiFi %s ...", ssid);

  WiFi.disconnect();  //清楚WiFi信息，防止路由器重启后可能变道导致原先记录的信息不一样
  WiFi.begin(ssid, pwd);
  while (!WiFi.isConnected()) {
    if (LED_status) LED_dark(); else LED_bright();
    delay(500);
  }
  
  Serial.println("connected.");
  LED_dark();
}

void LED_bright() {
  digitalWrite(LED_BUILTIN, LOW);
  LED_status = true;
}

void LED_dark() {
  digitalWrite(LED_BUILTIN, HIGH);
  LED_status = false;
}

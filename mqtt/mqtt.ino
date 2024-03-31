#include <ESP8266WiFi.h>
#include <PubSubClient.h> //https://www.arduino.cc/reference/en/libraries/pubsubclient/   https://pubsubclient.knolleary.net/api

//WiFi config
const char * ssid = "Tenda_D7BEA8";
const char * pwd = "tt174020";

//mqtt config
const char * mqtt_broker = "121.41.80.56";
const char * topic = "/lock";
const int mqtt_port = 1883;

//wifi client
WiFiClient espClient;
//mqtt client
PubSubClient client(espClient);

//status variable
bool LED_status;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  LED_dark();

  Serial.println();
  Serial.println();

  connect();

  //mqtt
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str())) {
    Serial.println("Public emqx mqtt broker connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }

  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}


void loop() {
  client.loop();
  // if (WiFi.status() != WL_CONNECTED) {
  //   reconnect();
  // }
  // Serial.println("ok");
  // delay(1000);
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

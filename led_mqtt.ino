#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// Static IP address in case DHCP fails
IPAddress ip(10, 197, 12, 226);

// User config
const char* username = "username"; // my AskSensors username
const char* subTopic = "actuator/username/apiKeyOut"; 
const int LED_pin = 8; // Led pin

// AskSensors MQTT config
const char* mqtt_server = "mqtt.asksensors.com";
unsigned int mqtt_port = 1883;

EthernetClient cliente;
PubSubClient client(cliente);

void setup() {
  Serial.begin(115200);
  Serial.println("*****************************************************");
  Serial.println("********** Program Start: Control LED with AskSensors over MQTT");
  Serial.println("Set LED as output");
  pinMode(LED_pin, OUTPUT);
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Try to configure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // Give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());
  Serial.println("connecting...");
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  if (!client.connected()) 
    reconnect();
  Serial.print("********** Subscribe to AskSensors actuator topic:");
  Serial.print(subTopic);
  client.subscribe(subTopic);
}

void loop() {
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Command received from AskSensors[");
  Serial.print(topic);
  Serial.print("] ");
  String content = "";
  for (int i = 0; i < length; i++) {
    content += (char)payload[i];
  }
  Serial.print(content);
  Serial.println("********** Parse Actuator command");
  if(content.equals("module1=1")){
    digitalWrite(LED_pin, 1);
    Serial.println("LED is ON"); 
  }
  if(content.equals("module1=0")){
    digitalWrite(LED_pin, 0);
    Serial.println("LED is OFF");
  }
    content = "";
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("********** Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ArduinoClient", username, "")) {  
      Serial.println("-> MQTT client connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("-> try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

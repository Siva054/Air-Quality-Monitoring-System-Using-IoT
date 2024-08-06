#include <DHT.h>
#include <ESP8266WiFi.h>

String api_key = "SL8AS9C2DOY2TTXS";
const char *ssid =  "Redmi 9"; 
const char *pass =  "9626314249"; 
const char* server = "api.thingspeak.com";

#define DHTPIN 0 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(2000); 
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  dht.begin();
}

void loop() {
  int chk = dht.read(DHTPIN);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (client.connect(server, 80)) {
    String data_to_send = api_key;
    data_to_send += "&field1=";
    data_to_send += String(h);
    data_to_send += "&field2=";
    data_to_send += String(t);
    data_to_send += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);
    delay(1000);
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celsius, Humidity: ");
    Serial.print(h);
    Serial.println("%. Sent to ThingSpeak.");
  }
  client.stop();
  Serial.println("Waiting...");

  
  delay(15000); 
}
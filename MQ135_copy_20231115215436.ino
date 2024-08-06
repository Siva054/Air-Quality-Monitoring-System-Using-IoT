/*#include <ESP8266WiFi.h>
String apiKey = "SL8AS9C2DOY2TTXS";
const char *ssid = "Redmi 9"; 
const char *pass = "9626314249";
const char* server = "api.thingspeak.com";
WiFiClient client;
void setup()
{
Serial.begin(115200);
delay(1000);
Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status()!=WL_CONNECTED)
{
delay(5000);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
}
void loop()
{
float h = analogRead(A0);
if (isnan(h))
{
Serial.println("Failed to read from MQ-135 sensor!");
return;
}
 
if (client.connect(server, 80))
{
String postStr = apiKey;
postStr += "&field3=";
postStr += String(h);
//postStr += String(h/1023*100);
postStr += "\r\n";
//client.print("POST /update HTTP/1.1\n");
//client.print("Host: api.thingspeak.com\n");
//client.print("Connection: close\n");
//client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
//client.print("Content-Type: application/x-www-form-urlencoded\n");
//client.print("Content-Length: ");
//client.print(postStr.length());
//client.print("\n\n");
//client.print(postStr);
//Serial.print("Gas Level: ");

//Serial.println(h/1023*100);

//Serial.println("Data Send to Thingspeak");
// Construct the HTTP POST request
String httpRequest = "POST /update HTTP/1.1\r\n";
httpRequest += "Host: " + String(server) + "\r\n";
httpRequest += "Connection: close\r\n";
httpRequest += "X-THINGSPEAKAPIKEY: " + apiKey + "\r\n";
httpRequest += "Content-Type: application/x-www-form-urlencoded\r\n";
httpRequest += "Content-Length: " + String(postStr.length()) + "\r\n\r\n";
httpRequest += postStr;

  // Send the request
client.print(httpRequest);
Serial.println("Data Sent to ThingSpeak");

}
delay(500);
client.stop();
Serial.println("Waiting...");
 
delay(1500);
}
*/
#include <ESP8266WiFi.h>

String apiKey = "SL8AS9C2DOY2TTXS";
const char *ssid = "Redmi 9";
const char *pass = "9626314249";
const char *server = "api.thingspeak.com";
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  float h = analogRead(A0);

  if (isnan(h)) {
    Serial.println("Failed to read from MQ-135 sensor!");
    return;
  }

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field3=";
    postStr += String(int(h)); 
    postStr += "\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Gas Level: ");
    Serial.println(int(h)); 
    Serial.println("Data Sent to ThingSpeak");
  }

  delay(500);
  client.stop();
  Serial.println("Waiting...");
  delay(15000); 
}

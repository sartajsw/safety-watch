#include <ESP8266WiFi.h>

#define sensor_pin  A0
String sensor_value;

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(sensor_pin,INPUT);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("AP_1", "Password_1");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  Serial.println();
  Serial.println("Server started.");
  Serial.print("IP: ");     
  Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     
  Serial.println(WiFi.softAPmacAddress());
}

void loop()
{
  WiFiClient client = server.available();
  while (!client)
  if (!client) 
  {
    return;
  }
  sensor_value = analogRead(sensor_pin);
//  n++;
//  if (n>420)
//  {
//    n = 0;
//  }
  Serial.print("Sending sensor data to client: ");
  Serial.println(client.println("4224 S1"+ String(sensor_value) + "\r"));
  delay(500);
//  String ID = client.readStringUntil('\r');
//  Serial.println("From the station: " + ID);
//  client.flush();
}

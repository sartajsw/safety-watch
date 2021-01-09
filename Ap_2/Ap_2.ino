#include <ESP8266WiFi.h>

//int sensor_pin = A0;
String sensor_value;
int n=42;

WiFiServer server(80);
IPAddress IP(192,168,4,43);
IPAddress mask = (255, 255, 255, 0);


void setup()
{
  Serial.begin(115200);
  Serial.println();
//  pinMode(sensor_pin,INPUT);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("AP_2", "Password_2");
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
//  n = analogRead(sensor_pin);
  n++;
  if (n>420)
  {
    n = 0;
  }
  sensor_value = String(n);
  Serial.print("Sending sensor data to client: ");
  Serial.println(client.println(sensor_value + "\r"));
  delay(500);
//  String request = client.readStringUntil('\r');
//  Serial.println("********************************");
//  Serial.println("From the station: " + request);
//  client.flush();
}

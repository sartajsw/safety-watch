#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

//int sensor_pin = A0;
//String sensor_value;
//int n;

const char* ssid_1     = "OnePlus 5";
const char* password_1 = "siddharthhoree";
const char * host_1 = "192.168.4.1";
const char* ssid_2     = "Unknown Virus";
const char* password_2 = "sayplease";
const char * host_2 = "192.168.4.2";
const char* ssid_3     = "OnePlus 6";
const char* password_3 = "asdfghjk";
const char * host_3 = "192.168.4.3";

String ssid;
String old_ssid;
String server;

ESP8266WiFiMulti wifiMulti;
WiFiClient client;

void setup() 
{
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  Serial.setDebugOutput(true);
  // pinMode(sensor_pin, INPUT);
  // To set the ESP in Station Mode
  WiFi.mode(WIFI_STA);  
  // Add the WiFi networks you want to connect to
  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);
  wifiMulti.addAP(ssid_3, password_3);
  // Connecting to the best avialable WiFi
  Serial.println("Connection to AP");
  while(wifiMulti.run() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  ssid = WiFi.SSID();
  Serial.print("Connected to:\t");
  Serial.println(ssid);
  if (ssid != String(old_ssid))
  {
    if (ssid == String(ssid_1))
    {
      server = host_1; 
    }
    else if (ssid == String(ssid_2))
    {
      server = host_2;
    }
    else if (ssid == String(ssid_3))
    {
      server = host_3;
    }
    delay(1); 
    //client.connect(server, 80);
    old_ssid = ssid;
  }
  Serial.print("RSSI:");
  Serial.println(WiFi.RSSI());
  if (WiFi.RSSI()<-66)
  {
      WiFi.disconnect();
      WiFi.setAutoReconnect(true);
      //client.stop();
      while(wifiMulti.run() != WL_CONNECTED) 
      {
        Serial.print(".");
        delay(500);
      }
  }

//  Serial.println("********************************");
//  n = analogRead(sensor_pin);
//  sensor_value = String(n);
//  Serial.print("Byte sent to the AP: ");
//  Serial.println(client.print(sensor_value+"\r"));
//  String answer = client.readStringUntil('\r');
//  Serial.println("From the AP: " + answer);
//  client.flush();
//  client.stop();
//  delay(2000);
}

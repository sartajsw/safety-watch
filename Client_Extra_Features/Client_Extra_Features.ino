#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <math.h>
//#include <aREST.h>
//
//aREST rest = aREST();

#define motor_pin D5
#define threshold1 250
#define threshold2 240
int vibration = 0;
String recieved_value;
String AP_ID;
String Sensor_ID;
String sensor_value;
String ID;  
int n;
double d;
double t;

const char* ssid_1     = "AP_1";
const char* password_1 = "Password_1";
const char * host_1 = "192.168.4.15";
const char* ssid_2     = "AP_2";
const char* password_2 = "Password_2";
const char * host_2 = "192.168.4.43";
const char* ssid_3     = "OnePlus 6";
const char* password_3 = "asdfghjk";
const char * host_3 = "192.168.4.3";

String ssid;
String old_ssid;
String server;
int rssi;

ESP8266WiFiMulti wifiMulti;
WiFiClient client;

void setup() 
{
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
//  rest.variable("AP_ID",&AP_ID);
//  rest.variable("Sensor_ID",&Sensor_ID);
//  rest.variable("Sensor_value",&sensor_value);
//  rest.set_id("1");
//  rest.set_name("esp8266");
  Serial.setDebugOutput(true);
  pinMode(A0, INPUT);
  // To set the ESP in Station Mode
  WiFi.mode(WIFI_STA);  
  // Add the WiFi networks you want to connect to
  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);
  wifiMulti.addAP(ssid_3, password_3);
  // Connecting to the best avialable WiFi
  Serial.println("Connecting to AP");
  while(wifiMulti.run() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  pinMode(motor_pin, OUTPUT);
}

void loop() 
{
//  rest.handle(client);
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
    client.connect(server, 80);
    old_ssid = ssid;
  }
  else
  {
    client.connect(server, 80);
  }
  rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi);
  if (WiFi.RSSI()<-66 || WiFi.RSSI()>0) 
  {
      WiFi.disconnect();
      client.flush();
      client.stop();
      WiFi.setAutoReconnect(true);
      while(wifiMulti.run() != WL_CONNECTED) 
      {
        Serial.print(".");
        delay(500);
      }
  }
  // Calculation approx distance using RSSI
  d = pow (10, (20.5 - rssi)/20);
  Serial.print("Approx distance: ");Serial.println(d);
  // Recieving data from AP
  recieved_value = client.readStringUntil('\r');
  Serial.println("From the AP: " + recieved_value);
  AP_ID = recieved_value.substring(0, 4);
  Sensor_ID = recieved_value.substring(5, 7);
  sensor_value = recieved_value.substring(8);
  Serial.print("AP_ID: ");Serial.println(AP_ID);
  Serial.print("Sensor_ID: ");Serial.println(Sensor_ID);
  Serial.print("Sensor_Value: ");Serial.println(sensor_value);
//  t = analogRead(A0);
//  t = ( t/1024.0)*255;
//  Serial.print("Temperature: ");Serial.println(t);
  n = sensor_value.toInt();
  if (Sensor_ID == "S1" && n>threshold1)
  {
    digitalWrite(motor_pin, HIGH);
    delay(1000);
    digitalWrite(motor_pin, LOW);
  }
  else if (Sensor_ID == "S2" && n>threshold2)
  {
    digitalWrite(motor_pin, HIGH);
    delay(1000);
    digitalWrite(motor_pin, LOW);
  }
  client.flush();
  client.stop();
}

#include <ESP8266WiFi.h>
#include <SimpleTimer.h>
#include <DHT.h>

#define sensor_pin  A0
#define S0 D0
#define S1 D1
String sensor1_value;
String sensor2_value;
int S = 0;

#define DHTPIN D2
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
String h = "Hum: ";
String t = " Temp: ";
float hum;  //Stores humidity value
float temp; //Stores temperature value

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

SimpleTimer timer;

void setup()
{
  Serial.begin(115200);
  Serial.println();
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
  dht.begin();
  pinMode(sensor_pin,INPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  timer.setInterval(2500, sensor1);
  timer.setInterval(5000, sensor2);
}

void loop()
{
  WiFiClient client = server.available();
  while (!client)
  if (!client) 
  {
    return;
  }
  timer.run();
  if (S == 1)
  {
  sensor1_value = analogRead(sensor_pin);
  Serial.println("Sending Sensor 1 value ");
  Serial.println(client.println("4224 S1 "+ String(sensor1_value) + "\r"));
  }
  else if (S == 2)
  {
  hum = dht.readHumidity();
  temp= dht.readTemperature();
  Serial.println("Sending Sensor 2 value: ");
  Serial.println(client.println("4224 S2 "+ h + String(hum) + t + String(temp) + "\r"));
  }
  S = 0;
  digitalWrite(S1, LOW);
  digitalWrite(S0, LOW);
//  String ID = client.readStringUntil('\r');
//  Serial.println("From the station: " + ID);
//  client.flush();
}

void sensor1()
{
  S = 1;
  digitalWrite(S1, LOW);
  digitalWrite(S0, HIGH);
}

void sensor2()
{
  S = 2;
  digitalWrite(S1, HIGH);
  digitalWrite(S0, LOW);
}


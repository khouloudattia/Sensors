#include <WiFiClient.h>
#include <ThingSpeak.h>  
#include <WiFi.h> 
WiFiClient client;  
const char* server = "api.thingspeak.com";
char ssid[] = "Infinix";                       // Your WiFi credentials.
char pass[] = "khouloud123";
int count=0;
String apiKey = "1FQ8CZ2SPT14OGFA";     //  Enter your Write API key from ThingSpeak
boolean countStatus;
int BPM;
unsigned long millisBefore;
 const int analogIn = 39;
int RawValue= 0;
double Voltage = 0;
double Temperature = 0;,           
#define ADC_VREF_mV    3300.0                          // in millivolt
#define ADC_RESOLUTION 4096.

void setup()
{ Serial.begin(115200);
   delay(1000);
  Serial.println("\n");
  Serial.println();
  Serial.print("Connecting to ");
   Serial.println(ssid);
  WiFi.begin( ssid,pass);
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) 
  {
  Serial.print(".");
  delay(1000);
  }
 Serial.println("\n");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  
  delay(1000);
  Serial.println("connecting...");
  delay(1000);
  ThingSpeak.begin(client) ;
}
void loop()
{ RawValue = analogRead(analogIn);
Voltage = (RawValue / 2048.0) * 3300;                  // 5000 to get millivots.
Temperature = Voltage * 0.1;
Serial.print("Raw Value = " );                        // shows pre-scaled value
Serial.print(RawValue);
Serial.print("\t milli volts = ");                    // shows the voltage measured
Serial.print(Voltage,0); 
Serial.print("\t Temperature in C = ");
Serial.print(Temperature,1);
delay(500);
Serial.println("\n"); 
  int sensorValue = analogRead(36);
  Serial.print("sensorValue");
  Serial.println(sensorValue);
  delay(500);
   if (sensorValue > 2000)
    {
BPM= sensorValue/30;
      Serial.print("BPM: ");
      Serial.println(BPM);
      delay(500);
    }
  else
    {
      BPM= 0;
       Serial.print("BPM: ");
      Serial.println(BPM);
  delay(500);
  }        
if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(Temperature);
                             postStr +="&field2=";
                             postStr += String(BPM);
                             postStr += "\r\n\r\n";
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
                        }
}

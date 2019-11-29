// Libraries to be included
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <PubSubClient.h>
#include <Wire.h>


//In this example we are using SGX VZ89TE I2C sensor
#define I2CAddress 0x70
#define READINTERVAL  2000
#define PUBLISHINTERVAL 30000


// WIFI Access Credentials.
#define WIFI_AP "<WiFi SSID>"
#define WIFI_PASSWORD "<WiFi Passcode>"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.


// MQTT Broker token and in this case we are using demo.thingsboard.io as our broker
#define TOKEN "@@@@@" // Replace @@@@@ with your token
char mqttBroker[] = "demo.thingsboard.io"; // char mqttBroker[] = boker address; // modify to your local broker


// Global Variables declaration
long crc;
int R0Value;
int VOCvalue;
int CO2value = 400;
int CO2_without_modify;
int VOC_without_modify;
byte data[10];
int i;
int k = 0;
long lastRead = 0;
char msg[50];
int value = 0;


//Setting-Up WiFi client
LWiFiClient wifiClient;
PubSubClient client( wifiClient );

//Definition for last sent data
unsigned long lastSend;


void setup()
{
    Serial.begin( 115200 );
    Wire.begin();
    pinMode(13, OUTPUT);
    delay( 10000 );

// Prints to serial board information
    Serial.println("SGX Sensortech VT-89");
     VZ89TEReadData(0x0D); //date code & revision
     Serial.print("date code & revision  ");  Serial.print(data[2]); Serial.print("-"); Serial.print(data[1]); Serial.print("-"); Serial.print(data[0]); Serial.print(", ");
     Serial.print("Revision: "); Serial.println(data[3]);
     Serial.print("R0 Calibration Value  ");
     VZ89TEReadData(0x10); //R0 Calibration Value
     R0Value = ((data[1] & 0x3F ) << 8) | data[0];
     Serial.print(R0Value); Serial.println(" kohm");

// Calling class InitWifi() to initialize wifi connection
     InitLWiFi();

// Setting a pair of the broker and port number and tunnelling it through the wifi client.
   lastSend = 0;
}

void loop()
{
// Checking if the client is connected, if not connected we try to establish connection by calling the class reconnect()
  if( !client.connected() ) {
    reconnect();
  }

  // Send an update only after 5 seconds
  if( millis()-lastSend > 5000 ) {
    sendAnalogData();
    lastSend = millis();
  }

  client.loop();
}


// Class to send data to the broker
void sendAnalogData() {
  // Read data to send
  long now = millis();

	lastRead = now;
	VZ89TEReadData(0x0C); //status
	CO2_without_modify = CO2value;
	VOC_without_modify = VOCvalue;

  // The relation of these two lines exists in the datasheet
	VOCvalue = 0.25*((data[0] - 13) * (1000 / 229))+0.75*VOCvalue;
	CO2value = 0.25*((data[1] - 13) * (1600 / 229) + 400)+0.75*CO2value;

  // Just debug messages
  Serial.print( "Data to be sent" );

  // Prepare a JSON payload string that encapsulates all the data we want to publish to our MQTT broker
  String payload = "{";
  payload += "\"CO2Level\":"; payload += CO2value;  payload += ", ";
  payload += "\"VOCLevel\":"; payload += VOCvalue;
  payload += "}";

  // Send payload
  char attributes[100];
  payload.toCharArray( attributes, 100 );
  client.publish( "v1/devices/me/attributes", attributes );
  client.publish( "v1/devices/me/telemetry", attributes );
}


// Class to read dara from the sensor
void VZ89TEReadData(long request)
{
  crc = request;
  crc = (byte)(crc + (crc / 0x100));
  crc = 0xFF - crc;

  // Initiate Comms to device, initiate measure and read bytes of data
  Wire.beginTransmission(I2CAddress);
  Wire.write(request);  Wire.write(0);  Wire.write(0);  Wire.write(0);  Wire.write(0);  Wire.write(crc);
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(I2CAddress, 7);
  for (i = 0; i < 7; i++)
    {
      data[i] = Wire.read();
    }

  crc = data[0] + data[1] + data[2] + data[3] + data[4] + data[5];
  crc = (byte)(crc + (crc / 0x100));
  crc = 0xFF - crc;
}


// Class for establishing WiFi Connection
void InitLWiFi()
{
  LWiFi.begin();
  // Keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD))) {
    delay(1000);
  }
  Serial.println("Connected to AP");
}


// Class for establishing clent broker Connection
void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
 {
    Serial.print("Connecting to MQTT broker ...");

    // Attempt to connect
    if ( client.connect("@@@@", TOKEN, NULL) ) // Replace @@@@ with the name of your device at demo.thingsboard.io
    {
      Serial.print("Connected to MQTT broker ...");
    }
     else
    {
      Serial.print( "[FAILED] [ rc = " );
      Serial.print( client.state() );
      Serial.println( " : retrying in 5 seconds]" );

      // Wait 5 seconds before retrying
      delay( 5000 );
    }
 }
}

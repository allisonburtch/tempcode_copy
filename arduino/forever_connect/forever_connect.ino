/*
 Forever Web client
 
 Read temperature, connects to a a web server and makes a request every n seconds 

 Based on Repeating Web Client by by Tom Igoe (19 Apr 2012)
 http://arduino.cc/en/Tutorial/WebClientRepeating
 This code is in the public domain.
 
 Using TMP36 Analog temperature sensor
 http://www.adafruit.com/products/165
 Connected to Analog pin 0, +5v and Ground
 */

#include <SPI.h>
#include <Ethernet.h>

// The MAC address from YOUR ethernet controller.
byte macSergio[] = {0x90, 0xA2, 0xDA, 0x00, 0x6C, 0xFE};
byte macDonna[] = {0x90, 0xA2, 0xDA, 0x00, 0x86, 0x36};


// fill in an available IP address on your network here, for manual configuration:
IPAddress ipDonna(192,168,1,104); // Donna
IPAddress ipSergio(192,168,1,102);  //Sergio

IPAddress server(192,168,1,100);

// initialize the library instance:
EthernetClient client;

int sensorPin = 0;

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop

const unsigned long postingInterval = 20000;    // delay between updates, in milliseconds

void setup() {

  Serial.begin(9600);
  delay(1000);

  Ethernet.begin(macSergio, ipSergio);
 // Ethernet.begin(mac);

  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    httpRequest();
  }
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();

}


// this method makes a HTTP connection to the server:
void httpRequest() {
 
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(sensorPin);  

  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.0;
  voltage /= 1024.0; 

  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
  //                                               //to degrees ((voltage - 500mV) times 100)
  // Serial.print("save/AB/");Serial.println(temperatureC); 

  // now convert to Fahrenheit
  int temperatureF = floor((temperatureC * 9.0 / 5.0) + 32.0);
  // Serial.print(temperatureF); Serial.println(" degrees F");

  delay(500);   
  // if there's a successful connection:
  if (client.connect(server, 8888)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.print("GET /");
    client.print("save/DM/");
    client.print(temperatureF); 
    client.println(" HTTP/1.1");
    client.println("Host: 192.168.1.100:8888");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }

}


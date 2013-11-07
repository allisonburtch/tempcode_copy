/*
 Forever Web client
 Read temperature, connects to a a web server and makes a request every n seconds 
 Get the server code at https://github.com/sergiomajluf/Temp-Monitor
 
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
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x00, 0x6C, 0xFE};
byte macSergio[] = {
  0x90, 0xA2, 0xDA, 0x00, 0x6C, 0xE4};
byte macDonna[] = {
  0x90, 0xA2, 0xDA, 0x00, 0x86, 0x36};
byte macAllison[] = {
  0x7A, 0xC4, 0xE, 0x92, 0xEB, 0x2};


// Use an available IP address on your network here, for manual configuration:
/*
IPAddress ipDonna(192,168,1,104);    // Donna
 IPAddress ipSergio(192,168,0,5);     // Sergio
 IPAddress ipAllison(192,168,1,111);  // Allison
 */

//IPAddress server(192,168,1,100);
char server[] = "temp-monitor.herokuapp.com";

// initialize the library instance:
EthernetClient client;

int sensorPin = 0;

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop

const unsigned long postingInterval = 600000;    // 10 minutes delay between updates, in milliseconds

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  delay(1000);

  Ethernet.begin(mac);               // Choose the appropiate mac address
  // Ethernet.begin(mac, ip);         // If you set a manual IP, swap this commented .begin statements

  // Print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Debug, display incomming data if any:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // If there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  // If you're not connected, and 10 minutes have passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    httpRequest();
  }
  
  // Store the state of the connection for next time through
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
  // converting from 10 mv per degree wit 500 mV offset
  // to degrees ((voltage - 500mV) times 100)
  float temperatureC = (voltage - 0.5) * 100 ;
 
  // now convert to Fahrenheit
  int temperatureF = floor((temperatureC * 9.0 / 5.0) + 32.0);
 
  delay(500);   
 
  // if there's a successful connection:
  if (client.connect("temp-monitor.herokuapp.com",80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.print("GET /");
    client.print("save/SM/");
    client.print(temperatureF); 
    client.println(" HTTP/1.1");
    client.println("Host: temp-monitor.herokuapp.com");
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

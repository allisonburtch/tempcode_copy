
#include <SPI.h>
#include <Ethernet.h>
#include <WiFi.h>

char ssid[] = "fullcommunism";     // the name of your network
int status = WL_IDLE_STATUS;     // the Wifi radio's status
int sensorPin = 0;

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {  
    0x7A,0xC4,0xE,0x92,0xEB,0x2
//    7A:C4:E:92:EB:2
};  
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192,168,1,111);
IPAddress server(192,168,1,100);

// initialize the library instance:
WiFiClient client;

//char server[] = "192,168,1,100";

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 2000;  // delay between updates, in milliseconds

void setup() {
  // start serial port:
  Serial.begin(9600);
  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
//  Ethernet.begin(mac, ip);
//  // print the Ethernet board/shield's IP address:
//  Serial.print("My IP address: ");
//  Serial.println(Ethernet.localIP());
  Serial.println("Attempting to connect to open network...");
  status = WiFi.begin(ssid);

  // if you're not connected, stop here:
  if ( status != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
    while(true);
  } 
  // if you are connected :
  else {
      Serial.print("Connected to the network");
  }
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
   
   // print out the voltage
   //Serial.print(voltage); Serial.println(" volts");
   
   // now print out the temperature
   float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
  //                                               //to degrees ((voltage - 500mV) times 100)
   //Serial.print("save/AB/");Serial.println(temperatureC); 
   
   // now convert to Fahrenheit
   int temperatureF = floor((temperatureC * 9.0 / 5.0) + 32.0);
  //Serial.print(temperatureF); Serial.println(" degrees F");
   
   delay(500);   
  // if there's a successful connection:
  if (client.connect(server, 8888)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.print("GET /");
    client.print("save/AB/");client.print(temperatureF); 
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



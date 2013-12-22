#include <SPI.h>
#include <WiFi.h>

char ssid[] = "WIFI_AGINIZIN_ADI"; //  your network SSID (name) 
char pass[] = "WIFI_AGINIZIN_SIFRESI";    // your network password (use for WPA, or use as key for WEP)

char motorHizi=0;
int arkaMotor = 3;
int direksiyon = 11;


int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(23);

boolean alreadyConnected = false; // whether or not the client was connected previously

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  
  pinMode(9, OUTPUT);      // set the LED pin mode
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  } 
  // start the server:
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
 }


void loop() {
  // wait for a new client:
  WiFiClient client = server.available();


  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();    
      Serial.println("We have a new client");
      client.println("Hello, client!"); 
      alreadyConnected = true;
    } 

    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char thisChar = client.read();
      
       if (thisChar=='i') {
          digitalWrite(12, LOW);
          digitalWrite(9, LOW);
          analogWrite(arkaMotor, 250);
        }
        if(thisChar=='g'){
            digitalWrite(12, HIGH);
            digitalWrite(9, LOW);
            analogWrite(arkaMotor, 250);   
        }
        if(thisChar=='r'){
            digitalWrite(13, HIGH);
            digitalWrite(8, LOW);
            analogWrite(direksiyon, 250); 
        } 
        if(thisChar=='l'){
            digitalWrite(13, LOW);
            digitalWrite(8, LOW);
            analogWrite(direksiyon, 250);  
        } 
        if (thisChar=='d') {
          analogWrite(arkaMotor, 0);  
          analogWrite(direksiyon, 0);
        }
        
      // echo the bytes back to the client:
      //server.write(thisChar);
      // echo the bytes to the server as well:
      //Serial.write(thisChar);
    }
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  digitalWrite(9, HIGH); 
}



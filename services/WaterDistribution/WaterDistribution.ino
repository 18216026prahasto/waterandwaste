#include <SPI.h>
#include <Ethernet.h>


float threshold = 4.0;
byte mac[] = {
  0xFC, 0x77, 0x74, 0xC4, 0xF5, 0x4F };

IPAddress ip(10,5,25,96);
IPAddress server(10,5,24,1); 

EthernetClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ethernet.begin(mac, ip);

  delay(10000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A1);
  float voltage = (sensorValue) * 5.0 / 1024.0;
  // Check to see if the the circuit was connected or broken
  Serial.println(client.connect(server, 8008));
  if (client.connect(server, 8008)) {
    Serial.println(voltage);
    if (voltage < threshold) {
      client.print(String("GET ") + "/services/waterdatabase.php?value=" + voltage + "&status=1\r\n" + " HTTP/1.1\r\n" + "Host: " + server + "connection: close\r\n\r\n"); // This
      Serial.println("Broken");
    } else {
      client.print(String("GET ") + "/services/waterdatabase.php?value=" + voltage + "&status=0\r\n" + " HTTP/1.1\r\n" + "Host: " + server + "connection: close\r\n\r\n"); // This
      Serial.println("Ok");
    } 
  } else {
       Serial.println("--> connection failed\n");
  }
  delay(5000); 
}

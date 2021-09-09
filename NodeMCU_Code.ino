#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "*****";  // Enter SSID here in place of ****
const char* password = "****";  //Enter Password here in place of ****

ESP8266WebServer server(80);

SoftwareSerial s(D6,D5);

String data;

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);
  
  //check wi-fi is connected to wi-fi network
  while(WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

    server.on("/", handle_OnConnect);
    server.onNotFound(handle_NotFound);
    server.begin();
    Serial.println("HTTP server started");


}
 
void loop() {

   server.handleClient();

  
  s.write("s");
  if (s.available()>0)
  {
    data = s.readString();
    Serial.println(data);
  }

  //Serial.println(xyz);
  delay(2000);
 
}

void handle_OnConnect() {
  Serial.println("WebServer Working!!");
  server.send(200, "text/html", SendHTML()); 
}

  void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>IOT Project Webpage</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>IOT Smart Agriculture Monitoring System</h1>\n";
    ptr +="<h3>Displaying the data recieved from the sensors</h3>\n";

    ptr +="<p>" +data +"</p>";

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

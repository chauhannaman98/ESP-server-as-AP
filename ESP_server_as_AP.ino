#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>

//#include "index.h"

//===============================================================
//                         HTML Page
//===============================================================
String s = R"=====(
<html>
  <head>
      <title>My first web page</title>
  </head>
  <body bgcolor="#afafaf">
  <center>
      <h1>Techmirtz by <a href="https://github.com/chauhannaman98/">Naman Chauhan</a> </h1>
  </center> 
  <footer> Page hosted on ESP8266 </footer>
</body>
</html>
)=====";

//SSID and Password to your ESP Access Point
const char* ssid = "ESP-techmirtz";
const char* password = "esp123456";

static int count = 0;

ESP8266WebServer server(80); //Server on port 80

//==============================================================
//   This routine is executed when you open its IP in browser
//==============================================================
void handleRoot() {
  Serial.print(count++);
  Serial.println(" [INFO] /GET 200");
  server.send(200, "text/html", s);
  //server.send(200, "text/plain", s);
}

//===============================================================
//                           SETUP
//===============================================================
void setup(void){
  Serial.begin(115200);
  Serial.println("");
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password); //Start HOTspot removing password will disable security

  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
 
  server.on("/", handleRoot);      //Which routine to handle at root location

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

//===============================================================
//                            LOOP
//===============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}

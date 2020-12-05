#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define STASSID "Raihan"
#define STAPSK  "passwordnyadiganti"

const char* ssid     = STASSID;
const char* password = STAPSK;
const char* host = "nobonfre.000webhostapp.com";
const int port = 80;

WiFiClient client;

String str;
void setup() {
  Serial.begin(115200);

  //connect to your local wi-fi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //inisialisasi gerbang
  getG1();
  getG2();
  getG3();

}

void loop() {
  if (Serial.available()) {
     getComm();
   }else{
     getG1(); 
   }
   
   if (Serial.available()) {
     getComm();
   }else{
     getG2();
   }
   
   if (Serial.available()) {
     getComm();
   }else{
     getG3();
   }
}

void getG1(){
  String gateId = "01";
  if (WiFi.status() == WL_CONNECTED) {
//    Serial.print("Http Connecting");
    int r=0;
    while((!client.connect(host,port)) && (r < 30)){
      delay(100);
//      Serial.print(".");
      r++;
    }
    
//  Serial.println("Conn Succes");
    
    String Link;
    Link = "/api/gate/Read.php?id="+gateId;
  
  //    Serial.print("requesting: ");
  //    Serial.println(host+Link);
  
    client.print(String("GET ") + Link + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +               
               "Connection: close\r\n\r\n");
  
  //    Serial.println("request sent");
  
    while(client.connected()){
      String line = client.readStringUntil('\n');
      if(line == "\r"){
//        Serial.println("headers received");
        break;
      }
    }
  
  //    Serial.println("reply was:");
  //    Serial.println("==========");
    String line;
  
  while(client.available() && !(line == "Open" || line == "Close")){        
      line = client.readStringUntil('""');  //Read Line by Line
    }
    line = "G1_" + line;
    Serial.println(line); //Print response
//    Serial.println("==========");
//    Serial.println("closing connection");
    delay(1500);
  }
}

void getG2(){
  String gateId = "02";
  if (WiFi.status() == WL_CONNECTED) {
    int r=0;
    while((!client.connect(host,port)) && (r < 30)){
      delay(100);
      r++;
    }    
    String Link;
    Link = "/api/gate/Read.php?id="+gateId;

    client.print(String("GET ") + Link + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +               
               "Connection: close\r\n\r\n");

    while(client.connected()){
      String line = client.readStringUntil('\n');
      if(line == "\r"){
        break;
      }
    }

    String line;

    while(client.available() && !(line == "Open" || line == "Close")){        
      line = client.readStringUntil('""');  //Read Line by Line
    }
    line = "G2_" +line;
    Serial.println(line); //Print response
    delay(1500);
  }
}

void getG3(){
  String gateId = "03";
  if (WiFi.status() == WL_CONNECTED) {
    int r=0;
    while((!client.connect(host,port)) && (r < 30)){
      delay(100);
      r++;
    }
 
    String Link;
    Link = "/api/gate/Read.php?id="+gateId;

    client.print(String("GET ") + Link + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +               
               "Connection: close\r\n\r\n");

    while(client.connected()){
      String line = client.readStringUntil('\n');
      if(line == "\r"){
        break;
      }
    }

    String line;

    while(client.available() && !(line == "Open" || line == "Close")){        
      line = client.readStringUntil('""');  //Read Line by Line
    }
    line = "G3_" +line;
    Serial.println(line); //Print response
    delay(1500);
  }
}

void getComm(){
  str = Serial.readString();
  str.trim();
  String temp;
  if(str.equals("G1_Available")){
    temp = "Available";
    postG1(temp);
  }else{
    if(str.equals("G1_Parked")){
      temp = "Parked";
      postG1(temp);
    }else{
      if(str.equals("G2_Available")){
        temp = "Available";
        postG2(temp);
      }else{
        if(str.equals("G2_Parked")){
          temp = "Parked";
          postG2(temp);
        }else{
          if(str.equals("G3_Available")){
            temp = "Available";
            postG3(temp);
          }else{
            if(str.equals("G3_Parked")){
              temp = "Parked";
              postG3(temp);
            }
          }
        }
      }
    }
  }
}

void postG1(String flag){
  String gateId = "01";
  if (WiFi.status() == WL_CONNECTED) {
  //  Serial.print("Http Connecting");
    int r=0;
    while((!client.connect(host,port)) && (r < 30)){
      delay(100);
      r++;
    }
    
    if(r==30){
    //  Serial.println("Conn Failed");
        postG1(flag);
    }else{
    
      String Link;
      if(flag.equals("Parked")){
        Link = "/api/flag/Parked.php?Flag="+flag+"&Nomor="+gateId;
      }else{
        Link = "/api/flag/Available.php?Flag="+flag+"&Nomor="+gateId;
      }
  
      client.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +               
                 "Connection: close\r\n\r\n");  
    }

  }
  
}

void postG2(String flag){
  String gateId = "02";
  if (WiFi.status() == WL_CONNECTED) {
  //  Serial.print("Http Connecting");
    int r=0;
    while((!client.connect(host,port)) && (r < 30)){
      delay(100);
      r++;
    }
    
    if(r==30){
    //  Serial.println("Conn Failed");
        postG2(flag);
    }else{
    
      String Link;
      if(flag.equals("Parked")){
        Link = "/api/flag/Parked.php?Flag="+flag+"&Nomor="+gateId;
      }else{
        Link = "/api/flag/Available.php?Flag="+flag+"&Nomor="+gateId;
      }
  
      client.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +               
                 "Connection: close\r\n\r\n");  
    }

  }
  
}

void postG3(String flag){
  String gateId = "03";
  if (WiFi.status() == WL_CONNECTED) {
  //  Serial.print("Http Connecting");
    int r=0;
    while((!client.connect(host,port)) && (r < 30)){
      delay(100);
      r++;
    }
    
    if(r==30){
    //  Serial.println("Conn Failed");
        postG3(flag);
    }else{
      // Serial.println("Conn Success");
      String Link;
      if(flag.equals("Parked")){
        Link = "/api/flag/Parked.php?Flag="+flag+"&Nomor="+gateId;
      }else{
        Link = "/api/flag/Available.php?Flag="+flag+"&Nomor="+gateId;
      }
  
      client.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +               
                 "Connection: close\r\n\r\n");  
    }

  }
 
}

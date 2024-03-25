
/* https://arduino.esp8266.com/stable/package_esp8266com_index.json
 * ESP8266 as Web Server using WiFi Access Point (AP) mode
 * Connect to AP "Chitti", password = "87654321"
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

//SSID and Password to your ESP Access Point
const char* ssid = "Chitti";
const char* password = "";

#define ENA   4     // Enable/speed motors Right    GPIO4(D2)
#define IN_1  0     // L298N in1 motors Right       GPIO0(D3)
#define IN_2  2     // L298N in2 motors Right       GPIO2(D4)
#define IN_3  12    // L298N in3 motors Left        GPIO12(D6)
#define IN_4  13    // L298N in4 motors Left        GPIO13(D7)
#define ENB   15    // Enable/speed motors Left     GPIO15(D8)

#define R_S   5     // IR sensor right              GPIO5(D1)
#define L_S   14    // IR sensor left               GPIO14(D5)

#define Light  16 // Light  GPIO16(D0)

String command;             //String to store app command state.
int speedCar = 100; // 0 to 255
int speed_low = 60;
int speedCarA = 150 ;
int mode = 0 ;

ESP8266WebServer server(80);

void setup() {
 
Serial.begin(115200);

pinMode(R_S, INPUT); // declare if sensor as input  
pinMode(L_S, INPUT); // declare ir sensor as input

pinMode(ENA, OUTPUT); 
pinMode(IN_1, OUTPUT);
pinMode(IN_2, OUTPUT);
pinMode(IN_3, OUTPUT);
pinMode(IN_4, OUTPUT);
pinMode(ENB, OUTPUT); 

pinMode(Light, OUTPUT); 
 
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void loop() {
    server.handleClient();
    
      command = server.arg("State");

           if (command == "A"){mode=1; speedCarA=60;} //Auto Line Follower Command 
      else if(command == "M"){mode=0; stopRobot();}    //Manual Android Application Control Command

    //  analogWrite(ENA, speedCar); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
    //  analogWrite(ENB, speedCar); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 

      if(mode==0){ 
      // --------------------------------------------------
      //   Manual Commands 
      // ---------------------------------------------------- 
      
      analogWrite(ENA, speedCar); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
      analogWrite(ENB, speedCar); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 

           if (command == "F") goForword();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "0") speedCar = 60;
      else if (command == "1") speedCar = 80;
      else if (command == "2") speedCar = 100;
      else if (command == "3") speedCar = 125;
      else if (command == "4") speedCar = 150;
      else if (command == "5") speedCar = 175;
      else if (command == "6") speedCar = 200;
      else if (command == "7") speedCar = 225;
      else if (command == "8") speedCar = 240;
      else if (command == "9") speedCar = 255;
      else if (command == "S") stopRobot();
      }
      else{    
     //===============================================================================
     //                          Line Follower Control
     //===============================================================================    
     
     analogWrite(ENA, speedCarA); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
     analogWrite(ENB, speedCarA); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 
 
     if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){goForwordA();}  //if Right Sensor and Left Sensor are at White color then it will call forword function
     else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){goRightA();}//if Right Sensor is Black and Left Sensor is White then it will call turn Right function  
     else if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){goLeftA();} //if Right Sensor is White and Left Sensor is Black then it will call turn Left function
     else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){stopRobotA();}     //if Right Sensor and Left Sensor are at Black color then it will call Stop function
     }
    delay(5);
}      


void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}

void goForword(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goBack(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goLeft(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goRight(){

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }

// ========================================================================================
//  LINE FOLLOWER COMMANDS
// ========================================================================================
 void goForwordA(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCarA);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCarA);
  }

void goLeftA(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCarA);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCarA);
  }

void goRightA(){

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCarA);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCarA);
  }

void stopRobotA(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCarA);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCarA);
}
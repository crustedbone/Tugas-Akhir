#include <Servo.h>

const int triger1 = 2;
const int echo1 = 3;
const int servoPin1 = 4;
const int triger2 = 5;
const int echo2 = 6;
const int servoPin2 = 7;
const int triger3 = 8;
const int echo3 = 9;
const int servoPin3 = 10;

Servo servo1;
Servo servo2;
Servo servo3;

long durasi;
int jarak;

int gate1;
int gate2;
int gate3;

String str;
void setup() {
  Serial.begin(115200);
  
  pinMode(triger1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(triger2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(triger3, OUTPUT);
  pinMode(echo3, INPUT);

  //inisialisasi gerbang
  servo1.attach(servoPin1);
  servo1.write(90);
  servo2.attach(servoPin2);
  servo2.write(90);
  servo3.attach(servoPin3);
  servo3.write(90);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

}

void loop() {
  if (Serial.available()) {
    getComm();
  }
  ultra1();
  
  if (Serial.available()) {
    getComm();
  }
  ultra2();
  
  if (Serial.available()) {
    getComm();
  }
  ultra3();
}

void ultra1(){
  digitalWrite(triger1, LOW);
  delayMicroseconds(500);

  digitalWrite(triger1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(triger1, LOW);

  durasi = pulseIn(echo1, HIGH);
  jarak = durasi*0.034/2;

  // Serial.print("Jarak Ultra 1: ");
  // Serial.println(jarak); 

  if (jarak  < 20 && (gate1 == 1 || gate1 == 2)){
      //posting parked
      Serial.println("G1_Parked");
      gate1 = 0;
      delay(2500);
  }else if (jarak >= 20  && gate1 == 0){
    //posting available
    Serial.println("G1_Available");
    gate1 = 1;
    delay(2500);
  }
}

void ultra2(){
  digitalWrite(triger2, LOW);
  delayMicroseconds(500);

  digitalWrite(triger2, HIGH);
  delayMicroseconds(1000);
  digitalWrite(triger2, LOW);

  durasi = pulseIn(echo2, HIGH);
  jarak = durasi*0.034/2;

  // Serial.print("Jarak Ultra 2: ");
  // Serial.println(jarak); 
  
  if (jarak  < 20 && (gate2 == 1 || gate2 == 2)){
      //posting parked
      Serial.println("G2_Parked");
      gate2 = 0;
      delay(2500);
  }else if (jarak >= 20  && gate2 == 0){
    //posting available
    Serial.println("G2_Available");
    gate2 = 1;
    delay(2500);
  }
}

void ultra3(){
  digitalWrite(triger3, LOW);
  delayMicroseconds(500);

  digitalWrite(triger3, HIGH);
  delayMicroseconds(1000);
  digitalWrite(triger3, LOW);

  durasi = pulseIn(echo3, HIGH);
  jarak = durasi*0.034/2;

  // Serial.print("Jarak Ultra 3: ");
  // Serial.println(jarak); 

  if (jarak  < 20 && (gate3 == 1 || gate3 == 2)){
      //posting parked
      Serial.println("G3_Parked");
      gate3 = 0;
      delay(2500);
  }else if (jarak >= 20  && gate3 == 0){
    //posting available
    Serial.println("G3_Available");
    gate3 = 1;
    delay(2500);
  }
}

void getComm(){
  str = Serial.readString();
  str.trim();
  if(str.equals("G1_Open")){
    g1Open();
  }else{
    if(str.equals("G1_Close")){
      g1Close();
    }else{
      if(str.equals("G2_Open")){
        g2Open();
      }else{
        if(str.equals("G2_Close")){
          g2Close();
        }else{
          if(str.equals("G3_Open")){
            g3Open();
          }else{
            if(str.equals("G3_Close")){
              g3Close();
            }
          }
        }
      }
    }
  }
}

void g1Open(){
  servo1.write(90);
}
void g1Close(){
  servo1.write(180);
  gate1 = 2;
}

void g2Open(){
  servo2.write(90);
}
void g2Close(){
  servo2.write(180);
  gate2 = 2;
}

void g3Open(){
  servo3.write(90);
}
void g3Close(){
  servo3.write(180);
  gate3 = 2;
}

#include <L298N.h>                                  // Library for L298N Motor Driver Module
#include <TinyGPS.h>
#include <SoftwareSerial.h> ,

float lat = random(2000, 2500)/100.0,lon = random(8500, 8700)/100.0; // create variable for latitude and longitude object
SoftwareSerial gpsSerial(3,4);//rx,tx 
TinyGPS gps; // create gps object 

int val;                                                        // Initialize Variable
int nb;                                                         // Initialize Variable

int motorPin1a = 9; // pin 2 on L293D IC
int motorPin2a = 8; // pin 7 on L293D IC
int motorPin1b = 13; // pin 2 on L293D IC
int motorPin2b = 12; // pin 7 on L293D IC
int motorPin1_ena = 10;
int motorPin2_enb = 11;



int state;
int flag=0;        //makes sure that the serial only prints once the state
 
int TriggerPIN1 = 4;
int EchoPIN1 = 5; 
int TriggerPIN2 = 6;
int EchoPIN2 = 7;
//int ena = 8;
//int enb = 9;

void setup(){
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);                            // Baud Rate for Serial Communication
  gpsSerial.begin(9600);

  // sets the pins as outputs:
  pinMode(motorPin1a, OUTPUT);
  pinMode(motorPin2a, OUTPUT);
  pinMode(motorPin1b, OUTPUT);
  pinMode(motorPin2b, OUTPUT);
  pinMode(motorPin1_ena,OUTPUT);
  pinMode(motorPin2_enb,OUTPUT);
    
  pinMode(TriggerPIN1,OUTPUT);
  pinMode(EchoPIN2,INPUT);
  pinMode(TriggerPIN2,OUTPUT);
  pinMode(EchoPIN2,INPUT);
  Serial.begin(9600); 
  }

void loop(){ 

      while(gpsSerial.available()){ // check for gps data 
        if(gps.encode(gpsSerial.read()))// encode gps data 
        {  
          gps.f_get_position(&lat,&lon); // get latitude and longitude 
          Serial.print("Position: ");
        }
      }    
      //if some date is sent, reads it and saves in state
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }   
    // if the state is '0' the DC motor will turn off
    if (state == '0') {
        digitalWrite(motorPin1a, LOW); // set pin 2 on L293D low
        digitalWrite(motorPin2a, LOW); // set pin 7 on L293D low
        digitalWrite(motorPin1b, LOW); // set pin 2 on L293D low
        digitalWrite(motorPin2b, LOW);
        analogWrite(motorPin1_ena,0);
        analogWrite(motorPin2_enb,0);

        if(flag == 0){
          Serial.println("Motors: off");
          flag=1;
        }
    }
    // if the state is '1' the motor will turn right
    else if (state == '1') {
        digitalWrite(motorPin1a, HIGH); // set pin 2 on L293D low
        digitalWrite(motorPin2a, LOW); // set pin 7 on L293D high
        digitalWrite(motorPin1b, HIGH); // set pin 2 on L293D low
        digitalWrite(motorPin2b, LOW); // set pin 7 on L293D high
        analogWrite(motorPin1_ena,160);
        analogWrite(motorPin2_enb,160);
        
        if(flag == 0){
          Serial.println("Motor: right");
          flag=1;
        }
    }
  
  
        
  digitalWrite(TriggerPIN1,LOW);
  delayMicroseconds(100);
  digitalWrite(TriggerPIN1,HIGH);
  delayMicroseconds(100);
  digitalWrite(TriggerPIN1,LOW);

  long timedelay1 = pulseIn(EchoPIN1,HIGH);
  int distance1 = 0.0343 * (timedelay1/2);

  delayMicroseconds(2);

  digitalWrite(TriggerPIN2,LOW);
  delayMicroseconds(100);
  digitalWrite(TriggerPIN2,HIGH);
  delayMicroseconds(100);
  digitalWrite(TriggerPIN2,LOW);

  long timedelay2 = pulseIn(EchoPIN2,HIGH);
  int distance2 = 0.0343 * (timedelay2/2);

//  Serial.print("Sensor 1 : ");
//  Serial.println(distance1);
//  Serial.print("Sensor 2 : ");
//  Serial.println(distance2);

  
  if (distance1 < 10) {  // This is where the LED On/Off happens
    Serial.println(distance1);
    Serial.println(distance2);
  }
  else {
    //stop the motor
  }
  if (distance1 >= 10 || distance1 <= 0 ){
    Serial.println("crack detected");
    String latitude = String(random(2000, 2500)/100.0,6); 
    String longitude = String(random(8000, 8500)/100.0,6); 
    Serial.println(latitude+";"+longitude); 
//    delay(1000);
    digitalWrite(motorPin1a, LOW); // set pin 2 on L293D low
    digitalWrite(motorPin2a, LOW); // set pin 7 on L293D low
    digitalWrite(motorPin1b, LOW); // set pin 2 on L293D low
    digitalWrite(motorPin2b, LOW);
        if(flag == 0){
          Serial.println("Motors: off");
          flag=1;
        }
  }
  else {
//    Serial.print(distance1);
//    Serial.println(" cm");
//    Serial.print(distance2);
//    Serial.println(" cm");
  }
  }

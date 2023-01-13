#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver(2000,14,12);

long delayTime = 3*pow(10,6);

int ledPin = 13;                // choose the pin for the LED
int inputPin = 8;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
long previousTime=0;
long timeNow=0;

bool isActivated=0;
int count=0;

void setup() {
  driver.init();
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT_PULLUP);     // declare sensor as input
 
 previousTime=1000;
  Serial.begin(9600);
}
 
void loop(){
  detectMotion();
}

// ****************** LASER
void detectMotion(){
  val = digitalRead(inputPin);  // read input value

  if(val==0){
    activateSensor();
    Serial.println("Beam Detected");
  }
  else{
    if(isActivated){
       Serial.println("Beam Broken");
        limitTransmission();
        count++;
        if(count>60){
            isActivated=false;
            count=0;
        }
    }
  }
  delay(50);
}

void activateSensor(){
  isActivated=true;
}

void limitTransmission(){
  timeNow = micros();
  if((timeNow-previousTime)>delayTime){
    transmitData();
    Serial.println("Transmission Started");
    previousTime=timeNow;
  }
}

// ****************** TRANSMITTER_RECEIVER
void transmitData(){
    const char *msg = "1";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(200);
}

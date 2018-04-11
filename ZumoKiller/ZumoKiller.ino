#include <ZumoMotors.h>
#include <Pushbutton.h>
ZumoMotors motors;
#include "BluetoothParameters.h"



// -------------------------- Modes

int mode = 1;

#define STOP 0
#define ATTACK 1
#define DEFENCE 2
#define TRACK 3
#define EDGE 4
#define BLUETOOTH 5

// -------------------------- Bluetooth

#define TX 1
#define RX 0

BluetoothParameters bt = BluetoothParameters();
BluetoothManager btm = BluetoothManager(&bt, TX, RX);


// -------------------------- Sensors

// US
#define trigPin 6
#define echoCenterPin 5
#define echoLeftPin 4
#define echoRightPin 3
#define echoBackPin 11

#define usSenTrigDistanse 3000
#define usSenTrigTimeout 4000
#define usSenTrigDefThreshold 800

bool lastSeenLeft = true;


// IR

#define irProbeTimes 3
#define frontIRchangeToTrigg 30
int frontIRtreshold = 0;

#define FRONTIRTRIGGERPIN 2


// -------------------------- Movement

int motorMaxSpeed = 400;
int motorMaxTurnSpeed = 260;
int TURNTIME = 300;

int aks = 150;
int deseleration = 600;
int activeSpeed = 0;
int activeLeftSpeed = 0;
int activeRightSpeed = 0;
int turnSpeed = 0;

bool usL = false;
bool usC = false;
bool usR = false;

bool counterOn = false;
int counter;
int countLength = 80;
// -------------------------- Diverse

#define led 13
Pushbutton button(ZUMO_BUTTON);

// -------------------------- Setup
void setup() {
  //Serial.begin (9600);
  bt.add(&motorMaxSpeed, "motorMaxSpeed");
  bt.add(&motorMaxTurnSpeed, "motorMaxTurnSpeed");
  pinMode(FRONTIRTRIGGERPIN, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoCenterPin, INPUT);
  pinMode(echoLeftPin, INPUT);
  pinMode(echoRightPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(12, INPUT_PULLUP);

  delay(1000);
  //frontIRtreshold = calibrateFrontIR();
  //digitalWrite(FRONTIRTRIGGERPIN, HIGH);
  //Serial.println(frontIRtreshold);

  digitalWrite(led, HIGH);
  button.waitForButton();
  delay(1000);
  digitalWrite(led, LOW);
}

// -------------------------- Loop
void loop() {

  // Sett modus
  
  if ((mode != STOP) && checkLine()) {
    mode = EDGE;
  } else if((mode != STOP) && checkUS('B')) {
    mode = DEFENCE;
  }

  // Kjøring av satt modus
  
  if(mode == ATTACK) {
    modeAttack();
  } else if(mode == DEFENCE) {
    modeDefence();
  } else if(mode == TRACK) {
    modeTrack();
  } else if(mode == STOP) {
    modeStop();
  } else if(mode == EDGE) {
    modeEdge();
  } else if(mode == BLUETOOTH) {
    modeBluetooth();
  } 
  
  //printSensorCheck();
  //Serial.println(checkFrontIR());
  btm.receive();
}



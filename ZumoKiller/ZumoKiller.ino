#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

ZumoMotors motors;

// -------------------------- Modes

int mode = 1;

#define STOP 0
#define ATTACK 1
#define DEFENCE 2
#define TRACK 3
#define EDGE 4
#define BLUETOOTH 5

// -------------------------- Sensors

// US
#define trigPin 6
#define echoCenterPin 5
#define echoLeftPin 4
#define echoRightPin 3

#define usSenTrigDistanse 3000
#define usSenTrigTimeout 4000

bool lastSeenLeft = true;


// IR

ZumoReflectanceSensorArray ir;
 

// -------------------------- Movement

#define motorMaxSpeed 200

int aks = 150;
int deseleration = 600;
int activeSpeed = 0;
int activeLeftSpeed = 0;
int activeRightSpeed = 0;
int turnSpeed = 0;

bool usL = false;
bool usC = false;
bool usR = false;

// -------------------------- Diverse

#define led 13
Pushbutton button(ZUMO_BUTTON);

// -------------------------- Setup
void setup() {
  // Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoCenterPin, INPUT);
  pinMode(echoLeftPin, INPUT);
  pinMode(echoRightPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(12, INPUT_PULLUP);

  ir.init();

  digitalWrite(led, HIGH);
  button.waitForButton();
  digitalWrite(led, LOW);
}

// -------------------------- Loop
void loop() {

  // Sett modus
  if(button.isPressed()) {
    mode = STOP;
  }

  // Kjøring av satt modus
  if(mode == ATTACK) {
    modeAttack();
  } else if(mode == DEFENCE) {
    modeDefence();
  } else if(mode == STOP) {
    modeStop();
  } else if(mode == EDGE) {
    modeEdge();
  } else if(mode == BLUETOOTH) {
    modeBluetooth();
  } 
  /*
  else {
    modeTrack();
  }
  */
  
}



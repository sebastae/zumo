#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>

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
#define echoBackPin 11

#define usSenTrigDistanse 3000
#define usSenTrigTimeout 4000
#define usSenTrigDefThreshold 1200

bool lastSeenLeft = true;


// IR

#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  2  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2

QTRSensorsAnalog ir((unsigned char[]) {0, 1, 2, 3, 4, 5}, 
NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int irVal[NUM_SENSORS];

// -------------------------- Movement

#define motorMaxSpeed 400
#define TURNTIME 300

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
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoCenterPin, INPUT);
  pinMode(echoLeftPin, INPUT);
  pinMode(echoRightPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(12, INPUT_PULLUP);

  digitalWrite(led, HIGH);
  button.waitForButton();
  digitalWrite(led, LOW);
}

// -------------------------- Loop
void loop() {

  // Sett modus
  if(button.isPressed()) {
    mode = STOP;
  } else if (checkLine()) {
    mode = EDGE;
  } else if(checkUS('B')) {
    mode = DEFENCE;
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
  printSensorCheck();
  
}



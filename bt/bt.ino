#include "BluetoothParameters.h"

#define txPin 3
#define rxPin 2

BluetoothParameters btParams = BluetoothParameters();
BluetoothManager btManager = BluetoothManager(&btParams, txPin, rxPin);


int a = 0;
String b = "";

int aPrev = 0;
String bPrev = "";

int setup_times = 0;
void setup() {
    Serial.begin(9600);
    
    btParams.add(&a, "a");
    btParams.add(&b, "b");
}

void loop() {
  btManager.receive();
  if(a!= aPrev || b != bPrev){
    Serial.print(a);
    Serial.print(" , ");
    Serial.println(b);
   aPrev = a;
   bPrev = b;
  }
  delay(500);
}

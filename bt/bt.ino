#include "BluetoothParameters.h"


#define txPin 1
#define rxPin 0

BluetoothParameters btParams = BluetoothParameters();
BluetoothManager btManager = BluetoothManager(&btParams, txPin, rxPin);


int a = 0;
String b = "";

int aPrev = 0;
String bPrev = "";

void setup() {
    //Serial.begin(9600);
    
    btParams.add(&a, "a");
    btParams.add(&b, "b");
}

void loop() {
  btManager.receive();

  if(aPrev != a || bPrev != b){
    /*Serial.print("a: ");
    Serial.println(a);
    Serial.print("b: ");
    Serial.println(b);*/

    aPrev = a;
    bPrev = b;
    
  }
  
}

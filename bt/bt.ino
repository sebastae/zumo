#include "BluetoothParameters.h"

BluetoothParameters btParams = BluetoothParameters();
BluetoothManager btManager = BluetoothManager(&btParams);


int a = 0;
String b = "";

int aPrev = 0;
String bPrev = "";
void setup() {
    Serial.begin(9600);
    btParams.bindBTManager(&btManager);
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
}

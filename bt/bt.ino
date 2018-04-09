#include "BluetoothParameters.h"

BluetoothParameters btParams = BluetoothParameters();
BluetoothManager btManager = BluetoothManager(&btParams, 2, 3);


int a = 0;
String b = "";

int aPrev = 0;
String bPrev = "";
void setup() {
    Serial.begin(9600);

    btManager.setup("G17_BT", "1234");
    
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

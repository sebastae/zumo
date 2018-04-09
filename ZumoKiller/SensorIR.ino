// Lingesensor under bilen

bool checkLine() {
  if(checkIR(0) > 9) {
    return true;
  }
  return false;
}

int checkIR(int sensorNR) {
  int totalValue = 0;
  for (int i = 0; i < irProbeTimes; i++) {
    analogRead(5);
    totalValue += analogRead(sensorNR);
  }
  return totalValue / irProbeTimes;
}

// Front sensor


bool checkFrontIR() {
  int valDark = 0;
  int valLight = 0;
  digitalWrite(FRONTIRTRIGGERPIN, LOW);
  delayMicroseconds(260);
  for (int i = 0; i < irProbeTimes; i++) {
    valDark += analogRead(3);
  }
  digitalWrite(FRONTIRTRIGGERPIN, HIGH);
  delayMicroseconds(260);
  for (int i = 0; i < irProbeTimes; i++) {
    valLight += analogRead(3);
  }
  valDark = valDark / irProbeTimes;
  valLight = valLight / irProbeTimes;

/*
  Serial.println();
  Serial.print(valDark);
  Serial.print(" - ");
  Serial.print(valLight);
  Serial.print(" - ");
  Serial.print(valLight - valDark);
  Serial.println();
*/
  
  if (valLight - valDark > frontIRchangeToTrigg) {
    return true;
  }
  return false;
}

/*
bool checkFrontIR() {
  int value = 0;
  for (int i = 0; i < irProbeTimes; i++) {
    value += analogRead(3);
  }
  value = value / irProbeTimes;
  if (value > frontIRtreshold + frontIRchangeToTrigg) {
    return true;
  }
  return false;
} */

int calibrateFrontIR() {
  int totalValue = 0;
  for (int i = 0; i < 20; i++) {
    totalValue += analogRead(3);
  }
  return totalValue / irProbeTimes;
}


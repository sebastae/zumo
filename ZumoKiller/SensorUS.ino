bool checkCenter(char sensorLocation) {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  if(sensorLocation == 'C') {
    duration = pulseIn(echoCenterPin, HIGH, usSenTrigTimeout);
  }
  if(sensorLocation == 'R') {
    duration = pulseIn(echoRightPin, HIGH, usSenTrigTimeout);
  }
  if(sensorLocation == 'L') {
    duration = pulseIn(echoLeftPin, HIGH, usSenTrigTimeout);
  }
  if(duration != 0 && duration < usSenTrigDistanse) {
    return true;
  }
  return false;
}

void printSensorCheck() { // Husk å 
  Serial.print(checkCenter('C'));
  Serial.print(" - ");
  Serial.print(checkCenter('L'));
  Serial.print(" - ");
  Serial.print(checkCenter('R'));
  Serial.println();
}

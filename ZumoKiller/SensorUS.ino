bool checkUS(char sensorLocation) {
  long duration;
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
  if(sensorLocation == 'B') {
    duration = pulseIn(echoBackPin, HIGH, usSenTrigTimeout);
  }
  
  if(duration != 0 && duration < usSenTrigDistanse) {
    return true;
  }
  return false;
}

int checkUSdistanse(char sensorLocation) {
  long duration;
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
  if(sensorLocation == 'B') {
    duration = pulseIn(echoBackPin, HIGH, usSenTrigTimeout);
  }
  return duration;
}

void printSensorCheck() { // Husk å 
  Serial.print(checkUS('C'));
  Serial.print(" - ");
  Serial.print(checkUS('L'));
  Serial.print(" - ");
  Serial.print(checkUS('R'));
  Serial.println();
}

void modeEdge() {  
  //Serial.println("SO EDGY");
  motors.setSpeeds(-motorMaxSpeed, -motorMaxSpeed);
  //delay(TURNTIME/2);
  delay(300);
  motors.setSpeeds(motorMaxSpeed, -motorMaxSpeed);
  delay(TURNTIME);
  mode = ATTACK;
}

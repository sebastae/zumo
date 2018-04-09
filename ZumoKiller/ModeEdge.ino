void modeEdge() {  
  //Serial.println("SO EDGY");
  motors.setSpeeds(-motorMaxSpeed, -motorMaxSpeed);
  delay(TURNTIME/2);
  motors.setSpeeds(motorMaxSpeed, -motorMaxSpeed);
  delay(TURNTIME);
  mode = ATTACK;
}

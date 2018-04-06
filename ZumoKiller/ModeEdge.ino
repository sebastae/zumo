void modeEdge() {  
  motors.setSpeeds(-motorMaxSpeed, -motorMaxSpeed);
  delay(300);
  motors.setSpeeds(motorMaxSpeed, -motorMaxSpeed);
  delay(500);
  mode = ATTACK;
}

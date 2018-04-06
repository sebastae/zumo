void modeAttack() { 
  //Serial.println("FREMAD"); 
  usC = checkUS('C');
  usL = checkUS('L');
  usR = checkUS('R');
  
  //if((usC && !(usL || usR)) || (usC && usL && usR)) {
  if((usC && usL && usR) || (usC && !usL && !usR)) {
    motors.setSpeeds(motorMaxSpeed, motorMaxSpeed);
  } 

  else if(usL && usC) {
    motors.setSpeeds(motorMaxSpeed/2, motorMaxSpeed);
    lastSeenLeft = true;
  } 
  else if(usR && usC) {
    motors.setSpeeds(motorMaxSpeed, motorMaxSpeed/2);
    lastSeenLeft = false;
  } 

  else if(usL && !usC) {
    motors.setSpeeds(0, motorMaxSpeed);
    lastSeenLeft = true;
  } 
  else if(usR && !usC) {
    motors.setSpeeds(motorMaxSpeed, 0);
    lastSeenLeft = false;
  } 
  else {
    if(lastSeenLeft) {
      motors.setSpeeds(-motorMaxSpeed/2, motorMaxSpeed/2); 
    } else {
      motors.setSpeeds(motorMaxSpeed/2, -motorMaxSpeed/2);
    }
  }
  
}

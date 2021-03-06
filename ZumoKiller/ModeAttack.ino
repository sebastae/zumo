void modeAttack() { 
  //Serial.println("FREMAD"); 
  usC = checkUS('C');
  usL = checkUS('L');
  usR = checkUS('R');
  
  //if((usC && !(usL || usR)) || (usC && usL && usR)) {
  if(checkFrontIR() || (usC && usL && usR) || (usC && !usL && !usR) || (!usC && usL && usR)) {
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
      motors.setSpeeds(-motorMaxTurnSpeed, motorMaxTurnSpeed); 
    } else {
      motors.setSpeeds(motorMaxTurnSpeed, -motorMaxTurnSpeed);
    }

    if (!counterOn) {
      counterOn = true;
      counter = countLength;
      //Serial.println("Counter on");
    }
    if(counterOn) {
      counter--;
      //Serial.println(counter);
    }
    if (counter <= 0) { 
      mode = TRACK;
      counterOn = false;
    }
  }
}

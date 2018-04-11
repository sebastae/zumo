void modeTrack() {  
  motors.setSpeeds(motorMaxSpeed, motorMaxSpeed/2);
  if (checkUS('L') || checkUS('L') || checkUS('L')) {
    mode = ATTACK;
  }
}

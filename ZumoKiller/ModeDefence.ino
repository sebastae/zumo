void modeDefence() {
  //Lang avstand
  if(checkUSdistance('B') >= usSenTrigDefThreshold){
    motors.setSpeeds(motorMaxSpeed, -motorMaxSpeed);
    delay(TURNTIME);
    mode = ATTACK;
  }

  //Kort avstand
  else if (checkUSdistance('B') < usSenTrigDefThreshold){
   motors.setSpeeds(-motorMaxSpeed, -motorMaxSpeed);  
  }

  else {
    motors.setSpeeds(-motorMaxSpeed, motorMaxSpeed);
    delay(TURNTIME);
    mode = ATTACK;
  }
}

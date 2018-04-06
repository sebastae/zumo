void modeDefence() {
   //Serial.println("DEFENSIVE MANEUVERS");
    //Lang avstand
    
    //if(checkUSdistance('B') > usSenTrigDefThreshold && checkUSdistance('B') > 0){
      //Serial.println("DEFENSIVE TURN");
      //Serial.println(checkUSdistance('B'));
      motors.setSpeeds(motorMaxSpeed, -motorMaxSpeed);
      delay(TURNTIME);
      mode = ATTACK;
    //}
  
    //Kort avstand
    /*
    else if (checkUSdistance('B') < usSenTrigDefThreshold && checkUSdistance('B') > 0){
     Serial.println("RYGGER");
     Serial.println(checkUSdistance('B'));
     motors.setSpeeds(-motorMaxSpeed, -motorMaxSpeed);
     delay(100);
     mode = ATTACK;
    }*/

/*    else {
      mode = ATTACK;
    }*/
}

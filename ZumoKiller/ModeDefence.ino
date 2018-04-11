//void modeDefence() {
   //Serial.println("DEFENSIVE MANEUVERS");
    //Lang avstand
    
    //if(checkUSdistance('B') > usSenTrigDefThreshold && checkUSdistance('B') > 0){
      //Serial.println("DEFENSIVE TURN");
      //Serial.println(checkUSdistance('B'));
//      motors.setSpeeds(motorMaxSpeed, -motorMaxSpeed);
//      delay(TURNTIME);
//      mode = ATTACK;
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
//}

void modeDefence() {
      motors.setSpeeds(motorMaxTurnSpeed, -motorMaxTurnSpeed);
      defTurn();
        // Står i rekursiv loop (slik at bilen snurrer rundt) til en av sensorene på fremsiden detekterer noe.
        // Går så ut av while loopen og setter i ATTACK modus.
        // Dette er så den automatisk stopper å snurre rundt når den ser den andre bilen, i stede for å sette en satt snu mengde.
      mode = ATTACK;
}

void defTurn() {
  if(checkLine()){
    return;
  }
  if (!checkUS('L') && !checkUS('L') && !checkUS('L')) {
    defTurn();
  }
  
}


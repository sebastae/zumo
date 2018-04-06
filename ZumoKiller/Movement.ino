void setNewSpeed(int targetSpeed, int acceleration) {
  if (activeSpeed < targetSpeed) {
    if (activeSpeed < 0 && targetSpeed >= 0) {
      for (activeSpeed; activeSpeed <= 0; activeSpeed++) {
        motors.setLeftSpeed(activeSpeed);
        motors.setRightSpeed(activeSpeed);
        delayMicroseconds(deseleration);
      }  
    }
    if (activeSpeed != targetSpeed) {
      for (activeSpeed; activeSpeed <= targetSpeed; activeSpeed++) {
        motors.setLeftSpeed(activeSpeed);
        motors.setRightSpeed(activeSpeed);
        delayMicroseconds(acceleration);
      }  
    }
  }

  if (activeSpeed > targetSpeed) {
    if (activeSpeed > 0 && targetSpeed <= 0) {
      for (activeSpeed; activeSpeed >= 0; activeSpeed--) {
        motors.setLeftSpeed(activeSpeed);
        motors.setRightSpeed(activeSpeed);
        delayMicroseconds(deseleration);
      } 
    }
    if (activeSpeed != targetSpeed) {
      for (activeSpeed; activeSpeed >= targetSpeed; activeSpeed--) {
        motors.setLeftSpeed(activeSpeed);
        motors.setRightSpeed(activeSpeed);
        delayMicroseconds(acceleration);
      }  
    }
  }
}

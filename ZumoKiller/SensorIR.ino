bool checkLine() {
  ir.read(irVal);
  if(irVal[0] < 9) {
    return true;
  }
  return false;
}


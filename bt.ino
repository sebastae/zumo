
template <struct T>
class BTParam{
  private:
  T* var;

  public:

  void set(T val){
    *var = val;
  }

  T get(){
    return *var;
  }
}

class BluetoothParameters{
  private:

  struct dtypes{
    int i;
    String s;
    boolean b;
    double d;
  }

  map<String, dtypes> paramMap;

  public:
  
  BluetoothParameters(){
      
  }

  
  
}


void setup() {
    
}

void loop() {

}

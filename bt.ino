#include<StandardCplusplus.h>
#include <map>


enum REQUEST_TYPE{
  GET,
  SET,
  GETALL
};

enum REQUEST_DTYPE{
  INT,
  STR,
  DBL
};

template <class T>
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
};

class BTRequest{

  private:
  REQUEST_TYPE method;
  REQUEST_DTYPE type;
  String varname;
  String value;

  public:

  BTRequest(String requestString){
    
  }
  
};

class BluetoothParameters{
  private:

  // TODO: Reduce into one map, use inheritance?

  std::map<String, BTParam<int>> intMap;
  std::map<String, BTParam<String>> stringMap;
  std::map<String, BTParam<double>> doubleMap;

  public:
  
  BluetoothParameters(){
      intMap = std::map<String, BTParam<int>>();
      stringMap = std::map<String, BTParam<String>>();
      doubleMap = std::map<String, BTParam<double>>();
  }

  void handleRequest(String request){
    
  }

  
  
};


void setup() {
    
}

void loop() {

}

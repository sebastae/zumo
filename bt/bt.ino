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
    switch(requestString[0]){
      case 'A':
        method = GETALL;
        break;
      case 'S':
        method = SET;
        break;
      case 'G':
        method = GET;
        break;
      default:
        method = GETALL;
        Serial.println(requestString[0] + " is not a recognized request type, defaulting to GETALL");
        break;
    };

    if(method == GETALL){
      return;
    } else{
      String reqStr = requestString.substring(1);
      String dtype = reqStr.substring(0,3);

      int colonPos = reqStr.indexOf(':');

      String varName = reqStr.substring(2, colonPos-3);
      String varVal = reqStr.substring(colonPos+1);

     varVal = varVal.substring(0, varVal.length());


     if(dtype == "INT"){
      type = INT;
     } else if(dtype == "DBL") {
      type = DBL;
     } else if(dtype == "STR"){
      type = STR;
     }


     varname = varName;
     value = varVal;
    }


  };
};

class BluetoothParameters{
  private:

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

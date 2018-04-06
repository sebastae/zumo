#include<StandardCplusplus.h>
#include <map>

// Comment our to turn off debugging
#ifndef BT_DEBUG
#define BT_DEBUG
#endif

#ifndef BTPRMS_H
#define BTPRMS_H

//////////////////////////////////////////////////////////////
//                 Constants and Enums                      //
//////////////////////////////////////////////////////////////


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

//////////////////////////////////////////////////////////////
//                 Forward Declarations                     //
//////////////////////////////////////////////////////////////

template<class T> class BTParam;
class BluetoothParameters;
class BTRequests;
class BluetoothParameters;


//////////////////////////////////////////////////////////////
//                 Class Declarations                       //
//////////////////////////////////////////////////////////////

template<class T>
class BTParam{
  private:
    T* var;
  public:
    BTParam(T* v);
    T get();
    void set(T val);
};

class BTRequest{
  private:
    REQUEST_TYPE method;
    REQUEST_DTYPE type;
    String varname;
    String value;
  public:
    BTRequest(String requestString);
    REQUEST_TYPE getMethod();
    REQUEST_DTYPE getType();
    String getName();
    String getValue();
};

class BluetoothManager{
  private:
    BluetoothParameters* btParams;
  public:
    BluetoothManager(BluetoothParameters* btParams);
    void receive();
    void send(String requestString);
};

class BluetoothParameters{
  private:
    std::map<String, BTParam<int>> intMap;
    std::map<String, BTParam<String>> stringMap;
    std::map<String, BTParam<double>> doubleMap;
    BluetoothManager* btMng;
  public:
    BluetoothParameters();
    void bindBTManager(BluetoothManager* mng);
    void handleRequest(String request);
};


//////////////////////////////////////////////////////////////
//                 Class Definitions                        //
//////////////////////////////////////////////////////////////


// BTParam

template<class T>
BTParam<T>::BTParam(T* v) : var{v}{};

template<class T>
T BTParam<T>::get(){
  return *(this->var);
};

template<class T>
void BTParam<T>::set(T val){
  *var = val;
};


// BTRequest

BTRequest::BTRequest(String requestString){
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

      #ifdef BT_DEBUG
        Serial.println(requestString[0] + " is not a recognized request type, defaulting to GETALL");
      #endif
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

   varVal = varVal.substring(0, varVal.length()-1);


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

REQUEST_TYPE BTRequest::getMethod(){
  return method;
};

REQUEST_DTYPE BTRequest::getType(){
  return type;
};

String BTRequest::getName(){
  return varname;
};

String BTRequest::getValue(){
  return value;
};


// BluetoothManager

BluetoothManager::BluetoothManager(BluetoothParameters* btParams) : btParams(btParams){};

void BluetoothManager::receive(){
  String requestString = "";
  while(Serial.available()){
    char receivedByte = Serial.read();
    requestString += receivedByte;
    if(receivedByte == ';'){
      this->btParams->handleRequest(requestString);
      requestString = "";
    };
  };
};

void BluetoothManager::send(String requestString){
  #ifdef BT_DEBUG
    Serial.println(requestString);
  #endif
};


// BluetoothParameters

BluetoothParameters::BluetoothParameters(){
  intMap = std::map<String, BTParam<int>>();
  stringMap = std::map<String, BTParam<String>>();
  doubleMap = std::map<String, BTParam<double>>();
};

void BluetoothParameters::bindBTManager(BluetoothManager* mng){
  this->btMng = mng;
}

void BluetoothParameters::handleRequest(String request){
  BTRequest req = BTRequest(request);

  if(req.getMethod() == GETALL){
    
  }
};

#endif

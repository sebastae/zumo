#include<StandardCplusplus.h>
#include <map>

// Comment our to turn off debugging
#ifndef BT_DEBUG
//#define BT_DEBUG
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
    String reqStr;
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
    void add(int* i, String name);
    void add(double* d, String name);
    void add(String* s, String name);
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
        Serial.println((char) requestString[0] + " is not a recognized request type, defaulting to GETALL");
      #endif
      break;
  };

  if(method == GETALL){
    return;
  } else{
    #ifdef BT_DEBUG
      Serial.println(requestString);
    #endif

    String tinfo = requestString.substring(0,4);
    String pinfo = requestString.substring(4);

    String dtype = tinfo.substring(1);

    int colonPos = pinfo.indexOf(':');

    String varName = pinfo.substring(0,colonPos);
    String varVal = pinfo.substring(colonPos+1);

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
  while(Serial.available()){
    char receivedByte = Serial.read();
    this->reqStr.concat(receivedByte);
    if(receivedByte == ';'){
      #ifdef BT_DEBUG
        Serial.println(this->reqStr);
      #endif
      this->btParams->handleRequest(this->reqStr);
      this->reqStr = "";
    };
  };
};

void BluetoothManager::send(String requestString){
  Serial.print(requestString);
};


// BluetoothParameters

BluetoothParameters::BluetoothParameters(){
  intMap = std::map<String, BTParam<int>>();
  stringMap = std::map<String, BTParam<String>>();
  doubleMap = std::map<String, BTParam<double>>();
};

void BluetoothParameters::add(int* i, String name){
  if(this->intMap.find(name) == this->intMap.end()){

    BTParam<int> prm = BTParam<int>(i);

    this->intMap.insert(std::make_pair(name, prm)); 
  }
};

void BluetoothParameters::add(double* d, String name){
  if(this->doubleMap.find(name) == this->doubleMap.end()){
    BTParam<double> prm = BTParam<double>(d);
    this->doubleMap.insert(std::make_pair(name, prm));
  }
};

void BluetoothParameters::add(String* s, String name){
  if(this->stringMap.find(name) == this->stringMap.end()){
    BTParam<String> prm = BTParam<String>(s);

    this->stringMap.insert(std::make_pair(name, prm));
    
  }
};

void BluetoothParameters::bindBTManager(BluetoothManager* mng){
  this->btMng = mng;
}

void BluetoothParameters::handleRequest(String request){
  BTRequest req = BTRequest(request);

  if(req.getMethod() == GETALL){
    #ifdef BT_DEBUG
      Serial.println("GETALL");    
    #endif

    String str;

    auto intIter = this->intMap.begin();
    while(intIter != this->intMap.end()){
      str += "GINT";
      str +=  intIter->first;
      str += ":";
      str += String(intIter->second.get());
      str += ";";

      intIter++;
    }

    auto dblIter = this->doubleMap.begin();
    while(dblIter != this->doubleMap.end()){
      str += "GDBL";
      str += dblIter->first;
      str += ":";
      str += String(dblIter->second.get());
      str += ";";

      dblIter++;
    }

    auto strIter = this->stringMap.begin();
    while(strIter != this->stringMap.end()){
      str += "GSTR";
      str += strIter->first;
      str += ":";
      str += strIter->second.get();
      str += ";";

      strIter++;
    }

    this->btMng->send(str);
        
  } else if(req.getMethod() == GET){
    #ifdef BT_DEBUG
      Serial.println("GET");
    #endif

    String sStr = "G";
    String val = "";

    if(req.getType() == INT){
      sStr += "INT";
      val = this->intMap.find(req.getName()) != this->intMap.end() ? String(this->intMap.find(req.getName())->second.get()) : "";
    } else if (req.getType() == DBL){
      sStr += "DBL";
      val = this->doubleMap.find(req.getName()) != this->doubleMap.end() ? String(this->doubleMap.find(req.getName())->second.get()) : "";
    } else if (req.getType() == STR){
      sStr += "STR";
      val = this->stringMap.find(req.getName()) != this->stringMap.end() ? this->stringMap.find(req.getName())->second.get() : "";
    }

    sStr += req.getName();
    sStr += ":";
    sStr += val;
    sStr += ";";

    this->btMng->send(sStr);
    
  } else if(req.getMethod() == SET){
    #ifdef BT_DEBUG
      Serial.println("SET");
    #endif
    if(req.getType() == INT){
      auto search = this->intMap.find(req.getName());

      if(search != this->intMap.end()){
        search->second.set(req.getValue().toInt());
      } else {
        #ifdef BT_DEBUG
          Serial.println("Key \"" + req.getName() + "\" was not found in the int map");
        #endif
      }
    } else if(req.getType() == DBL){
      auto search = this->doubleMap.find(req.getName());

      if(search != this->doubleMap.end()){
        search->second.set(req.getValue().toDouble());
      } else {
        #ifdef BT_DEBUG
          Serial.println("Key \"" + req.getName() + "\" was not found in the double map");
        #endif
      }
    } else if(req.getType() == STR){
      auto search = this->stringMap.find(req.getName());

      if(search != this->stringMap.end()){
        search->second.set(req.getValue());
      } else {
        #ifdef BT_DEBUG
          Serial.println("Key \"" + req.getName() + "\" was not found in the string map");
        #endif
      }
    } else {
      #ifdef BT_DEBUG
        Serial.println("Datatype not supported");
      #endif
    }
  };
};

#endif

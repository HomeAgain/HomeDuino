/*
* HomeAgain - Main Home Duino
*
*
*
*
*/

//#define MOISTURE_SENSOR
//#define MOISTURE_PIN 1

#define TEMPERATURE_SENSOR
#define TEMPERATURE_PIN 0

//#define PRESENCE_SENSOR
//#define PRESENCE_PIN 2

#ifdef TEMPERATURE_SENSOR
  int temperatureAnalog ;
  float temperatureValue;
  int temperatureB=3975;                  //B value of the thermistor
  float temperatureResistance;
#endif

#ifdef MOISTURE_SENSOR
 int moistureAnalog;
#endif

#ifdef PRESENCE_SENSOR
  int presence;
  int lastPresence;
  boolean presenceInit = false;
#endif


void setup(){
  Serial.begin(9600);

  #ifdef MOISTURE_SENSOR
//  Serial.println("Initializing moisture sensor");
  pinMode(MOISTURE_PIN, INPUT);
  #endif
  
  #ifdef TEMPERATURE_SENSOR
//  Serial.println("Initializing temperature sensor");
  pinMode(TEMPERATURE_PIN, INPUT);
  #endif
  
  #ifdef PRESENCE_SENSOR
//  Serial.println("Initializing presence sensor");
  pinMode(PRESENCE_PIN, INPUT);
  #endif PRESENCE_SENSOR
  
  pinMode(13, OUTPUT);
  
  
}

void loop(){
  digitalWrite(13, HIGH);
  delay(1000);
  #ifdef TEMPERATURE_SENSOR
  temperatureAnalog=analogRead(TEMPERATURE_PIN);
  temperatureResistance=(float)(1023-temperatureAnalog)*10000/temperatureAnalog; //get the resistance of the sensor;
  temperatureValue=1/(log(temperatureResistance/10000)/temperatureB+1/298.15)-273.15;//convert to temperature via datasheet ;
  send("TEMP", "temperature.celsius", temperatureValue);
//  Serial.print("temperature=temperature.celsius=");
//  Serial.println(temperatureValue);
  #endif
  
  #ifdef MOISTURE_SENSOR
  moistureAnalog=analogRead(MOISTURE_PIN);
  send("MOISTURE", "moisture", moistureAnalog);
//  Serial.print("moisture=moisture=");
//  Serial.println(moistureAnalog);
  #endif
  
  #ifdef PRESENCE_SENSOR

  presence = digitalRead(PRESENCE_PIN);
  if(!presenceInit){
    presenceInit = true;
//    Serial.print("presence=presence=");
//    Serial.println(presence);
    send("PRESENCE", "presence", presence);
    lastPresence=presence;
  }
  else if(presence != lastPresence){
//    Serial.print("presence=presence=");
//    Serial.println(presence);
    send("PRESENCE", "presence", presence);
  }
  #endif PRESENCE_SENSOR  
  digitalWrite(13, LOW);
  delay(1000);
  
}

void send(String id, String unit, int value){
  Serial.println(id + "=" + unit + "=" + String(value, DEC));
}

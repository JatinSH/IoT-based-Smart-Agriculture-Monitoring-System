#include <SoftwareSerial.h>
#include <dht.h>

SoftwareSerial s(5,6);

dht DHT;



#define Humidity_sensor_pin 7

int Water_sensor_pin = A1;

int soil_sensor_pin = A0;

int water_val = 0;

int soil_output_value ;

String waterpump_status;

String to_nodemcu;

void setup() {

   s.begin(9600);

   Serial.begin(9600);

   pinMode(LED_BUILTIN, OUTPUT);        //built in led of arduino serves as the water pump

   pinMode(Humidity_sensor_pin, INPUT);

   pinMode(soil_sensor_pin, INPUT);

   pinMode(Water_sensor_pin, INPUT); 

   Serial.println("Reading From the Sensors ...");

   delay(2000);

   }

void loop() {

  //Reading Humidity and Temperature Sensor data

       int chk = DHT.read11(Humidity_sensor_pin);
       
       Serial.print("Temperature in degree Celsius= ");
        
       Serial.println(DHT.temperature);
       
       Serial.print("Humidity = ");
       
       Serial.println(DHT.humidity);

   //Reading Soil Moisture Sensor Data

       soil_output_value= analogRead(soil_sensor_pin);
    
       soil_output_value = map(soil_output_value,1050,550,0,100);
    
       Serial.print("Soil Mositure : ");
    
       Serial.print(soil_output_value);
    
       Serial.println("%");

  //Reading Water Level Sensor Data

      water_val = analogRead(Water_sensor_pin);
      
      Serial.print("Water level: ");
        
      Serial.println(water_val);

  //If the water level is above a certain level, then turn the pump off, otherwise turn it on
  
      if(water_val > 100)
       {
          digitalWrite(LED_BUILTIN, LOW);
          waterpump_status = String("OFF");
       }
       else if(water_val<100){

          digitalWrite(LED_BUILTIN, HIGH);
          waterpump_status = String("ON");
       }

       Serial.print("Water Pump Status: ");
       Serial.println(waterpump_status);

       Serial.println("\n\t...Waiting ...");
  //Creting String to be sent to NodeMCU

      to_nodemcu = String("Temperature : ") + String(DHT.temperature) + String(" Humidity : ") + String(DHT.humidity) + String(" Soil Moisture : ") + String(soil_output_value) + String(" Water Level : ") + String(water_val) + String("Water Pump Status : ") + waterpump_status; 
  
  //Sending data to NodeMCU

      if(s.available()>0)
      {
        
          s.print(to_nodemcu);        
      }

   delay(3000);

   }

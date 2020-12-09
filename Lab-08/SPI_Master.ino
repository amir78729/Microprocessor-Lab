//MASTER
#include <SPI.h>
#define ss1 49
#define ss2 48
#define PIN_TEMPRETURE A0
#define PIN_LIGHT A1

String tempreture_value ;
String light_value;

void transferStringToSlave(int port){
  
    // tempreture or light...
    // what do we want to transfer?...
    bool is_temp;
    if (port == ss1){
      is_temp = true;
      Serial.print("TEMPRETURE: ");
    }
    else if (port == ss2) {
      is_temp = false;
      Serial.print("LIGHT:      ");
    }
    else return;
    
    // activation of the slave:
    digitalWrite(port,LOW);
    
    // sending the data byte-to-byte:
    if (is_temp ){
      for (int i = 0 ; i < sizeof tempreture_value ; i++ ){
        SPI.transfer((char)tempreture_value[i]);
        Serial.print(tempreture_value[i]);  
        delay(1);
      }
    }else{
      for (int i = 0 ; i < sizeof light_value ; i++ ){
        SPI.transfer(light_value[i]);
        Serial.print(light_value[i]);  
        delay(1);
      }
    }

    // sending '\r' → end of the transmition
    SPI.transfer('\r');
    
    // deactivation of the slave:
    digitalWrite(port,HIGH); 

    // go to the next line
    Serial.println();
}

void setup()
  {
    pinMode(PIN_LIGHT, INPUT);
    pinMode(PIN_TEMPRETURE, INPUT);
    pinMode(ss1,OUTPUT);
    pinMode(ss2,OUTPUT);
    Serial.begin(9600);

    // active-low slave selects
    digitalWrite(ss1,HIGH);
    digitalWrite(ss2,HIGH);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    delay(100);
    Serial.println("< MASTER >");
   }

void loop(){
  
  // get analog values from the outside
  int lght = analogRead(PIN_LIGHT);
  int tmp = analogRead(PIN_TEMPRETURE);

  // map inputs into percentages
  lght = map(lght, 0, 1023, 0, 100);
  tmp = map(tmp, 0, 1023, -55, 150);

  // convert them into Strings
  light_value = (String)lght + '%';
  tempreture_value = (String)tmp + "c";
  
  transferStringToSlave(ss1);   
  delay(500);
  transferStringToSlave(ss2);   
  delay(500);

  Serial.println("---------------");
}

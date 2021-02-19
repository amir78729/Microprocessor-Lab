/*
  Microprocessor and Assembly Language lab
  Winter 1399
  Amirhossein Alibakhshi (9731096)
  Final Project
*/

#include "bitmap7x11.h"
//                     OUTPUT_1  OUTPUT_2  OUTPUT_3  OUTPUT_4  OUTPUT_5  OUTPUT_6  OUTPUT_7
#define OUTPUT_1 21 //    x         -         -         -         -         -         - 
#define OUTPUT_2 20 //    -         x         -         -         -         -         - 
#define OUTPUT_3 19 //    -         -         x         -         -         -         - 
#define OUTPUT_4 18 //    -         -         -         x         -         -         - 
#define OUTPUT_5 17 //    -         -         -         -         x         -         - 
#define OUTPUT_6 16 //    -         -         -         -         -         x         - 
#define OUTPUT_7 15 //    -         -         -         -         -         -         x 
#define OUTPUT_BUZZER 14

String input_string ;
int ports[7] = {OUTPUT_1, OUTPUT_2, OUTPUT_3, OUTPUT_4, OUTPUT_5, OUTPUT_6, OUTPUT_7};

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  for (int i = 0; i < 7; i++)
    pinMode(ports[i], OUTPUT);
  pinMode(OUTPUT_BUZZER, OUTPUT);
  Serial.setTimeout(2000);
}

void loop() {
  if (Serial.available() > 0) {
    input_string = Serial.readStringUntil('\n'); // read the incoming String:
    Serial.println("> USER INPUT: " + input_string);
    buzz_it(2);
    for (int i = 0; i < input_string.length(); i++){
      char character = input_string[i];
      int ascii = int(character);
      if (ascii - 33 >= 0){
        Serial.print(character);
        Serial.println(" (" + String(ascii) + ") :");
        activate_leds(ascii - 33); // because in "bitmap7x11" the first 33 ascii characters are not implemented
        Serial.println("-------");
      }
      
    }
    // clear the LEDs for the last line
    buzz_it(3);
    for (int j = 6; j >= 0 ; j--)
      digitalWrite(ports[j], LOW);
  }
}

// sending a character to the LEDs
void activate_leds(int index){
  for (int i = 10; i >= 0 ; i--){
    for (int j = 0; j < 7 ; j++){
      if (bitmap[index][7 * i + j] == 0){ // the LED is going to be deactive
        digitalWrite(ports[j], LOW);
        Serial.print(" ");  
      }else{
        digitalWrite(ports[j], HIGH); // the LED is going to be active
        Serial.print("*");
      }
    } // inner for loop
    Serial.println();
    delay(500); // waiting 0.5 s for showing the next row on the LEDs
  } // outer for loop
}

void buzz_it(int n){
  for (int j = 0; j < n ; j++){
    digitalWrite(OUTPUT_BUZZER, HIGH);
    delay(100);
    digitalWrite(OUTPUT_BUZZER, LOW);
    delay(100);
  }
}

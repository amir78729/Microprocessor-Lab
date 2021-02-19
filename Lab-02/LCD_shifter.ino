/*
  Microprocessor and Assembly Language lab
  Fall 1399
  Amirhossein Alibakhshi (9731096)
  Negin Hajisobhani      (9731078)
  Lab #2

  The circuit:
 LCD RS pin to digital pin 12
 LCD Enable pin to digital pin 11
 LCD D4 pin to digital pin 5
 LCD D5 pin to digital pin 4
 LCD D6 pin to digital pin 3
 LCD D7 pin to digital pin 2
 LCD R/W pin to ground
 LCD VSS pin to ground
 LCD VCC pin to 5V
 10K resistor:
 ends to +5V and ground
** wiper to LCD VO pin (pin 3)
*/

#include <LiquidCrystal.h>


#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
#define DELAY_PERIOD 500

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int btn1 = 1;
int btn2 = 1;
int btn3 = 1;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Negin/Amir");

  // initializing buttons
  pinMode(8 , INPUT);
  pinMode(9 , INPUT);
  pinMode(10, INPUT);
}

void loop() {
  btn1 = digitalRead(8);
  btn2 = digitalRead(9);
  btn3 = digitalRead(10);
  if (btn3 == LOW) { // clear screen
    lcd.clear();
    delay(DELAY_PERIOD);
    
  }else if (btn2 == LOW){ // shift left
    lcd.scrollDisplayLeft();
    delay(DELAY_PERIOD);
    
  }else if (btn1 == LOW){ // shift right    
    lcd.scrollDisplayRight();
    delay(DELAY_PERIOD);   
  }
}

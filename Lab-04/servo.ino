/*
  Microprocessor and Assembly Language lab
  Fall 1399
  Amirhossein Alibakhshi (9731096)
  Lab #4
*/
// importing libraries
#include <LiquidCrystal.h> 
#include <Keypad.h> 
#include <Servo.h>

#define RS 16
#define EN 17
#define D4 18
#define D5 19
#define D6 20
#define D7 21
#define DELAY_PERIOD 500
 
const byte ROWS = 4; // Four rows
const byte COLS = 4; //Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'7','8','9','D'},
  {'4','5','6','C'},
  {'1','2','3','B'},
  {'R','0','=','A'}
};
byte rowPins[ROWS] = { 7, 6, 5, 4 }; // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 3, 2, 1, 0 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.

//creating component objects
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
Servo myservo; 

int degree;
String degree_string;
void setup() {
  myservo.attach(9 , 1000 , 2000);  
  degree = 0;
  degree_string = "";
  lcd.begin(16, 2); //We are using a 16*2 LCD display
  lcd.print("A.Alibakhshi"); //Display a intro message
  lcd.setCursor(0, 1);   // set the cursor to column 0, line 1
  lcd.print("Lab4"); //Display a intro message 
  delay(DELAY_PERIOD * 2); //Wait for display to show info
  lcd.clear(); //Then clean it
  lcd.setCursor(0, 0);   // set the cursor to column 0, line 1
}
 
void loop() {  
  lcd.print("> "); //Display a intro message 
  char a = kpd.waitForKey();
  while (a != '='){
    lcd.print(a); //Display a intro message 
    degree_string += a;
    a = kpd.waitForKey();
  }
  degree = degree_string.toInt();
  degree = degree % 360;
  lcd.clear(); //Then clean it
  lcd.setCursor(0, 1);   // set the cursor to column 0, line 1
  lcd.print("currentDeg.: "); //Display a intro message 
  lcd.print(degree); //Display a intro message
  degree_string = "";
  degree = map(degree, 0 , 360, 0 , 180);
//  myservo.write(degree / 2 ); // sets the servo position according to the scaled degreeue
  myservo.write(degree ); // sets the servo position according to the scaled degreeue
  lcd.setCursor(0, 0);   // set the cursor to column 0, line 1
  delay(DELAY_PERIOD);
}

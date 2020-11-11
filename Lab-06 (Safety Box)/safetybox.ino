/*
  Microprocessor and Assembly Language lab
  Fall 1399
  Amirhossein Alibakhshi (9731096)
  Lab #6
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
#define BUZZER_PORT 10
#define SERVO_PORT 9
#define LED_PORT 11
 
const byte ROWS = 4; // Four rows
const byte COLS = 4; //Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'R','0','=','+'}
};
byte rowPins[ROWS] = { 7, 6, 5, 4 }; // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 3, 2, 1, 0 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.

//creating component objects
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
Servo myservo; 

int pasword; // input password
String pasword_string;
bool is_open = false; // corrent state of the door
char key;
int timer = 0; // the time left 
int mil; //
int correct_password = 1234; // initial password
int waiting_period = 15 ;// initial waiting period in seconds


void setup() {
  myservo.attach(SERVO_PORT , 1000 , 2000);  
  myservo.write(0); // initially closed
  pasword = 0;
  pasword_string = "";
  lcd.begin(16, 2); 
  lcd.print("  A.Alibakhshi  "); 
  lcd.setCursor(0, 1);  
  lcd.print("   SAFETY BOX   ");
  delay(DELAY_PERIOD * 2); 
  lcd.clear(); 
  lcd.setCursor(0, 0);
  pinMode(BUZZER_PORT, OUTPUT);
  pinMode(LED_PORT, OUTPUT);
  digitalWrite(LED_PORT, HIGH);
  print_status();
}
 
void loop() { 
  lcd.setCursor(0, 0); 
  lcd.print("> ");
  key = kpd.getKey(); // Storing pressed key value in a char
  if (key!=NO_KEY) // If a button was pressed...
    if (key != '='){
      if(key == '+'){ // change the password
        close_it();
        buzz(1);
        is_open = false;
        lcd.clear(); 
        lcd.setCursor(0, 0); 
        lcd.print("CURRENT PASS:");
        lcd.setCursor(0, 1);
        lcd.print("> ");
        pasword_string = "";
        char a = kpd.waitForKey();
        while (a != '='){
          lcd.print("*"); //Display a intro message 
          pasword_string += a;
          a = kpd.waitForKey();
        }
        pasword = pasword_string.toInt();
        if (pasword == correct_password) {
          lcd.clear(); 
          lcd.setCursor(0, 0); 
          lcd.print("NEW PASS:");
          lcd.setCursor(0, 1);
          lcd.print("> ");
          pasword_string = "";
          char a = kpd.waitForKey();
          while (a != '='){
            lcd.print("*"); //Display a intro message 
            pasword_string += a;
            a = kpd.waitForKey();
          }
          correct_password = pasword_string.toInt();
          lcd.clear(); 
          lcd.setCursor(0, 0); 
          lcd.print("  PASS CHANGED  ");
          lcd.setCursor(0, 1);
          lcd.print("  SUCCESSFULLY  ");
          pasword_string = "";
          delay(DELAY_PERIOD * 4);
          lcd.clear();
          print_status();
          lcd.setCursor(0, 0);
        }else {
          lcd.clear(); 
          lcd.setCursor(0, 0); 
          lcd.print("   WRONG PASS   ");
          lcd.setCursor(0, 1);
          lcd.print("   TRY AGAIN!   ");
          pasword_string = "";
          delay(DELAY_PERIOD * 4);
          lcd.clear();
          print_status();
          lcd.setCursor(0, 0);
        }
      ////////////////////////////////////////////////////////////////////////////
      }else if(key == '-'){ // change the waiting period
        close_it();
        buzz(1);
        is_open = false;
        lcd.clear(); 
        lcd.setCursor(0, 0); 
        lcd.print("CURRENT PASS:");
        lcd.setCursor(0, 1);
        lcd.print("> ");
        pasword_string = "";
        char a = kpd.waitForKey();
        while (a != '='){
          lcd.print("*"); //Display a intro message 
          pasword_string += a;
          a = kpd.waitForKey();
        }
        pasword = pasword_string.toInt();
        if (pasword == correct_password) {
          lcd.clear(); 
          lcd.setCursor(0, 0); 
          lcd.print("NEW TIME PERIOD:");
          lcd.setCursor(0, 1);
          lcd.print("> ");
          pasword_string = "";
          char a = kpd.waitForKey();
          while (a != '='){
            lcd.print(a); //Display a intro message 
            pasword_string += a;
            a = kpd.waitForKey();
          }
          waiting_period = pasword_string.toInt();
          lcd.clear(); 
          lcd.setCursor(0, 0); 
          lcd.print(" TIMER CHANGED  ");
          lcd.setCursor(0, 1);
          lcd.print("  SUCCESSFULLY  ");
          pasword_string = "";
          delay(DELAY_PERIOD * 4);
          lcd.clear();
          print_status();
          lcd.setCursor(0, 0);
        }else {
          lcd.clear(); 
          lcd.setCursor(0, 0); 
          lcd.print("   WRONG PASS   ");
          lcd.setCursor(0, 1);
          lcd.print("   TRY AGAIN!   ");
          pasword_string = "";
          delay(DELAY_PERIOD * 4);
          lcd.clear();
          print_status();
          lcd.setCursor(0, 0);
        }
      ////////////////////////////////////////////////////////////////////////////
      }else{
        pasword_string += key;
        for (int i = 0; i < pasword_string.length() ; i++)
          lcd.print("*");
      }   
    ////////////////////////////////////////////////////////////////////////////
    }else{ // The password has been entered completely.
      pasword = pasword_string.toInt();
      if (pasword == correct_password){ // The Password was correct!
        open_it();
        if (!is_open)
          buzz(2);
        is_open = true;
      }else{ // The Password was not correct!
        close_it();
        if (is_open)
          buzz(3);
        is_open = false;
      }
      pasword_string = "";
      lcd.clear();
      print_status();
    } 
  if(is_open){ // the timer is activated
    delay(100);
    mil++;
    if (mil % 10 == 0){
      timer -= 1;
      lcd.setCursor(7, 1);
      lcd.print("       ");
      lcd.setCursor(7, 1);
      lcd.print(timer); 
      lcd.print("s"); 
    }
    lcd.setCursor(7, 1);
    lcd.print("       ");
    lcd.setCursor(7, 1);
    lcd.print(timer); 
    lcd.print("s");    
    if (timer < 0){ // time is up!
      lcd.setCursor(7, 1);
      lcd.print("TIMEs UP");
      close_it();
      buzz(3);
      is_open = false;
      delay(500);
      lcd.clear();
      print_status();
    }
    lcd.setCursor(0, 0);
  }
}

void open_it(){
  digitalWrite(LED_PORT, LOW);
  myservo.write(90);
  timer += waiting_period;
  mil = 0;
}

void close_it(){
  digitalWrite(LED_PORT, HIGH);
  myservo.write(0); 
  timer = 0;
  pasword_string = "";
}

void buzz(int repeat){
  for(int i = 0; i < repeat; i++){
    digitalWrite(BUZZER_PORT, HIGH);
    delay(100);
    digitalWrite(BUZZER_PORT, LOW);
    delay(100);
  }
}

void print_status(){
  lcd.setCursor(0, 1);
  if (is_open)
    lcd.print("OPENED ");
  else
    lcd.print("CLOSED "); 
}

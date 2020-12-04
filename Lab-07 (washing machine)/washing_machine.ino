#include <LiquidCrystal.h> 
#include <Keypad.h> 
#include <Wire.h>

#define RS 14
#define EN 15
#define D4 16
#define D5 17
#define D6 18
#define D7 19
#define LED1 25
#define LED2 24
#define LED3 23
#define LED4 22
#define DELAY_PERIOD 500
#define MEMORY_ADDRESS 0b1010000
 
const byte ROWS = 4; // Four rows
const byte COLS = 4; //Four columns
 
// Define the Keymap
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'n','0','=','+'}
};
 
byte rowPins[ROWS] = { 7, 6, 5, 4 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 3, 2, 1, 0 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.
 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad
 
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

String step_names[5]={"PREWASH","DETERGENT WASH","WATER WASH","DRYING","FINISH"};
int mode;
int LED[4]={LED1, LED2, LED3, LED4};

void turn_off_LEDs(){
  for (int i = 0 ; i < 4 ; i++)
    digitalWrite(LED[i],LOW);
}


// write "Size" bytes on the memory from "mem_address"
void memory_write(byte mem_address, byte* data, byte Size){ 
  for (int i = 0 ; i < Size ; i++){
    Wire.beginTransmission(MEMORY_ADDRESS);
    Wire.write(mem_address + i);
    Wire.write(data[i]);
    Wire.endTransmission();
    delay(200);
  }
}

// Read "Size" bytes from the memory from "mem_address"
void memory_read(byte mem_address, byte* data, byte Size){ 
  for (int i = 0 ; i < Size ; i++){
    Wire.beginTransmission(MEMORY_ADDRESS);
    Wire.write(mem_address + i);
    Wire.endTransmission();
    Wire.requestFrom(MEMORY_ADDRESS, Size);
    data[i] = Wire.read();
  }
}

byte read_byte(byte address){
  Wire.beginTransmission(MEMORY_ADDRESS); 
  Wire.write(address);
  Wire.endTransmission(); 
  Wire.requestFrom(MEMORY_ADDRESS,1);
  byte num = 0;
  num = Wire.read();
  return num;
}

void write_byte(byte address,byte num){
  Wire.beginTransmission(MEMORY_ADDRESS); 
  Wire.write(address);
  Wire.write(num);
  Wire.endTransmission(); 
  delay(200);
}

void enter_mode_settings(byte *data){
  byte index=0;
  while(true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Settings:");
    lcd.setCursor(0,1);
    switch (index){
      case 0:
        lcd.print("PreWash:");
        break;
      case 1:
        lcd.print("DetergentW.:");
        break;
      case 2:
        lcd.print("WaterW.:");
        break;
      case 3:
        lcd.print("Drying:");
        break;
      case 4:
        lcd.print("Press +");
        break;
    }
    lcd.setCursor(0,2);
    char key;
    key = keypad.waitForKey();
    lcd.print(key);
    lcd.setCursor(0,3);
    lcd.print("...");
    delay(1000);    
    data[index]= key - 48;
    index++;
    if (index != 4){
        continue;
    }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PreWash:");
        lcd.print(data[0]);
        lcd.setCursor(0,1);
        lcd.print("DetergentW.:");
        lcd.print(data[1]);
        lcd.setCursor(0,2);
        lcd.print("WaterW.:");
        lcd.print(data[2]);
        lcd.setCursor(0,3);
        lcd.print("Drying:");
        lcd.print(data[3]);
        char tmp = keypad.waitForKey();
      break;
    }
  }
}

void get_info(){
  byte num = read_byte(99);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" # of modes : ");
  lcd.setCursor(0,1);
  lcd.print("       ");
  lcd.print(num);  
  lcd.setCursor(0,3);
  lcd.print(" press any key. ");
  keypad.waitForKey();
}

void wash_time(byte Time,byte step_num){
  Time++;
  lcd.clear();
  digitalWrite(LED[step_num],HIGH);
  unsigned long currentMillis =0;
  unsigned long previousMillis = 0;
  lcd.setCursor(0,0);
  lcd.print(step_names[step_num]);
  int i = Time;
  while(i > 0){
    currentMillis = millis();
     if(currentMillis - previousMillis >= 1000) {
        previousMillis = currentMillis;
        i=i-1;
        lcd.setCursor(0,1);
        lcd.print(i);
      }
    char skey;
    skey = keypad.getKey();
    if(skey=='+'){
      write_byte(98,step_num); // save current step at 98
    }
  }
  // digitalWrite(LED[step_num],LOW);
}

void wash_mode(byte *data){
  for (int Step = 0; Step < 4; Step++){
    lcd.setCursor(0,0);
    lcd.print(step_names[Step]);
    wash_time(data[Step], Step);
  }
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("    finished    ");
  lcd.setCursor(0,2);
  lcd.print(" press any key. ");
  Serial.println(step_names[4]);
  for(int i=0;i<4;i++){
    digitalWrite(LED[i],HIGH);
  }
  write_byte(98,0); // current step (98) is ZERO
  keypad.waitForKey();//enter any key
  turn_off_LEDs();
}
///////////////////////////////
void setup() {
  lcd.begin(16, 4); 
  lcd.setCursor(0, 1);  
  lcd.print("  A.Alibakhshi  "); 
  lcd.setCursor(0, 2);  
  lcd.print(" WashingMachine ");
  delay(DELAY_PERIOD * 3); 
  lcd.clear(); 
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT); 
  
  Wire.begin();
  Serial.begin(9600);

  mode=0;//set mode to default
}


void loop() {
  byte myData[4];
  byte chosen_mode[4]; // each mode: 4 bytes
  //menu
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("n:RESET,x:INFO");
  lcd.setCursor(0,1);
  lcd.print("+:ADD M.");
  lcd.setCursor(0,2);
  lcd.print("/:SELECT M.");
  lcd.setCursor(0,3);
  lcd.print("-:DEFAULT WASH");
  char key;
  key=keypad.waitForKey();
  
  if(key=='n'){ // reset everything to default
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("     SET TO     ");
    lcd.setCursor(0,2);
    lcd.print("    DEFAULT!    ");
    for(int i = 0; i < 4 ; i++){
      myData[i] = i + 1;
    }
    memory_write(100,myData,4);
    write_byte(99,1); // number of modes: 1 (only the DEFAULT mode from 100 to 104)
    memory_read(100,myData,4);

    
  }else if(key=='+'){ // ADD MODE
    byte num = read_byte(99); // how many modes do we have?!
    enter_mode_settings(myData);
    memory_write(100+(4*num),myData,4); // write the new mode on memory
    write_byte(99,num+1); // update the number of modes

    
  }else if(key=='/'){ // SELECT MODE
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  SELECT  MODE  ");
    lcd.setCursor(0,1);
    byte num = read_byte(99);
    lcd.print("  # modes =");
    lcd.print(num);
    key=keypad.waitForKey();
    int mode_number_modified = 10;
    if(key-48<=num){
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("/ : WASH");
      lcd.setCursor(0,2);
      lcd.print("x : CHANGE");
      mode_number_modified = key - 49;
      memset(chosen_mode,0,4);
      memory_read(100+(4*mode_number_modified),chosen_mode,4);
      key=keypad.waitForKey();
      if(key=='/'){// wash it!
        wash_mode(chosen_mode);
      }else if(key == '*'){//change 
        byte data[4];
        memset(data,0,4);
        lcd.clear();
        lcd.print("change mode");
        enter_mode_settings(data);
        memory_write(100+(4 * mode_number_modified),data,4);
      }else{
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("   PLEASE TRY   ");
        lcd.setCursor(0,2);
        lcd.print("     AGAIN!     ");
        delay(1000);
      }
    }

    
  }else if(key=='-'){// DEFAULT WASH
      byte default_wash[4];
      memory_read(100,default_wash,4); //read from 100 to 104
      wash_mode(default_wash);
      
  }else if(key=='*'){// get info
      get_info();
    

          
  }else{// bad input
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("   PLEASE TRY   ");
      lcd.setCursor(0,2);
      lcd.print("     AGAIN!     ");
      delay(1000);
  } 
}

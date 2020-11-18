/*
  Microprocessor and Assembly Language lab
  Fall 1399
  Amirhossein Alibakhshi (9731096)
  Lab #6 (Yaghoob Barghi)
*/
// importing libraries
#include <LiquidCrystal.h> 
#include <Keypad.h> 
#include <Servo.h>
#include <MenuBackend.h>


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

#define HOTDOG        13
#define HAMBURGER     12
#define CHEESEBURGER  11
#define MEAT_HAM      10
#define CHICKEN_HAM   9
#define OLOVIYEH      8
#define NESCAFE       7
#define COFFEE        6
#define TEA           5
#define CHERRY_JUICE  4
#define ORANGE_JUICE  3
#define APPLE_JUICE   2

 
const byte ROWS = 4; // Four rows
const byte COLS = 4; //Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'R','0','=','+'}
};
byte rowPins[ROWS] = { 29, 28, 27, 26 }; // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 25, 24, 23, 22 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

Servo HOTDOG_servo;
Servo HAMBURGER_servo;
Servo CHEESEBURGER_servo;
Servo MEAT_HAM_servo;
Servo CHICKEN_HAM_servo;
Servo OLOVIYEH_servo; 
Servo NESCAFE_servo;
Servo COFFEE_servo;
Servo TEA_servo;
Servo CHERRY_JUICE_servo;
Servo ORANGE_JUICE_servo;
Servo APPLE_JUICE_servo; 
Servo selected_servo;
int selected_price;
long prices[12] = {20000, // HOTDOG        
                  25000, // HAMBURGER     
                  30000, // CHEESEBURGER  
                  15000, // MEAT_HAM      
                  15000, // CHICKEN_HAM  
                  13000, // OLOVIYEH     
                  5000,  // NESCAFE      
                  4000,  // COFFEE       
                  3500,  // TEA          
                  4000,  // CHERRY_JUICE 
                  4000,  // ORANGE_JUICE 
                  4000}; // APPLE_JUICE  
 
// prototypes for menu functions
void menu_change (MenuChangeEvent changed);
void menu_use (MenuUseEvent changed);

MenuBackend menu = MenuBackend (menu_use, menu_change);

MenuItem sandwiches = MenuItem ("sandwiches");
    MenuItem hot_sandwiches = MenuItem ("hot sandwiches");
        MenuItem hotdog = MenuItem ("hotdog");
        MenuItem hamburger = MenuItem ("hamburger");
        MenuItem cheeseburger = MenuItem ("cheeseburger");
    MenuItem cold_sandwiches= MenuItem ("cold sandwiches");
        MenuItem meat_ham = MenuItem ("meat ham");
        MenuItem chicken_ham = MenuItem ("chicken ham");
        MenuItem oloviyeh = MenuItem ("oloviyeh");
MenuItem beverages = MenuItem ("beverages");
    MenuItem hot_beverages = MenuItem ("hot beverages");
        MenuItem nescafe = MenuItem ("nescafe");
        MenuItem coffee = MenuItem ("coffee");
        MenuItem tea = MenuItem ("tea");
    MenuItem cold_beverages= MenuItem ("cold beverages");
        MenuItem cherry_juice = MenuItem ("cherry juice");
        MenuItem orange_juice = MenuItem ("orange juice");
        MenuItem apple_juice = MenuItem ("apple juice");
    
void setup() {
  //set servo pins
  pinMode(HOTDOG, OUTPUT);
  pinMode(HAMBURGER, OUTPUT);
  pinMode(CHEESEBURGER, OUTPUT);
  pinMode(MEAT_HAM, OUTPUT);
  pinMode(CHICKEN_HAM, OUTPUT);
  pinMode(OLOVIYEH, OUTPUT);
  pinMode(NESCAFE, OUTPUT);
  pinMode(COFFEE, OUTPUT);
  pinMode(TEA, OUTPUT);
  pinMode(CHERRY_JUICE, OUTPUT);
  pinMode(ORANGE_JUICE, OUTPUT);
  pinMode(APPLE_JUICE, OUTPUT);
  
  //attach servo pins
  HOTDOG_servo.attach(HOTDOG , 1000 , 2000); 
  HAMBURGER_servo.attach(HAMBURGER , 1000 , 2000); 
  CHEESEBURGER_servo.attach(CHEESEBURGER , 1000 , 2000); 
  MEAT_HAM_servo.attach(MEAT_HAM , 1000 , 2000); 
  CHICKEN_HAM_servo.attach(CHICKEN_HAM , 1000 , 2000); 
  OLOVIYEH_servo.attach(OLOVIYEH , 1000 , 2000); 
  NESCAFE_servo.attach(NESCAFE , 1000 , 2000); 
  COFFEE_servo.attach(COFFEE , 1000 , 2000); 
  TEA_servo.attach(TEA , 1000 , 2000); 
  CHERRY_JUICE_servo.attach(CHERRY_JUICE , 1000 , 2000); 
  ORANGE_JUICE_servo.attach(ORANGE_JUICE , 1000 , 2000); 
  APPLE_JUICE_servo.attach(APPLE_JUICE , 1000 , 2000);
   
  //initialize the servos
  HOTDOG_servo.write(0);
  HAMBURGER_servo.write(0);
  CHEESEBURGER_servo.write(0);
  MEAT_HAM_servo.write(0);
  CHICKEN_HAM_servo.write(0);
  OLOVIYEH_servo.write(0);
  NESCAFE_servo.write(0);
  COFFEE_servo.write(0);
  TEA_servo.write(0);
  CHERRY_JUICE_servo.write(0);
  ORANGE_JUICE_servo.write(0);
  APPLE_JUICE_servo.write(0);

  //creating the menu
  menu.getRoot().add(sandwiches);
  sandwiches.addRight(beverages);
  sandwiches.add(hot_sandwiches).addRight(cold_sandwiches);
  hot_sandwiches.add(hotdog).addRight(hamburger).addRight(cheeseburger);
  cold_sandwiches.add(meat_ham).addRight(chicken_ham).addRight(oloviyeh);
  beverages.add(hot_beverages).addRight(cold_beverages);
  hot_beverages.add(nescafe).addRight(coffee).addRight(tea);
  cold_beverages.add(cherry_juice).addRight(orange_juice).addRight(apple_juice);
  menu.toRoot();
  
  lcd.begin(16, 2); 
  lcd.print("  A.Alibakhshi  "); 
  lcd.setCursor(0, 1);  
  lcd.print(" YAGHOOB-BARGHI ");
  delay(DELAY_PERIOD * 2); 
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print ("<  Main  Menu  >");
  lcd.setCursor(0, 1);
  lcd.print ("Press = to start");
}
 
void loop() { 
  char key = kpd.waitForKey();
  navigateMenus(key);
}


void menu_change (MenuChangeEvent changed){ // after changing our current position in the menu...
  MenuItem newMenuItem = changed.to; 
  if ( newMenuItem.getName () == menu.getRoot () ){
    lcd.setCursor(0, 0);
    lcd.print ("<  Main  Menu  >");
    lcd.setCursor(0, 1);
    lcd.print ("Press = to start");
  }
  else if ( newMenuItem.getName () == "sandwiches" ){
    lcd.setCursor(0, 0);
    lcd.print ("<     Menu     >");
    lcd.setCursor(0, 1);
    lcd.print ("   sandwiches  +");
  }
  else if ( newMenuItem.getName () == "hot sandwiches" ){
    lcd.setCursor(0, 0);
    lcd.print ("<  sandwiches  >");
    lcd.setCursor(0, 1);
    lcd.print (" hot sandwiches+");
  }
  else if ( newMenuItem.getName () == "hotdog" ){
    selected_servo = HOTDOG_servo;
    selected_price = HOTDOG;
    lcd.setCursor(0, 0);
    lcd.print ("<hot sandwiches>");
    lcd.setCursor(0, 1);
    lcd.print ("     hotdog    +");
  }
  else if ( newMenuItem.getName () == "hamburger" ){
    selected_servo = HAMBURGER_servo;
    selected_price = HAMBURGER;
    lcd.setCursor(0, 0);
    lcd.print ("<hot sandwiches>");
    lcd.setCursor(0, 1);
    lcd.print ("-   hamburger  +");
  }
  else if ( newMenuItem.getName () == "cheeseburger" ){
    selected_servo = CHEESEBURGER_servo;
    selected_price = CHEESEBURGER;
    lcd.setCursor(0, 0);
    lcd.print ("<hot sandwiches>");
    lcd.setCursor(0, 1);
    lcd.print ("- cheeseburger  ");
  }
  else if ( newMenuItem.getName () == "cold sandwiches" ){
    lcd.setCursor(0, 0);
    lcd.print ("<  sandwiches  >");
    lcd.setCursor(0, 1);
    lcd.print ("-coldSandwiches ");
  }
  else if ( newMenuItem.getName () == "meat ham" ){
    selected_servo = MEAT_HAM_servo;
    selected_price = MEAT_HAM;
    lcd.setCursor(0, 0);
    lcd.print ("<coldSandwiches>");
    lcd.setCursor(0, 1);
    lcd.print ("    meat ham   +");
    }
  else if ( newMenuItem.getName () == "chicken ham" ){
    selected_servo = CHICKEN_HAM_servo;
    selected_price = CHICKEN_HAM;
    lcd.setCursor(0, 0);
    lcd.print ("<coldSandwiches>");
    lcd.setCursor(0, 1);
    lcd.print ("- chicken ham  +");
  }
  else if ( newMenuItem.getName () == "oloviyeh" ){
    selected_servo = OLOVIYEH_servo; 
    selected_price = OLOVIYEH;
    lcd.setCursor(0, 0);
    lcd.print ("<coldSandwiches>");
    lcd.setCursor(0, 1);
    lcd.print ("-   oloviyeh    ");
  }  
  else if ( newMenuItem.getName () == "beverages" ){
    lcd.setCursor(0, 0);
    lcd.print ("<     Menu     >");
    lcd.setCursor(0, 1);
    lcd.print ("-   beverages   ");
  }  
  else if ( newMenuItem.getName () == "hot beverages" ){
    lcd.setCursor(0, 0);
    lcd.print ("<   beverages  >");
    lcd.setCursor(0, 1);
    lcd.print (" hot beverages +");
  }  
  else if ( newMenuItem.getName () == "nescafe" ){
    selected_servo = NESCAFE_servo;
    selected_price = NESCAFE;
    lcd.setCursor(0, 0);
    lcd.print ("<hot  beverages>");
    lcd.setCursor(0, 1);
    lcd.print ("    nescafe    +");
  }  
  else if ( newMenuItem.getName () == "coffee" ){
    selected_servo = COFFEE_servo;
    selected_price = COFFEE;
    lcd.setCursor(0, 0);
    lcd.print ("<hot  beverages>");
    lcd.setCursor(0, 1);
    lcd.print ("-    coffee    +");
  }  
  else if ( newMenuItem.getName () == "tea" ){
    selected_servo = TEA_servo;
    selected_price = TEA;
    lcd.setCursor(0, 0);
    lcd.print ("<hot  beverages>");
    lcd.setCursor(0, 1);
    lcd.print ("-      tea      ");
  }  
  else if ( newMenuItem.getName () == "cold beverages" ){
    lcd.setCursor(0, 0);
    lcd.print ("<   beverages  >");
    lcd.setCursor(0, 1);
    lcd.print ("- cold beverages");
  }  
  else if ( newMenuItem.getName () == "cherry juice" ){
    selected_servo = CHERRY_JUICE_servo;
    selected_price = CHERRY_JUICE;
    lcd.setCursor(0, 0);
    lcd.print ("<cold beverages>");
    lcd.setCursor(0, 1);
    lcd.print ("  cherry juice +");
  }  
  else if ( newMenuItem.getName () == "orange juice" ){
    selected_servo = ORANGE_JUICE_servo;
    selected_price = ORANGE_JUICE;
    lcd.setCursor(0, 0);
    lcd.print ("<cold beverages>");
    lcd.setCursor(0, 1);
    lcd.print ("- orange juice +");
  }  
  else if ( newMenuItem.getName () == "apple juice" ){
    selected_servo = APPLE_JUICE_servo; 
    selected_price = APPLE_JUICE;
    lcd.setCursor(0, 0);
    lcd.print ("<cold beverages>");
    lcd.setCursor(0, 1);
    lcd.print ("-  apple juice  ");
  }  
}
 
void menu_use (MenuUseEvent used){// after selecting the priduct...
  // update screen
  lcd.clear ();
  lcd.setCursor(0,0);
  lcd.print ("> ");
  lcd.print (used.item.getName ());
  lcd.setCursor(0, 1);
  lcd.print ("> How many? ");
  // get the number of products
  String number_string = "";
  char n = kpd.waitForKey();
  while (n != '='){
    number_string += n;
    lcd.print(n);
    n = kpd.waitForKey();
  }  
  int number = number_string.toInt();
  // get the products from Yaghoub:)
  open_servo(selected_servo, number);
}

void open_servo(Servo servo, int n){
  //print
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print (n);
  lcd.print ("*");
  lcd.print (prices[13 - selected_price]);
  long result = n*prices[13 - selected_price];
  lcd.print ("=");
  lcd.setCursor(0, 1);
  lcd.print (result);
  lcd.print (" : ");
  lcd.print(n); 
  //wait 
  delay(DELAY_PERIOD);
  for (int i = 0; i < n; i++){
    //open
    servo.write(180);
    // update screen
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print (n);
    lcd.print ("*");
    lcd.print (prices[13 - selected_price]);
    lcd.print ("=");
    lcd.setCursor(0, 1);
    lcd.print (result);
    lcd.print (" : ");
    lcd.print(n-i-1);
    //wait
    delay(DELAY_PERIOD);
    //close
    servo.write(0);
    //wait
    delay(DELAY_PERIOD * 2);
  }
  //go to root
  menu.toRoot ();
}

void navigateMenus (char key){
  MenuItem currentMenu = menu.getCurrent ();  
  switch ( key ){
    case '=': //enter
      if ( !(currentMenu.moveDown ()) ){  // No child found; the node is a leaf.
        menu.use();
        }
      else{  // Go to the next level
      menu.moveDown();
        }
      break;
    case 'R': // reset. Go back to the root.
      menu.toRoot ();  
      break;
    case '+': //right
      menu.moveRight ();
      break;
    case '-': //left
      menu.moveLeft ();
      break;
    // update the screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(key);
    delay(1000);
  }
}

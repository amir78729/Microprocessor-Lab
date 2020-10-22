/*
**  Microprocessor and Assembly Language lab
**  Fall 1399
**  name: Amirhossein Alibakhshi
**  id: 9731096
**  Lab #1
*/
int button_1 = 1; //the value of button#1
int button_2 = 1; //the value of button#2
int button_3 = 1; //the value of button#3
int delay_period = 100; //delay period (ms)
void setup() {
    // initialize LEDs
    pinMode(0, OUTPUT);//LED0
    pinMode(1, OUTPUT);//LED1
    pinMode(2, OUTPUT);//LED2
    pinMode(3, OUTPUT);//LED3
    pinMode(4, OUTPUT);//LED4
    pinMode(5, OUTPUT);//LED5
    pinMode(6, OUTPUT);//LED6
    // initialize Buttons
    pinMode(8 , INPUT);// key #1
    pinMode(9 , INPUT);// key #2
    pinMode(10, INPUT);// key #3
}
void loop() {
  //read Buttons
  button_1 = digitalRead(8);
  button_2 = digitalRead(9);
  button_3 = digitalRead(10);
  if ( button_3 == LOW ){// button#3 has been pressed
    //deactivate all LEDs
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }else if ( button_2 == LOW ){//button#2 has been pressed
    //activate LED #1
    digitalWrite(0, HIGH);
//    digitalWrite(1, LOW);
//    digitalWrite(2, LOW);
//    digitalWrite(3, LOW);
//    digitalWrite(4, LOW);
//    digitalWrite(5, LOW);
//    digitalWrite(6, LOW);
    delay(delay_period);
    //activate LED #2
//    digitalWrite(0, LOW);
    digitalWrite(1, HIGH);
    delay(delay_period);
    //activate LED #3
//    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    delay(delay_period);
    //activate LED #4
//    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    delay(delay_period);
    //activate LED #5  
//    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(delay_period);
    //activate LED #6
//    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(delay_period);
    //activate LED #7
//    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    delay(delay_period);
  }else if ( button_1 == LOW ){//button#1 has been pressed
    //activate LED #7
//    digitalWrite(0, LOW);
//    digitalWrite(1, LOW);
//    digitalWrite(2, LOW);
//    digitalWrite(3, LOW);
//    digitalWrite(4, LOW);
//    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    delay(delay_period);
    //activate LED #6
    digitalWrite(5, HIGH);
//    digitalWrite(6, LOW);
    delay(delay_period);
    //activate LED #5
    digitalWrite(4, HIGH);
//    digitalWrite(5, LOW);
    delay(delay_period);
    //activate LED #4
    digitalWrite(3, HIGH);
//    digitalWrite(4, LOW);
    delay(delay_period);
    //activate LED #3
    digitalWrite(2, HIGH);
//    digitalWrite(3, LOW);
    delay(delay_period);
    //activate LED #2
    digitalWrite(1, HIGH);
//    digitalWrite(2, LOW);
    delay(delay_period);
    //activate LED #1
    digitalWrite(0, HIGH);
//    digitalWrite(1, LOW);
    delay(delay_period);
  }
}

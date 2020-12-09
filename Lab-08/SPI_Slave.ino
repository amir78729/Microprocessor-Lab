//slave
#include<SPI.h>

char buff [100];
volatile byte index;
volatile boolean process_is_done;
volatile boolean start;

void setup(){
  Serial.begin(9600);
  SPCR |= _BV(SPE);
  index = 0;
  process_is_done = false; 
  start = true; 
  
  //allow SPI interrupts
  SPI.attachInterrupt();  
  Serial.println("< SLAVE >");
}

void loop(void){
  
  // character '\r' is recieved → the process is done
  if (process_is_done) {
    process_is_done = false; //reset the process
    index= 0; //reset the index to zero
  }
  
  delay(5); 
}

// Interrupt Service Routine
ISR (SPI_STC_vect) {
  // new input data recieved → the process is not done yet
  process_is_done = false;
  
  // print the begenning of each line
  if (start){ 
    Serial.print("recieved data: ");
    start = false;
  }

  // read byte from SPI Data Register in each interrupt
  byte c= SPDR; 
  if (index < sizeof buff) {
    
    // save data in the array buff
    buff [index++] = c; 

    // check if the data is finished or not
    if (c != '\r') 
      Serial.print((char)c); // print each recieved character

    // done...
    else { 
      process_is_done = true;
      start = true;
      Serial.println();
    }
  }
}

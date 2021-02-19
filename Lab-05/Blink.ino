/*
**  Microprocessor and Assembly Language lab
**  Fall 1399
**  name: Amirhossein Alibakhshi
**  id: 9731096
**  Lab #5
*/

int delay_period = 1000; //delay period (ms)
void setup() {
    // output pins
    pinMode(22, OUTPUT);
}
void loop() {
  digitalWrite(22, LOW);
  delay(delay_period);
  digitalWrite(22, HIGH);
  delay(delay_period);
}

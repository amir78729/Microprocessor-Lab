#include "pitches.h"
//#include "themes.h"
//#include "Ode_to_joy.h"
#include"THE_IMPERIAL_MARCH.h"

#define SOUNDER_PORT 53

float scale;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int note = 0; note < sizeof(melody)/sizeof(int); note++){
    scale = analogRead(A15)/512.0;
    int duration = 1000/noteDurations[note];
    tone(SOUNDER_PORT, (int)(melody[note] * scale), duration);
    delay(int(duration * 1.2));
  }
}

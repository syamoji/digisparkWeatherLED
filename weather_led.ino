#include <DigiUSB.h>
#define PIN_RED 0
#define PIN_GREEN 1
#define PIN_BLUE 2

unsigned char led_r, led_g, led_b;
unsigned char count = 0;

void setup() {
  pinMode(PIN_RED, true);
  pinMode(PIN_GREEN, true);
  pinMode(PIN_BLUE, true);
  led_r = led_g = led_b = 0;
  DigiUSB.begin();
}

void setBlue(){
    if(led_b == 0){
      digitalWrite(2,LOW);
      return;
    }
    else if(led_b == 255){
      digitalWrite(2,HIGH);
      return;
    }
    // On period  
    for (int x=0;x<led_b;x++){
    digitalWrite(2,HIGH);
    } 
    
    // Off period
    for(int x=0;x<(255-led_b);x++){
    digitalWrite(2,LOW);
    }
  
} 

void loop() {
  setBlue();
  DigiUSB.refresh();
  setBlue();
  char recv = DigiUSB.read();
  switch (recv)
  {
    case 's':
      led_r += 5;
      analogWrite(PIN_RED, led_r);
      break;
    case 'c':
      led_g += 5;
      analogWrite(PIN_GREEN, led_g);
      break;
    case 'r':
      led_b += (byte)5;
      setBlue();
      break;
    case 'x':
      led_r = led_g = led_b = 0;
      analogWrite(PIN_RED, led_r);
      analogWrite(PIN_GREEN, led_g);
      analogWrite(PIN_BLUE, led_b);
      break;
  }
  if (led_r >= 255) led_r = 0;
  if (led_g >= 255) led_g = 0;
  if (led_b >= 255) led_b = 0;
  if (count >= 255) count = 0;
}

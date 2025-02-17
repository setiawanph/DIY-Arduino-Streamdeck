#include "Keyboard.h"

//Key cap
#define Butt_Key1 KEY_F13
#define Butt_Key2 KEY_F14
#define Butt_Key3 KEY_F15
#define Butt_Key4 KEY_F16

#define Butt_Key5 KEY_F17
#define Butt_Key6 KEY_F18
#define Butt_Key7 KEY_F19
#define Butt_Key8 KEY_F20
#define Butt_Key9 KEY_F21

//Pin to connect
#define Butt_Pin1 2
#define Butt_Pin2 3
#define Butt_Pin3 4
#define Butt_Pin4 5
#define Butt_Pin5 6

#define Butt_Pin6 7
#define Butt_Pin7 8
#define Butt_Pin8 9
#define Butt_Pin9 10

class button {
  public:
  const char key;
  const uint8_t pin;

  button(uint8_t k, uint8_t p) : key(k), pin(p){}

  void press(boolean state){
    if(state == pressed || (millis() - lastPressed <= debounceTime)){
      return; //Nothing to see
    }

    lastPressed = millis();

    state ? Keyboard.press(key) : Keyboard.release(key);
    pressed = state;
  }

  void update(){
    press(!digitalRead(pin));
  }

  private:
  const unsigned long debounceTime = 30;
  unsigned long lastPressed = 0;
  boolean pressed = 0;

};

//Button objects, organised in array
button buttons[]={
  {Butt_Key1, Butt_Pin1},
  {Butt_Key2, Butt_Pin2},
  {Butt_Key3, Butt_Pin3},
  {Butt_Key4, Butt_Pin4},
  {Butt_Key5, Butt_Pin5},
  {Butt_Key6, Butt_Pin6},
  {Butt_Key7, Butt_Pin7},
  {Butt_Key8, Butt_Pin8},
  {Butt_Key9, Butt_Pin9},
};

const uint8_t NumButtons = sizeof(buttons)/sizeof(button);
const uint8_t ledPin = 17;

void setup() {
  // Safety check. Ground pin #1 (RX) to cancel keyboard inputs.
  pinMode(1, INPUT_PULLUP);
  if(!digitalRead(1)){
    failsafe();
  }

  //Set LEDs Off. Active low
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  TXLED0;

  for (int i = 0; i < NumButtons; i++){
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
}

void loop() {
  for(int i = 0; i < NumButtons; i++){
    buttons[i].update();
  }

}

void failsafe(){
  for(;;){} // Just going to hang out here for awhile :D
}
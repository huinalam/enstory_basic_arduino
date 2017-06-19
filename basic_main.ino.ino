#include <TimerOne.h>
#include "TM1637.h"

#define CLK 2
#define DIO 3

#define PIN_LED_INPUT 8
#define PIN_LED_DOOR 9
#define PIN_IS_EVLP_INPUT 10
#define PIN_IS_OPEN_DOOR 11
  
unsigned int evlp_count = 0;
bool isEvlpInput = false;
bool isOpenDoor = false;

char is_led = 0;
int8_t ListDisp[4];

TM1637 tm1637(CLK,DIO);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LED_INPUT, OUTPUT);
  pinMode(PIN_LED_DOOR, OUTPUT);
  pinMode(PIN_IS_EVLP_INPUT, INPUT);
  pinMode(PIN_IS_OPEN_DOOR, INPUT);

  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  
  Serial.println("start");
  updateDisplay(0);
}

void updateDisplay(unsigned int count) {
  ListDisp[3] = count % 10;
  ListDisp[2] = (count/10) % 10;
  ListDisp[1] = (count/100) % 10;
  ListDisp[0] = (count/1000);
  tm1637.display(ListDisp);
}

void addEvlpCount() {
  evlp_count++;
  updateDisplay(evlp_count);
}

void checkEvlpInput() {
  if (isEvlpInput && digitalRead(PIN_IS_EVLP_INPUT)) {
    
  } else if (!isEvlpInput && digitalRead(PIN_IS_EVLP_INPUT)) {
    isEvlpInput = true;
    digitalWrite(PIN_LED_INPUT, HIGH);
    Serial.println("checkEvlpInput on");
    addEvlpCount();
  } else if (isEvlpInput && !digitalRead(PIN_IS_EVLP_INPUT)) {
    isEvlpInput = false;
    digitalWrite(PIN_LED_INPUT, LOW);
    Serial.println("checkEvlpInput off");
  } else if (!isEvlpInput && !digitalRead(PIN_IS_EVLP_INPUT)) {
    
  } else {
    // 예외상황
  }
}

void checkOpenDoor() {
  if (isOpenDoor && digitalRead(PIN_IS_OPEN_DOOR)) {
    
  } else if (!isOpenDoor && digitalRead(PIN_IS_OPEN_DOOR)) {
    isOpenDoor = true;
    digitalWrite(PIN_LED_DOOR, LOW);
    Serial.println("checkOpenDoor on");
  } else if (isOpenDoor && !digitalRead(PIN_IS_OPEN_DOOR)) {
    isOpenDoor = false;
    digitalWrite(PIN_LED_DOOR, HIGH);
    Serial.println("checkOpenDoor off");
  } else if (!isOpenDoor && !digitalRead(PIN_IS_OPEN_DOOR)) {
    
  } else {
    // 예외상황
  }
}

void loop() {
  checkEvlpInput();
  checkOpenDoor();
  delay(80);
}



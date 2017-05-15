#define PIN_LED_INPUT 8
#define PIN_LED_DOOR 9
#define PIN_IS_EVLP_INPUT 10
#define PIN_IS_OPEN_DOOR 11
  
unsigned int evlp_count = 0;
bool isEvlpInput = false;
bool isOpenDoor = false;

char is_led = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LED_INPUT, OUTPUT);
  pinMode(PIN_LED_DOOR, OUTPUT);
  pinMode(PIN_IS_EVLP_INPUT, INPUT);
  pinMode(PIN_IS_OPEN_DOOR, INPUT);
  Serial.println("start");
}

void addEvlpCount() {
  evlp_count++;

  // 7세그먼트 관련 코드 입력 필요
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
    digitalWrite(PIN_LED_DOOR, HIGH);
    Serial.println("checkOpenDoor on");
  } else if (isOpenDoor && !digitalRead(PIN_IS_OPEN_DOOR)) {
    isOpenDoor = false;
    digitalWrite(PIN_LED_DOOR, LOW);
    Serial.println("checkOpenDoor off");
  } else if (!isOpenDoor && !digitalRead(PIN_IS_OPEN_DOOR)) {
    
  } else {
    // 예외상황
  }
}

void loop() {
  checkEvlpInput();
  checkOpenDoor();
}

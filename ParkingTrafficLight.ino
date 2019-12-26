int IN_GREEN_LED_PIN = 10;
int IN_RED_LED_PIN = 9;
int IN_BUTTON_PIN = 8;

int OUT_GREEN_LED_PIN = 13;
int OUT_RED_LED_PIN = 12;
int OUT_BUTTON_PIN = 11;

int inButtonState = HIGH;
int outButtonState = HIGH;

int inRedLedState = LOW;
int inGreenLedState = HIGH;

int outRedLedState = HIGH;
int outGreenLedState = LOW;

int LIGHT_SENSOR_PIN_STATE = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor

int isEvning = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IN_RED_LED_PIN,OUTPUT);
  pinMode(IN_GREEN_LED_PIN,OUTPUT);
  pinMode(OUT_RED_LED_PIN,OUTPUT);
  pinMode(OUT_GREEN_LED_PIN,OUTPUT);
  pinMode(IN_BUTTON_PIN,INPUT_PULLUP);
  pinMode(OUT_BUTTON_PIN,INPUT_PULLUP);

  digitalWrite(OUT_GREEN_LED_PIN, outGreenLedState);
  digitalWrite(OUT_RED_LED_PIN, outRedLedState);
  digitalWrite(IN_GREEN_LED_PIN, inGreenLedState);
  digitalWrite(IN_RED_LED_PIN, inRedLedState);
  sensorValue = analogRead(LIGHT_SENSOR_PIN_STATE); // read the value from the sensor
  isEvning = (sensorValue / 1000);
}

void loop() {
  inButtonState = digitalRead(IN_BUTTON_PIN);
  //Serial.println(inButtonState);
  outButtonState = digitalRead(OUT_BUTTON_PIN);
  //Serial.println(outButtonState);

  sensorValue = analogRead(LIGHT_SENSOR_PIN_STATE); // read the value from the sensor
  //Serial.println(sensorValue); //prints the values coming from the sensor on the screen

  Serial.println(inButtonState == LOW && isEvning);

  if(isEvning != sensorValue / 1000){
    isEvning = sensorValue / 1000;
    systemChangeDirection();
  }

  if(inButtonState == LOW && isEvning){
    onInClicked();
  }

  if(outButtonState == LOW && !isEvning){
    onOutClicked();
  }
}

void systemChangeDirection(){
  if(inGreenLedState == HIGH){
    writeToInState(LOW,HIGH);
    delay(3000);
    writeToOutState(HIGH,LOW);
  }
  else {
    writeToOutState(LOW,HIGH);
    delay(3000);
    writeToInState(HIGH,LOW);
  }
}

void onOutClicked(){
   writeToInState(LOW, HIGH);
   delay(3000);
   writeToOutState(HIGH, LOW);
   delay(5000);
   writeToOutState(LOW, HIGH);
   delay(3000);
   writeToInState(HIGH, LOW);
}

void onInClicked(){
   writeToOutState(LOW, HIGH);
   delay(3000);
   writeToInState(HIGH, LOW);
   delay(5000);
   writeToInState(LOW, HIGH);
   delay(3000);
   writeToOutState(HIGH, LOW);
}

void writeToOutState(int greenState,int redState){
  outGreenLedState = greenState;
  outRedLedState = redState;
  writeToLeds();
}

void writeToInState(int greenState,int redState){
  inGreenLedState = greenState;
  inRedLedState = redState;
  writeToLeds();
}

void writeToLeds(){
  digitalWrite(IN_GREEN_LED_PIN, inGreenLedState);
  digitalWrite(IN_RED_LED_PIN, inRedLedState);
  digitalWrite(OUT_GREEN_LED_PIN, outGreenLedState);
  digitalWrite(OUT_RED_LED_PIN, outRedLedState);
}

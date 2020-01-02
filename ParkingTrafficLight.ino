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

// setup function
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

// loop function
void loop() {
  inButtonState = digitalRead(IN_BUTTON_PIN);
  //Serial.println(inButtonState);
  outButtonState = digitalRead(OUT_BUTTON_PIN);
  //Serial.println(outButtonState);

  sensorValue = analogRead(LIGHT_SENSOR_PIN_STATE); // read the value from the sensor
  //Serial.println(sensorValue); //prints the values coming from the sensor on the screen

  Serial.println(inButtonState == LOW && isEvning);

  // sensorValue between 900-1100 so divied by 1000 return 0 or 1, evning = 1
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

// The function change the system direction from it to out or out to in with same change routine
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

// The function called when out clicked button cliked and change to in direction with same change routine
void onOutClicked(){
   writeToInState(LOW, HIGH);
   delay(3000);
   writeToOutState(HIGH, LOW);
   delay(5000);
   writeToOutState(LOW, HIGH);
   delay(3000);
   writeToInState(HIGH, LOW);
}

// The function called when in clicked button cliked and change to out direction with same change routine
void onInClicked(){
   writeToOutState(LOW, HIGH);
   delay(3000);
   writeToInState(HIGH, LOW);
   delay(5000);
   writeToInState(LOW, HIGH);
   delay(3000);
   writeToOutState(HIGH, LOW);
}

// The function write to green and red leds the states
void writeToOutState(int greenState,int redState){
  outGreenLedState = greenState;
  outRedLedState = redState;
  writeToLeds();
}

// The function write red and green state to in led state
void writeToInState(int greenState,int redState){
  inGreenLedState = greenState;
  inRedLedState = redState;
  writeToLeds();
}

// The function write to 2 in green, red leds and 2 out green, red leds the states

void writeToLeds(){
  digitalWrite(IN_GREEN_LED_PIN, inGreenLedState);
  digitalWrite(IN_RED_LED_PIN, inRedLedState);
  digitalWrite(OUT_GREEN_LED_PIN, outGreenLedState);
  digitalWrite(OUT_RED_LED_PIN, outRedLedState);
}

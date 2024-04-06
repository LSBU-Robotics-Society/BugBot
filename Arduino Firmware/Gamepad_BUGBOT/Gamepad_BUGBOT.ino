/*
   Gamepad module provides three different mode namely Digital, JoyStick and Accerleometer.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/game-pad-module/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

// the number of the LED pin
const int leftMotorpin1 =  32;  
const int leftMotorpin2 =  33;
const int rightMotorpin1 = 27;
const int rightMotorpin2 = 14;

// setting PWM properties
const int freq = 5000;
const int leftMotorChanel1 = 0;
const int leftMotorChanel2 = 1;

const int rightMotorChanel1 = 2;
const int rightMotorChanel2 = 3;
const int resolution = 8;



void setLeftMotorPWM(int dutyCycle,int direction){
  if (direction == 1){
    ledcWrite(leftMotorChanel1, dutyCycle);
    ledcWrite(leftMotorChanel2, 0);
  }
  if (direction == -1){
    ledcWrite(leftMotorChanel1, 0);
    ledcWrite(leftMotorChanel2, dutyCycle);
  }
}
void setRightMotorPWM(int dutyCycle, int direction){
  if (direction == 1){
    ledcWrite(rightMotorChanel1, 0);
    ledcWrite(rightMotorChanel2, dutyCycle);
  }
  if (direction == -1){
    ledcWrite(rightMotorChanel1, dutyCycle);
    ledcWrite(rightMotorChanel2, 0);
  }

}

  int leftDuty = 0;
  int rightDuty = 0;

void setup() {

   // configure LED PWM functionalitites
  ledcSetup(leftMotorChanel1, freq, resolution);
  ledcSetup(leftMotorChanel2, freq, resolution);
  ledcSetup(rightMotorChanel1, freq, resolution);
  ledcSetup(rightMotorChanel2, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(leftMotorpin1,  leftMotorChanel1);
  ledcAttachPin(leftMotorpin2,  leftMotorChanel2);
  ledcAttachPin(rightMotorpin1, rightMotorChanel1);
  ledcAttachPin(rightMotorpin2, rightMotorChanel2);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 
  
  // put your setup code here, to run once:
  Serial.begin(115200);          // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("kuuga");  //set bluetooth name of your device


}

void loop() {

  if (int(analogRead(35)*200/4095) < 75 ) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  //Serial.println(int(analogRead(35)*200/4095));
  Dabble.processInput();  //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  
  float c = GamePad.getXaxisData();

  leftDuty = map(c,-7,0,0,255);
  leftDuty =constrain(leftDuty, 0, 255);

  rightDuty =  map(c,6,0,0,255);
  rightDuty =constrain(rightDuty, 0, 255);
  //Serial.println(leftDuty);
  //Serial.println(rightDuty);
  Serial.println();


  if (GamePad.isCrossPressed()){
    //Serial.print("Cross");
    setLeftMotorPWM(leftDuty,1);
    setRightMotorPWM(rightDuty,1);
  }
  else if (GamePad.isTrianglePressed()){
    //Serial.print("Triangle");
    setLeftMotorPWM(leftDuty,-1);
    setRightMotorPWM(rightDuty,-1);
  }
  else{
    setLeftMotorPWM(0,1);
    setRightMotorPWM(0,1);
  }

  //float d = GamePad.getYaxisData();
  //Serial.print("y_axis: ");
  //Serial.println(d);
  //Serial.println();

}

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  sensor.setTimeout(500);

  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  sensor.startContinuous();
  // put your setup code here, to run once:
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
}

void loop() {

  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();

if (sensor.readRangeContinuousMillimeters() < 70) {
  digitalWrite(32, LOW);
  digitalWrite(33, HIGH);
  digitalWrite(27, LOW);
  digitalWrite(14, HIGH);
}
else {
  digitalWrite(32, HIGH);
  digitalWrite(33, LOW);
  digitalWrite(27, LOW);
  digitalWrite(14, HIGH);

}

}

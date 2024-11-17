#include <Servo.h>

// Light sensor configuration
int lightSensorValue;
int lightSensorLow = 1023;
int lightSensorHigh = 0;

const int LIGHT_SENSOR_PIN = A0;

// Servo configuration
const int SERVO_PIN = 9;
Servo myServo;

int servo_angle;
int prev_servo_angle;


void setup() {
  Serial.begin(9600);

  // Calibrate the light sensor
  while(millis() < 5000){
    lightSensorValue = analogRead(LIGHT_SENSOR_PIN);
    // Calibrate high value
    if(lightSensorValue > lightSensorHigh){
      lightSensorHigh = lightSensorValue;
    }
    // Calibrate low value
    if(lightSensorValue < lightSensorLow){
      lightSensorLow = lightSensorValue;
    }
  }

  Serial.print("Calibration results: ");
  Serial.print("Low: ");
  Serial.print(lightSensorLow);
  Serial.print(" | High: ");
  Serial.println(lightSensorHigh);

  // Initialize servo
  myServo.attach(SERVO_PIN);
  servo_angle = 0;
  prev_servo_angle = 0;

  // Shows the servo movement range and leave it on the initial position
  myServo.write(0);
  delay(500);
  myServo.write(179);
  delay(1200);
  myServo.write(0);
  delay(1200);

}

void loop() {
  lightSensorValue = analogRead(LIGHT_SENSOR_PIN);

  // Recalibrate the light sensor
  if(lightSensorValue > lightSensorHigh){
    lightSensorHigh = lightSensorValue;
  }
  if(lightSensorValue < lightSensorLow){
    lightSensorLow = lightSensorValue;
  }

  int servoAngle = map(lightSensorValue, lightSensorLow, lightSensorHigh, 0, 179);
  servoAngle = constrain(servoAngle, 0, 179);

  myServo.write(servoAngle);
  delay(50); // Wait the servo to be there

  Serial.print("Light sensor value: ");
  Serial.print(lightSensorValue);
  Serial.print(" | Servo angle: ");
  Serial.println(servoAngle);

}

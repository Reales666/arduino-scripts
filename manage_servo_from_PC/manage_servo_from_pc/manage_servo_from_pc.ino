/**
  You can send the servo angle from the serial monitor or from this Python program: 
  
*/

#include <Servo.h>

// Configuration
int SERVO_PIN = 9;

Servo myServo;

int input_value;

void setup() {
  // Initialize serial comm
  Serial.begin(115200);
  Serial.setTimeout(1);

  // Initialize servo
  myServo.attach(SERVO_PIN);

  myServo.write(0);
  delay(500);
  myServo.write(179);
  delay(1200);
  myServo.write(0);
  delay(1200);
}

void loop() {
    while (!Serial.available()); // Wait until Serial port is available
    
    input_value = Serial.readString().toInt(); // Read input value
    
    if(input_value >= 0 && input_value < 180) {
      // Print the values to check
      Serial.print("Input value: ");
      Serial.println(input_value);
      
      // If the value is inside the range, set the servo position.
      myServo.write(input_value);
      delay(15); // Wait the servo to be there
    }
}
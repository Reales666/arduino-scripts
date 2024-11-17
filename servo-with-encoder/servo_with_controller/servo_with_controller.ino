/*
 This sketch shows how to control a 180º servo with a encoder.
*/



// Servo configuration
int SERVO_PIN = 9;
Servo myServo;

int servo_angle;
int prev_servo_angle;

// Encoder configuration
#define encoder_output_a 2
#define encoder_output_b 3
#define encoder_switch 4

int state_a;
int prev_state_a;

void setup() {
  // Initialize serial comm
  Serial.begin(9600);
  Serial.setTimeout(1);

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

  // Initialize encoder
  pinMode (encoder_output_a, INPUT);
  pinMode (encoder_output_b, INPUT);
  // The switch must be polarized with value HIGH
  pinMode (encoder_switch, INPUT_PULLUP);
  // Read the initial stastus of the encoder
  state_a = digitalRead(encoder_output_a);
  prev_state_a = state_a;
}

void loop() {
  // Read the encoder position

  // Read the state of the encoder output A
  state_a = digitalRead(encoder_output_a);

  // If the state has changed, it means that we have movement
  if (state_a != prev_state_a) {     

    // Check the output B. If A and B are different, the encoder is turning rightwards
    if (digitalRead(encoder_output_b) != state_a && servo_angle < 178) { 
      servo_angle = servo_angle + 2;
    } else {
      if(servo_angle > 1) {
        servo_angle = servo_angle - 2;
      }
    }
    Serial.print("Current angle: ");
    Serial.println(servo_angle);
  } 
   
  // Update encoder output A state
  prev_state_a = state_a;
  
  // If angle has been updated, move the servo
  if(servo_angle != prev_servo_angle) {
    prev_servo_angle = servo_angle;
    myServo.write(servo_angle);
    delay(5); // Wait the servo to be there
  }
}
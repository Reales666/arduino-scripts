const int redLedPin = 2;
const int greenLedPin = 3;
const int sensor1Pin = A0;
const int sensor2Pin = A1;
const int sensor3Pin = A2;
const int sensor4Pin = A3;
const int sensor5Pin = A4;
const int sensor6Pin = A5;
const int sensor7Pin = 4;
const int sensor8Pin = 5;
const int sensor9sPin = 6;
const int sensor10Pin = 7;

const long detectionThreshold = 700;

unsigned long detectionTime; 

boolean isDetected = false;

void setup() {

  Serial.begin(9600);
  
  // Setting the leds
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  digitalWrite(greenLedPin, HIGH);
  digitalWrite(redLedPin, LOW); 

  // Setting the sensors
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);
  pinMode(sensor4Pin, INPUT);
  pinMode(sensor5Pin, INPUT);
  pinMode(sensor6Pin, INPUT);
  pinMode(sensor7Pin, INPUT);
  pinMode(sensor8Pin, INPUT);
  pinMode(sensor9sPin, INPUT);
  pinMode(sensor10Pin, INPUT);
}

boolean isCarDetected() {
  return !digitalRead(sensor1Pin) || !digitalRead(sensor2Pin) || !digitalRead(sensor3Pin) || !digitalRead(sensor4Pin) || !digitalRead(sensor5Pin) || !digitalRead(sensor6Pin) || !digitalRead(sensor7Pin) || !digitalRead(sensor8Pin) || !digitalRead(sensor9sPin) || !digitalRead(sensor10Pin);
}


void loop() {

  // No car detected on the previous loop
  if(!isDetected) {
    boolean carDetected = isCarDetected();

    // Car detected on this loop
    if(carDetected) {
      isDetected = true; 

      detectionTime = millis();

      Serial.print("Car detected: "); 
      Serial.println(detectionTime);
    }
  } else { // Car detected on the previous loop
    
    // Check if the car is still there
    boolean carDetected = isCarDetected();
    
    if(carDetected) {
      unsigned long detectionPeriod = millis() - detectionTime;
      
      // The car is stopped in front of the sensor 
      if(detectionPeriod > detectionThreshold) {
        digitalWrite(greenLedPin, LOW);
        digitalWrite(redLedPin, HIGH); 

      }  
    } else {
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(redLedPin, LOW); 

      Serial.print("Car not detected");
      
      isDetected = false;
    }
  }
}

const int redLedPin = 8;
const int greenLedPin = 7;
const int sensorPin = 12;
const int buzzerPin = 6;

cont int buzzerNote = 330;

const long detectionThreshold = 600;

unsigned long detectionTime; 

boolean isDetected = false;

void setup() {

  Serial.begin(9600);
  
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  pinMode(sensorPin, INPUT);

  digitalWrite(greenLedPin, HIGH);
  digitalWrite(redLedPin, LOW); 
  noTone(buzzerPin);
}

void loop() {

  Serial.println("Hello World");

  // No car detected on the previous loop
  if(!isDetected) {
    boolean carDetected = !digitalRead(sensorPin);

    Serial.println("Inside first if");

    Serial.print("Car detected value: ");
    Serial.println(carDetected);

    // Car detected on this loop
    if(carDetected) {
      isDetected = true; 

      detectionTime = millis();

      Serial.print("Sensor activated: "); 
      Serial.println(detectionTime);
    }
  } else { // Car detected on the previous loop

    Serial.println("Inside first else");
    
    // Check if the car is still there
    boolean carDetected = !digitalRead(sensorPin);

    Serial.print("Car detected value: ");
    Serial.println(carDetected);
    
    if(carDetected) {
      unsigned long detectionPeriod = millis() - detectionTime;

      Serial.print("detectionPeriod value: ");
      Serial.println(detectionPeriod);
      
      // The car is stopped in front of the sensor 
      if(detectionPeriod > detectionThreshold) {
        digitalWrite(greenLedPin, LOW);
        digitalWrite(redLedPin, HIGH); 
        tone(buzzerPin, buzzerNote);

        Serial.print("Car detected");
        Serial.println(detectionPeriod);
      }  
    } else {
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(redLedPin, LOW); 
      digitalWrite(buzzerPin, LOW);
      noTone(buzzerPin);
      
      isDetected = false;
    }
  }
}

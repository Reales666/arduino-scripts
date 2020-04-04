
int switchPin = 2;
int greenPin = 3;
int redPin1 = 4;
int redPin2 = 5;

int switchState = 0;
int switchStatePrev = 0;

int lightsState = 0;
int counter = 0; 

void setup() {
	pinMode(greenPin, OUTPUT);
	pinMode(redPin1, OUTPUT);
	pinMode(redPin2, OUTPUT);
	pinMode(switchPin, INPUT);

}

void loop() {

	// Read switch
	switchState = digitalRead(2);

	// The switch is pulsed
	if(switchState == HIGH)
	{
		// The switch was released (The state has changed)
		if(switchStatePrev == LOW)
		{
			// if the red ligths are in state 0, change the sate and wait
			if(lightsState == 0)
			{		
				digitalWrite(redPin1, LOW);
				digitalWrite(redPin2, HIGH);

				lightsState = 1; 

			} else {
				digitalWrite(redPin1, HIGH);
				digitalWrite(redPin2, LOW);

				lightsState = 0;
			}

		// The switch was already pulsed (The state remains the same)	
		} else {
			digitalWrite(greenPin, HIGH);
		digitalWrite(redPin1, LOW);
		digitalWrite(redPin2, LOW);

		}

		
	
	}
	delay(250);
}

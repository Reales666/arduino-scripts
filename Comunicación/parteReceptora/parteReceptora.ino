int pinSensor1 = A0;
int pinSensor2 = A1;
int pinSensor3 = A2;

int sensor1Value;
int sensor2Value;
int sensor3Value;

int prevSensor1Value = 0;
int prevSensor2Value = 0;
int prevSensor3Value = 0;

boolean iPrint;

void setup ()
{
	Serial.begin(9600);
}

void loop ()
{
	iPrint = false;
	sensor1Value = analogRead(pinSensor1);

	if(sensor1Value != prevSensor1Value)
	{
		iPrint = true;
		prevSensor1Value = sensor1Value;
	}

	sensor2Value = analogRead(pinSensor2);

	if(sensor2Value != prevSensor2Value)
	{
		iPrint = true;
		prevSensor2Value = sensor2Value;
	}

	sensor3Value = analogRead(pinSensor3);

	if(sensor3Value != prevSensor3Value)
	{
		iPrint = true;
		prevSensor3Value = sensor3Value;
	}

	if(iPrint)
	{
		Serial.print("Sensor 1: ");
		Serial.print(sensor1Value);
		Serial.print(", Sensor 2: ");
		Serial.print(sensor2Value);
		Serial.print(", Sensor 3: ");
		Serial.println(sensor3Value);
	}
}


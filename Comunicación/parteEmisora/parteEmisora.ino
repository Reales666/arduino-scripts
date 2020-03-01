// #define numDistances 5;
int numDistances = 5;

int pinTrigger[] = {3,  5, 7};
int pinEcho[] = {4, 6, 8};
// int pinExit[] = {9, 10, 11};
byte delimiter = 0;

int values[] = {0, 50, 100, 200, 255};

int getDistance(int numSensor)
{
	long distance;
	long echoTime;
	long averageMeasure = -1;

	if(numSensor >= 0 && numSensor <= 2)
	{
		for(int i = 0; i < numDistances; i ++)
		{
			digitalWrite(pinTrigger[numSensor], LOW);
			delayMicroseconds(5);
			digitalWrite(pinTrigger[numSensor], HIGH);
			delayMicroseconds(10);

			echoTime = pulseIn(pinEcho[numSensor], HIGH);
			distance = int(0.017 * echoTime);
			averageMeasure += distance;

			delay(50);
		}		

		averageMeasure = averageMeasure / numDistances;
	}else
	{
		// Serial.print("Error. No existe el sensor: ");
		// Serial.println(numSensor);
	}

	return averageMeasure;
}

void setup ()
{
	Serial.begin(9600);

	for(int i = 0; i < 3; i ++)
	{
		pinMode(pinTrigger[i], OUTPUT);
		pinMode(pinEcho[i], INPUT);
	}
}

void loop ()
{
	/*
	for(int i = 0; i < 5; i ++)
	{
		for(int j = 0; j < 3; j ++)
		{
			analogWrite(values[i], pinExit[j]);
			delay(10);
			// Serial.print(values[i]);
			// Serial.print(" ");
		}

		// Serial.println();

		delay(500);
	}*/

	// Serial.println("Distancias:");
	int distancia;

	for(int i = 0; i < 3; i ++)
	{
		// Serial.print("D");
		// Serial.print(i + 1);
		// Serial.print(" = ");

		distancia = getDistance(i);

		Serial.write(distancia);
		// Serial.print(distancia);

		// if(i == 2)
			 // Serial.println(" ");

		// if (distancia > 255)
		// {
		// 	distancia = 255;
		// }

		// analogWrite(distancia, pinExit[i]);


		delay(5);
	}

	Serial.write(delimiter);

	// Serial.println(".");

	delay(10);
}

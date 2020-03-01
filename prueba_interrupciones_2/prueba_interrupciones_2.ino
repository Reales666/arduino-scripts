#define trigPin1 7
#define ledPin1 11
#define trigPin2 8
#define ledPin2 10
#define ledPin13 13
#define interruptNumber1 0
#define interruptNumber2 1

// volatile int state = LOW;
volatile boolean actualizado1 = false;
volatile boolean actualizado2 = false;
unsigned long tiempoIda1;
unsigned long tiempoVuelta1;
unsigned long tiempoTotal1;
unsigned long tiempoIda2;
unsigned long tiempoVuelta2;
unsigned long tiempoTotal2;
boolean lanzado1 = false;
boolean lanzado2 = false;

// False: Lanzo el 1
// True: Lanzo el 2
boolean cualLanzo = false;

void cambiaEstado1()
{
	actualizado1 = true;
}

void cambiaEstado2()
{
	actualizado2 = true;
}

void setup()
{
	// Serial.begin(9600);
	pinMode(trigPin1, OUTPUT);
	pinMode(trigPin2, OUTPUT);

	pinMode(ledPin1, OUTPUT);
	pinMode(ledPin2, OUTPUT);
	pinMode(ledPin13, OUTPUT);

	// state: RISING FALLING CHANGE LOW
	attachInterrupt(interruptNumber1, cambiaEstado1, FALLING);
	attachInterrupt(interruptNumber2, cambiaEstado2, FALLING);

	delay(1000);
}

void loop()
{
	if(!lanzado1)
	{
		// Serial.println("Pulso Lanzado!");
		digitalWrite(ledPin13, HIGH);
		lanzado1 = true;
		digitalWrite(trigPin1, LOW);
		delayMicroseconds(5);
		digitalWrite(trigPin1, HIGH);
		delayMicroseconds(10);
		// digitalWrite(trigPin, LOW);
		tiempoIda1 = micros();
	}/*else // Descomentar si el sckech se queda bloqueado
	{
		if(millis() - tiempoIda > 2000)
		{
			lanzado = false;
			digitalWrite(ledPin, LOW);
			Serial.println("Reinicio");
		}
	}*/

	if(!lanzado2)
	{
		// Serial.println("Pulso Lanzado!");
		digitalWrite(ledPin13, HIGH);
		lanzado2 = true;
		digitalWrite(trigPin2, LOW);
		delayMicroseconds(5);
		digitalWrite(trigPin2, HIGH);
		delayMicroseconds(10);
		// digitalWrite(trigPin, LOW);
		tiempoIda2 = micros();
	}

	if(actualizado1)
	{
		// digitalWrite(ledPin13, LOW);
		tiempoVuelta1 = micros();
		// Serial.println("Pulso Recogido");
		tiempoTotal1 = tiempoVuelta1 - tiempoIda1;

		// Serial.print("Tiempo Ida: "); Serial.println(tiempoIda);
		// Serial.print("Tiempo Vuelta: "); Serial.println(tiempoVuelta);	
		// Serial.print("Tiempo Total: "); Serial.println(tiempoTotal);


		int distancia = (0.034 * tiempoTotal1)/2; // distancia en cm

		int potencia = map(distancia, 5, 400, 0, 255);

		analogWrite(ledPin1, potencia);

		// Serial.print("Distancia 1: ");
		// Serial.println(distancia);

		actualizado1 = false;
		lanzado1 = false;
		delay(10);
	}

	if(actualizado2)
	{
		// digitalWrite(ledPin13, LOW);
		tiempoVuelta2 = micros();
		// Serial.println("Pulso Recogido");
		tiempoTotal2 = tiempoVuelta2 - tiempoIda2;

		// Serial.print("Tiempo Ida: "); Serial.println(tiempoIda);
		// Serial.print("Tiempo Vuelta: "); Serial.println(tiempoVuelta);	
		// Serial.print("Tiempo Total: "); Serial.println(tiempoTotal);


		int distancia = (0.034 * tiempoTotal2)/2; // distancia en cm

		int potencia = map(distancia, 5, 400, 0, 255);

		analogWrite(ledPin2, potencia);

		// Serial.print("Distancia 2: ");
		// Serial.println(distancia);

		actualizado2 = false;
		lanzado2 = false;

		delay(10);
	}

}

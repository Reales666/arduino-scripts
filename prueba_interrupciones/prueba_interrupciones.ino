#define trigPin 6
#define echoPin 7
#define ledPin 5
#define interruptNumber 0

volatile int state = LOW;
boolean correcta = false;

int getDistance()
{
	long tiempo;
	int distancia;
	digitalWrite(trigPin, LOW);
	delayMicroseconds(5);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);

	/* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
	  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
	  deja de hacerlo, LOW, la longitud del pulso entrante*/
	tiempo = pulseIn(echoPin, HIGH);

	/*fórmula para calcular la distancia obteniendo un valor entero*/
  /*Monitorización en centímetros por el monitor serial*/
	distancia = int(0.017 * tiempo);

	// Serial.println(ultrasonic.Ranging());
	return distancia;
	// Serial.print("Distancia ");
	// Serial.print(distancia);
	// Serial.println(" cm.");
}

void cambiaEstado()
{
	state = !state;
}


void setup()
{
	Serial.begin(9600);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(ledPin, OUTPUT);

	attachInterrupt(interruptNumber, cambiaEstado, LOW);

	delay(1000);
}

void loop()
{
	/*
	int distancia = getDistance();

	if(distancia >= 10)
	{
		if(!correcta)
		{	
			correcta = true;
			digitalWrite(ledPin, HIGH);
			delay(10);
		}
	}else
	{
		if(correcta)
		{
			correcta = false;
			digitalWrite(ledPin, LOW);
			delay(10);
		}
	}

	Serial.print("Distancia ");
	Serial.print(distancia);
	Serial.println(" cm.");*/

	digitalWrite(ledPin, state);
}
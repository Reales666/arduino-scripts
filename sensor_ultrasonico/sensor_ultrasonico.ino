// #include "Ultrasonic.h"

#define trigPin 9
#define echoPin 8

// Ultrasonic ultrasonic(trigPin, echoPin);

long tiempo;
long distancia;

void setup()
{
	Serial.begin(9600);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	delay(1000);
}

void loop()
{
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

	Serial.print("Distancia ");
	Serial.print(distancia);
	Serial.println(" cm.");

	delay(200);
}


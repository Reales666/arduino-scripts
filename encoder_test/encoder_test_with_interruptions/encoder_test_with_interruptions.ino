int A = 2; // Pin 2
int B = 3; // Pin 3

int ANTERIOR = 0;

volatile int POSICION = 0;

void setup() {
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(A), codificador, LOW);
}


void loop() {
  if (POSICION != ANTERIOR) {
    Serial.println(POSICION);
    ANTERIOR = POSICION;
  }
}

void codificador()  {
  static unsigned long ultimaInterrupcion = 0;
  unsigned long tiempoInterrupcion = millis();

  if (tiempoInterrupcion - ultimaInterrupcion > 5) {
    if (digitalRead(B) == HIGH){
      POSICION++;
    }else{
      POSICION--;
    }

    POSICION = min(50, max(-50, POSICION));
    ultimaInterrupcion = tiempoInterrupcion;
  }
}
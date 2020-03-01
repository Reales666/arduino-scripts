//Conexiones Arduino Uno
int pinEnable = 6;
int pinStep = 7;
int pinDir = 8;
  
  int numPasos = 100;
  
  int pasos = 0;
boolean direccion = HIGH;
  
void setup()
{
  pinMode(pinEnable, OUTPUT);
  pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);

  Serial.begin(9600);
  
  digitalWrite(pinEnable, LOW);
  digitalWrite(pinDir, direccion);  
  digitalWrite(pinStep, HIGH);
  
  delay(500);
}

void loop()
{
  
   while(pasos < numPasos)
   {
     digitalWrite(pinDir, direccion);
     Serial.println("Doy un paso");
     digitalWrite(pinStep, HIGH);
     pasos ++;
     delay(20);
     digitalWrite(pinStep, LOW);
   }
   
   if(pasos == numPasos)
   {
     digitalWrite(pinStep, LOW);
     Serial.println("Reinicio!");
     pasos = 0;
     
     if(direccion == LOW)
       direccion = HIGH;
     else
       direccion = LOW;
     
     delay(1000);
   }
}

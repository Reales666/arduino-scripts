#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);

int adc_key_val[5] = {5, 200, 400, 600, 800 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;
boolean luzEncendida=true;
boolean cursorActivo=false;
unsigned long time;
int x=0;
char caracterActual = 'A';

void setup()
{
  lcd.clear(); 
  lcd.begin(16, 2);
  lcd.setCursor(0,0); 
  lcd.print("www.ajpdsoft.com");
  time = millis();
  //  pinMode(10, OUTPUT);
}

void loop()
{
  if (millis()-time > 10000) {  // Si han pasado mas de 10 segundos apagamos la luz
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);
    luzEncendida=false;
  }
  if (millis()-time > 5000) {  // Si han pasado mas de 5 segundos apagamos el cursor
    lcd.noBlink();
    cursorActivo=false;
  } 

  adc_key_in = analogRead(0);    // Leemos el valor de la pulsacion
  key = get_key(adc_key_in);    // Obtenemos el boton pulsado

  if (key != oldkey)   // if keypress is detected
  {
    delay(50);  // Espera para evitar los rebotes de las pulsaciones
    adc_key_in = analogRead(0);    // Leemos el valor de la pulsacion
    key = get_key(adc_key_in);    // Obtenemos el boton pulsado
    if (key != oldkey)    
    {
      time = millis();  // TODO: falta la comprobacion de si se ha desbordado el tiempo
      if (!luzEncendida) {  // Al pulsar cualquier tecla encendemos la pantalla
        pinMode(10, INPUT);
        luzEncendida=true;
      } 
      else {  // si la pantalla esta encendida seguimos funcionando normalmente
        lcd.setCursor(x, 1);
        oldkey = key;
        if (key >=0){  // Si se ha pulsado cualquier tecla
          lcd.blink();  // Mostramos el cursor parpadeando
          cursorActivo=true;
        }
        if (key == 0){  // Se ha pulsado la tecla derecha
          x++;
          if (x>15) x=15;
          caracterActual='A';
        }
        if (key == 1) {  // Se ha pulsado la tecla arriba
          caracterActual++;
          if (caracterActual > 'Z') caracterActual='Z';
          lcd.write(caracterActual);
        }
        if (key == 2) {  // Se ha pulsado la tecla abajo
          caracterActual--;
          if (caracterActual < 'A') caracterActual='A';
          lcd.write(caracterActual);
        }
        if (key == 3) {  // Se ha pulsado la tecla izquierda
          x--;
          if (x<0) x=0;
          caracterActual='A';
        }
        if (key == 4){  // Se ha pulsado la tecla de seleccion
        }
        lcd.setCursor(x, 1);
      }
    }
  }
  delay(100);
}

// Convertimos el valor leido en analogico en un numero de boton pulsado
int get_key(unsigned int input)
{
  int k;

  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k])
    {
      return k;
    }
  }

  if (k >= NUM_KEYS)k = -1;  // Error en la lectura
  return k;
}

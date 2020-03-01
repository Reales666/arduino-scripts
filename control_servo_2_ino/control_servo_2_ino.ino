
#include <Servo.h>

Servo myServo; //Declaramos una variable de tipo Servo
           
//Pin conexion Servo
int attachServo = 12;

//Pines conexion botones
int pinBoton1 = 22;
int pinBoton2 = 24;
int pinBoton3 = 26;

//Pines led 
int pinLed1 = 23;
int pinLed2 = 25;
int pinLed3 = 27;

//Estado previo de los botones
int prevBoton1;
int prevBoton2;
int prevBoton3;

//Estado de los botones
int boton1;
int boton2;
int boton3;

//Angulo del Servo
int angle;ºº

//Valores Iniciales
int anguloBoton1 = 0;
int anguloBoton2 = 180;
int anguloBoton3 = 90;
int anguloNeutro = 90;


//Tiempo de margen para el servo en ms
int espera = 15;

void setup()
{
  Serial.begin(9600);
  
  myServo.attach(attachServo);
  
  pinMode(pinBoton1, INPUT);
  pinMode(pinBoton2, INPUT);
  pinMode(pinBoton3, INPUT);
  
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  
  prevBoton1 = LOW;
  prevBoton2 = LOW;
  prevBoton3 = LOW;

  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
  digitalWrite(pinLed3, LOW);

  angle = anguloNeutro;
  
  delay(2000);
  
//  myServo.write(angle);
  
  Serial.println("Salgo de la configuracion");
}

//Control del servo mediante el potenciómetro
void loop()
{ 
  //Calculamos el angulo del servo
  boton1 = digitalRead(pinBoton1);
  boton2 = digitalRead(pinBoton2);
  boton3 = digitalRead(pinBoton3);
  
  /**
  * Boton1
  * Este lo pone a 0
  */
  if(boton1 != prevBoton1)
  {
    Serial.println("Estoy en el boton1");
    if(boton1 == HIGH)
    {
      if(angle == anguloBoton1)
      {
        Serial.println("Apago Boton 1");
        digitalWrite(pinLed1, LOW);
        angle = anguloNeutro;
        imprimir();
      }else
     { 
      if(angle == anguloNeutro)
      {
        Serial.println("Enciendo Boton 1");
        digitalWrite(pinLed1, HIGH);
        angle = anguloBoton1;
        imprimir();
      }
     }
    }
    
    prevBoton1 = boton1;
  }
  
  if(boton2 != prevBoton2)
  {
    Serial.println(boton2);
    
    if(boton2 == 1)
    {
      if(angle == anguloNeutro)
      {
        Serial.println("Enciendo Boton 2");
        digitalWrite(pinLed2, HIGH);
        angle = anguloBoton2;
        imprimir();
      }else
     { 
      if(angle == anguloBoton2)
      {
        Serial.println("Apago Boton 2");
        digitalWrite(pinLed2, LOW);
        angle = anguloNeutro;
        imprimir();
      }
     }
    }
    
    prevBoton2 = boton2;
  }  
  
  if(boton3 != prevBoton3)
  {
    Serial.println("Estoy en el boton3");
    Serial.println(boton3);
    if(boton3 == 1)
    {
      if(angle == anguloNeutro)
      {
        Serial.println("Enciendo Boton 3");
        digitalWrite(pinLed3, HIGH);
        angle = anguloBoton3;
        imprimir();
      }else
     { 
      if(angle == anguloBoton3)
      {
        Serial.println("Apago Boton 3");
        digitalWrite(pinLed3, LOW);
        angle = anguloNeutro;
        imprimir();
      }
     }
    }
    
    prevBoton3 = boton3;
  }
 
  Serial.println("Angulo = " + angle);
  myServo.write(angle);
  delay(espera);
}

void imprimir()
{
  Serial.print("Boton1: ");
  Serial.print(boton1);
  
  Serial.print(", Angle: ");
  Serial.println(angle);
}



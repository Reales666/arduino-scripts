//***************************************************************
//* Author: Alberto Reales Díaz - 71720363-S - ard13@alu.ua.es  *
//* Universidad de Alicante									 	*
//*																*
//* TRABAJO FINAL DE GRADO										*
//* Tutor: Diego Viejo Hernando - dviejo@dccia.ua.es			*
//***************************************************************

#include <String.h>
#include <LiquidCrystal.h>

// Sensor 1 Interruption Number - Pin 2
// #define sensorInterruptOne 0;

//Arduino Mega 2560 Pines

// Right Motor Pines
int motorEnablePin= 22; //Both motors has the same enable pin
int rightStepPin =	24;
int rightDirPin = 	26;

// Left Motor Pines
int leftStepPin = 	25;
int leftDirPin = 	27;

// Button Pines
int enableButtonPin = 5;

unsigned long tiempoIda1;
unsigned long tiempoVuelta1;
unsigned long tiempoTotal1;

int triggerSensor1 = 4;
volatile boolean updatedSensor1 = false;
boolean launchSignal1 = false;
unsigned long distanceSensor1;

// Motor State
// HIGH = Forward
// LOW = Backward
boolean leftMotorDir = HIGH;
boolean rightMotorDir = HIGH;

// Button States
boolean enableButton = false;
boolean prevEnablebutton = false;

// Robot States
boolean moving = false;

// Time Control
unsigned long startTime;
unsigned long currentTime;
unsigned long lcdOntime = 5000;

unsigned long clock1Init;
unsigned long clock1Current;
unsigned long clock1Limit = 100;

// Distance Sensor Values
byte distances[4];

/*
// Thermometer Read (0- 1023)
int thermoRead;

// Thermometer Volts
float thermoVolts;

// Thermometer Temp
float thermoTemp;
*/

// Lyquid Crystal Instance
// LiquidCrystal lcd(30, 32, 31, 33, 35, 37);
boolean lcdOn = true;
// boolean prevLcdOn = true;
// int lcdOnPin = 34;

void sensor1Ready()
{
	updatedSensor1 = true;
}

void showButtonState(String cadena)
{
	Serial.print(cadena);
	Serial.print(" - ");
	Serial.print("Estado boton: ");
	Serial.print(enableButton);
	Serial.print(", Estado previo Boton: ");
	Serial.println(prevEnablebutton);
}

void printScreen(String line1, String line2)
{
	String auxLine1 = line1.substring(0, 15);
	String auxLine2 = line2.substring(0, 15);

	// lcd.clear();
	// lcd.setCursor(0, 0);
	// lcd.print(auxLine1);

	// lcd.setCursor(0, 1);
	// lcd.print(auxLine2);
}

void setup()
{
	// Set motor connections
	pinMode(motorEnablePin, OUTPUT);
	pinMode(rightDirPin, OUTPUT);
	pinMode(rightStepPin, OUTPUT);
	pinMode(leftDirPin, OUTPUT);
	pinMode(leftStepPin, OUTPUT);
	// pinMode(lcdOnPin, OUTPUT);
	pinMode(triggerSensor1, OUTPUT);

	// digitalWrite(lcdOnPin, HIGH);

	digitalWrite(motorEnablePin, LOW);

	digitalWrite(rightDirPin, rightMotorDir); 
	digitalWrite(leftMotorDir, leftMotorDir);
	
	// Set on/off button
	pinMode(enableButtonPin, INPUT);

	// Set LCD Screen
	// lcd.begin(16, 2);
	// lcd.clear();
	printScreen("Proyecto TFG", "Alberto Reales");

	Serial.begin(9600);
	// Serial1.begin(9600);

	// Serial1.flush();
	attachInterrupt(1, sensor1Ready, FALLING);

	// delay(500);

	startTime = millis();
	clock1Init = millis();
}

void loop()
{
	// Serial.println("Itero!");
	// showButtonState("Previo");
	enableButton = digitalRead(enableButtonPin);

	currentTime = millis();

	if((currentTime - startTime) >= lcdOntime)
	{
		lcdOn = false;
	}

	if(enableButton != prevEnablebutton)
	{
		// showButtonState("Boton cmabiado");
		if(enableButton == true)
		{
			// showButtonState("Boton pulsado");
			digitalWrite(motorEnablePin, HIGH);
			prevEnablebutton = enableButton;

			// startTime = millis();

			lcdOn = true;

			if(moving)
			{
				// Serial.println("me paro");
				// printScreen("Parado", "");
				moving = false;
			}else
			{
				// Serial.println("Sigo");
				// printScreen("Funcionando...", "");
				moving = true;
			}
		}else
		{
			// showButtonState("boton soltado");
			digitalWrite(motorEnablePin, LOW);
			prevEnablebutton = enableButton;
		}
	}

	if(moving)
	{
		if(!launchSignal1)
		{
			Serial.println("Pulso Lanzado!");
			digitalWrite(triggerSensor1, LOW);
			delayMicroseconds(5);
			digitalWrite(triggerSensor1, HIGH);
			delayMicroseconds(10);

			tiempoIda1 = micros();
			launchSignal1 = true;
		}

		if(updatedSensor1)
		{
			Serial.println("Pulso recogido");
			tiempoVuelta1 = micros();
			tiempoTotal1 = tiempoVuelta1 - tiempoIda1;

			// Serial.print("Tiempo Ida: "); 
			//Serial.println(tiempoIda1);
			// Serial.print("Tiempo Vuelta: "); 
			// Serial.println(tiempoVuelta1);	
			// Serial.print("Tiempo Total: "); 
			// Serial.println(tiempoTotal1);

			distanceSensor1 = (int)(0.034 * tiempoTotal1)/2; // distancia en cm

			// Serial.print("Distancia: ");
			// Serial.println(distanceSensor1);

			updatedSensor1 = false;
			launchSignal1 = false;
		}

		if(distanceSensor1 >= 20)
		{
			// Serial.println("Palante");
			rightMotorDir = HIGH;
			leftMotorDir = LOW;
		}else
		{
			// Serial.println("Patras");
			rightMotorDir = LOW;
			leftMotorDir = HIGH;
		}

		digitalWrite(rightDirPin, rightMotorDir);
		digitalWrite(leftDirPin, leftMotorDir);
		digitalWrite(rightStepPin, HIGH);
		digitalWrite(leftStepPin, HIGH);

		delay(5);

		digitalWrite(rightStepPin, LOW);
		digitalWrite(leftStepPin, LOW);
	}
}
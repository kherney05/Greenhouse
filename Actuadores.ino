#include "Actuadores.h"
#include "Sensores.h"
#include <ESP32Servo.h>

//Instanciamos nuestro servo
Servo servo;
int pinServo = 15;

// inicializamos la posiscion de los servos de la ventana
int pos = 0;

// en esta funcion se pone los pines de los actuadores como salida
void actuadorSetup() {
  Serial.begin(115200);

  //dispositivos actuadore
  pinMode(bombaPin, OUTPUT);
  pinMode(tiraLedPin, OUTPUT);
  pinMode(ventiladorPin, OUTPUT);

  //alarmas visuales y sonicas
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  //Inicializamos la posicion del servo
  servo.attach(pinServo, 500, 2500);
}

//  esta funcion contiene las condiciones para que se activen o se desativen los diferentipos de actuadores 
void actuadores() {
  //condicional bomba
  if (humeFloor <= humbralHumeFloor) {
    digitalWrite(bombaPin, HIGH);
  } else {
    digitalWrite(bombaPin, LOW);
  }

  // condicional led rojo y alarma soninica
  if (humeFloor <= 0) {
    digitalWrite(ledRed, HIGH);
  } else {
    digitalWrite(ledRed, LOW);
  }
  // condicional led amarillo
  if (temp > humbralTemp) {
    digitalWrite(ledYellow, HIGH);
  } else {
    digitalWrite(ledYellow, LOW);
  }

  //condicional led verde
  if (temp < humbralTemp && humeFloor > humbralHumeFloor) {
    digitalWrite(ledGreen, HIGH);
  } else {
    digitalWrite(ledGreen, LOW);
  }

  // condicional ventilador
  if (hume < humbralHume || temp > humbralTemp) {
    digitalWrite(ventiladorPin, HIGH);
    ServosCerrar();
  } else {
    digitalWrite(ventiladorPin, LOW);
    ServosAbrir();
  }

  // condicional tira led
  if (lightValue < humbralLight) {
    digitalWrite(tiraLedPin, HIGH);
  } else {
    digitalWrite(tiraLedPin, LOW);
  }
}
// esta funcion abre las ventanas
void ServosAbrir() {
  //Ciclo que posicionara el servo desde 0 hsta 90 grados
  for (pos = 0; pos <= 90; pos += 1) {
    //Movemos el servo a los grados que le entreguemos
    servo.write(pos);
    delay(15);
  }
  
}
// esta funcion cierra las ventanas
void ServosCerrar() {
  //Ciclo que posicionara el servo desde 90 hsta 0 grados
  for (pos = 90; pos >= 0; pos -= 1) {
    //Movemos el servo a los grados que le entreguemos
    servo.write(pos);
    delay(15);
  }
}

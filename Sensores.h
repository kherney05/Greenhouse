#ifndef _Sensores_h_
#define _Sensores_h_

#include "DHT.h"

#define DHTPIN 14 //leemos la temperatura y la humedad a travez del pin 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//definio de los pines de los sensores 
extern const int lightPin = 34;
extern const int humeFloorPin = 35;

//inicializamos los valores de los sensores en cero
extern int lightValue = 0;
extern int humeFloor = 0;
extern float hume = 0;
extern float temp = 0;

//Funciones para obtener el valor de los sensores
void readLight(void);
void readHumeFloor(void);
void readTemp(void);

#endif
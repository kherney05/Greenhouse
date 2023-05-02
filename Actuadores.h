#ifndef _Actuadores_h_
#define _Actuadores_h_

// definicion de pines actuadores
extern const int bombaPin = 2;
extern const int tiraLedPin = 4;
extern const int ventiladorPin = 5;

//definicion de pines de alarmas visuales
extern const int ledRed = 25; // en este pin tambien se coneta la alarma sonica
extern const int ledYellow = 26;
extern const int ledGreen = 27;

// definicion de humbrales para los actuadores
extern int humbralHumeFloor = 10;
extern int humbralHume = 35;
extern int humbralTemp = 25;
extern int humbralLight = 20;

//definicion de las funciones de los actuadores
void actuadorSetup(void);
void ventilador(void);
void actuadores(void);
void ServosAbrir(void);
void ServosCerrar(void);



#endif
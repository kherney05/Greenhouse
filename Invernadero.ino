// incluimos las librerias
#include "Conection.h"
#include "AsyncTaskLib.h"
#include "Sensores.h"
#include "Actuadores.h"

#define DEBUG(a) \
  Serial.print(millis()); \
  Serial.print(": "); \
  Serial.println(a);

/*
  @ Creamos las tareas
  @ Medimos la temperatura cado 3 minutos = 180000 milisecunds.
  @ Medimos la luz cada 2 sgundos.
  @ medimos la humedad cada minuto.
  @ llamamos a los actuadores cada 2 segundos.
*/

AsyncTask asyncTaskTemp(180000, true, readTemp);
AsyncTask asyncTaskLight(2000, true, readLight);
AsyncTask asyncTaskHumeFloor(60000, true, readHumeFloor);
AsyncTask asyncTaskActuadores(1000, true, actuadores);

void setup() {
  conectionWifi();
  actuadorSetup();
  asyncTaskTemp.Start();
  asyncTaskLight.Start();
  asyncTaskHumeFloor.Start();
  asyncTaskActuadores.Start();
}

void loop() {
  //actualizamos los valores de los sensores
  asyncTaskTemp.Update();
  asyncTaskLight.Update();
  asyncTaskHumeFloor.Update();
  //actualizamos los actuadores
  asyncTaskActuadores.Update();
  //funcion que responde a las difernetes opciones del menu de telegram
  ifTelegramLoop ();
  //visualizamos los datos a traves del web server
  webServer();
}

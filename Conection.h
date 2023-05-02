#ifndef _Conection_h_
#define _Conection_h_

// definimos las funciones de las diferentes conexiones telegram, web server y wifi
void conectionWifi(void);
void handleNewMessages(int numNewMessages);
void ifTelegramLoop ();
void webServer(void);

#endif
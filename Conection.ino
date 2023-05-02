#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "WebServer.h"
#include "DHT.h"
#include <math.h>

// Wifi network station credentials
/*#define WIFI_SSID "Milagros_Rangel_5G"
#define WIFI_PASSWORD "milagros14"*/
/*#define WIFI_SSID "TP-LINK_DE16"
#define WIFI_PASSWORD "67743667"*/
#define WIFI_SSID "HUAWEI P30 Pro"
#define WIFI_PASSWORD "lacasa123"
/*#define WIFI_SSID "HOME-D817"
#define WIFI_PASSWORD "1061771886"*/

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output2State = "off";
String output4State = "off";
String output5State = "off";

// Assign output variables to GPIO pins
const int output2 = 2;
const int output4 = 4;
//const int output5 = 5;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "5894039918:AAEOr-rNYwHBe5_ryyRM0H1yzUuUrqRoF48"

const unsigned long BOT_MTBS = 1000;  // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;  // last time messages' scan has been done

// funcion para la conexion del wifi
void conectionWifi() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));
  //web server
  pinMode(bombaPin, OUTPUT);
  pinMode(tiraLedPin, OUTPUT);
  pinMode(ventiladorPin, OUTPUT);

  // Set outputs to LOW
  // Initialize the output variables as outputs
  pinMode(bombaPin, OUTPUT);
  pinMode(tiraLedPin, OUTPUT);
  pinMode(ventiladorPin, OUTPUT);

  // Set outputs to LOW
  digitalWrite(bombaPin, LOW);
  digitalWrite(tiraLedPin, LOW);
  digitalWrite(ventiladorPin, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  dht.begin();

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Add root certificate for api.telegram.org

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

// menu de telegram con opciones
void handleNewMessages(int numNewMessages) {
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "/temp") {
      temp = dht.readTemperature();
      round(temp);
      char cadenaTemp[50];
      sprintf(cadenaTemp, "La temperatura es de: %0.2f°C", temp);
      bot.sendMessage(chat_id, cadenaTemp);
    }

    if (text == "/hume") {
      hume = dht.readHumidity();
      round(hume);
      char cadenaHume[50];
      sprintf(cadenaHume, "La humedad es del: %0.2f", hume);
      bot.sendMessage(chat_id, cadenaHume);
    }

    if (text == "/luz") {
      lightValue = map(analogRead(lightPin),4092, 0, 0, 100);
      round(lightValue);
      char cadenaLuz[50];
      sprintf(cadenaLuz, "La luz es de: %d", lightValue);
      bot.sendMessage(chat_id, cadenaLuz);
    }

    if (text == "/humesuelo") {
      humeFloor = map(analogRead(humeFloorPin), 4092, 0, 0, 100);
      round(humeFloor);
      char cadenaHumeFloor[50];
      sprintf(cadenaHumeFloor, "La humedad del suelo es de: %d", humeFloor);
      bot.sendMessage(chat_id, cadenaHumeFloor);
    }

    if (text == "/info") {
      //temperature
      temp = dht.readTemperature();
      round(temp);
      char cadenaTemp[50];
      sprintf(cadenaTemp, "La temperatura es de: %0.2f°C", temp);
      bot.sendMessage(chat_id, cadenaTemp);

      //humidity
      hume = dht.readHumidity();
      round(hume);
      char cadenaHume[50];
      sprintf(cadenaHume, "La humedad es del: %0.2f", hume);
      bot.sendMessage(chat_id, cadenaHume);

      //ligth
      lightValue = map(analogRead(lightPin), 4092, 0, 0, 100);
      round(lightValue);
      char cadenaLuz[50];
      sprintf(cadenaLuz, "La luz es de: %d", lightValue);
      bot.sendMessage(chat_id, cadenaLuz);
      
      //humeFloor
      humeFloor = map(analogRead(humeFloorPin), 4092, 0, 0, 100);
      round(humeFloor);
      char cadenaHumeFloor[50];
      sprintf(cadenaHumeFloor, "La humedad del suelo es de: %d", humeFloor);
      bot.sendMessage(chat_id, cadenaHumeFloor);
    }

    if (text == "/start") {
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Flash Led Bot example.\n\n";
      welcome += "/ledon : to switch the Led ON\n";
      welcome += "/ledoff : to switch the Led OFF\n";
      welcome += "/temp : to switch the Led OFF\n";
      welcome += "/hume : to switch the Led OFF\n";
      welcome += "/luz : to switch the Led OFF\n";
      welcome += "/humesuelo : to switch the Led OFF\n";
      welcome += "/info : to switch the Led OFF\n";
      welcome += "/status : Returns current status of LED\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}

// funcion de telegran para responder a las diferentes opciones del menu
void ifTelegramLoop() {

  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}

//funcion para el contenido del web server
void webServer(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(bombaPin, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(bombaPin, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(tiraLedPin, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(tiraLedPin, LOW);
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(ventiladorPin, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(ventiladorPin, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<META HTTP-EQUIV='Refresh' CONTENT='1'>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");

            client.println("<h2>Light: " + String(lightValue) + "</h2>");;
            client.println("<h2>Floor's humidity: " + String(humeFloor) + "</h2>");;
            client.println("<h2>Humidity: " + String(hume) + "</h2>");;
            client.println("<h2>Temperature: " + String(temp) + "</h2>");;
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO 2 - State " + output2State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 4 - State " + output4State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("<p>GPIO 5 - State " + output5State + "</p>");
            // If the output28State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

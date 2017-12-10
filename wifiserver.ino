#include <ArduinoJson.h>
#include <ESP8266WiFi.h>


#define pin A0
const char *ssid = "JESUSMYSAVIOR";
const char *password = "salvador";
float tempc=0;
int samples[8]; 

IPAddress ip(192, 168, 0, 120);

//IP do roteador da sua rede wifi
IPAddress gateway(192, 168, 0, 1);

//Mascara de rede da sua rede wifi
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);

void setup()
{
  Serial.begin(9600);
  delay(10);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Conectado");

  // Start the server
  server.begin();
  Serial.println("Servidor Iniciado");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop()
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Wait until the client sends some data
  Serial.println("Novo Cliente");
  while (!client.available())
  {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("ler") != -1)
  {
    int i;
     for(i = 0;i<=7;i++){ // Loop que faz a leitura da temperatura 8 vezes
    samples[i] = ( 5.0 * analogRead(pin) * 100.0) / 1024.0;
    //A cada leitura, incrementa o valor da variavel tempc
    tempc = tempc + samples[i]; 
    delay(100);
     }
    tempc = tempc/8.0; 
  }
  

  String retorno = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n\r";
  client.print(retorno);

  String json = "{";
  json += "\"Temperatura\":"; 
  json += tempc;
  json += "}";
  Serial.println(json);
  client.print(json);
  delay(1);
  Serial.println("Client disonnected");
}

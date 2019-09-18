/* Código referente à captura de dados com 
  o sensor DHT11.

  Autor: MO technology
  Data: Setembro, 2019

*/


#include <dht.h>                         // Biblioteca do sensor DHT11

#define DHT11_PIN 5                      // Pino de transmissão de dados

dht DHT;                                 // Objeto Sensor 

String enviar;                          // Dados a serem enviados
String estado;                          // Variável para máquina de estados
int est_aux = 3;

void setup()
{
  Serial.begin(9600);
  
}

void loop()
{
  
  DHT.read11(DHT11_PIN);                // Realizando leitura
  int temperatura = DHT.temperature;    // Valor temperatura  
  int umidade     = DHT.humidity;       // Valor umidade

  switch (est_aux) {
    case 1:
      estado = "tarde";
      est_aux = 2;
      break;

    case 2:
      estado = "noite";
      est_aux = 3;
      break;

    case 3:
      estado = "manhã";
      est_aux = 1;
      break;    
  }

  enviar = "período:" + estado + " temperatura:" + String(temperatura) + " umidade:" + String(umidade); // Estrutura do dado a ser enviado

  Serial.println(enviar);
 
  delay(3000);
}




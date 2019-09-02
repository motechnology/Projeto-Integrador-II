/*
   Leitura e armazenamento de dados coletados pelo sensor DHT11.
   Autor: MO technology
   Data: Setembro de 2019
*/

#include <dht.h>   // Biblioteca DHT11
#include <Arduino_FreeRTOS.h> // Biblioteca FreeRTOS
#include <FreeRTOSVariant.h>

#define    dht_pin    5   // DHT11 ligado no pino digital 5

dht   sensor;   // Objeto para o sensor

int    temperatura = 0x00,   // Armazena a temperatura em inteiro
       umidade     = 0x00;   // Armazena a umidade em inteiro

QueueHandle_t filaTemperatura = NULL; // Fila para armazenar temperaturas
QueueHandle_t filaUmidade = NULL;     // Fila para armazenar umidades
int tamanhoFilaTotal = 3;

void setup() 
{
   Serial.begin(9600);   
   filaTemperatura = xQueueCreate(tamanhoFilaTotal, sizeof(int)); // Fila com tamanho 3 que armazenará dados inteiros
   filaUmidade     = xQueueCreate(tamanhoFilaTotal, sizeof(int)); // Fila com tamanho 3 que armazenará dados inteiros

} 

void loop() 
{
   sensor.read11(dht_pin);

   temperatura = sensor.temperature;
   umidade     = sensor.humidity;

   // Adicionando dados em suas respectivas listas
   // armazenaTemperaturas(temperatura);
   // armazenaUmidades(umidade);

   Serial.print(temperatura);
   Serial.print(" ");
   Serial.println(umidade);
   
   delay(1000);
 
} 
 
/* Armazena temperaturas lidas em uma lista */
void armazenaTemperaturas (int t) 
{
   int temperaturaLida = t;
   if (uxQueueMessagesWaiting(filaTemperatura)>tamanhoFilaTotal) {
      Serial.print("Fila de temperaturas cheia!");
   } 
   else {
      xQueueSendToBack(filaTemperatura, &temperaturaLida, 0);
   }
}

/* Armazena umidades lidas em uma lista */
void armazenaUmidades (int u) 
{
   int umidadeLida = u;
   if (uxQueueMessagesWaiting(filaUmidade)>tamanhoFilaTotal) {
      Serial.print("Fila de umidades cheia!");
   } 
   else {
      xQueueSendToBack(filaTemperatura, &umidadeLida, 0);
   }
}

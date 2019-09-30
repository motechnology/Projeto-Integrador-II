#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);                      //definindo portas CE porta 9 e CSN porta 10     
const uint64_t pipe1 = 0xE14BC8F482LL; //endereço de comunicação para abertura de pipe
int recebidos=0;                       //variável que receberá a mensagem a enviar

void setup()
{ 
  Serial.begin(9600);
  radio.begin();                     //Inicializa a comunicaçao entre os módulos
  radio.openReadingPipe(1, pipe1);   //Entra em modo de recepcao
  radio.startListening();            //Entra em modo de recepcao
  radio.setDataRate(RF24_250KBPS);   //Define a taxa de transmissão
}

void loop()
{
  
  if (radio.available()){                   
    radio.read(&recebidos, sizeof(int));  //lendo informações contidas no pipe1 e armazenando em recebidos
    Serial.print("Recebendo: ");
    Serial.println(recebidos);            //imprimindo em tela a variável recebida
  }
  delay(1000);    //delay para estabilização do sistema
}



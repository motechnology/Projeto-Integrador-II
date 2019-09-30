#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);                     //definindo portas CE porta 9 e CSN porta 10     
const uint64_t pipe1 = 0xE14BC8F482LL; //endereço de comunicação para abertura de pipe
int i=0;                               //variável que receberá a mensagem a enviar

void setup()
{ 
  Serial.begin(9600);
  radio.begin();                  //iniciando comunicação radio
  radio.openWritingPipe(pipe1);   //configurando endereço para comunicação pipe
  radio.stopListening();          //bloqueando estado de leitura no módulo de rádio
  radio.setDataRate(RF24_250KBPS);//Define a taxa de transmissão
}

void inicializacao(){
  radio.begin();                  //iniciando comunicação radio
  radio.openWritingPipe(pipe1);   //configurando endereço para comunicação pipe
  radio.stopListening();          //bloqueando estado de leitura no módulo de rádio
  radio.setDataRate(RF24_250KBPS);//Define a taxa de transmissão
}

void loop()
{ 
  Serial.print("Enviando:");
  radio.write(&i, sizeof(int));     //escrita no pipe1 da variável i
  Serial.println(i);                //impressão em tela da variável i
  i++;                              //incremento da variável i
  inicializacao();                  //inicialização para nova ponte de comunicação
  delay(3000);                      //delay para estabilização do sistema
}



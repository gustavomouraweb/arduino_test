#include <dht.h>                                                //  Inclui biblioteca dht.h
#include <SPI.h>                                                //  Inclui a biblioteca SPI.h
#include <Ethernet.h>                                           //  Inclui a biblioteca Ethernet.h

#define dht_dpin A1                                             //  Pino DATA do Sensor ligado na porta Analogica A1
dht DHT;                                                        //  Inicializa o sensor
int tempSensor;                                                 //  Declara variável tempSensor

// Configurações para o Ethernet Shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x83, 0xEA };            //  Entre com o valor do MAC
IPAddress ip(192,168,1,2);                                      //  Configure um IP válido 
byte gateway[] = { 192 , 168, 1, 1 };                           //  Entre com o IP do Computador onde a Câmera esta instalada
byte subnet[] = { 255, 255, 255, 0 };                           //  Entre com a Máskara de Subrede
EthernetServer server(80);                                      //  Inicializa a biblioteca EthernetServer com os valores de IP acima citados e configura a porta de acesso(80)


void setup()
{
  Ethernet.begin(mac, ip);                                      //  Inicializa o Server com o IP e Mac atribuido acima
  delay(1000);                                                  //  Aguarda 1 segundo para a inicialização do shield
}

void loop()
{
  EthernetClient client = server.available();                  //  Verifica se tem alguém conectado

  if (client){
    
    while ((client.connected())&&(client.available())){
      
      DHT.read11(dht_dpin);                                    //  Lê as informações do sensor
      tempSensor = DHT.temperature;                            //  Armazena a temperatura do Sensor
      client.print(tempSensor);                                //  Envia o valor da temperatura para o cliente     
      delay(1000);                                             //  Espera 1 segundo antes de reiniciar o ciclo

    }
    
    delay(1000);                                               //  Espera um tempo para o navegador receber os dados
    client.stop();                                             //  Fecha a conexão
    
  }
  
}

// Experimento 1 - Aula 4 - Sensor DHT11 (Temperatura e Umidade)

#include<dht.h>

dht DHT11;

#define DHT11_PIN A0

void setup(){
  Serial.begin(9600);

  Serial.println("DHT11");
}


void loop(){
  int chk = DHT11.read11(DHT11_PIN);

  Serial.print(" Umidade ");
  
  Serial.print(DHT11.humidity, 1);

  Serial.print(" ");

  Serial.print(" Temperatura ");

  Serial.println(DHT11.temperature, 1);

  delay(2000);
  
}

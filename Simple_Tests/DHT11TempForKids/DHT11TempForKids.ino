// Experimento 1 - Aula 4 - Sensor DHT11 (Temperatura e Umidade)

#include<dht.h>

dht DHT11;

#define DHT11_PIN A0

int VERMELHO = 8;
int AMARELO = 9;
int VERDE = 10;

void setup(){
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.println("DHT11");
}


void loop(){
  int chk = DHT11.read11(DHT11_PIN);

  Serial.print(" Umidade ");
  
  Serial.print(DHT11.humidity, 1);

  Serial.print(" ");

  Serial.print(" Temperatura ");

  Serial.println(DHT11.temperature, 1);

  if (DHT11.temperature < 30){
    Serial.println(" Temperatura está baixa. Você está viva mesmo? ");
    digitalWrite(VERMELHO, LOW);
    digitalWrite(AMARELO, HIGH);
    digitalWrite(VERDE, LOW);
  }
  else if (DHT11.temperature >= 30 && DHT11.temperature < 37.8){
    Serial.println(" Você está viva e a temperatura está normal, que bom! ");
    digitalWrite(VERMELHO, LOW);
    digitalWrite(AMARELO, LOW);
    digitalWrite(VERDE, HIGH);
  }
  else if (DHT11.temperature >= 37.8 && DHT11.temperature < 42.5){
    Serial.println(" Você está com febre. Procure a mamãe, para te dar Alivium! :-) ");
    digitalWrite(VERMELHO, HIGH);
    digitalWrite(AMARELO, LOW);
    digitalWrite(VERDE, LOW);
  }
  else{
    Serial.println(" Você está muito quente. Por acaso está pegando fogo ou te colocaram na churrasqueira? :-) ");
    digitalWrite(VERMELHO, HIGH);
    digitalWrite(AMARELO, HIGH);
    digitalWrite(VERDE, HIGH);
    delay(250);
    digitalWrite(VERMELHO, LOW);
    digitalWrite(AMARELO, LOW);
    digitalWrite(VERDE, LOW);
  }
  delay(250);
  
}

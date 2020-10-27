// Experimento 2 - Aula 2 - SENSOR DE CHAMAS/CHUVA

/* Exemplo de utilização de sensor de chamas/chuva.
  Baseado no original de Reichenstein7 (thejamerson.com)
*/

// leituras mínimas e máximas do sensor (treshold)
const int sensorMin = 0;     // mínima do sensor
const int sensorMax = 1024;  // máxima do sensor
int VERMELHO = 8;
int AMARELO = 9;
int VERDE = 10;


void setup() {
  // inicializando comunicação serial na banda 9600:
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
}
void loop() {
  // lendo sensor no pino analógico A0:
  int sensorReading = analogRead(A0);
  // mapeando o alcance do sensor (quatro opções):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 4);

  // valores de alcance possíveis:
  switch (range) {
    case 0:    // Sensor mais que encharcado
      Serial.println("Está parecendo um oceano.");
      digitalWrite(VERMELHO, HIGH);
      digitalWrite(AMARELO, HIGH);
      digitalWrite(VERDE, HIGH);
      break;
    case 1:    // Sensor encharcado
      Serial.println("Alerta enchente");
      digitalWrite(VERMELHO, HIGH);
      digitalWrite(AMARELO, LOW);
      digitalWrite(VERDE, LOW);
      break;
    case 2:    // Sensor detecta chuva
      Serial.println("Alerta de chuva");
      digitalWrite(VERMELHO, LOW);
      digitalWrite(AMARELO, HIGH);
      digitalWrite(VERDE, LOW);
      break;
    case 3:    // Sensor seco - se achar incoveniente ter sempre essa mensagem, delete ou comente a linha " Serial.println("Not Raining"); " abaixo.
      Serial.println("Nao esta chovendo");
      digitalWrite(VERMELHO, LOW);
      digitalWrite(AMARELO, LOW);
      digitalWrite(VERDE, HIGH);
      break;
  }
  delay(1);  // atraso entre leituras
}

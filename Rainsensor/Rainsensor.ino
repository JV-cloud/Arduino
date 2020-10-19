// Experimento 2 - Aula 2 - SENSOR DE CHAMAS/CHUVA

/* Exemplo de utilização de sensor de chamas/chuva.
  Baseado no original de Reichenstein7 (thejamerson.com)
*/

// leituras mínimas e máximas do sensor (treshold)
const int sensorMin = 0;     // mínima do sensor
const int sensorMax = 1024;  // máxima do sensor

void setup() {
  // inicializando comunicação serial na banda 9600:
  Serial.begin(9600);
}
void loop() {
  // lendo sensor no pino analógico A0:
  int sensorReading = analogRead(A0);
  // mapeando o alcance do sensor (quatro opções):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  // valores de alcance possíveis:
  switch (range) {
    case 0:    // Sensor encharcado
      Serial.println("Alerta de enchente");
      break;
    case 1:    // Sensor detecta chuva
      Serial.println("Alerta de chuva");
      break;
    case 2:    // Sensor seco - se achar incoveniente ter sempre essa mensagem, delete ou comente a linha " Serial.println("Not Raining"); " abaixo.
      Serial.println("Nao esta chovendo");
      break;
  }
  delay(1);  // atraso entre leituras
}

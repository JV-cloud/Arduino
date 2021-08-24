// Código simples para uso do sensor de presença PIRSensor
// Indicação no LED

int sensorState = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  sensorState = digitalRead(2);
  //Caso o sensor seja difícil para testar, alterne entre HIGH e LOW a linha abaixo, para ver o melhor resultado do experimento.
  if (sensorState == HIGH) { 
    digitalWrite(13, HIGH);
    Serial.println("Sensor corretamente ativado. Perigo!");
  } else {
    digitalWrite(13, LOW);
  }
  delay(15);
}

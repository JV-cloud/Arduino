//Piscar LED

//DECLARAÇÃO DE VARIÁVEIS

int LEDpin = 10;

void setup()
{
  pinMode(LEDpin, OUTPUT);
}

void loop()
{
  digitalWrite(LEDpin, HIGH);
  delay(500);
  digitalWrite(LEDpin, LOW);
  delay(500);
}

// Após o código acima, monte num protoboard um circuito com LED e resistor de 2,2kohm. GND do Arduino no negativo do LED e Porta 10 do Arduino no resistor
// Configure a porta serial / USB e faça o Upload do Sketch.

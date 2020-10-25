// Simples uso do Fotoresistor para escalas de luminosidade
// Uso prático para classificar um ambiente
// Ergonomia e saúde

# define VERDE 2
# define AMARELO 3
# define VERMELHO 4
# define BUZZER 5
# define Sensor A0

void setup(){
  // configura os pinos de 2 a 5 como OUTPUT
  for (int i =2; i < 6; i++)
    pinMode(i, OUTPUT);
  
  Serial.begin(9600);
}

void loop(){
  // altera os pinos de 2 a 5 para LOW
  for (int i =2; i < 6; i++)
    digitalWrite(i, LOW);

  // Chama a função
  status_Indicator();
}

void status_Indicator(){

  //Leitura do sensor fotoresistor
  int sensor_In = analogRead(A0);
  Serial.println(sensor_In);

  //Ajuste conforme a necessidade
  if ( sensor_In >=890 ){
    digitalWrite(VERMELHO, HIGH);
    digitalWrite(BUZZER, HIGH);
  }
  //Ajuste conforme a necessidade
  else if ( sensor_In >=680 ){
    digitalWrite(AMARELO, HIGH);
  }
  //Se abaixo que os 2 valores acima, então fica o LED Verde
  else{
    digitalWrite(VERDE, HIGH);
  }
  delay(15);
}

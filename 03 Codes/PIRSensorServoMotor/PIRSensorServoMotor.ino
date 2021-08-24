#include <Servo.h>

Servo MyServo;
const int SERVO_PIN = 9;
int LED_PIN = 2;
const int PIR_PIN = 7;
const int PIR_POS_PIN = 13;

void setup()
{
  Serial.begin(9600);
  MyServo.attach(SERVO_PIN);
  MyServo.write(0);
  pinMode(PIR_PIN, INPUT);
  pinMode(PIR_POS_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(PIR_POS_PIN, HIGH);
  
  Serial.println("Sensor Ativo");
}

void loop()
{
  if (digitalRead(PIR_PIN) == HIGH){
    digitalWrite(LED_PIN, HIGH);
    delay(3000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
    Serial.println("Movimento detectado em");
    Serial.println(millis()/1000);
    Serial.println("segundos.");
    MyServo.write(180);
    delay(500);
    MyServo.write(0);
  }
  else{
    digitalWrite(LED_PIN, LOW);
    MyServo.write(0);
  }
}

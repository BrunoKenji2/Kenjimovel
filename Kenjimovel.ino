#include "Ultrasonic.h"
int velocidade = 60;
// pinos do carro
const int dirEsq = 10;
const int dirDir = 8;
const int veloEsq = 11;
const int veloDir = 9;

const int pinEcho = 7;
const int pinTrig = 6;

const int led1 = 12;
const int led2 =13;

const int botao = 3;
const int buzzer = 5;
int valor;

int flag = 0;
int buzzer_state = LOW;

int buttonState;
int lastButtonState = LOW;

unsigned long lastDebounce = 0;
unsigned long debounceDelay = 30;

Ultrasonic ultrasonic(pinTrig,pinEcho); //inicializa os pinos do arduino

int distancia;
String resultado;

// função que pega a distancia com o sensor
void sensor_ultra(){

  digitalWrite(pinTrig,LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig,LOW);

  distancia = (ultrasonic.Ranging(CM));
  delay(500);
  
  }

void pwm(int pin1, int pin2){
   for(int i = 0; i<255; i++){
      analogWrite(pin2,i);
      analogWrite(pin1,i);
      delay(10);
    }
  
  }

void setup() {
  // put your setup code here, to run once:
    pinMode(dirEsq,OUTPUT);
    pinMode(dirDir,OUTPUT);
    pinMode(veloEsq,OUTPUT);
    pinMode(veloDir,OUTPUT);

    pinMode(pinEcho, INPUT);
    pinMode(pinTrig, OUTPUT);

    pinMode(led1, OUTPUT);
    pinMode(led2,OUTPUT);
    Serial.begin(9600);
    Serial1.begin(9600);

    pinMode(botao,INPUT);
    pinMode(buzzer,OUTPUT);
    
}

void loop() {
    
    sensor_ultra();
    Serial.print("Distancia :");
    Serial.println(distancia);

    
   if (Serial1.available()){ // Verificar se há caracteres disponíveis
        int caractere = Serial1.read();
        Serial.println(caractere);
        valor = caractere%2;
   } 
   if(distancia > 20 && valor == 1){
    digitalWrite(led1, LOW);
    digitalWrite(led2,LOW);
    digitalWrite(dirDir,LOW);
    digitalWrite(dirEsq,LOW);
    analogWrite(veloDir,velocidade);
    analogWrite(veloEsq, velocidade);
    flag = 0;
   }else{
        analogWrite(veloDir, 0);
        analogWrite(veloEsq,0);
        if(flag == 0){
        pwm(led1,led2);
        flag = 1;
        }
      }
   if(distancia < 3){
      digitalWrite(buzzer,HIGH);
    }else{
      digitalWrite(buzzer,LOW);
      }

}

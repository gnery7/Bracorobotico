//Desenvolvido por Geovanne Nery, Henrico Santa Rosa, Eduardo Guimarães e Luiz Ricardo em 06/06/22
//Braço Robotico com 5 motores MG996R

#include <Servo.h>

Servo servoBase, servoBraco1, servoBraco2, servoPulso, servoGarra;

int potpinBase = A0; //servoBase - Porta: D9
int potpinBraco1 = A1; //servoBraco1 - Porta: D6
int potpinBraco2 = A2; //servoBraco2 - Porta: D10
int potpinPulso = A3; //servoPulso - Porta: D5
int potpinGarra = A4; //servoGarra - Porta: D11
int valBase, valBraco1, valBraco2, valPulso, valGarra;
int buttonSwitch = 2;
int buttonPos1 = 7;
int buttonPos2 = 12;
int buttonPos3 = 11;
int buttonPos4 = 4;
bool operationMode = false; //Manual = False | Automático = True
bool status = false; //SEM OBJETO = false | COM OBJETO = true
unsigned long previousMillis_sI_M = 0;
unsigned long previousMillis_sI_A = 0;
const long interval_sI = 1500;

void potLoop() {
  valBase = analogRead(potpinBase);
  valBase = map(valBase, 0, 1021, 5, 175);
  servoBase.write(valBase);
  delay(15);
  valBraco1 = analogRead(potpinBraco1);
  valBraco1 = map(valBraco1, 0, 1021, 5, 165);
  servoBraco1.write(valBraco1);
  delay(15);
  valBraco2 = analogRead(potpinBraco2);
  valBraco2 = map(valBraco2, 0, 1021, 5, 165);
  servoBraco2.write(valBraco2);
  delay(15);
  valPulso = analogRead(potpinPulso);
  valPulso = map(valPulso, 0, 1021, 5, 165);
  servoPulso.write(valPulso);
  delay(15);
  valGarra = analogRead(potpinGarra);
  valGarra = map(valGarra, 0, 1021, 5, 165);
  servoGarra.write(valGarra);
  delay(15);
}

void serialInfo() {
  if (operationMode == false) {
    unsigned long currentMillis_sI_M = millis();
    if (currentMillis_sI_M - previousMillis_sI_M >= interval_sI) {
      previousMillis_sI_M = currentMillis_sI_M;
      Serial.print("\nBase - Servo | Potenciometro = ");
      Serial.println(valBase);
      Serial.print("Braco1 - Servo | Potenciometro = ");
      Serial.println(valBraco1);
      Serial.print("Braco2 - Servo | Potenciometro = ");
      Serial.println(valBraco2);
      Serial.print("Pulso - Servo | Potenciometro = ");
      Serial.println(valPulso);
      Serial.print("Garra - Servo | Potenciometro = ");
      Serial.println(valGarra);
    }
  }
  else {
    unsigned long currentMillis_sI_A = millis();
    if (currentMillis_sI_A - previousMillis_sI_A >= interval_sI) {
      previousMillis_sI_A = currentMillis_sI_A;
      Serial.println("");
      Serial.println("Modo automatico!");
    }
  }
}

void movServo(int mov1, int mov2, int mov3, int mov4, int mov5) {
  servoBase.write(mov1);
  delay(1000);
  servoBraco1.write(mov2);
  delay(1000);
  servoBraco2.write(mov3);
  delay(1000);
  servoPulso.write(mov4);
  delay(1000);
  servoGarra.write(mov5);
  delay(1000);
}

void posicaoPadrao() {
  servoBase.write(91);
  delay(1000);
  servoBraco1.write(5);
  delay(1000);
  servoBraco2.write(5);
  delay(1000);
  servoPulso.write(109);
  delay(1000);
  if (status == false) {
    servoGarra.write(96);
  }
  else {
    servoGarra.write(5);
  }
  delay(1000);
}

void buttonLoop() {
  if (digitalRead(buttonPos2) == HIGH) { //centro perto
    if (status == false) {
      posicaoPadrao();
      movServo(96, 48, 24, 165, 5);
      status = true;
      return;
    }
    else {
      posicaoPadrao();
      movServo(96, 48, 24, 165, 96);
      status = false;
      return;
    }
  }
  if (digitalRead(buttonPos3) == HIGH) { //lateral direita
    if (status == false) {
      posicaoPadrao();
      movServo(58, 47, 92, 76, 5);
      status = true;
      return;
    }
    else {
      posicaoPadrao();
      movServo(58, 47, 92, 76, 96);
      status = false;
      return;
    }
  }
  if (digitalRead(buttonPos4) == HIGH) { //centro longe
    if (status == false) {
      posicaoPadrao();
      movServo(92, 60, 133, 51, 5);
      status = true;
      return;
    }
    else {
      posicaoPadrao();
      movServo(92, 60, 133, 51, 96);
      status = false;
      return;
    }
  }
}

void switchMode() {
  operationMode = !operationMode;
};

void mainLoop() {
  buttonLoop();
}

void setup() {
  Serial.begin(9600);
  servoBase.attach(9);
  servoBraco1.attach(6);
  servoBraco2.attach(10);
  servoPulso.attach(5);
  servoGarra.attach(11);
  attachInterrupt(digitalPinToInterrupt(buttonSwitch), switchMode, RISING);
  pinMode(buttonPos1, INPUT);
  pinMode(buttonPos2, INPUT);
  pinMode(buttonPos3, INPUT);
  pinMode(buttonPos4, INPUT);
}

void loop() {
  mainLoop();
}

/* Programa para Balança com o HX711
 Blog Eletrogate - https://blog.eletrogate.com/balanca-digital-com-arduino-aprenda-a-usar-a-celula-de-carga
 Arduino UNO - IDE 1.8.5 - Modulo HX711 - celulas de Carga 50 Kg
 Gustavo Murta   17/abril/2019
 Biblioteca https://github.com/bogde/HX711
 Baseado em https://www.hackster.io/MOHAN_CHANDALURU/hx711-load-cell-amplifier-interface-with-arduino-fa47f3
*/
/*
#include "HX711.h"                 // Biblioteca HX711
#define DOUT A0                    // HX711 DATA OUT = pino A0 do Arduino
#define CLK A1                     // HX711 SCK IN = pino A1 do Arduino
HX711 balanca;                     // define instancia balança HX711
float calibration_factor = 447530.00;  // fator de calibração aferido na Calibraçao
void setup() {
  Serial.begin(9600);
  balanca.begin(DOUT, CLK);  // inicializa a balança
  Serial.println("Balança com HX711 - celula de carga 5 Kg");
  Serial.println("Pressione t para Tara");  // imprime no monitor serial
  balanca.set_scale(calibration_factor);    // ajusta fator de calibração
  balanca.tare();                           // zera a Balança
}
void loop() {
  Serial.print("Peso: ");                // imprime no monitor serial
  Serial.print(balanca.get_units(), 3);  // imprime peso na balança com 3 casas decimais
  Serial.println(" kg");                 // imprime no monitor serial
  delay(500);                            // atraso de 0,5 segundos
  if (Serial.available())                // se a serial estiver disponivel
  {
    char temp = Serial.read();       // le carcter da serial
    if (temp == 't' || temp == 'T')  // se pressionar t ou T
    {
      balanca.tare();                     // zera a balança
      Serial.println(" Balança zerada");  // imprime no monitor serial
    }
  }
}
*/

#include <HX711.h>

#define DOUT 6
#define CLK 7

HX711 balanca;

void setup() {
  Serial.begin(9600);
  balanca.begin(DOUT, CLK);
  balanca.set_scale(447530.00); // Use seu fator de calibração
  balanca.tare();
  Serial.println("Sensor HX711 Test");
}

void loop() {
  Serial.print("Peso: ");
  Serial.print(balanca.get_units(10), 3); // Obtém a média de 10 leituras
  Serial.println(" kg");
  delay(1000);
}




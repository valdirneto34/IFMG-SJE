#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>

#define DOUT 6
#define CLK 7
#define LED_R 8
#define LED_Y 9
#define LED_G 10
#define RELE 12
float calibration_factor = 447530.00, peso;
HX711 balanca;
LiquidCrystal_I2C lcd(0x27, 16, 2);
String lastMsg1;
String lastMsg2;

void ImpMsg(String msg1, String msg2, int led) {
  if (msg1 == lastMsg1 && msg2 == lastMsg2) {
    return;
  }
  lastMsg1 = msg1;
  lastMsg2 = msg2;
  switch (led) {
    case 0:
      {
        digitalWrite(LED_R, 1);
        digitalWrite(LED_Y, 1);
        digitalWrite(LED_G, 1);
        digitalWrite(RELE, 1);
      }
    case 1:
      {
        digitalWrite(LED_R, 1);
        digitalWrite(LED_Y, 0);
        digitalWrite(LED_G, 0);
        digitalWrite(RELE, 0);
        break;
      }
    case 2:
      {
        digitalWrite(LED_R, 0);
        digitalWrite(LED_Y, 1);
        digitalWrite(LED_G, 0);
        digitalWrite(RELE, 0);
        break;
      }
    case 3:
      {
        digitalWrite(LED_R, 0);
        digitalWrite(LED_Y, 0);
        digitalWrite(LED_G, 1);
        digitalWrite(RELE, 0);
        break;
      }
    default:
      {
        digitalWrite(LED_R, 0);
        digitalWrite(LED_Y, 0);
        digitalWrite(LED_G, 0);
        digitalWrite(RELE, 1);
        break;
      }
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg1);
  lcd.setCursor(0, 1);
  lcd.print(msg2);
}

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(RELE, OUTPUT);
  digitalWrite(LED_R, 0);
  digitalWrite(LED_Y, 0);
  digitalWrite(LED_G, 0);
  digitalWrite(RELE, 1);
  Wire.begin();
  lcd.init();
  delay(2000);
  lcd.backlight();
  lcd.clear();
  balanca.begin(DOUT, CLK);
  balanca.set_scale(calibration_factor);
  balanca.tare();
  ImpMsg("AGUARDANDO", "RECIPIENTE", 0);  // Mensagem inicial
}

void loop() {
  peso = balanca.get_units(3);
  if (peso > 0.008 && peso < 0.015) {
    ImpMsg("POTE", "PEQUENO", 3);
  } else if (peso > 0.018 && peso < 0.022) {
    ImpMsg("POTE", "MEDIO", 2);
  } else if (peso > 0.032 && peso < 0.036) {
    ImpMsg("POTE", "GRANDE", 1);
  } else if (peso > 0.036) {
    ImpMsg("PESO", "DESCONHECIDO", 1);
  } else {
    ImpMsg("AGUARDANDO", "RECIPIENTE", 0);  // Exibe a mensagem padrão se nenhuma condição for atendida
  }
  delay(1000);  // Adicione um delay para evitar leituras muito rápidas
}
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>

#define DOUT A0
#define CLK A1
float calibration_factor = 447530.00, peso;
HX711 balanca;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void ImpMsg(String msg1, String msg2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg1);
  lcd.setCursor(0, 1);
  lcd.print(msg2);
}

void setup() {
  Wire.begin();
  lcd.init();
  delay(2000);
  lcd.backlight();
  lcd.clear();
  balanca.begin(DOUT, CLK);
  balanca.set_scale(calibration_factor);
  balanca.tare();
  ImpMsg("AGUARDANDO", "RECIPIENTE"); // Mensagem inicial
}

void loop() {
  peso = balanca.get_units(3);
  if (peso > 0.008 && peso < 0.015) {
    ImpMsg("Pote", "Pequeno");
  } else if (peso > 0.018 && peso < 0.022) {
    ImpMsg("Pote", "Medio");
  } else if (peso > 0.032 && peso < 0.036) {
    ImpMsg("Pote", "Grande");
  } else {
    ImpMsg("AGUARDANDO", "RECIPIENTE"); // Exibe a mensagem padrão se nenhuma condição for atendida
  }
  delay(1000); // Adicione um delay para evitar leituras muito rápidas
}

/*
#include <HX711.h>
#define DOUT A4
#define CLK A5
float calibration_factor = 447530.00, peso;
HX711 balanca;

void ImpMsgSerial(String msg1, String msg2) {
  Serial.println(msg1 + " " + msg2);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando balanca...");
  balanca.begin(DOUT, CLK);
  balanca.set_scale(calibration_factor);
  balanca.tare();
  Serial.println("Tara realizada.");
}

void loop() {
  ImpMsgSerial("AGUARDANDO", "RECIPIENTE");
  while (true) {
    peso = balanca.get_units(3);
    if (peso > 0.008 && peso < 0.015) {
      ImpMsgSerial("Pote", "Pequeno");
    } else if (peso > 0.018 && peso < 0.022) {
      ImpMsgSerial("Pote", "Medio");
    } else if (peso > 0.032 && peso < 0.036) {
      ImpMsgSerial("Pote", "Grande");
    }
    delay(1000);
  }
}*/
/**
 * @file Enchedor_Teste_Tempo.ino
 * @brief Código de teste para medição de tempo de envase (Projeto SmartFill).
 * @author Valdir de Souza Carvalho Neto
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>

/** Definição dos pinos do Arduino. */
#define LED_VERMELHO 8
#define LED_AMARELO 9
#define LED_VERDE 10
#define DOUT 6
#define CLK 7
#define RELE 12
#define BOTAO_EMERGENCIA 3
#define BOTAO_RESET 2

/** * =================================================================
 * CONSTANTES DE TESTE (ALTERE AQUI PARA O TESTE DE 500mL)
 * =================================================================
 */
#define PESO_LIQUIDO_TESTE 0.500  // Mude para 0.500 no teste de 500mL
#define PESO_MINIMO_POTE 0.030    // Peso mínimo para iniciar (30g)
#define PESO_MAXIMO_POTE 0.080    // Margem superior para o pote vazio

#define CALIBRATION_FACTOR 447530.00
#define TIMEOUT_ENCHIMENTO 120000 // Aumentado para 120s por segurança nos 500mL

float MAX_PESO;
float PESO_ATUAL;
volatile bool EMERGENCIA = false;
bool displayEmergenciaJaMostrado = false;

String msg1, msg2;

HX711 balanca;
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool delayComEmergencia(unsigned long ms) {
  unsigned long startTime = millis();
  while ((millis() - startTime) < ms) {
    if (EMERGENCIA) {
      return true;
    }
    delay(10);
  }
  return false;
}

void exibirEstado(const String& msg1, const String& msg2, const String& cor) {
  static String lastMsg1 = "";
  static String lastMsg2 = "";
  static String lastCor = "";
  if (msg1 != lastMsg1 || msg2 != lastMsg2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(msg1);
    lcd.setCursor(0, 1);
    lcd.print(msg2);
    lastMsg1 = msg1;
    lastMsg2 = msg2;
  }

  if (cor != lastCor) {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);

    if (cor == "vermelho") {
      digitalWrite(LED_VERMELHO, HIGH);
    } else if (cor == "verde") {
      digitalWrite(LED_VERDE, HIGH);
    } else if (cor == "amarelo") {
      digitalWrite(LED_AMARELO, HIGH);
    } else if (cor == "todos") {
      digitalWrite(LED_VERMELHO, HIGH);
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_AMARELO, HIGH);
    }
    lastCor = cor;
  }
}

float aguardarEstabilizacao(unsigned long timeoutMs = 2000) {
  float leituraAnterior = balanca.get_units(5);
  unsigned long inicio = millis();
  int leiturasEstaveis = 0;

  while ((millis() - inicio) < timeoutMs && leiturasEstaveis < 3) {
    float leituraAtual = balanca.get_units(5);
    float diferenca = abs(leituraAtual - leituraAnterior);

    if (diferenca < 0.005) { 
      leiturasEstaveis++;
    } else {
      leiturasEstaveis = 0;
    }

    leituraAnterior = leituraAtual;
    delay(100);
  }
  return balanca.get_units(5); 
}

bool executarEnchimentoTeste(float pesoInicial, float pesoAlvo) {
  exibirEstado("   INICIANDO", "     EM 3", "amarelo");
  if (delayComEmergencia(1000)) return false;
  exibirEstado("   INICIANDO", "     EM 2", "amarelo");
  if (delayComEmergencia(1000)) return false;
  exibirEstado("   INICIANDO", "     EM 1", "amarelo");
  if (delayComEmergencia(1000)) return false;

  PESO_ATUAL = balanca.get_units(5);
  
  if (PESO_ATUAL < PESO_MINIMO_POTE) {
    exibirEstado("    OPERACAO", "   CANCELADA", "todos");
    delayComEmergencia(3000);
    return false;
  }

  msg1 = " PESO: " + String(PESO_ATUAL, 3) + " KG";
  msg2 = " MAX: " + String(pesoAlvo, 3) + " KG";
  exibirEstado(msg1, msg2, "amarelo");
  
  // Liga a bomba (relé ativa com LOW)
  digitalWrite(RELE, LOW);
  delay(100);
  
  unsigned long tempoInicio = millis();
  unsigned long ultimaAtualizacao = 0;
  
  // Loop de enchimento
  while (PESO_ATUAL < pesoAlvo && !EMERGENCIA) {
    if ((millis() - tempoInicio) > TIMEOUT_ENCHIMENTO) {
      digitalWrite(RELE, HIGH);
      delay(100);
      exibirEstado("TEMPO ESGOTADO", "CANCELAR ENVASE", "todos");
      delayComEmergencia(4000);
      return false;
    }

    PESO_ATUAL = balanca.get_units(5);

    if (PESO_ATUAL < PESO_MINIMO_POTE) {
      digitalWrite(RELE, HIGH);
      delay(100);
      exibirEstado(" POTE REMOVIDO", "CANCELOU ENVASE", "todos");
      delayComEmergencia(4000);
      return false;
    }

    if (millis() - ultimaAtualizacao > 500) {
      msg1 = " PESO: " + String(PESO_ATUAL, 3) + " KG";
      msg2 = " MAX: " + String(pesoAlvo, 3) + " KG";
      exibirEstado(msg1, msg2, "amarelo");
      ultimaAtualizacao = millis();
    }
    delay(50);
  }

  // Desliga a bomba
  digitalWrite(RELE, HIGH);
  unsigned long tempoFinal = millis(); // Captura o tempo final exato
  delay(100);
  
  if (EMERGENCIA) return false;

  // Calcula o tempo decorrido em segundos
  float tempoSegundos = (tempoFinal - tempoInicio) / 1000.0;

  // Exibe o tempo final para você anotar na sua tabela
  exibirEstado("TEMPO: " + String(tempoSegundos, 1) + "s", "   FINALIZADO", "verde");
  delayComEmergencia(10000); // Fica na tela por 8 segundos para você anotar

  return true;
}

void handleEmergencyButton() {
  digitalWrite(RELE, HIGH);
  EMERGENCIA = true;
  displayEmergenciaJaMostrado = false;
}

void handleResetButton() {
  if (EMERGENCIA) {
    EMERGENCIA = false;
    displayEmergenciaJaMostrado = false;
  }
}

void setup() {
  pinMode(BOTAO_EMERGENCIA, INPUT_PULLUP);
  pinMode(BOTAO_RESET, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BOTAO_EMERGENCIA), handleEmergencyButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(BOTAO_RESET), handleResetButton, FALLING);
  
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(RELE, OUTPUT);
  
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(RELE, HIGH);

  balanca.begin(DOUT, CLK);
  delay(100);
  balanca.set_scale(CALIBRATION_FACTOR);
  balanca.tare(20);

  EMERGENCIA = false;
  displayEmergenciaJaMostrado = false;

  exibirEstado("   AGUARDANDO", "   POTE TESTE", "vermelho");
}

void loop() {
  PESO_ATUAL = balanca.get_units(5);
  
  if (EMERGENCIA) {
    digitalWrite(RELE, HIGH);
    if (!displayEmergenciaJaMostrado) {
      exibirEstado(" EM  EMERGENCIA", "  APERTE RESET", "todos");
      displayEmergenciaJaMostrado = true;
    }
    return;
  }

  // Verifica se colocou o pote teste na balança
  if (PESO_ATUAL >= PESO_MINIMO_POTE && PESO_ATUAL <= PESO_MAXIMO_POTE) {
    exibirEstado("   AGUARDE...", " ESTABILIZANDO", "amarelo");
    float pesoEstavel = aguardarEstabilizacao(1500);

    if (pesoEstavel >= PESO_MINIMO_POTE && pesoEstavel <= PESO_MAXIMO_POTE) {
      // Calcula o alvo baseando-se no que definimos lá no topo do código
      MAX_PESO = pesoEstavel + PESO_LIQUIDO_TESTE;
      
      executarEnchimentoTeste(pesoEstavel, MAX_PESO);
    }
  }
  else if (PESO_ATUAL > PESO_MAXIMO_POTE) {
    exibirEstado(" POTE NAO VAZIO", " COLOQUE VAZIO", "todos");
    delayComEmergencia(3000);
  }
  else {
    exibirEstado("   AGUARDANDO", "   POTE TESTE", "vermelho");
    delayComEmergencia(500);
  }
}
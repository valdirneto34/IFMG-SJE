/**
 * @file Classificador_Potes_Peso.ino
 * @brief Sistema de identificação de tipo de recipiente por peso usando HX711 e LCD I2C.
 * @author Valdir de Souza Carvalho Neto
 * @date 22/05/2025
 * @version 1.2
 *
 * Este código mede o peso de um recipiente usando um sensor HX711 e o classifica
 * como Pequeno, Médio ou Grande com base em faixas de peso predefinidas.
 * As informações são exibidas em um display LCD I2C, e LEDs indicam o estado
 * e o tipo de recipiente detectado.
 *
 * Hardware Necessário:
 * - Arduino Uno
 * - Sensor de peso HX711
 * - Display LCD 16x2 I2C
 * - LEDs (vermelho, amarelo, verde)
 *
 * Conexões Essenciais:
 * - HX711: DOUT (Pino Digital 6), CLK (Pino Digital 7)
 * - LCD I2C: SDA (Pino Analógico A4), SCL (Pino Analógico A5)
 * - LED Vermelho: Pino Analógico A0
 * - LED Amarelo: Pino Analógico A1
 * - LED Verde: Pino Analógico A2
 */

// Inclusão de bibliotecas
#include <Wire.h>               // Necessária para comunicação I2C (para o LCD)
#include <LiquidCrystal_I2C.h>  // Biblioteca para o display LCD I2C
#include <HX711.h>              // Biblioteca para o sensor de peso HX711

/** Definição dos pinos do Arduino. */
#define LED_VERMELHO 8
#define LED_AMARELO 9
#define LED_VERDE 10
// Pinos para o HX711 - foram movidos para evitar conflito com I2C (A4/A5)
#define DOUT A0  // Pino de dados do HX711
#define CLK A1   // Pino de clock do HX711

/** Constantes e variáveis globais. */
float const CALIBRATION_FACTOR = 447530.00; /** Fator de calibração do sensor de peso. */
float PESO_ATUAL;                           // Peso atual lido pelo sensor.

/** Instâncias dos objetos. */
HX711 balanca;  // Objeto para o sensor de peso
// Objeto para o LCD I2C (endereço 0x27, 16 colunas, 2 linhas)
// Verifique o endereço correto do seu LCD com um scanner I2C (ex: 0x27 ou 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

/**
 * @brief Exibe mensagens no display LCD e controla as cores dos LEDs.
 * Esta função otimiza a escrita no LCD para evitar piscar, atualizando apenas se a mensagem
 * ou cor mudou.
 * @param msg1 Mensagem da primeira linha do LCD (padrão "sa" para sem alteração).
 * @param msg2 Mensagem da segunda linha do LCD (padrão "sa" para sem alteração).
 * @param cor Cor dos LEDs ("vermelho", "amarelo", "verde", "todos" ou "sa" para sem alteração).
 */
void exibirEstado(const String& msg1 = "sa", const String& msg2 = "sa", const String& cor = "sa") {
  // Variáveis estáticas para guardar o último estado exibido e evitar reescrita desnecessária
  static String lastMsg1 = "";
  static String lastMsg2 = "";
  static String lastCor = "";

  // Verifica se a mensagem da primeira linha ou da segunda linha mudou
  if (msg1 != "sa" && (msg1 != lastMsg1 || msg2 != lastMsg2)) {
    lcd.clear();          // Limpa o LCD para exibir a nova mensagem
    lcd.setCursor(0, 0);  // Posiciona o cursor na primeira linha
    lcd.print(msg1);      // Imprime a primeira mensagem
    lcd.setCursor(0, 1);  // Posiciona o cursor na segunda linha
    lcd.print(msg2);      // Imprime a segunda mensagem
    lastMsg1 = msg1;      // Atualiza o último estado da primeira mensagem
    lastMsg2 = msg2;      // Atualiza o último estado da segunda mensagem
  }

  // Verifica se a cor dos LEDs mudou
  if (cor != "sa" && cor != lastCor) {
    // Apaga todos os LEDs e acende apenas os da cor especificada
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);

    if (cor == "vermelho") {
      digitalWrite(LED_VERMELHO, HIGH);
    } else if (cor == "verde") {
      digitalWrite(LED_VERDE, HIGH);
    } else if (cor == "amarelo") {
      digitalWrite(LED_AMARELO, HIGH);
    } else if (cor == "todos") {  // Acende todos os LEDs
      digitalWrite(LED_VERMELHO, HIGH);
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_AMARELO, HIGH);
    }
    lastCor = cor;  // Atualiza o último estado da cor
  }
}

/**
 * @brief Mede o peso atual na balança e exibe o tipo de pote no LCD,
 * controlando os LEDs de acordo.
 * @param peso_atual O peso atual lido pela balança.
 */
void MedePeso(float peso_atual) {
  if (peso_atual > 0.008 && peso_atual < 0.015) {
    exibirEstado("   POTE", "   PEQUENO", "vermelho");
  } else if (peso_atual > 0.018 && peso_atual < 0.022) {
    exibirEstado("   POTE", "   MEDIO", "amarelo");
  } else if (peso_atual > 0.032 && peso_atual < 0.036) {
    exibirEstado("   POTE", "   GRANDE", "verde");
  } else {
    // Se o peso não se encaixa em nenhuma categoria conhecida
    // Você pode ajustar a mensagem ou cor para "Pote Desconhecido" ou "Posicione Pote"
    exibirEstado("   POSICIONE", "   RECIPIENTE", "todos");  // Acende todos os LEDs para indicar um estado de espera/indefinido
  }
}

/**
 * @brief Configura o hardware e inicializa o sistema.
 * É executada uma única vez ao ligar ou reiniciar o Arduino.
 */
void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial para depuração (opcional)

  // Configura os pinos dos LEDs como saída
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  // O relé (pino 4) e outros pinos (2,3,5) não são usados neste código simplificado,
  // então não precisam ser configurados aqui se não tiverem função.

  // Inicializa a comunicação I2C e o display LCD
  Wire.begin();     // Inicia a biblioteca Wire para comunicação I2C
  lcd.init();       // Inicializa o display LCD
  lcd.backlight();  // Liga a luz de fundo do LCD
  lcd.clear();      // Limpa o conteúdo do LCD

  // Garante que todos os LEDs comecem desligados
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);

  // Inicializa o sensor de peso HX711
  balanca.begin(DOUT, CLK);
  balanca.set_scale(CALIBRATION_FACTOR);  // Aplica o fator de calibração
  balanca.tare();                         // Zera a balança (subtrai o peso atual como referência)

  // Exibe a mensagem inicial de aguardo
  exibirEstado("   INICIANDO...", "", "todos");                // Acende todos os LEDs rapidamente
  delay(1000);                                                 // Exibe por 1 segundo
  exibirEstado("   AGUARDANDO", "   RECIPIENTE", "vermelho");  // Estado inicial
}

/**
 * @brief Loop principal do programa.
 * É executado repetidamente enquanto o Arduino estiver ligado.
 */
void loop() {
  PESO_ATUAL = balanca.get_units(3);  // Obtém a média de 3 leituras para maior estabilidade
  MedePeso(PESO_ATUAL);               // Chama a função para medir e exibir o tipo de pote
  delay(100);                         // Pequeno atraso para não sobrecarregar o loop e o LCD
}
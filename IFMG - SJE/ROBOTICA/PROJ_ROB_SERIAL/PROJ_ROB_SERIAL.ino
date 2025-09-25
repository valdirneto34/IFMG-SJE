/**
 * @file Enchedor_Automatico.ino
 * @brief Sistema de enchimento automático com controle de peso.
 * @author Valdir de Souza Carvalho Neto
 * @date 27/02/2025
 * @version 1.0
 *
 * Este código implementa um sistema de enchimento automático que utiliza um sensor de peso (HX711)
 * para controlar o enchimento de recipientes. O sistema mede o peso do recipiente, inicia o
 * enchimento se o peso estiver dentro de um intervalo válido e para o enchimento quando o
 * peso máximo é atingido. O sistema possui um botão de emergência que interrompe o processo de
 * enchimento.
 *
 * Hardware Necessário:
 * - Arduino
 * - Sensor de peso HX711
 * - Relé
 * - LEDs (vermelho, amarelo, verde)
 * - Botão
 *
 * Conexões:
 * - HX711: DOUT (A4), CLK (A5)
 * - Relé: Pino 4
 * - LEDs: Vermelho (A0), Amarelo (A1), Verde (A2)
 * - Botão: Pino 2
 */

#include <HX711.h> /** Biblioteca para o sensor de peso HX711. */

/** Definição dos pinos. */
#define LED_VERMELHO A0
#define LED_AMARELO A1
#define LED_VERDE A2
#define DOUT A4
#define CLK A5
#define RELE 4
#define BOTAO 2

/** Constantes e variáveis. */
float const CALIBRATION_FACTOR = 447530.00; /** Fator de calibração do sensor de peso. */
float MAX_PESO, PESO_ATUAL;                 /** Pesos máximo e atual. */
bool EMERGENCIA = false;                    /** Estado de emergência. */

/** Instâncias dos objetos. */
HX711 balanca;

/**
 * @brief Exibe mensagens no monitor serial e controla as cores dos LEDs.
 * @param msg Mensagem a ser exibida no monitor serial.
 * @param cor Cor dos LEDs ("vermelho", "amarelo", "verde", "todos" ou "sa" para sem alteração).
 *
 * As cores dos LEDs indicam o estado do sistema:
 * - Vermelho: Aguardando recipiente.
 * - Amarelo: Enchendo recipiente.
 * - Verde: Recipiente cheio.
 * - Todos: Operação cancelada ou emergência acionada.
 */
void exibirEstado(const String& msg, const String& cor = "sa") {
  Serial.println(msg);

  if (cor != "sa") {
    digitalWrite(LED_VERMELHO, cor == "vermelho" || cor == "todos");
    digitalWrite(LED_VERDE, cor == "verde" || cor == "todos");
    digitalWrite(LED_AMARELO, cor == "amarelo" || cor == "todos");
  }
}

/**
 * @brief Configura o hardware e inicializa o sistema.
 *
 * Inicializa o sensor de peso, configura o botão de emergência e exibe a mensagem
 * inicial no monitor serial.
 */
void setup() {
  Serial.begin(9600); /** Inicializa a comunicação serial na taxa de 9600 bps. */
  attachInterrupt(
    digitalPinToInterrupt(BOTAO), []() {
      digitalWrite(RELE, LOW);
      EMERGENCIA = !EMERGENCIA;
    },
    RISING);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(RELE, OUTPUT);
  balanca.begin(DOUT, CLK);
  balanca.set_scale(CALIBRATION_FACTOR);
  balanca.tare();
  exibirEstado("AGUARDANDO RECIPIENTE", "vermelho");
}

/**
 * @brief Loop principal do programa.
 */
void loop() {
  /** Obtém a média de 3 leituras do sensor de peso. */
  PESO_ATUAL = balanca.get_units(3);

  /** Verifica se o peso inicial é válido e inicia o processo de enchimento. */
  if (PESO_ATUAL > 0.005 && PESO_ATUAL < 0.04 && !EMERGENCIA) {
    /** Inicia a sequência de inicialização com uma contagem regressiva. */
    exibirEstado("INICIANDO EM 3");
    delay(1000);
    exibirEstado("INICIANDO EM 2");
    delay(1000);
    exibirEstado("INICIANDO EM 1");
    delay(1000);

    /** Verifica se a operação deve ser cancelada devido ao peso inadequado ou emergência. */
    PESO_ATUAL = balanca.get_units(3);
    if (PESO_ATUAL < 0.005 || PESO_ATUAL > 0.04 || EMERGENCIA) {
      exibirEstado("OPERACAO CANCELADA", "todos");
      delay(3000);
      return;
    } else if (PESO_ATUAL > 0.008 && PESO_ATUAL < 0.015) {
      MAX_PESO = 0.2 + PESO_ATUAL;
    } else if (PESO_ATUAL > 0.018 && PESO_ATUAL < 0.022) {
      MAX_PESO = 0.5 + PESO_ATUAL;
    } else if (PESO_ATUAL > 0.032 && PESO_ATUAL < 0.036) {
      MAX_PESO = 1.0 + PESO_ATUAL;
    } else {
      /** Cancela a operação se o peso inicial não se encaixar em nenhuma faixa. */
      exibirEstado("PESO DESCONHECIDO", "todos");
      delay(3000);
      return;
    }
    exibirEstado("PESO: " + String(PESO_ATUAL, 3) + " KG - MAX: " + String(MAX_PESO, 3) + " KG", "amarelo");
    digitalWrite(RELE, HIGH); /** Inicia o processo de enchimento do recipiente. */

    /** Monitora o peso durante o enchimento. */
    while (PESO_ATUAL < MAX_PESO && !EMERGENCIA) {
      PESO_ATUAL = balanca.get_units(3);
      exibirEstado("PESO: " + String(PESO_ATUAL, 3) + " KG - MAX: " + String(MAX_PESO, 3) + " KG");
      delay(50); /** Tempo de estabilização */
    }

    digitalWrite(RELE, LOW); /** Finaliza o enchimento desligando o relé. */

    /** Verifica se a emergência foi acionada durante o enchimento. */
    if (EMERGENCIA) {
      return; /** Interrompe a execução se a emergência foi acionada. */
    }

    /** Exibe mensagem de recipiente cheio e aguarda antes de reiniciar o sistema. */
    exibirEstado("RECIPIENTE CHEIO", "verde");
    delay(3000);
  } else if (EMERGENCIA) {
    /** Trata o estado de emergência, exibindo mensagem e aguardando reinicialização. */
    exibirEstado("EMERGENCIA ACIONADA", "todos");
    delay(3000);
    if (EMERGENCIA) {
      exibirEstado("APERTE NOVAMENTE PARA REINICIAR");
    }
    while (EMERGENCIA) {}
  } else {
    /** Exibe mensagem de aguardo */
    exibirEstado("AGUARDANDO RECIPIENTE", "vermelho");
    delay(500);
  }
}
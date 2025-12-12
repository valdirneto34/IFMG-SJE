/**
 * @file Enchedor_Automatico.ino
 * @brief Sistema de enchimento automático com controle de peso.
 * @author Valdir de Souza Carvalho Neto
 * @date 27/08/2025
 * @version 2.1
 *
 * Este código implementa um sistema de enchimento automático que utiliza um sensor de peso (HX711)
 * para controlar o enchimento de recipientes. O sistema mede o peso do recipiente, inicia o
 * enchimento se o peso estiver dentro de um intervalo válido e para o enchimento quando o
 * peso máximo é atingido. Possui um sistema de segurança robusto com um botão de emergência
 * para interromper o processo imediatamente e um botão de reset dedicado para retomar a operação.
 * A lógica de controle do relé foi ajustada para operar com módulos que ATIVAM com LOW
 * e DESATIVAM com HIGH.
 *
 * Hardware Necessário:
 * - Arduino Uno
 * - Sensor de peso HX711
 * - Display LCD 16x2 I2C
 * - Módulo Relé (conectado de forma que o pino de controle do Arduino ATIVE o relé com LOW, e DESATIVE com HIGH)
 * - LEDs (vermelho, amarelo, verde)
 * - Botão de Emergência (físico, com pull-up interno/externo, aciona interrupção em LOW)
 * - Botão de Reset (físico, com pull-up interno/externo, aciona interrupção em LOW)
 *
 * Conexões Essenciais:
 * - HX711: DOUT (A0), CLK (A1) 
 * - LCD I2C: SDA (A4), SCL (A5)
 * - Relé: Pino Digital 4 (Conectado ao pino de controle do módulo relé. A fonte na COM, e o fio da bomba no NA)
 * - LED Vermelho: Pino Digital 8
 * - LED Amarelo: Pino Digital 9
 * - LED Verde: Pino Digital 10
 * - Botão de Emergência: Pino Digital 2 (conectado ao GND, usando INPUT_PULLUP)
 * - Botão de Reset: Pino Digital 3 (conectado ao GND, usando INPUT_PULLUP)
 */

// Inclusão de bibliotecas
#include <Wire.h>               // Necessária para comunicação I2C (para o LCD)
#include <LiquidCrystal_I2C.h>  // Biblioteca para o display LCD I2C
#include <HX711.h>              // Biblioteca para o sensor de peso HX711

/** Definição dos pinos do Arduino. */
#define LED_VERMELHO 8
#define LED_AMARELO 9
#define LED_VERDE 10
#define DOUT A0             // Pino de dados do HX711
#define CLK A1              // Pino de clock do HX711
#define RELE 12              // Pino de controle do relé
#define BOTAO_EMERGENCIA 3  // Pino para o botão de emergência (com interrupção)
#define BOTAO_RESET 2       // Pino para o botão de reset (com interrupção)

/** Constantes e variáveis globais. */
// Fator de calibração da balança
float const CALIBRATION_FACTOR = 447530.00;
float MAX_PESO;    // Peso máximo a ser atingido para o enchimento
float PESO_ATUAL;  // Peso atual lido pelo sensor
// Variável volátil para o estado de emergência (compartilhada entre ISR e loop)
volatile bool EMERGENCIA = false;

// Variável volátil para controle de debounce na interrupção do botão de reset
volatile unsigned long ultimoTempoBotaoReset = 0;
// Tempo mínimo entre detecções de pressionamento para debounce do reset (em milissegundos)
const unsigned long TEMPO_DEBOUNCE_RESET = 200;

// Flag para garantir que as mensagens de emergência no LCD sejam exibidas apenas uma vez
bool displayEmergenciaJaMostrado = false;

/** Instâncias dos objetos. */
HX711 balanca;  // Objeto para o sensor de peso
// Objeto para o LCD I2C (endereço 0x27, 16 colunas, 2 linhas)
LiquidCrystal_I2C lcd(0x27, 16, 2);

/**
 * @brief Exibe mensagens no display LCD e controla as cores dos LEDs.
 * Esta função otimiza a escrita no LCD para evitar piscar, atualizando apenas se a mensagem
 * ou cor mudou.
 * @param msg1 Mensagem da primeira linha do LCD (padrão "sa" para sem alteração).
 * @param msg2 Mensagem da segunda linha do LCD (padrão "sa" para sem alteração).
 * @param cor Cor dos LEDs ("vermelho", "amarelo", "verde", "todos" ou "sa" para sem alteração).
 *
 * As cores dos LEDs indicam o estado do sistema:
 * - Vermelho: Aguardando recipiente / Estado inicial.
 * - Amarelo: Enchendo recipiente.
 * - Verde: Recipiente cheio.
 * - Todos: Operação cancelada ou emergência acionada.
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
    } else if (cor == "todos") {  // Acende todos os LEDs para indicar emergência/cancelamento
      digitalWrite(LED_VERMELHO, HIGH);
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_AMARELO, HIGH);
    }
    lastCor = cor;  // Atualiza o último estado da cor
  }
}

/**
 * @brief Função da Rotina de Serviço de Interrupção (ISR) para o Botão de Emergência.
 * Acionada na borda de queda (FALLING) do pino do botão de emergência.
 * Sua única responsabilidade é ATIVAR o estado de emergência.
 * O debounce é intencionalmente omitido aqui para resposta imediata.
 */
void handleEmergencyButton() {
  digitalWrite(RELE, HIGH);             // Desliga a bomba (relé ATIVA com LOW, DESATIVA com HIGH)
  EMERGENCIA = true;                    // Define o estado de emergência como verdadeiro
  displayEmergenciaJaMostrado = false;  // Reseta a flag para exibir as mensagens de emergência
}

/**
 * @brief Função da Rotina de Serviço de Interrupção (ISR) para o Botão de Reset.
 * Acionada na borda de queda (FALLING) do pino do botão de reset.
 * Inclui um mecanismo de debounce para evitar múltiplos resets por um único toque.
 */
void handleResetButton() {
  // Implementa um debounce simples para o botão de reset dentro da ISR
  if (millis() - ultimoTempoBotaoReset > TEMPO_DEBOUNCE_RESET) {
    if (EMERGENCIA) {                       // O reset só tem efeito se o sistema estiver em emergência
      EMERGENCIA = false;                   // Desativa o estado de emergência
      displayEmergenciaJaMostrado = false;  // Reseta a flag para exibir mensagens normais após o reset
    }
    ultimoTempoBotaoReset = millis();  // Atualiza o tempo do último reset válido
  }
}

/**
 * @brief Configura o hardware e inicializa o sistema.
 * É executada uma única vez ao ligar ou reiniciar o Arduino.
 */
void setup() {
  // Configura os pinos dos botões como entrada com pull-up interno
  pinMode(BOTAO_EMERGENCIA, INPUT_PULLUP);
  pinMode(BOTAO_RESET, INPUT_PULLUP);

  // Anexa as funções de interrupção aos pinos dos botões
  // FALLING: Detecta a transição de HIGH para LOW (quando o botão é pressionado com pull-up)
  attachInterrupt(digitalPinToInterrupt(BOTAO_EMERGENCIA), handleEmergencyButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(BOTAO_RESET), handleResetButton, FALLING);

  // Inicializa a comunicação I2C e o display LCD
  Wire.begin();     // Inicia a biblioteca Wire para comunicação I2C
  lcd.init();       // Inicializa o display LCD
  lcd.backlight();  // Liga a luz de fundo do LCD
  lcd.clear();      // Limpa o conteúdo do LCD

  // Configura os pinos dos LEDs e do relé como saída
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(RELE, OUTPUT);

  // Garante que todos os LEDs e o relé comecem desligados.
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(RELE, HIGH);  // Relé começa DESLIGADO (HIGH)

  // Inicializa o sensor de peso HX711
  balanca.begin(DOUT, CLK);
  balanca.set_scale(CALIBRATION_FACTOR);  // Aplica o fator de calibração
  balanca.tare();                         // Zera a balança (subtrai o peso atual como referência)

  // Define o estado inicial do sistema como não-emergência e exibe a mensagem de aguardo
  EMERGENCIA = false;
  displayEmergenciaJaMostrado = false;
  exibirEstado("   AGUARDANDO", "   RECIPIENTE", "vermelho");
}

/**
 * @brief Loop principal do programa.
 * É executado repetidamente enquanto o Arduino estiver ligado.
 */
void loop() {
  // O estado de EMERGENCIA é verificado em cada iteração do loop para controle do fluxo.

  /** Obtém a média de 3 leituras do sensor de peso para maior estabilidade. */
  PESO_ATUAL = balanca.get_units(3);

  /**
   * Bloco principal de operação: enchimento automático.
   * Só é executado se o sistema NÃO estiver em estado de EMERGÊNCIA.
   */
  if (PESO_ATUAL > 0.005 && PESO_ATUAL < 0.040 && !EMERGENCIA) {
    /** Inicia a sequência de inicialização com uma contagem regressiva no LCD. */
    exibirEstado("   INICIANDO", "     EM 3");
    delay(1000);  // Espera 1 segundo
    exibirEstado("   INICIANDO", "     EM 2");
    delay(1000);  // Espera 1 segundo
    exibirEstado("   INICIANDO", "     EM 1");
    delay(1000);  // Espera 1 segundo

    PESO_ATUAL = balanca.get_units(3);  // Recalcula o peso após a contagem regressiva

    if (PESO_ATUAL < 0.005 || PESO_ATUAL > 0.04 || EMERGENCIA) {
      exibirEstado("    OPERACAO", "   CANCELADA", "todos");
      delay(3000);
      digitalWrite(RELE, HIGH);  /Garante que o relé esteja DESLIGADO (HIGH)
      return;
    } else if (PESO_ATUAL > 0.008 && PESO_ATUAL < 0.015) {
      MAX_PESO = 0.2 + PESO_ATUAL;
    } else if (PESO_ATUAL > 0.018 && PESO_ATUAL < 0.022) {
      MAX_PESO = 0.5 + PESO_ATUAL;
    } else if (PESO_ATUAL > 0.032 && PESO_ATUAL < 0.036) {
      MAX_PESO = 1.0 + PESO_ATUAL;
    } else {
      exibirEstado("     PESO", "  DESCONHECIDO", "todos");
      delay(3000);
      digitalWrite(RELE, HIGH);  //Garante que o relé esteja DESLIGADO (HIGH)
      return;
    }

    // Exibe o peso atual e o peso máximo no LCD e acende o LED amarelo (enchendo)
    exibirEstado(" PESO: " + String(PESO_ATUAL, 3) + " KG", " MAX: " + String(MAX_PESO, 3) + " KG", "amarelo");
    digitalWrite(RELE, LOW); /** Inicia o processo de enchimento LIGANDO o relé (LOW) */

    /**
     * Loop de monitoramento do peso durante o enchimento.
     * Continua enchendo enquanto o peso for menor que o máximo e a emergência não for acionada.
     */
    while (PESO_ATUAL < MAX_PESO && !EMERGENCIA) {
      PESO_ATUAL = balanca.get_units(3);  // Atualiza o peso
      // Atualiza o display com o peso em tempo real (exibirEstado gerencia a otimização)
      exibirEstado(" PESO: " + String(PESO_ATUAL, 3) + " KG", " MAX: " + String(MAX_PESO, 3) + " KG");
      delay(50);  // Pequeno atraso para estabilização da leitura e atualização do LCD
    }

    digitalWrite(RELE, HIGH); /** Finaliza o enchimento DESLIGANDO o relé (HIGH) */

    /** Verifica se a emergência foi acionada durante o enchimento. */
    if (EMERGENCIA) {
      return;  // Se sim, o sistema entra no bloco de emergência na próxima iteração do loop
    }

    /** Exibe mensagem de recipiente cheio e aguarda antes de reiniciar o ciclo. */
    exibirEstado("   RECIPIENTE", "     CHEIO", "verde");  // LED verde aceso
    delay(3000);                                           // Exibe a mensagem por 3 segundos
  }
  /**
   * Bloco de tratamento de emergência.
   * É executado se a variável EMERGENCIA for 'true'.
   */
  else if (EMERGENCIA) {
    digitalWrite(RELE, HIGH);  // !!! Garante que o relé esteja DESLIGADO (HIGH) durante a emergência

    // Exibe as mensagens de emergência APENAS UMA VEZ
    if (!displayEmergenciaJaMostrado) {
      exibirEstado("   EMERGENCIA", "   ACIONADA", "todos");  // Acende todos os LEDs
      delay(2000);                                            // Exibe a mensagem "EMERGENCIA ACIONADA" por 2 segundos
      exibirEstado("  APERTE BOTAO", "   DE RESET");          // Mensagem para o usuário reiniciar
      displayEmergenciaJaMostrado = true;                     // Marca que as mensagens já foram exibidas
    }
    // O loop continua executando este bloco, mas o LCD não piscará,
    // pois 'displayEmergenciaJaMostrado' é true.
    // O sistema aguarda o pressionamento do botão de reset (que aciona a interrupção).
  }
  /**
   * Bloco de estado de aguardo.
   * É executado quando o sistema não está enchendo nem em emergência.
   */
  else {
    exibirEstado("   AGUARDANDO", "   RECIPIENTE", "vermelho");  // LED vermelho aceso
    delay(500);                                                  // Pequeno atraso para reduzir o consumo de recursos e evitar piscar
  }
}
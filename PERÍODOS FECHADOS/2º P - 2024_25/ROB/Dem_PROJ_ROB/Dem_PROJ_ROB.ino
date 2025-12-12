/**
 * @file Enchedor_Automatico.ino
 * @brief Sistema de enchimento automático com controle de peso.
 * @author Valdir de Souza Carvalho Neto
 * @date 27/02/2025
 * @version 1.1
 *
 * Este código implementa um sistema de enchimento automático que utiliza um sensor de peso (HX711)
 * para controlar o enchimento de recipientes.
 * O sistema possui um botão de emergência que interrompe o processo de enchimento.
 *
 * Hardware Necessário:
 * - Arduino
 * - Sensor de peso HX711
 * - Display LCD 16x2 I2C
 * - Relé
 * - LEDs (vermelho, amarelo, verde)
 * - Botão de Emergência (pino 2)
 * - Botão de Reset (pino 3)
 *
 * Conexões:
 * - HX711: DOUT (A0), CLK (A1) - ATENÇÃO: Pode haver conflito com LCD I2C (A4/A5) dependendo da sua versão.
 * Se tiver problemas, considere mover HX711 para pinos digitais como 6 e 7.
 * - LCD I2C: SDA (A4 ou pino SDA do Arduino), SCL (A5 ou pino SCL do Arduino) - Verificar endereço I2C com um scanner.
 * - Relé: Pino 4 (Conectado ao pino de controle do módulo relé. A fonte na COM, e o fio da bomba no NA)
 * - LEDs: Vermelho (8), Amarelo (9), Verde (10)
 * - Botão de Emergência: Pino 2 (conectado ao GND, usando INPUT_PULLUP)
 * - Botão de Reset: Pino 3 (conectado ao GND, usando INPUT_PULLUP)
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h> /** Biblioteca para o display LCD I2C. */
#include <HX711.h>             /** Biblioteca para o sensor de peso HX711. */

/** Definição dos pinos. */
#define LED_VERMELHO 8
#define LED_AMARELO 9
#define LED_VERDE 10
#define DOUT A0
#define CLK A1
#define RELE 4
#define BOTAO_EMERGENCIA 2
#define BOTAO_RESET 3

/** Constantes e variáveis. */
float const CALIBRATION_FACTOR = 447530.00; /** Fator de calibração do sensor de peso. */
float MAX_PESO = 0.05, PESO_ATUAL;          /** Pesos máximo e atual. */
volatile bool EMERGENCIA = false;           /** Estado de emergência. */

// Variáveis para debounce do Botão de Reset (usando a interrupção no pino 3)
volatile unsigned long ultimoTempoBotaoReset = 0;  // Para controle de debounce na interrupção do reset
const unsigned long TEMPO_DEBOUNCE_RESET = 200;    // Tempo de debounce para o botão de reset (milissegundos)

// Nova variável para controlar a exibição das mensagens de emergência no LCD
bool displayEmergenciaJaMostrado = false;

/** Instâncias dos objetos. */
HX711 balanca;
LiquidCrystal_I2C lcd(0x27, 16, 2); /** Inicializa o LCD I2C com o endereço 0x27 e dimensões 16x2.
                                     * Verifique o endereço do seu LCD com um scanner I2C.
                                     * Endereços comuns: 0x27 ou 0x3F.
                                     */

/**
 * @brief Exibe mensagens no display LCD e controla as cores dos LEDs.
 * @param msg1 Mensagem da primeira linha do LCD.
 * @param msg2 Mensagem da segunda linha do LCD.
 * @param cor Cor dos LEDs ("vermelho", "amarelo", "verde", "todos" ou "sa" para sem alteração).
 *
 * As cores dos LEDs indicam o estado do sistema:
 * - Vermelho: Aguardando recipiente.
 * - Amarelo: Enchendo recipiente.
 * - Verde: Recipiente cheio.
 * - Todos: Operação cancelada ou emergência acionada.
 */
void exibirEstado(const String& msg1 = "sa", const String& msg2 = "sa", const String& cor = "sa") {
  // Usamos static para manter o último estado e evitar escritas desnecessárias no LCD
  static String lastMsg1 = "";
  static String lastMsg2 = "";
  static String lastCor = "";

  bool changed = false;

  if (msg1 != "sa" && (msg1 != lastMsg1 || msg2 != lastMsg2)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(msg1);
    lcd.setCursor(0, 1);
    lcd.print(msg2);
    lastMsg1 = msg1;
    lastMsg2 = msg2;
    changed = true;
  }

  if (cor != "sa" && cor != lastCor) {
    digitalWrite(LED_VERMELHO, cor == "vermelho" || cor == "todos");
    digitalWrite(LED_VERDE, cor == "verde" || cor == "todos");
    digitalWrite(LED_AMARELO, cor == "amarelo" || cor == "todos");
    lastCor = cor;
    changed = true;
  }
}

/**
 * @brief Função da Rotina de Serviço de Interrupção (ISR) para o Botão de Emergência.
 * Acionada na borda de queda (FALLING) do pino do botão de emergência.
 * Sua única responsabilidade é ATIVAR o estado de emergência.
 * O debounce é intencionalmente omitido aqui para resposta imediata.
 */
void handleEmergencyButton() {
  digitalWrite(RELE, HIGH);             // !!! MUDANÇA AQUI: Desliga a bomba (relé ATIVA com LOW, DESATIVA com HIGH)
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
  Serial.begin(9600);  // Inicializa a comunicação serial para depuração (opcional)

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
  // Para o relé que ATIVA com LOW, 'HIGH' o mantém DESLIGADO na inicialização.
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(RELE, HIGH);  // !!! MUDANÇA AQUI: Relé começa DESLIGADO (HIGH)

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
  if (PESO_ATUAL > 0.001 && PESO_ATUAL < 0.010 && !EMERGENCIA) {
    /** Inicia a sequência de inicialização com uma contagem regressiva no LCD. */
    exibirEstado("   INICIANDO", "     EM 3");
    delay(1000);  // Espera 1 segundo
    exibirEstado("   INICIANDO", "     EM 2");
    delay(1000);  // Espera 1 segundo
    exibirEstado("   INICIANDO", "     EM 1");
    delay(1000);  // Espera 1 segundo

    /** Verifica se a operação deve ser cancelada devido ao peso inadequado ou emergência. */
    PESO_ATUAL = balanca.get_units(3);  // Recalcula o peso após a contagem regressiva
    if (PESO_ATUAL >= MAX_PESO || PESO_ATUAL >= 0.005 || PESO_ATUAL < 0.001 || EMERGENCIA) {
      exibirEstado("    OPERACAO", "   CANCELADA", "todos");  // LEDs todos acesos
      delay(3000);
      digitalWrite(RELE, HIGH);  // !!! MUDANÇA AQUI: Garante que o relé esteja DESLIGADO (HIGH)
      return;
    }
    MAX_PESO = 0.050 + PESO_ATUAL;
    exibirEstado(" PESO: " + String(PESO_ATUAL, 3) + " KG", " MAX: " + String(MAX_PESO, 3) + " KG", "amarelo");
    digitalWrite(RELE, LOW); /** !!! MUDANÇA AQUI: Inicia o processo de enchimento LIGANDO o relé (LOW) */

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

    digitalWrite(RELE, HIGH); /** !!! MUDANÇA AQUI: Finaliza o enchimento DESLIGANDO o relé (HIGH) */

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
    digitalWrite(RELE, HIGH);  // !!! MUDANÇA AQUI: Garante que o relé esteja DESLIGADO (HIGH) durante a emergência

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
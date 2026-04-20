/**
 * @file Enchedor_Automatico.ino
 * @brief Sistema de enchimento automático com controle de peso.
 * @author Valdir de Souza Carvalho Neto
 * @date 20/04/2026
 * @version 1.0
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
 * - HX711: DOUT (6), CLK (7) 
 * - LCD I2C: SDA (A4), SCL (A5)
 * - Relé: Pino Digital 12 (Conectado ao pino de controle do módulo relé. A fonte na COM, e o fio da bomba no NA)
 * - LED Vermelho: Pino Digital 8
 * - LED Amarelo: Pino Digital 9
 * - LED Verde: Pino Digital 10
 * - Botão de Emergência: Pino Digital 3 (conectado ao GND, usando INPUT_PULLUP)
 * - Botão de Reset: Pino Digital 2 (conectado ao GND, usando INPUT_PULLUP)
 */

// Inclusão de bibliotecas
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

/** Constantes do sistema */
#define CALIBRATION_FACTOR 447530.00
#define PESO_MIN_PEQUENO 0.008
#define PESO_MAX_PEQUENO 0.015
#define PESO_MIN_MEDIO 0.018
#define PESO_MAX_MEDIO 0.022
#define PESO_MIN_GRANDE 0.032
#define PESO_MAX_GRANDE 0.036
#define PESO_MIN_VALIDO 0.005
#define PESO_MAX_VALIDO 0.040
#define ENCHIMENTO_PEQUENO 0.2
#define ENCHIMENTO_MEDIO 0.5
#define ENCHIMENTO_GRANDE 1.0
#define TIMEOUT_ENCHIMENTO 60000  // 60 segundos

/** Estrutura para salvar estado do enchimento interrompido */
struct EnchimentoPendente {
  bool pendente = false;
  float pesoInicial;
  float pesoAlvo;
  float pesoAtualSalvo;
  String tipoPote;
};

/** Variáveis globais. */
float MAX_PESO;
float PESO_ATUAL;
volatile bool EMERGENCIA = false;
bool displayEmergenciaJaMostrado = false;
EnchimentoPendente enchimentoPendente;

String msg1, msg2;

/** Instâncias dos objetos. */
HX711 balanca;
LiquidCrystal_I2C lcd(0x27, 16, 2);

/**
 * @brief Função auxiliar para delay com verificação de emergência.
 * Permite interromper delays longos se a emergência for acionada.
 * @param ms Tempo de delay em milissegundos.
 * @return true se o delay foi interrompido por emergência, false se completou normalmente.
 */
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

/**
 * @brief Exibe mensagens no display LCD e controla as cores dos LEDs.
 * Esta função otimiza a escrita no LCD para evitar piscar, atualizando apenas se a mensagem
 * ou cor mudou.
 * @param msg1 Mensagem da primeira linha do LCD.
 * @param msg2 Mensagem da segunda linha do LCD.
 * @param cor Cor dos LEDs ("vermelho", "amarelo", "verde", "todos" ou "" para nenhum).
 */
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

/**
 * @brief Identifica o tipo de pote VAZIO baseado no peso.
 * @param peso Peso do pote em kg
 * @return String com o tipo do pote ("PEQUENO", "MEDIO", "GRANDE") ou "DESCONHECIDO"
 */
String identificarPoteVazio(float peso) {
  if (peso > PESO_MIN_PEQUENO && peso < PESO_MAX_PEQUENO) {
    return "PEQUENO";
  } else if (peso > PESO_MIN_MEDIO && peso < PESO_MAX_MEDIO) {
    return "MEDIO";
  } else if (peso > PESO_MIN_GRANDE && peso < PESO_MAX_GRANDE) {
    return "GRANDE";
  }
  return "DESCONHECIDO";
}

/**
 * @brief Calcula o peso alvo baseado no tipo de pote e peso INICIAL do pote vazio.
 * @param tipoPote Tipo do pote (PEQUENO, MEDIO, GRANDE)
 * @param pesoInicial Peso do pote VAZIO (não o peso atual!)
 * @return Peso alvo final (peso inicial + quantidade de enchimento)
 */
float calcularPesoAlvoPorTipo(String tipoPote, float pesoInicial) {
  if (tipoPote == "PEQUENO") {
    return ENCHIMENTO_PEQUENO + pesoInicial;
  } else if (tipoPote == "MEDIO") {
    return ENCHIMENTO_MEDIO + pesoInicial;
  } else if (tipoPote == "GRANDE") {
    return ENCHIMENTO_GRANDE + pesoInicial;
  }
  return 0;
}

/**
 * @brief Salva o estado atual do enchimento para possível retomada.
 * @param pesoInicial Peso do pote vazio
 * @param pesoAlvo Peso alvo a ser atingido
 * @param pesoAtual Peso atual no momento da interrupção
 * @param tipoPote Tipo do pote
 */
void salvarEnchimentoPendente(float pesoInicial, float pesoAlvo, float pesoAtual, String tipoPote) {
  enchimentoPendente.pendente = true;
  enchimentoPendente.pesoInicial = pesoInicial;
  enchimentoPendente.pesoAlvo = pesoAlvo;
  enchimentoPendente.pesoAtualSalvo = pesoAtual;
  enchimentoPendente.tipoPote = tipoPote;
}

/**
 * @brief Limpa o estado de enchimento pendente.
 */
void limparEnchimentoPendente() {
  enchimentoPendente.pendente = false;
}

/**
 * @brief Aguarda a balança estabilizar e retorna o peso estável.
 * Importante para evitar leituras intermediárias quando um pote é colocado.
 * @param timeoutMs Tempo máximo de espera em ms
 * @return Peso estabilizado (média de 5 leituras)
 */
float aguardarEstabilizacao(unsigned long timeoutMs = 2000) {
  float leituraAnterior = balanca.get_units(5);
  unsigned long inicio = millis();
  int leiturasEstaveis = 0;

  while ((millis() - inicio) < timeoutMs && leiturasEstaveis < 3) {
    float leituraAtual = balanca.get_units(5);
    float diferenca = abs(leituraAtual - leituraAnterior);

    if (diferenca < 0.005) {  // Variação menor que 5g - estável
      leiturasEstaveis++;
    } else {
      leiturasEstaveis = 0;
    }

    leituraAnterior = leituraAtual;
    delay(100);
  }

  return balanca.get_units(5);  // Retorna média de 5 leituras
}

/**
 * @brief Executa o processo de enchimento.
 * @param pesoInicial Peso inicial do pote VAZIO
 * @param pesoAlvo Peso alvo a ser atingido
 * @param tipoPote Tipo do pote (PEQUENO, MEDIO, GRANDE)
 * @param continuar Deve pular a contagem regressiva? (true para retomada)
 * @return true se completou com sucesso, false se interrompido
 */
bool executarEnchimento(float pesoInicial, float pesoAlvo, String tipoPote, bool continuar = false) {

  // Se não for continuação, faz a contagem regressiva
  if (!continuar) {
    exibirEstado("   INICIANDO", "     EM 3", "amarelo");
    if (delayComEmergencia(1000)) {
      salvarEnchimentoPendente(pesoInicial, pesoAlvo, pesoInicial, tipoPote);
      return false;
    }
    exibirEstado("   INICIANDO", "     EM 2", "amarelo");
    if (delayComEmergencia(1000)) {
      salvarEnchimentoPendente(pesoInicial, pesoAlvo, pesoInicial, tipoPote);
      return false;
    }
    exibirEstado("   INICIANDO", "     EM 1", "amarelo");
    if (delayComEmergencia(1000)) {
      salvarEnchimentoPendente(pesoInicial, pesoAlvo, pesoInicial, tipoPote);
      return false;
    }
  } else {
    // Mensagem para continuação de enchimento
    exibirEstado(" COMPLETANDO...", " " + tipoPote, "amarelo");
    delayComEmergencia(3000);
  }

  // Atualiza peso atual com múltiplas leituras para precisão
  PESO_ATUAL = balanca.get_units(5);

  // Verifica se o pote ainda está presente
  if (PESO_ATUAL < PESO_MIN_VALIDO) {
    exibirEstado("    OPERACAO", "   CANCELADA", "todos");
    delayComEmergencia(3000);
    limparEnchimentoPendente();
    return false;
  }

  // NOTA: Na continuação, NÃO recalculamos o pesoAlvo!
  // O pesoAlvo já é o valor correto salvo no enchimentoPendente

  // Exibe informações do enchimento
  msg1 = " PESO: " + String(PESO_ATUAL, 3) + " KG";
  msg2 = " MAX: " + String(pesoAlvo, 3) + " KG";
  exibirEstado(msg1, msg2, "amarelo");

  // Liga a bomba (relé ativa com LOW)
  digitalWrite(RELE, LOW);
  delay(100);

  // Loop de enchimento
  unsigned long tempoInicio = millis();
  float maiorPeso = PESO_ATUAL;
  unsigned long ultimaAtualizacao = 0;

  while (PESO_ATUAL < pesoAlvo && !EMERGENCIA) {
    // Verifica timeout de segurança
    if ((millis() - tempoInicio) > TIMEOUT_ENCHIMENTO) {
      digitalWrite(RELE, HIGH);
      delay(100);
      exibirEstado("TEMPO ESGOTADO", "CANCELAR ENVASE", "todos");
      salvarEnchimentoPendente(pesoInicial, pesoAlvo, maiorPeso, tipoPote);
      delayComEmergencia(4000);
      return false;
    }

    // Lê o peso atual
    PESO_ATUAL = balanca.get_units(5);
    if (PESO_ATUAL > maiorPeso) {
      maiorPeso = PESO_ATUAL;
    }

    // Verifica se o pote foi removido durante enchimento
    if (PESO_ATUAL < PESO_MIN_VALIDO) {
      digitalWrite(RELE, HIGH);
      delay(100);
      exibirEstado(" POTE REMOVIDO", "CANCELAR ENVASE", "todos");
      salvarEnchimentoPendente(pesoInicial, pesoAlvo, maiorPeso, tipoPote);
      delayComEmergencia(4000);
      return false;
    }

    // Atualiza display a cada 500ms para não sobrecarregar
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
  delay(100);

  // Verifica se foi interrompido por emergência
  if (EMERGENCIA) {
    salvarEnchimentoPendente(pesoInicial, pesoAlvo, maiorPeso, tipoPote);
    return false;
  }

  // Enchimento concluído com sucesso
  limparEnchimentoPendente();
  exibirEstado("   RECIPIENTE", "     CHEIO", "verde");
  delayComEmergencia(3000);

  return true;
}

/**
 * @brief ISR para o Botão de Emergência.
 * Acionada na borda de queda do botão. Desliga a bomba imediatamente.
 */
void handleEmergencyButton() {
  digitalWrite(RELE, HIGH);
  EMERGENCIA = true;
  displayEmergenciaJaMostrado = false;
}

/**
 * @brief ISR para o Botão de Reset.
 * Acionada na borda de queda do botão. Sai do estado de emergência.
 */
void handleResetButton() {
  if (EMERGENCIA) {
    EMERGENCIA = false;
    displayEmergenciaJaMostrado = false;
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
  attachInterrupt(digitalPinToInterrupt(BOTAO_EMERGENCIA), handleEmergencyButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(BOTAO_RESET), handleResetButton, FALLING);

  // Inicializa a comunicação I2C e o display LCD
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Configura os pinos dos LEDs e do relé como saída
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(RELE, OUTPUT);

  // Garante que todos os LEDs e o relé comecem desligados
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(RELE, HIGH);  // Relé DESLIGADO (HIGH)

  // Inicializa o sensor de peso HX711
  balanca.begin(DOUT, CLK);
  delay(100);
  balanca.set_scale(CALIBRATION_FACTOR);
  balanca.tare(20);  // Tara com média de 20 leituras para precisão

  // Define o estado inicial do sistema
  EMERGENCIA = false;
  displayEmergenciaJaMostrado = false;

  exibirEstado("   AGUARDANDO", "   RECIPIENTE", "vermelho");
}

/**
 * @brief Loop principal do programa.
 * É executado repetidamente enquanto o Arduino estiver ligado.
 */
void loop() {
  // Lê o peso atual com média de 5 leituras
  PESO_ATUAL = balanca.get_units(5);

  // TRATAMENTO DE EMERGÊNCIA (prioridade máxima)
  if (EMERGENCIA) {
    digitalWrite(RELE, HIGH);

    if (!displayEmergenciaJaMostrado) {
      exibirEstado(" EM  EMERGENCIA", "  APERTE RESET", "todos");
      displayEmergenciaJaMostrado = true;
    }
    return;
  }

  // VERIFICAÇÃO PRIORITÁRIA: Enchimento pendente (pote parcialmente cheio)
  if (enchimentoPendente.pendente) {
    // Detectou algo na balança?
    if (PESO_ATUAL > PESO_MIN_VALIDO) {

      // AGUARDA ESTABILIZAÇÃO antes de decidir se é o pote pendente
      // Isso evita leituras erradas quando o pote é recém-colocado
      exibirEstado("   AGUARDE...", " ESTABILIZANDO", "amarelo");
      float pesoEstavel = aguardarEstabilizacao(2000);

      // Agora verifica com o peso estabilizado
      float diferenca = abs(pesoEstavel - enchimentoPendente.pesoAtualSalvo);

      // Verifica se é o mesmo pote:
      // - Diferença menor que 30g (margem para variações)
      // - OU peso está entre o peso inicial e o peso alvo (com 5% de tolerância)
      if (diferenca < 0.030 || (pesoEstavel > enchimentoPendente.pesoInicial && pesoEstavel < enchimentoPendente.pesoAlvo * 1.05)) {

        // É o mesmo pote! Calcula quanto falta para completar
        float faltante = enchimentoPendente.pesoAlvo - pesoEstavel;
        float totalEnchimento = enchimentoPendente.pesoAlvo - enchimentoPendente.pesoInicial;
        float jaEnchido = pesoEstavel - enchimentoPendente.pesoInicial;
        int percentual = constrain((int)((jaEnchido / totalEnchimento) * 100), 0, 100);

        // Mostra status do enchimento pendente
        msg1 = "POTE " + String(percentual) + "% CHEIO";
        msg2 = "FALTA " + String(faltante, 3) + " KG";
        exibirEstado(msg1, msg2, "amarelo");
        delayComEmergencia(3000);

        // Pergunta se quer continuar o enchimento
        exibirEstado("CONTINUAR? AGORA", "TIRE P/ CANCELAR", "amarelo");

        // Aguarda decisão por 5 segundos
        unsigned long tempoDecisao = millis();
        bool continuar = true;

        while ((millis() - tempoDecisao) < 5000) {
          PESO_ATUAL = balanca.get_units(5);

          // Se removeu o pote, cancela
          if (PESO_ATUAL < PESO_MIN_VALIDO) {
            continuar = false;
            break;
          }

          if (EMERGENCIA) return;
          delay(100);
        }

        // Se ainda tem peso, continua o enchimento
        PESO_ATUAL = balanca.get_units(5);
        if (continuar && PESO_ATUAL > PESO_MIN_VALIDO) {
          // Passa os dados salvos do pendente para retomar o enchimento
          executarEnchimento(enchimentoPendente.pesoInicial, enchimentoPendente.pesoAlvo, enchimentoPendente.tipoPote, true);  // true = continuar sem contagem regressiva
        } else {
          exibirEstado("  ENCHIMENTO", "   CANCELADO", "todos");
          limparEnchimentoPendente();
          delayComEmergencia(3000);
        }
        return;
      } else {
        // Peso diferente - é outro pote, ignora o pendente
        limparEnchimentoPendente();
      }
    }
  }

  // FLUXO NORMAL: Aguardando pote VAZIO
  if (PESO_ATUAL > PESO_MIN_VALIDO && PESO_ATUAL < PESO_MAX_VALIDO) {
    // Aguarda estabilização para identificar corretamente o tipo de pote
    exibirEstado("   AGUARDE...", " ESTABILIZANDO", "amarelo");
    float pesoEstavel = aguardarEstabilizacao(1500);

    String tipoPote = identificarPoteVazio(pesoEstavel);

    if (tipoPote != "DESCONHECIDO") {
      MAX_PESO = calcularPesoAlvoPorTipo(tipoPote, pesoEstavel);

      // Verifica se o pote já está cheio (improvável para pote vazio, mas por segurança)
      if (pesoEstavel >= MAX_PESO) {
        exibirEstado("  POTE JA ESTA", "     CHEIO", "verde");
        delayComEmergencia(3000);
        return;
      }

      // Inicia enchimento normal
      executarEnchimento(pesoEstavel, MAX_PESO, tipoPote, false);
    } else {
      exibirEstado("     PESO", "  DESCONHECIDO", "todos");
      delayComEmergencia(3000);
    }
  }
  // Peso alto mas sem pendente ativo - provavelmente pote não vazio
  else if (PESO_ATUAL >= PESO_MAX_VALIDO && !enchimentoPendente.pendente) {
    exibirEstado(" POTE NAO VAZIO", " COLOQUE VAZIO", "todos");
    delayComEmergencia(3000);
  }
  // Balança vazia - estado de aguardo
  else {
    exibirEstado("   AGUARDANDO", "   RECIPIENTE", "vermelho");
    delayComEmergencia(500);
  }
}
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
 * Novas funcionalidades na versão 1.2:
 * - Retomada de enchimento interrompido (emergência ou timeout)
 * - Detecção automática de pote parcialmente cheio
 * - Opção de continuar ou cancelar enchimento anterior
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
#define MARGEM_RETOMADA 0.010     // Margem de 10g para identificar mesmo pote

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
 * @brief Obtém o tipo do pote (do pendente ou identifica se for vazio).
 */
String obterTipoPote(float peso, bool podeSerParcial = false) {
  // Se temos um enchimento pendente e o peso é similar, usa o tipo salvo
  if (enchimentoPendente.pendente) {
    float diferenca = abs(peso - enchimentoPendente.pesoAtualSalvo);
    if (diferenca < MARGEM_RETOMADA) {
      return enchimentoPendente.tipoPote;  // ← Usa o tipo já conhecido!
    }
  }
  // Caso contrário, tenta identificar como pote vazio
  return identificarPoteVazio(peso);
}

/**
 * @brief Calcula o peso alvo baseado no peso do pote vazio.
 * @param peso Peso atual do pote vazio
 * @return Peso alvo para enchimento, ou 0 se pote desconhecido
 */
float obterPesoAlvo(float peso) {
  if (peso > PESO_MIN_PEQUENO && peso < PESO_MAX_PEQUENO) {
    return ENCHIMENTO_PEQUENO + peso;
  } else if (peso > PESO_MIN_MEDIO && peso < PESO_MAX_MEDIO) {
    return ENCHIMENTO_MEDIO + peso;
  } else if (peso > PESO_MIN_GRANDE && peso < PESO_MAX_GRANDE) {
    return ENCHIMENTO_GRANDE + peso;
  }
  return 0;
}

/**
 * @brief Salva o estado atual do enchimento para possível retomada.
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
 * @brief Executa o processo de enchimento.
 * @param pesoInicial Peso inicial do pote vazio
 * @param pesoAlvo Peso alvo a ser atingido
 * @param continuar Deve pular a contagem regressiva?
 * @return true se completou com sucesso, false se interrompido
 */
bool executarEnchimento(float pesoInicial, float pesoAlvo, bool continuar = false) {
  String tipoPote = obterTipoPote(pesoInicial);

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
    // Mensagem para continuação
    exibirEstado(" COMPLETANDO...", " " + tipoPote, "amarelo");
    delayComEmergencia(1500);
  }

  // Atualiza peso atual
  PESO_ATUAL = balanca.get_units(3);

  // Verifica se o pote ainda está presente
  if (PESO_ATUAL < PESO_MIN_VALIDO) {
    exibirEstado("    OPERACAO", "   CANCELADA", "todos");
    delayComEmergencia(2000);
    limparEnchimentoPendente();
    return false;
  }

  // Atualiza o peso alvo se necessário (caso o peso tenha mudado)
  if (continuar) {
    pesoAlvo = obterPesoAlvo(PESO_ATUAL);
  }

  // Exibe informações do enchimento
  String msg1 = " PESO: " + String(PESO_ATUAL, 3) + " KG";
  String msg2 = " MAX: " + String(pesoAlvo, 3) + " KG";
  exibirEstado(msg1, msg2, "amarelo");

  // Liga a bomba
  digitalWrite(RELE, LOW);
  delay(100);

  // Loop de enchimento
  unsigned long tempoInicio = millis();
  float ultimoPesoSalvo = PESO_ATUAL;
  unsigned long ultimaAtualizacao = 0;

  while (PESO_ATUAL < pesoAlvo && !EMERGENCIA) {
    // Verifica timeout
    if ((millis() - tempoInicio) > TIMEOUT_ENCHIMENTO) {
      digitalWrite(RELE, HIGH);
      delay(100);
      exibirEstado("TEMPO ESGOTADO", "CANC. ENCHIMENTO", "todos");
      salvarEnchimentoPendente(pesoInicial, pesoAlvo, PESO_ATUAL, tipoPote);
      delayComEmergencia(4000);
      return false;
    }

    PESO_ATUAL = balanca.get_units(3);

    // Verifica se o pote foi removido durante enchimento
    if (PESO_ATUAL < PESO_MIN_VALIDO) {
      digitalWrite(RELE, HIGH);
      delay(100);
      exibirEstado(" POTE REMOVIDO", "CANC. ENCHIMENTO", "todos");
      salvarEnchimentoPendente(pesoInicial, pesoAlvo, ultimoPesoSalvo, tipoPote);
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

    ultimoPesoSalvo = PESO_ATUAL;
    delay(50);
  }

  // Desliga a bomba
  digitalWrite(RELE, HIGH);
  delay(100);

  // Verifica se foi interrompido por emergência
  if (EMERGENCIA) {
    salvarEnchimentoPendente(pesoInicial, pesoAlvo, PESO_ATUAL, tipoPote);
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
 */
void handleEmergencyButton() {
  digitalWrite(RELE, HIGH);
  EMERGENCIA = true;
  displayEmergenciaJaMostrado = false;
}

/**
 * @brief ISR para o Botão de Reset.
 */
void handleResetButton() {
  if (EMERGENCIA) {
    EMERGENCIA = false;
    displayEmergenciaJaMostrado = false;
  }
}

/**
 * @brief Configura o hardware e inicializa o sistema.
 */
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

  exibirEstado("   AGUARDANDO", "   RECIPIENTE", "vermelho");
}

/**
 * @brief Loop principal do programa.
 */
void loop() {
  PESO_ATUAL = balanca.get_units(3);

  // Tratamento de emergência (prioridade máxima)
  if (EMERGENCIA) {
    digitalWrite(RELE, HIGH);

    if (!displayEmergenciaJaMostrado) {
      exibirEstado(" EM  EMERGENCIA", "  APERTE RESET", "todos");
      displayEmergenciaJaMostrado = true;
    }
    return;
  }

  // Verifica se há um enchimento pendente
  if (enchimentoPendente.pendente && PESO_ATUAL > PESO_MIN_VALIDO && PESO_ATUAL < enchimentoPendente.pesoAlvo) {
    // Verifica se é realmente o mesmo pote
    float diferenca = abs(PESO_ATUAL - enchimentoPendente.pesoAtualSalvo);

    if (diferenca < MARGEM_RETOMADA) {
      // É o mesmo pote! Calcula quanto falta para completar
      float faltante = enchimentoPendente.pesoAlvo - PESO_ATUAL;
      int percentual = (int)((PESO_ATUAL - enchimentoPendente.pesoInicial) / (enchimentoPendente.pesoAlvo - enchimentoPendente.pesoInicial) * 100);

      // Mostra status do enchimento pendente
      String msg1 = "POTE " + String(percentual) + "% CHEIO";
      String msg2 = "FALTA " + String(faltante, 3) + " KG";
      exibirEstado(msg1, msg2, "amarelo");
      delayComEmergencia(4000);

      // Pergunta se quer continuar
      exibirEstado("CONTINUAR? AGORA", "TIRE P/ CANCELAR", "amarelo");

      // Aguarda decisão por 5 segundos
      unsigned long tempoDecisao = millis();
      bool continuar = true;

      while ((millis() - tempoDecisao) < 5000) {
        PESO_ATUAL = balanca.get_units(3);
        // Se removeu o pote, cancela
        if (PESO_ATUAL < PESO_MIN_VALIDO) {
          continuar = false;
          break;
        }

        if (EMERGENCIA) return;
        delay(100);
      }

      // Se ainda tem peso, continua o enchimento
      PESO_ATUAL = balanca.get_units(3);
      if (continuar && PESO_ATUAL > PESO_MIN_VALIDO) {
        executarEnchimento(enchimentoPendente.pesoInicial, enchimentoPendente.pesoAlvo, true);  // true = continuar sem contagem
      } else {
        exibirEstado("  ENCHIMENTO", "   CANCELADO", "todos");
        limparEnchimentoPendente();
        delayComEmergencia(2000);
      }
      return;
    } else {
      // É um pote diferente - ignora o pendente
      limparEnchimentoPendente();
    }
  }

  // Fluxo normal: aguardando pote
  if (PESO_ATUAL > PESO_MIN_VALIDO && PESO_ATUAL < PESO_MAX_VALIDO) {
    MAX_PESO = obterPesoAlvo(PESO_ATUAL);

    if (MAX_PESO > 0) {
      // Verifica se o pote já está cheio
      if (PESO_ATUAL >= MAX_PESO) {
        exibirEstado("  POTE JA ESTA", "     CHEIO", "verde");
        delayComEmergencia(2000);
        return;
      }

      // Inicia enchimento normal
      executarEnchimento(PESO_ATUAL, MAX_PESO, false);
    }
  } else {
    // Estado de aguardo
    exibirEstado("   AGUARDANDO", "   RECIPIENTE", "vermelho");
    delayComEmergencia(500);
  }
}
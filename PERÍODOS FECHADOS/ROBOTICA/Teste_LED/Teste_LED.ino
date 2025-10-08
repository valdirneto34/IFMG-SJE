/** Definição dos pinos. */
#define LED_VERMELHO 8
#define LED_AMARELO 9
#define LED_VERDE 10

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT); 
}

void loop() {
  digitalWrite(LED_VERMELHO, 1);
  digitalWrite(LED_AMARELO, 0);
  digitalWrite(LED_VERDE, 0);
  delay(3000);

  digitalWrite(LED_VERMELHO, 0);
  digitalWrite(LED_AMARELO, 1);
  digitalWrite(LED_VERDE, 0);
  delay(3000);

  digitalWrite(LED_VERMELHO, 0);
  digitalWrite(LED_AMARELO, 0);
  digitalWrite(LED_VERDE, 1);
  delay(3000);

}

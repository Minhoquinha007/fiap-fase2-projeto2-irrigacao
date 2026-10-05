#include <Arduino.h>
#include <DHTesp.h>
#include <math.h>

// Projeto 2 - irrigacao simulada de alface no Wokwi.
// Os componentes DHT22 e LDR sao substitutos didaticos, nao sensores de solo/pH.
constexpr int PIN_N = 13;
constexpr int PIN_P = 14;
constexpr int PIN_K = 27;
constexpr int PIN_LDR = 34;   // Entrada analogica ADC1 do ESP32.
constexpr int PIN_DHT = 18;
constexpr int PIN_RELE = 26;

// Confirmado no Wokwi para o modulo com transistor="npn": GPIO em HIGH
// fecha COM-NO e acende o LED da bomba; LOW deixa o LED apagado.
// Em um rele fisico, conferir a polaridade do modulo antes de energizar bomba.
constexpr int RELE_ATIVO = HIGH;
constexpr int RELE_INATIVO = LOW;

// Limiares de DEMONSTRACAO sobre a umidade do ar do DHT22. Nao sao uma
// recomendacao agronomica nem uma conversao para umidade real do solo.
constexpr float UMIDADE_LIGAR = 45.0f;
constexpr float UMIDADE_DESLIGAR = 55.0f;

constexpr float PH_ALFACE_MIN = 6.0f;
constexpr float PH_ALFACE_MAX = 6.8f;

DHTesp dht;
bool bombaLigada = false;

void setup() {
  Serial.begin(115200);

  pinMode(PIN_N, INPUT_PULLUP);
  pinMode(PIN_P, INPUT_PULLUP);
  pinMode(PIN_K, INPUT_PULLUP);

  // Estado seguro antes de iniciar a leitura dos sensores.
  digitalWrite(PIN_RELE, RELE_INATIVO);
  pinMode(PIN_RELE, OUTPUT);

  analogReadResolution(12);  // 0 a 4095
  dht.setup(PIN_DHT, DHTesp::DHT22);

  Serial.println("Projeto 2 - irrigacao simulada de alface");
  Serial.println("N/P/K: botao pressionado = 1; solto = 0.");
  Serial.println("LDR -> pH e DHT22 -> umidade do solo: apenas simulacoes.");
}

void loop() {
  // Cada botao representa somente um estado binario do respectivo nutriente.
  const bool nPresente = digitalRead(PIN_N) == LOW;
  const bool pPresente = digitalRead(PIN_P) == LOW;
  const bool kPresente = digitalRead(PIN_K) == LOW;

  const int adcLdr = analogRead(PIN_LDR);
  const float phSimulado = 14.0f * adcLdr / 4095.0f;
  const bool phNaFaixa = phSimulado >= PH_ALFACE_MIN &&
                         phSimulado <= PH_ALFACE_MAX;

  const TempAndHumidity amostra = dht.getTempAndHumidity();
  const float umidadeSimulada = amostra.humidity;
  const bool leituraValida = !isnan(umidadeSimulada) &&
                              umidadeSimulada >= 0.0f &&
                              umidadeSimulada <= 100.0f;

  // Histerese: inicia abaixo de 45%; para a partir de 55%. Entre esses
  // valores, conserva o estado anterior para evitar liga/desliga frequente.
  if (!leituraValida) {
    bombaLigada = false;  // Falha de leitura: desligamento preventivo.
  } else if (!bombaLigada && umidadeSimulada < UMIDADE_LIGAR) {
    bombaLigada = true;
  } else if (bombaLigada && umidadeSimulada >= UMIDADE_DESLIGAR) {
    bombaLigada = false;
  }

  digitalWrite(PIN_RELE, bombaLigada ? RELE_ATIVO : RELE_INATIVO);

  Serial.print("N=");
  Serial.print(nPresente ? 1 : 0);
  Serial.print(" P=");
  Serial.print(pPresente ? 1 : 0);
  Serial.print(" K=");
  Serial.print(kPresente ? 1 : 0);
  Serial.print(" | LDR_ADC=");
  Serial.print(adcLdr);
  Serial.print(" pH_SIM=");
  Serial.print(phSimulado, 2);
  Serial.print(phNaFaixa ? " (faixa da alface)" : " (fora da faixa)");
  Serial.print(" | Umidade_SIM=");
  if (leituraValida) {
    Serial.print(umidadeSimulada, 1);
    Serial.print('%');
  } else {
    Serial.print("ERRO");
  }
  Serial.print(" | BOMBA=");
  Serial.println(bombaLigada ? "ON" : "OFF");

  delay(2000);  // Intervalo apropriado para novas leituras do DHT22.
}


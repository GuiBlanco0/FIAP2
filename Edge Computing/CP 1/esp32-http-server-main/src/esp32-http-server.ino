#include <Arduino.h>
#include <DHT.h>

#define PIN_DHT 15
#define DHT_TIPO DHT22

#define PIN_GAS_DOUT 16
#define PIN_GAS_VCC 32 
#define PIN_BUZZER 33
#define PIN_LED_R 25
#define PIN_LED_G 26
#define PIN_LED_B 27
#define LED_ACESO LOW
#define LED_APAGADO HIGH
#define GAS_DETECTADO HIGH

DHT dht(PIN_DHT, DHT_TIPO);

const float TEMP_MIN_IDEAL = 2.0;    // abaixo disso já preocupa
const float TEMP_MAX_IDEAL = 8.0;    // acima disso já preocupa
const float TEMP_MIN_CRITICA = 0.0;  // congelamento indevido
const float TEMP_MAX_CRITICA = 12.0; // ruptura grave da cadeia fria
const float UMID_MAX_IDEAL = 80.0;   // umidade alta favorece mofo/deterioração


enum EstadoSistema
{
  ESTADO_NORMAL = 0,
  ESTADO_ALERTA,
  ESTADO_CRITICO
};

EstadoSistema estadoAtual = ESTADO_NORMAL;

const char *nomeEstado(EstadoSistema e)
{
  switch (e)
  {
  case ESTADO_NORMAL:
    return "NORMAL";
  case ESTADO_ALERTA:
    return "ALERTA";
  case ESTADO_CRITICO:
    return "CRITICO";
  }
  return "DESCONHECIDO";
}

struct Leituras
{
  float temperatura;
  float umidade;
  bool leituraDhtValida;
  bool gasDetectado;
};

Leituras lerSensores()
{
  Leituras l;
  l.temperatura = dht.readTemperature();
  l.umidade = dht.readHumidity();
  l.leituraDhtValida = !(isnan(l.temperatura) || isnan(l.umidade));
  l.gasDetectado = (digitalRead(PIN_GAS_DOUT) == GAS_DETECTADO);

  return l;
}

EstadoSistema decidirEstado(const Leituras &l)
{

  if (!l.leituraDhtValida)
  {
    return ESTADO_ALERTA;
  }

  if (l.gasDetectado)
  {
    return ESTADO_CRITICO;
  }

  bool tempCritica = (l.temperatura < TEMP_MIN_CRITICA) || (l.temperatura > TEMP_MAX_CRITICA);
  bool umidAlta = (l.umidade > UMID_MAX_IDEAL);
  if (tempCritica && umidAlta)
  {
    return ESTADO_CRITICO;
  }

  bool tempForaIdeal = (l.temperatura < TEMP_MIN_IDEAL) || (l.temperatura > TEMP_MAX_IDEAL);
  if (tempForaIdeal || umidAlta || tempCritica)
  {
    return ESTADO_ALERTA;
  }

  return ESTADO_NORMAL;
}

void definirCorLed(bool r, bool g, bool b)
{
  digitalWrite(PIN_LED_R, r ? LED_ACESO : LED_APAGADO);
  digitalWrite(PIN_LED_G, g ? LED_ACESO : LED_APAGADO);
  digitalWrite(PIN_LED_B, b ? LED_ACESO : LED_APAGADO);
}

void atualizarAtuadores(EstadoSistema estado)
{
  switch (estado)
  {
  case ESTADO_NORMAL:
    definirCorLed(false, true, false); 
    noTone(PIN_BUZZER);
    break;

  case ESTADO_ALERTA:
    definirCorLed(true, true, false); 
    tone(PIN_BUZZER, 1000);           
    break;

  case ESTADO_CRITICO:
    definirCorLed(true, false, false); 
    tone(PIN_BUZZER, 2500);            
    break;
  }
}

void setup()
{
  Serial.begin(115200);
  delay(300);
  Serial.println("=== FrioLog - No de Borda Inteligente (Checkpoint 1) ===");

  dht.begin();

  pinMode(PIN_GAS_DOUT, INPUT);
  pinMode(PIN_GAS_VCC, OUTPUT);
  digitalWrite(PIN_GAS_VCC, HIGH);

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);

  definirCorLed(false, false, false);
  noTone(PIN_BUZZER);


  atualizarAtuadores(estadoAtual);
  Serial.print("Estado inicial: ");
  Serial.println(nomeEstado(estadoAtual));
}

void loop()
{
  Leituras leituras = lerSensores();

  Serial.print("Temp: ");
  if (leituras.leituraDhtValida)
    Serial.print(leituras.temperatura, 1);
  else
    Serial.print("ERRO");
  Serial.print(" C | Umid: ");
  if (leituras.leituraDhtValida)
    Serial.print(leituras.umidade, 1);
  else
    Serial.print("ERRO");
    Serial.print(" % | Gas: ");
  Serial.print(leituras.gasDetectado ? "DETECTADO" : "ok");

  EstadoSistema novoEstado = decidirEstado(leituras);

  if (novoEstado != estadoAtual)
  {
    Serial.print(" || >>> MUDANCA DE ESTADO: ");
    Serial.print(nomeEstado(estadoAtual));
    Serial.print(" -> ");
    Serial.println(nomeEstado(novoEstado));
    estadoAtual = novoEstado;
    atualizarAtuadores(estadoAtual);
  }
  else
  {
    Serial.print(" || Estado: ");
    Serial.println(nomeEstado(estadoAtual));
  }

  delay(2000); // DHT22 precisa de um intervalo mínimo entre leituras
}
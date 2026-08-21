#include "DHT.h"

#define DHTPIN 15

#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321

#define BUZZER 23 // atuador sonoro

const float LIMIAR = 30.0; // % de umidade p/ o alarme

DHT dht(DHTPIN, DHTTYPE);

void setup()
{

    Serial.begin(115200);

    Serial.println(F("DHT22 - exemplo"));

    dht.begin();

    pinMode(BUZZER, OUTPUT);
}

void loop()
{

    float temp = dht.readTemperature();

    float umid = dht.readHumidity();

    // Verificar a leitura

    if (isnan(temp) || isnan(umid))
    {

        Serial.println(F("Failed to read from DHT sensor!"));

        return;
    }

    // decisão local: umidade alta -> alarme sonoro

    if (umid < LIMIAR)
    {

        tone(BUZZER, 500); // Tocar na frequência de 500 Hz

        delay(1000);       // Aguardar 1 segundo
        tone(BUZZER, 800); // Tocar na frequência de 800 Hz

        delay(1000); // Aguardar 1 segundo
    }
    else
    {

        noTone(BUZZER); // silencia
    }

    Serial.print(F("Umidade: "));

    Serial.print(umid);

    Serial.print(F("%  Temperatura: "));

    Serial.print(temp);

    Serial.println(F("°C "));

    // Aguardar 2 segundos para nova medida

    delay(2000);
}
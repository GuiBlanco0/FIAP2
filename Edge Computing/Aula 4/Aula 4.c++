#include <"DHT.h">
#include <WiFi.h>
#include <PubSubClient.h>

// ---- Wi-Fi (rede simulada do Wokwi) ----

const char *SSID  = "Wokwi-GUEST";

const char *SENHA = "";

// ---- MQTT ----

const char *BROKER = "broker.hivemq.com";

const int   PORTA  = 1883;

const char *TOPICO     = "fiap/edge/aula4/SEUNOME/temp"; // troque SEUNOME

const char *TOPICO_LED = "fiap/edge/aula4/SEUNOME/led";
  // <-- NOVO: comando do LED

// ---- Sensor e atuadores

#define DHTPIN 15

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#define BUZZER  23       // atuador sonoro

#define LED     21       // <-- NOVO: atuador luminoso

    const float LIMIAR  = 70.0;
  // % de umidade p/ o alarme

    DHT dht(DHTPIN, DHTTYPE);

WiFiClient rede;

PubSubClient mqtt(rede);

void conectarWiFi()
{

      Serial.print("Conectando ao Wi-Fi");

      WiFi.begin(SSID, SENHA, 6);
                // canal 6 acelera no Wokwi 

  while (WiFi.status() != WL_CONNECTED)
    {

            delay(300);
        Serial.print(".");

         
    }

      Serial.println("\nWi-Fi conectado! IP: " + WiFi.localIP().toString());
}

// <-- NOVO: chamado a cada mensagem recebida

void callback(char *topico, byte *payload, unsigned int tamanho)
{

      String msg;

      for (unsigned int i = 0; i < tamanho; i++) msg += (char)payload[i];

      Serial.print("Recebido [");
    Serial.print(topico);

      Serial.print("]: ");
    Serial.println(msg);

      if (msg == "1" || msg == "on" || msg == "ON")
    {

            digitalWrite(LED, HIGH);

            Serial.println("LED ligado");

         
    }
    else if (msg == "0" || msg == "off" || msg == "OFF")
    {

            digitalWrite(LED, LOW);

            Serial.println("LED desligado");

         
    }
}

void conectarMQTT()
{

      mqtt.setServer(BROKER, PORTA);

      mqtt.setCallback(callback);
              // <-- NOVO: registra o callback 

  while (!mqtt.connected())
    {

            Serial.print("Conectando ao broker MQTT...");

            String id = "esp32-fiap-" + String(random(0xffff), HEX);

            if (mqtt.connect(id.c_str()))
        {

                  Serial.println(" conectado!");

                  mqtt.subscribe(TOPICO_LED);
                  // <-- NOVO: assina o tópico do LED 

      Serial.println("Inscrito em: " + String(TOPICO_LED));

               
        }
        else
        {

                  Serial.print(" falhou, estado=");
            Serial.println(mqtt.state());

                  delay(2000);

               
        }

         
    }
}

void setup()
{

      Serial.begin(115200);

      Serial.println(F("DHT22 - exemplo"));

      dht.begin();

      pinMode(BUZZER, OUTPUT);

      pinMode(LED, OUTPUT);
                      // <-- NOVO 

  digitalWrite(LED, LOW);
                  // <-- NOVO: começa apagado 

  // Conexão com o WiFi 

  conectarWiFi();

      conectarMQTT();
}

void loop()
{

      //Verificar a conexão com o WiFi 

  if (!mqtt.connected()) conectarMQTT();

      mqtt.loop();

      float temp = dht.readTemperature();

      float umid = dht.readHumidity();

      // Check if any reads failed and exit early (to try again). 

  if (isnan(temp) || isnan(umid))
    {

            Serial.println(F("Failed to read from DHT sensor!"));

            return;

         
    }

        // decisão local: umidade alta -> alarme sonoro 

  if (umid > LIMIAR)
    {

            tone(BUZZER, 500); // Tocar na frequência de 500 Hz

            delay(1000); // Aguardar 1 segundo

            tone(BUZZER, 800); // Tocar na frequência de 800 Hz

            delay(1000); // Aguardar 1 segundo

         
    }
    else
    {

            noTone(BUZZER);
              // silencia 

 
    }

      Serial.print(F("Umidade: "));

      Serial.print(umid);

      Serial.print(F("%  Temperatura: "));

      Serial.print(temp);

      Serial.println(F("°C "));

      // Sistema de mensageria 

  char msg[16];

      dtostrf(temp, 4, 1, msg);
                // float -> texto 

  mqtt.publish(TOPICO, msg);
                // publica (QoS 0) 

 

  Serial.print("Publicado em ");

      Serial.print(TOPICO);

      Serial.print(": ");

      Serial.println(msg);

      // Aguardar 2 segundos para nova medida 

  delay(2000);
}
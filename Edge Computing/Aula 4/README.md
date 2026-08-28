# Aula 4 - Edge Computing

## 📚 FIAP - Edge Computing

Projeto desenvolvido durante a Aula 4 da disciplina de Edge Computing.

O objetivo do projeto é utilizar um **ESP32** para realizar a leitura de temperatura e umidade através de um sensor **DHT22**, além de utilizar comunicação **MQTT** para enviar dados e controlar um LED remotamente.

---

## 🛠️ Tecnologias e componentes utilizados

- ESP32
- Sensor DHT22
- LED
- Buzzer
- MQTT
- Wi-Fi
- C++
- Arduino

---

## 📡 Funcionalidades

O projeto possui as seguintes funcionalidades:

- Leitura da temperatura através do sensor DHT22.
- Leitura da umidade do ambiente.
- Publicação dos dados de temperatura utilizando MQTT.
- Conexão com um broker MQTT.
- Controle remoto de um LED através de um tópico MQTT.
- Acionamento de um buzzer quando a umidade ultrapassa o limite definido.
- Reconexão automática ao broker MQTT caso a conexão seja perdida.

---

## 🌐 Comunicação MQTT

O ESP32 se conecta ao broker:

```text
broker.hivemq.com
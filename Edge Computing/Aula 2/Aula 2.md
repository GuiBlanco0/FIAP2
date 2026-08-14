# Projeto Arduino — Sensor de Temperatura e Luminosidade

## 📌 Descrição

Projeto desenvolvido no **Arduino/Tinkercad** utilizando um sensor de temperatura **TMP36** e um **LDR** para monitorar as condições do ambiente.

Com base nos valores medidos, o Arduino acende um dos três LEDs:

* 🟢 **Verde:** temperatura confortável e iluminação adequada.
* 🟡 **Amarelo:** temperatura elevada ou pouca iluminação.
* 🔴 **Vermelho:** temperatura acima de 30 °C.

Os valores de temperatura e luminosidade também são exibidos no **Monitor Serial**.

## 🔧 Componentes

* Arduino Uno
* Sensor de temperatura TMP36
* LDR (sensor de luminosidade)
* LED verde
* LED amarelo
* LED vermelho
* Resistores
* Protoboard
* Jumpers

## ⚙️ Funcionamento

### Temperatura

O TMP36 é conectado à entrada analógica **A0**.

| Temperatura | LED         |
| ----------- | ----------- |
| > 30 °C     | 🔴 Vermelho |
| > 25 °C     | 🟡 Amarelo  |
| ≤ 25 °C     | 🟢 Verde    |

### Luminosidade

O LDR é conectado à entrada analógica **A1**.

Quando a luminosidade fica abaixo de **40%**, o LED amarelo é acionado, desde que a temperatura não esteja acima de 30 °C.

## 🧠 Lógica do Sistema

```text
          ┌──────────────┐
          │    TMP36     │
          │ Temperatura  │
          └──────┬───────┘
                 │ A0
                 ▼
          ┌──────────────┐
          │   Arduino    │
          │              │
          │  Decisão     │
          └──────┬───────┘
                 │
       ┌─────────┼─────────┐
       ▼         ▼         ▼
   🟢 Verde  🟡 Amarelo  🔴 Vermelho
```

O LDR fornece a leitura de luminosidade pela entrada **A1**, que também é utilizada na decisão do LED.

## 📟 Monitor Serial

A cada 500 ms, o Arduino envia os valores medidos:

```text
Temp: 24.50 C | Luz: 72.33 %
```

## 📁 Arquivos

O código-fonte do projeto está disponível separadamente neste repositório.

* `codigo.ino` — Código do Arduino
* `README.md` — Documentação do projeto

## 🎯 Objetivo

Demonstrar o uso de **sensores analógicos**, conversão de valores, estruturas condicionais (`if`, `else if`, `else`) e acionamento de LEDs para representar diferentes estados do ambiente.

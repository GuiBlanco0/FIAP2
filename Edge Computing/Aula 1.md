# 🌡️ Aula 1 - Edge Computing | Monitoramento de Temperatura com Arduino

## 📖 Sobre o projeto

Este projeto foi desenvolvido durante a **Aula 1 de Edge Computing** e tem como objetivo realizar a leitura da temperatura utilizando um sensor **TMP36** conectado a um **Arduino Uno**.

O sistema converte o valor analógico lido pelo sensor em graus Celsius e acende um LED quando a temperatura ultrapassa **30°C**.

---

## 🛠️ Componentes utilizados

- Arduino Uno
- Sensor de temperatura TMP36
- LED vermelho
- Resistor de 220 Ω
- Protoboard
- Jumpers

---

## ⚙️ Funcionamento

1. O Arduino realiza a leitura da tensão fornecida pelo sensor TMP36.
2. O valor analógico é convertido para temperatura em graus Celsius.
3. A temperatura é exibida no **Monitor Serial**.
4. Caso a temperatura seja superior a **30°C**, o LED é ligado.
5. Caso contrário, o LED permanece desligado.

---

## 💻 Código

A conversão da leitura analógica para temperatura é feita utilizando a seguinte fórmula:

```cpp
float tCelsius = (t * (5.0 / 1023.0) - 0.5) * 100.0;
```

Lógica implementada:

- Temperatura ≤ **30°C** → LED desligado.
- Temperatura > **30°C** → LED ligado.

---

## 📋 Fluxo do programa

```text
Inicialização
      │
      ▼
Leitura do sensor (A0)
      │
      ▼
Conversão para °C
      │
      ▼
Exibição no Monitor Serial
      │
      ▼
Temperatura > 30°C?
   │             │
  Sim           Não
   │             │
Liga LED    Desliga LED
   │             │
   └──────┬──────┘
          ▼
     Repetição
```

---

## 📁 Estrutura do projeto

```text
📂 Aula-1-Edge-Computing
│
├── README.md
└── codigo.ino
```

---

## 📚 Conceitos abordados

- Edge Computing
- Arduino Uno
- Sensor TMP36
- Leitura analógica (`analogRead`)
- Conversão de tensão para temperatura
- Estruturas condicionais (`if/else`)
- Saídas digitais (`digitalWrite`)
- Monitor Serial

---

## ✅ Resultado esperado

O sistema monitora continuamente a temperatura ambiente. Quando a temperatura ultrapassa **30°C**, o LED vermelho é acionado automaticamente, enquanto o valor da temperatura continua sendo exibido no Monitor Serial em tempo real.

---

## 👨‍💻 Autor

**Guilherme Blanco Ribeiro**

Projeto desenvolvido para a disciplina de **Edge Computing**.

# FrioLog · Nó de Borda Inteligente

Protótipo (prova de conceito) de um **nó de Edge Computing** para monitoramento de uma câmara-piloto climatizada da FrioLog Soluções em Logística. O sistema percebe o ambiente, decide localmente no ESP32 e aciona os atuadores de forma **autônoma, sem depender de internet**.

> Checkpoint 1 · FIAP · Graduação em Ciência da Computação · Edge Computing

![Circuito simulado no Wokwi](./Screenshot%202026-09-17%20203145.png)

## Visão geral

| | |
|---|---|
| **Placa** | ESP32 DevKit C |
| **Ambiente de desenvolvimento** | VS Code + PlatformIO |
| **Simulação** | Wokwi (extensão Wokwi para VS Code) |
| **Sensores** | DHT22 (temperatura e umidade) · Sensor de gás MQ (saída digital) |
| **Atuadores** | LED RGB (ânodo comum) · Buzzer |
| **Estados** | `NORMAL` · `ALERTA` · `CRITICO` |

## Por que esses sensores e atuadores

- **DHT22** – lê temperatura e umidade da câmara, as duas grandezas que causaram perdas no trimestre anterior por oscilarem sem serem percebidas a tempo.
- **Sensor de gás (MQ, saída digital)** – detecta vazamentos/gases anômalos que poderiam indicar deterioração de produtos ou risco de contaminação, agravando o cenário além da temperatura/umidade.
- **LED RGB** – sinalização visual imediata do estado do sistema (verde = normal, amarelo = alerta, vermelho = crítico), útil para quem está fisicamente na câmara.
- **Buzzer** – alarme sonoro nos estados de alerta/crítico, para chamar atenção mesmo sem olhar para o painel.

## Pinagem (ESP32)

| Componente | Pino | Tipo |
|---|---|---|
| DHT22 – SDA | GPIO 15 | Digital (protocolo 1-wire) |
| Sensor de gás – DOUT | GPIO 16 | Digital |
| Sensor de gás – VCC | GPIO 32 (nível alto) | Alimentação via GPIO |
| Buzzer | GPIO 33 | Digital/PWM (`tone`) |
| LED RGB – R | GPIO 25 | Digital (ativo em `LOW`, ânodo comum) |
| LED RGB – G | GPIO 26 | Digital (ativo em `LOW`, ânodo comum) |
| LED RGB – B | GPIO 27 | Digital (ativo em `LOW`, ânodo comum) |

O LED RGB é de **ânodo comum**, alimentado pelo 3V3 através de um resistor de 1 kΩ — por isso a lógica de acionamento é invertida (`LOW` acende, `HIGH` apaga).

## Lógica de decisão local

Toda a decisão acontece dentro do ESP32, na função `decidirEstado()`, sem nenhuma chamada de rede. As regras são avaliadas em ordem de prioridade — a primeira verdadeira define o estado:

1. **Gás detectado** → `CRITICO` (prioridade máxima, independente das demais leituras).
2. **Regra combinada**: temperatura fora da faixa crítica **e** umidade acima do limite ao mesmo tempo → `CRITICO`.
3. Temperatura ou umidade fora da faixa ideal (sem caracterizar o cenário acima) → `ALERTA`.
4. Nenhuma das condições anteriores → `NORMAL`.

| Estado | LED | Buzzer |
|---|---|---|
| `NORMAL` | Verde | Desligado |
| `ALERTA` | Amarelo | Bipe de aviso (1 kHz) |
| `CRITICO` | Vermelho | Alarme agudo (2,5 kHz) |

Toda mudança de estado é registrada no Serial Monitor junto com as leituras dos sensores.

## Estrutura do projeto

```
friolog-node/
├── src/
│   └── main.cpp        # lógica completa do nó (sensores, decisão, atuadores)
├── platformio.ini       # dependências e configuração da placa
└── diagram.json         # circuito simulado no Wokwi
```

## Como rodar

1. Abra a pasta `friolog-node` no VS Code com a extensão **PlatformIO IDE** instalada.
2. Rode **PlatformIO: Build** (ícone ✓ na barra inferior) para baixar as libs e compilar.
3. Instale a extensão **Wokwi for VS Code** e inicie a simulação (`Wokwi: Start Simulator`) apontando para o `diagram.json` deste projeto.
4. Acompanhe as leituras e as mudanças de estado pelo **Serial Monitor**.

## Autores

- Leonardo Kenji Kubo Barboza
- *(adicionar segundo integrante da dupla)*

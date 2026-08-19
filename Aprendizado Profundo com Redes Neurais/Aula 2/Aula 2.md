# 🧠 Fundamentos Matemáticos para Redes Neurais

Anotações e códigos práticos sobre a matemática mínima necessária para entender o treinamento de Redes Neurais e Aprendizado Profundo (Deep Learning).

---

## 📌 Visão Geral & Objetivos

* **Objetivo:** Compreender a intuição matemática por trás do PyTorch e TensorFlow sem se perder em provas formais.
* **Conceito Chave:** Uma rede neural aprende ajustando números (pesos e bias) a partir do erro calculado.

---

## 📐 1. Representação de Dados: Tensores

Em Deep Learning, quase toda estrutura de dados é representada como um **tensor**.

| Tipo | Descrição | Exemplo de Shape | Exemplo Prático |
| :--- | :--- | :--- | :--- |
| **Escalar** | Único número | `()` | Uma idade (`32`) |
| **Vetor** | Vetor 1D | `(3,)` | `[altura, peso, idade]`[cite: 1] |
| **Matriz** | Tabela 2D | `(4, 3)` | Matriz de 4 linhas e 3 colunas[cite: 1] |
| **Tensor 3D** | Matriz com profundidade | `(8, 8, 3)` | Imagem RGB (Altura x Largura x Canais)[cite: 1] |
| **Tensor 4D** | Lote (batch) de tensores 3D | `(32, 224, 224, 3)` | Lote de 32 imagens RGB de 224x224 pixels[cite: 1] |

> 💡 **Dica de Debug:** A verificação do `.shape` dos tensores é o primeiro passo para resolver erros em frameworks de IA[cite: 1]!

---

## ⚙️ 2. Operações Fundamentais & O Neurônio Artificial

### O Produto Escalar e Operações Matriciais
Um neurônio calcula uma combinação ponderada das suas entradas através do **produto escalar** e soma com um desvio (*bias*)[cite: 1]:

$$z = x \cdot w + b$$
[cite: 1]

Em nível de camada (multiplicação de matrizes)[cite: 1]:

$$Z = X \cdot W + b$$
[cite: 1]

### Funções de Ativação (Não Linearidade)
Sem funções de ativação, múltiplas camadas neurais seriam apenas uma grande equação linear[cite: 1]. Elas permitem modelar padrões complexos[cite: 1]:

* **ReLU:** Mantém valores positivos e zera os negativos ($f(x) = \max(0, x)$). Usada em camadas ocultas[cite: 1].
* **Sigmoid:** Mapeia valores para o intervalo $(0, 1)$. Usada na saída de problemas binários[cite: 1].
* **Softmax:** Transforma *scores* (logits) em uma distribuição de probabilidades que somam 1. Usada para classificação multiclasse[cite: 1].

---

## 🎯 3. Perda (Loss), Gradiente e Otimização

### Métrica de Erro (Loss Functions)
* **MSE (Mean Squared Error):** Usado para problemas de **regressão**[cite: 1].
  $$MSE = \frac{1}{N} \sum (y_{real} - y_{pred})^2$$
[cite: 1]
* **Cross-Entropy / BCE:** Usada para problemas de **classificação**. Penaliza fortemente previsões confiantes e erradas[cite: 1].

### O Ciclo de Treinamento
1. **Forward:** O modelo processa as entradas e gera uma predição[cite: 1].
2. **Loss:** Calcula-se o quão distante a predição está da resposta real[cite: 1].
3. **Backward:** A derivada (gradiente) calcula como a variação de cada peso altera a perda[cite: 1].
4. **Update:** Atualizam-se os pesos na direção oposta ao gradiente[cite: 1]:
   $$w_{novo} = w_{atual} - (\text{learning\_rate} \times \text{gradiente})$$
[cite: 1]
5. **Repeat:** O ciclo se repete por várias épocas[cite: 1].

---

## 💻 4. Laboratório Prático (NumPy)

### 📍 Script 1: Criando Tensores e Checando Shapes
```python
import numpy as np

escalar = np.array(7.5)[cite: 1]
vetor = np.array([1.0, 2.0, 3.0])[cite: 1]
matriz = np.array([[1, 2, 3], [4, 5, 6]])[cite: 1]
tensor = np.zeros((2, 4, 4, 3)) # Batch de 2 imagens 4x4 RGB[cite: 1]

print('Escalar:', escalar.shape)[cite: 1]
print('Vetor:', vetor.shape)[cite: 1]
print('Matriz:', matriz.shape)[cite: 1]
print('Tensor:', tensor.shape)[cite: 1]

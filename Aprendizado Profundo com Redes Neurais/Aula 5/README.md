# Classificação com Perceptron Multicamadas (MLP) em Dados Bancários

Este repositório contém um pipeline em Python para pré-processamento de dados e treinamento de um modelo de **Rede Neural Perceptron Multicamadas (MLP)** utilizando **TensorFlow/Keras** e **scikit-learn**. O objetivo é realizar a classificação binária a partir de um conjunto de dados bancários (Bank Marketing).

---

## 📌 Fluxo do Projeto

1. **Carregamento dos Dados**: Importação dos conjuntos de dados de treino (`bank_train.csv`), validação (`bank_validation.csv`) e teste (`bank_test.csv`).
2. **Separação de Variáveis**: Divisão dos atributos de entrada (*features*) e da variável alvo (*target* `y`).
3. **Pré-processamento**:
   - **Variáveis Numéricas**: Padronizadas via `StandardScaler`.
   - **Variáveis Categóricas**: Codificadas via `OneHotEncoder`.
   - Utilização do `ColumnTransformer` para evitar vazamento de dados (*data leakage*), ajustando (`fit`) apenas com os dados de treino.
4. **Modelagem (Rede Neural MLP)**:
   - **Entrada**: 50 atributos após o pré-processamento.
   - **Camada Oculta 1**: 32 neurônios (Ativação `ReLU`).
   - **Camada Oculta 2**: 16 neurônios (Ativação `ReLU`).
   - **Camada de Saída**: 1 neurônio (Ativação `Sigmoid` para classificação binária).
   - **Otimizador**: `Adam` (taxa de aprendizado = 0.001).
   - **Função de Perda**: `binary_crossentropy`.
5. **Avaliação**: Cálculo de métricas de desempenho (Acurácia, Precisão, Recall, F1-Score e Matriz de Confusão) nos conjuntos de validação e teste.

---

## 🛠️ Tecnologias e Bibliotecas Utilizadas

- **Python 3**
- **Pandas** - Manipulação e análise de dados
- **NumPy** - Operações numéricas
- **Scikit-Learn** - Pré-processamento e métricas de avaliação
- **TensorFlow / Keras** - Construção e treinamento da rede neural

---

## 📊 Estrutura dos Dados

### Variáveis Numéricas (6)
- `age`, `balance`, `day_of_week`, `campaign`, `pdays`, `previous`

### Variáveis Categóricas (9)
- `job`, `marital`, `education`, `default`, `housing`, `loan`, `contact`, `month`, `poutcome`

---

## 🚀 Como Executar

1. Certifique-se de ter os arquivos de dados na raiz do projeto:
   - `bank_train.csv`
   - `bank_validation.csv`
   - `bank_test.csv`

2. Instale as dependências necessárias:
   ```bash
   pip install pandas numpy scikit-learn tensorflow
   ```

3. Execute o notebook Jupytec/Colab ou converta o código para um script Python:
   ```bash
   python main.py
   ```

---

## 📈 Resultados e Métricas

O modelo gera relatórios completos de classificação (`classification_report`) e matrizes de confusão (`confusion_matrix`) para avaliar a capacidade preditiva da rede tanto na etapa de validação quanto no teste final.